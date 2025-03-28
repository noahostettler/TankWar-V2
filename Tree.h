#pragma once
#include "MeshActor.h"

class Tree : public MeshActor
{
public:
	Tree(Level* _level, const RectangleShapeData& _data);

	Tree(const Tree& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;


};