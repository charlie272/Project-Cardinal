#include "Client.h"
#include "../Utils/Utils.h"
#include "../Utils/Renderer.h"

Client::Client(std::string name) {
	this->name = name;
	Utils::DebugLogF("Client Instance has been Initialized", std::string(name + "/Logs/Output.txt").c_str(), true);
}

/* Hook Includes */

#include "../Memory/Hooks/Hook.h"

#include "../Memory/Hooks/Hook/ClientInstance.h"
#include "../Memory/Hooks/Hook/GameMode.h"
#include "../Memory/Hooks/Hook/Actor.h"

#include "../Memory/Hooks/Hook/KeyItem.h"

#include "../Memory/Hooks/Hook/SwapChain.h"

#include "../Memory/Hooks/Hook/LoopbackPacketSender.h"

/* Module Includes */

/* Combat */
#include "Modules/Module/Killaura.h"
#include "Modules/Module/Hitbox.h"
#include "Modules/Module/BoostHit.h"
#include "Modules/Module/EntityAura.h"
/* Movement */
#include "Modules/Module/AirJump.h"
#include "Modules/Module/Step.h"
#include "Modules/Module/Jetpack.h"
/* Player */
#include "Modules/Module/Coordinates.h"
#include "Modules/Module/Velocity.h"
/* Visuals */
#include "Modules/Module/Zoom.h"
#include "Modules/Module/TabGui.h"
#include "Modules/Module/ModuleList.h"
/* World */
#include "Modules/Module/Instabreak.h"
#include "Modules/Module/Nuker.h"
#include "Modules/Module/Scaffold.h"
/* Exploits */
//
/* Other */
#include "Modules/Module/TestMod.h"
#include "Modules/Module/Commands.h"
#include "Modules/Module/PacketLogger.h"

/* Commands */
#include "Commands/Command/Teleport.h"

/* */

void Client::init() {

	Utils::DebugLogF("Initializing Client...");

	Hook::initMH(this); /* Initialize MinHook */

	this->isRunning = true;

	/* Initialize SwapChain (Dx11) Hook */

	SwapChain_Hook* swapChain_Hook = new SwapChain_Hook();
	swapChain_Hook->init();

	/* Initialize Client Instance Hook */
	CInstance_Hook* cI_Hook = new CInstance_Hook();
	cI_Hook->init();

	/* Initialize GameMode tick */
	GameMode_Hook* gm_Hook = new GameMode_Hook();
	gm_Hook->init();

	/* Initialize Actor Hooks */
	Actor_Hook* actor_Hook = new Actor_Hook();
	actor_Hook->init();

	/* Initialize AVKeyItem Hook */
	KeyItem_Hook* key_Hook = new KeyItem_Hook();
	key_Hook->init();

	/* Initialize LoopbackPacketSender Hook */
	Loopback_Hook* loop_Hook = new Loopback_Hook();
	loop_Hook->init();

	/* Initialize Categories */

	Category* combat = new Category(this, "Combat");
	Category* movement = new Category(this, "Movement");
	Category* player = new Category(this, "Player");
	Category* visuals = new Category(this, "Visuals");
	Category* world = new Category(this, "World");
	Category* exploits = new Category(this, "Exploits");
	Category* other = new Category(this, "Other");

	/* Initialize Modules */

	/* Combat */
	new Killaura(this, combat);
	new Hitbox(this, combat);
	new BoostHit(this, combat);
	new EntityAura(this, combat);
	/* Movement */
	new AirJump(this, movement);
	new Step(this, movement);
	new Jetpack(this, movement);
	/* Player */
	new Coords(this, player);
	new Velocity(this, player);
	/* Visuals */
	new Zoom(this, visuals);
	new TabGui(this, visuals);
	new ModuleList(this, visuals);
	/* World */
	new Instabreak(this, world);
	new Nuker(this, world);
	new Scaffold(this, world);
	/* Exploits */
	//
	/* Other */
	new TestMod(this, other);
	new Commands(this, other);
	new PacketLogger(this, other);

	/* Teleport Commands */

	this->commands.push_back(new TeleportCmd());

	while (isRunning) {
		for (auto C : this->categories) {
			for (auto M : C->modules) M->baseTick();
		}
	}
}