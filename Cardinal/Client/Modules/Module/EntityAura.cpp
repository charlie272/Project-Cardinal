#include "EntityAura.h"

void attackEnt1(GameMode* GM, Actor* e) {
	GM->attack(e);
	GM->player->swing();
}

void EntityAura::onGmTick(GameMode* GM) {
	auto level = player->getLevel();
	if (level == nullptr)
		return;

	auto ents = level->getEntities();
	auto pos = *player->getPos();

	if (multi) {
		for (auto e : ents) {
			//if (e == player)
				//continue;

			auto dis = e->getPos()->distance(pos);

			if (dis <= range) {
				if (player->canAttack(e, false) && e->isAlive()) attackEnt1(GM, e);
			}
		}
	}
	else {
		std::vector<float> distances = std::vector<float>();
		for (auto e : ents) {
			if (e == player)
				continue;

			auto dis = e->getPos()->distance(pos);

			if (dis <= range) distances.push_back(dis);
		}

		std::sort(distances.begin(), distances.end());

		if (distances.empty())
			return;

		for (auto e : ents) {
			auto dis = e->getPos()->distance(pos);

			if (dis == distances[0]) {
				if (player->canAttack(e, false) && e->isAlive()) attackEnt1(GM, e);
			}
		}
	}
}