#pragma once
#include "MeshActor.h"


class Rock : public MeshActor
{
public:
	Rock(Level* _level, const RectangleShapeData& _data);
	Rock(const Rock& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;

};

