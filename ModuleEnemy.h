#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(bool active = true);
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool Die();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	bool destroyed = false;
	iPoint position = { 0,0,0 };
	Collider* collider;
};


#endif