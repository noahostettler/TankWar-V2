#include "MapGenerator.h"
#include "Utilities.h"
#include "LevelManager.h"

LevelElement::LevelElement(MeshActor* _actor, const int _chance)
{
	prefab = _actor;
	chance = _chance;
	variants = vector<LevelElement*>();
}

LevelElement::LevelElement(MeshActor* _actor, const int _chance, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = _chance;
	variants = _variants;
}

LevelElement::LevelElement(MeshActor* _actor, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = 0;
	variants = _variants;
}

LevelElement::~LevelElement()
{
	for (LevelElement* _variant : variants)
	{
		delete _variant;
	}
	delete prefab;
}

LevelElement* LevelElement::GetRandomVariant()
{
	LevelElement* _element = MapGenerator::GetRandomElement(variants);
	return _element ? _element : this;
}



MapGenerator::MapGenerator(Level* _level, const Vector2f& _size, const u_int& _spaceBetweenElements)
{
	level = _level;
	size = _size;
	elementsList = vector<LevelElement*>();
	spaceBetweenElements = _spaceBetweenElements;
	ground = nullptr;
}

MapGenerator::MapGenerator(Level* _level, const Vector2f& _size, const vector<LevelElement*>& _elementsList, const u_int& _spaceBetweenElements)
{
	level = _level;
	size = _size;
	elementsList = _elementsList;
	spaceBetweenElements = _spaceBetweenElements;
	ground = nullptr;
}

MapGenerator::~MapGenerator()
{
	for (LevelElement* _element : elementsList)
	{
		delete _element;
	}
	delete ground;
}

void MapGenerator::GenerateGround()
{
	if (!ground) return;

	Level* _level = M_LEVEL.GetCurrentLevel();

	for (u_int _y = 0; _y < size.y; _y += groundTileSize.y)
	{
		for (u_int _x = 0; _x < size.x; _x += groundTileSize.x)
		{
			LevelElement* _groundElement = ground;
			if (_groundElement->HasVariants())
			{
				_groundElement = ground->GetRandomVariant();
			}
	
			MeshActor* _ground = _level->SpawnActor<MeshActor>
			(
				*ground->GetPrefab()->GetMesh()->GetShape()->GetData().data.rectangleData
			);

			_ground->SetPosition(Vector2f((float)_x, (float)_y));
			_ground->GetMesh()->SetOriginAtMiddle();
		}
	}

}

map<Vector2f, MeshActor*> MapGenerator::GenerateMap()
{
	map<Vector2f, MeshActor*> _map;

	const float _offset = 100.0f;

	//GenerateGround();

	for (u_int _x = 0; _x < size.x; _x += spaceBetweenElements)
	{
		if (_x + spaceBetweenElements >= size.x) continue;

		for (u_int _y = 0; _y < size.y; _y += spaceBetweenElements)
		{
			if (_y + spaceBetweenElements >= size.y) continue;

			const float _offsetX = GetRandomNumberInRange<float>(-_offset, _offset);
			const float _offsetY = GetRandomNumberInRange<float>(-_offset, _offset);
			const Vector2f& _position = Vector2f((float)_x + _offsetX, (float)_y + _offsetY);
			GenerateRandomElement(_position);
		}
	}


	return _map;

}

bool MapGenerator::IsElementOverlap(const Vector2f& _pos) const
{
	for (MeshActor* _actor : generatedElements)
	{
		if (_actor->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds().contains(_pos)) return true;
	}

	return false;
}

bool MapGenerator::GenerateRandomElement(const Vector2f& _pos)
{
	if (IsElementOverlap(_pos)) return false;

	LevelElement* _element = GetRandomElement(elementsList);
	if (!_element) return false;

	MeshActor* _actor = M_LEVEL.GetCurrentLevel()->SpawnActor<MeshActor>
		(
			*_element->GetPrefab()->GetMesh()->GetShape()->GetData().data.rectangleData
		);

	_actor->SetPosition(_pos);
	//_actor->SetOriginAtMiddle();
	generatedElements.push_back(_actor);

	return true;
}
