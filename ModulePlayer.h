#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool Die();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation walk;
	Animation simplePunch;
	Animation strongPunch;
	Animation skyHook;
	Animation jump;
	Animation jumpForward;
	fPoint position;
	bool destroyed = false;
	Collider* collider;
	int frames;
};

#endif