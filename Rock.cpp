#include "Rock.h"
#include "Tank.h"

Rock::Rock(Level* _level, const RectangleShapeData& _data) : MeshActor(_level, _data, "Rock")
{
}

Rock::Rock(const Rock& _other) : MeshActor(_other)
{

}

void Rock::BeginPlay()
{
	Super::BeginPlay();
}

void Rock::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Rock::CollisionEnter(const CollisionData& _data)
{
}

void Rock::CollisionUpdate(const CollisionData& _data)
{
}

void Rock::CollisionExit(const CollisionData& _data)
{
}
