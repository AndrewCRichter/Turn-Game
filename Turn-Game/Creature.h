#pragma once
#include "RenderableEntity.h"
class Creature :
	public RenderableEntity
{
public:
	Creature();
	~Creature();
	void Creature::processPhysics(float dt);
};

