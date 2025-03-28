#include "Tree.h"

Tree::Tree(Level* _level, const RectangleShapeData& _data) : MeshActor(_level, _data, "Rock")
{
	SetZOrder(1);
}

Tree::Tree(const Tree& _other) : MeshActor(_other)
{
	SetZOrder(1);
}


void Tree::BeginPlay()
{
	Super::BeginPlay();
}

void Tree::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Tree::CollisionEnter(const CollisionData& _data)
{
}

void Tree::CollisionUpdate(const CollisionData& _data)
{
}

void Tree::CollisionExit(const CollisionData& _data)
{
}
