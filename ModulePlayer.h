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
	Animation receiveHit;
	Animation fall;
	Animation tryGetUp;
	Animation getUp;
	SDL_Rect currentFrame;
	iPoint position;
	float maxCamera;
	bool facing = true; 
	bool destroyed = false;
	Collider* collider;
	bool canAttack = true;
	float cooldown = 2.5f;
	float timerAttack = 0;
};

#define LEVEL1_CAM_MIN 0
#define LEVEL1_CAM_MAX -2940

#endif