#include "DebugLevel.h"
#include "Tank.h"
#include "MapGenerator.h"
#include "Rock.h"
#include "Tree.h"
#include "CameraManager.h"

DebugLevel::DebugLevel(const string& _name) : Level(_name)
{
	hud = nullptr;
	camera = new CameraActor(this, Vector2f(1920, 1080), Vector2f(4000, 2200), "TestCamera");
	cameraManager = new Camera::CameraManager();
}

void DebugLevel::InitLevel()
{
	Super::InitLevel();
	hud = GetGameMode()->GetHUD();

	cameraManager->Register(camera->GetCamera());
	cameraManager->SetCurrent(camera->GetCamera());
	cameraManager->SetRenderView(camera->GetCamera(), GetRenderWindow());
	camera->SetPosition(Vector2f(50000, 50000));
	//SpawnActor<Tank>();
	//hud->AddToViewport(gameHUD.canvas);

	vector<LevelElement*> _rockVariants;
	const Vector2f& _rockSize = Vector2f(28.0f, 28.0f);
	_rockVariants.push_back(new LevelElement(new Rock(this, RectangleShapeData( _rockSize, "Object/Rock_1")), 1));
	_rockVariants.push_back(new LevelElement(new Rock(this, RectangleShapeData(_rockSize, "Object/Rock_2")), 1));
	_rockVariants.push_back(new LevelElement(new Rock(this, RectangleShapeData(_rockSize, "Object/Rock_3")), 1));
	LevelElement* _rock = new LevelElement(new Rock(this, RectangleShapeData(_rockSize, "Object/Rock_4")), 3, _rockVariants);

	vector<LevelElement*> _treeVariant;
	_treeVariant.push_back(new LevelElement(new Tree(this, RectangleShapeData(_rockSize, "Object/Tree_4")), 2));
	_treeVariant.push_back(new LevelElement(new Tree(this, RectangleShapeData(_rockSize, "Object/Tree_3")), 2));
	_treeVariant.push_back(new LevelElement(new Tree(this, RectangleShapeData(_rockSize, "Object/Tree_2")), 2));
	LevelElement* _tree = new LevelElement(new Tree(this, RectangleShapeData(_rockSize, "Object/Tree_1")), 10, _treeVariant);

	MapGenerator* _map = new MapGenerator(this, Vector2f(3840, 2160), 100);
	_map->AddGenerableElement(_rock);
	_map->AddGenerableElement(_tree);
	_map->GenerateMap();

	

}
