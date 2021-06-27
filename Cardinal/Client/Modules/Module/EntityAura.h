#pragma once
#include "../Module.h"

class EntityAura : public Module {
public:
	EntityAura(Client* c, Category* o) : Module(c, o, "EntityAura") {};
	void onGmTick(GameMode*);

	float range = 8.f;
	bool multi = true;
};
