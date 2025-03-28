#pragma once
#include "CoreMinimal.h"
#include "MeshActor.h"

class LevelElement 
{
	int chance;
	vector<LevelElement*> variants;
	MeshActor* prefab;

public:
	FORCEINLINE float GetChance() const
	{
		return chance;
	}
	FORCEINLINE MeshActor GetSubclass() const
	{
		return *prefab;
	}
	FORCEINLINE MeshActor* GetPrefab() const
	{
		return prefab;
	}



public:
#pragma region Constructors
	LevelElement(MeshActor* _actor, const int _chance);
	LevelElement(MeshActor* _actor, const int _chance, const vector<LevelElement*>& _variants);
	/// <summary>
	/// Constructeur pour créer un LevelElement qui servira de sol
	/// </summary>
	LevelElement(MeshActor* _actor, const vector<LevelElement*>& _variants = vector<LevelElement*>());
	LevelElement() = default;
	~LevelElement();
#pragma endregion

public:
	FORCEINLINE bool HasVariants() const
	{
		return variants.size() > 0;
	}
	LevelElement* GetRandomVariant(); // Pas de const, ça bloque le return this

};

class MapGenerator
{
	Vector2f size;
	vector<MeshActor*> generatedElements;
	vector<LevelElement*> elementsList;
	Level* level;
	u_int spaceBetweenElements;
	LevelElement* ground;
	Vector2f groundTileSize;

public:
	FORCEINLINE void SetGround(LevelElement* _ground, const Vector2f& _groundTileSize)
	{
		ground = _ground;
		groundTileSize = _groundTileSize;
	}

public:
#pragma region Constructors
	MapGenerator(Level* _level, const Vector2f& _size, const u_int& _spaceBetweenElements);
	MapGenerator(Level* _level, const Vector2f& _size, const vector<LevelElement*>& _elementsList, const u_int& _spaceBetweenElements);
	~MapGenerator();
#pragma endregion

public:
	FORCEINLINE void AddGenerableElement(LevelElement* _element)
	{
		elementsList.push_back(_element);
	}

public:
	void GenerateGround();

	map<Vector2f, MeshActor*> GenerateMap();

	bool IsElementOverlap(const Vector2f& _pos) const;

	bool GenerateRandomElement(const Vector2f& _pos);


	static LevelElement* GetRandomElement(const vector<LevelElement*>& _vector)
	{
		if (_vector.empty()) return nullptr;

		int _spawnChance = 60; // % de chance qu'un élément spawn

		if (GetRandomNumberInRange(0, 100) > _spawnChance)
			return nullptr; // Aucun élément ne spawn

		// Créer une table cumulative pour les chances
		vector<int> _cumulativeChances;
		int _totalChance = 0;

		for (const LevelElement* _element : _vector)
		{
			_totalChance += _element->GetChance();
			_cumulativeChances.push_back(_totalChance);
		}

		// Tirage aléatoire en fonction de la table cumulative
		const int _random = GetRandomNumberInRange(0, _totalChance - 1);
		const u_int _vectorSize = CAST(u_int, _vector.size());
		for (u_int _index = 0; _index < _vectorSize; ++_index)
		{
			if (_random < _cumulativeChances[_index])
			{
				LevelElement* _element = _vector[_index];
				return _element->HasVariants() ? _element->GetRandomVariant() : _element;
			}
		}
		return nullptr;
	}

};

