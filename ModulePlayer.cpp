#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// idle animation 
	idle.frames.push_back({ 31,	25,	59,	93});

	//Walk
	walk.frames.push_back({ 117, 26, 46, 93});
	walk.frames.push_back({ 187, 26, 61, 93});
	walk.frames.push_back({ 270, 28, 61, 94});
	walk.frames.push_back({ 358, 30, 48, 94});

	walk.frames.push_back({ 436, 27, 30, 95});
	walk.frames.push_back({ 504, 28, 29, 94});
	walk.frames.push_back({ 563, 27, 46, 93});
	walk.frames.push_back({ 634, 28, 61, 93});

	walk.frames.push_back({ 721, 30, 60, 93});
	walk.frames.push_back({ 805, 31, 50, 93});
	walk.frames.push_back({ 883, 28, 30, 94});
	walk.frames.push_back({ 941, 28, 31, 92});

	//Simple Punch
	simplePunch.frames.push_back({ 29, 316, 63, 90});
	simplePunch.frames.push_back({ 127, 313, 83, 90});

	//Strong Punch
	strongPunch.frames.push_back({ 237, 321, 67, 81});
	strongPunch.frames.push_back({ 333, 324, 110, 78});

	//Sky Hook
	skyHook.frames.push_back({ 465, 320, 67, 81});
	skyHook.frames.push_back({ 559, 334, 78, 70});
	skyHook.frames.push_back({ 668, 325, 82, 78});
	skyHook.frames.push_back({ 774, 315, 79, 91});
	skyHook.frames.push_back({ 874, 293, 55, 111});
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Sprites/Personajes/FF_Cody.png");
	
	destroyed = false;
	position.x = 100;
	position.y = 100;

	frames = 1;

	// Collider
	/*
	SDL_Rect texture;
	texture.x = position.x;
	texture.y = position.y;
	texture.w = 30;
	texture.h = 10;
	collider = App->collision->AddCollider(texture);*/
	//collider = new Collider({ position.x, position.y, 30, 10 });
	//App->collision->AddCollider(collider->rect);
	
	//collider = App->collision->AddCollider({ position.x, position.y, 30, 10 });

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	/*int speed = 1;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
		collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
		collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
		collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// TODO 6: Shoot a laser using the particle system
		App->particles->AddParticle(App->particles->laser, position.x, position.y);
	}


	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		// TODO 6: Shoot a laser using the particle system
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		//Die();
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		current_animation = &idle;

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));*/
	current_animation = &skyHook;
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 0.1f);
	/*if (frames/100 == 1) {
		frames = 0;
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 0.1f);
	}
	else {
		frames++;
	}*/

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

/*bool ModulePlayer::Die()
{
	this->destroyed = true;
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	return true;
}*/