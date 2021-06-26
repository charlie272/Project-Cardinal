#pragma once
#include "../Module.h"

class Coords : public Module {
public:
	Coords(Client* c, Category* o) : Module(c, o, "Coords") {
		//this->isEnabled = true;
	};
	void onGmTick(GameMode*);
	void onRender(Renderer*);
	void updateAlpha();

	Vec3 cPos = Vec3();
	_RGBA textColor = _RGBA(255, 255, 255, 0);
	_RGBA backgroundColor = _RGBA(_RGBA(30, 70, 115, 0));
};