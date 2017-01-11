#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"

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
	
	walk.speed = 0.2f;

	//Simple Punch
	simplePunch.frames.push_back({ 29, 316, 63, 90});
	simplePunch.frames.push_back({ 127, 313, 83, 90});

	simplePunch.speed = 0.2f;

	//Strong Punch
	strongPunch.frames.push_back({ 237, 321, 67, 81});
	strongPunch.frames.push_back({ 333, 324, 110, 78});

	strongPunch.speed = 0.15f;

	//Sky Hook
	skyHook.frames.push_back({ 465, 320, 67, 81});
	skyHook.frames.push_back({ 559, 334, 78, 70});
	skyHook.frames.push_back({ 668, 325, 82, 78});
	skyHook.frames.push_back({ 774, 315, 79, 91});
	skyHook.frames.push_back({ 874, 293, 55, 111});

	skyHook.speed = 0.2f;

	//Jump
	jump.frames.push_back({ 32, 186, 53, 82});
	jump.frames.push_back({ 125, 156, 41, 107});
	jump.frames.push_back({ 199, 156, 54, 76});
	jump.frames.push_back({ 283, 159, 69, 85});
	jump.frames.push_back({ 32, 186, 53, 82 });

	jump.speed = 0.15f;

	//Jump Forward
	jumpForward.frames.push_back({ 32, 186, 53, 82});
	jumpForward.frames.push_back({ 125, 156, 41, 107});
	jumpForward.frames.push_back({ 199, 156, 54, 76});
	jumpForward.frames.push_back({ 283, 159, 69, 85});
	jumpForward.frames.push_back({ 377, 171, 81, 52});
	jumpForward.frames.push_back({ 488, 161, 64, 60});
	jumpForward.frames.push_back({ 582, 167, 81, 52});
	jumpForward.frames.push_back({ 697, 167, 64, 60});
	jumpForward.frames.push_back({ 32, 186, 53, 82});

	jumpForward.speed = 0.15f;

	//Receive hit
	receiveHit.frames.push_back({ 26, 712, 54, 84});
	receiveHit.frames.push_back({ 31, 25, 59, 93});

	receiveHit.speed = 0.2f;

	//Fall
	fall.frames.push_back({ 112, 700, 60, 96});
	fall.frames.push_back({ 214, 704, 94, 52});
	fall.frames.push_back({ 337, 753, 116, 36});

	fall.speed = 0.2f;

	//Try to get up
	tryGetUp.frames.push_back({ 337,753,116,36});
	tryGetUp.frames.push_back({ 481, 759, 93, 34});

	tryGetUp.speed = 0.2f;

	//Get up
	getUp.frames.push_back({ 337,753,116,36 });
	getUp.frames.push_back({ 481, 759, 93, 34 });
	getUp.frames.push_back({ 602, 739, 53, 59});
	getUp.frames.push_back({ 31, 25, 59, 93});

	getUp.speed = 0.2f;
	
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
	float speedX = 0.85f;
	float speedY = 0.5f;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		facing = false;
		position.x -= speedX;
		//if(App->renderer->camera.x < LEVEL1_CAM_MIN) App->renderer->camera.x += 15;
		current_animation = &walk;
		//collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		facing = true;
		position.x += speedX;
		if (App->renderer->camera.x > LEVEL1_CAM_MAX) App->renderer->camera.x -= 15;
		current_animation = &walk;
		//collider->rect = { position.x, position.y, 30, 10 };
	}

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		position.y -= speedY;
		current_animation = &walk;
		/*if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		collider->rect = { position.x, position.y, 30, 10 };*/
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		position.y += speedY;
		current_animation = &walk;
		/*if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
		collider->rect = { position.x, position.y, 30, 10 };*/
	}

	if(App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		current_animation = &jump;
	}

	/*if (keyDown(KEY_SPACE)) {
		jumping = true;
		oldY = yPos;
	}
	if (jumping) {
		jumpSum += jumpSpeed;    tracks the amount of jumping
			if (jumpSum >= jumpHeight)
				jumpSpeed = -jumpSpeed;
		if (jumpSum <= 0) {
			jumpSum = 0;    // Reset for next time
			jumpSpeed = -jumpSpeed;    // Or: jumpSpeed = abs(jumpSpeed);
			yPos = oldY - jumpSpeed;   // In case jumpSum was > 0 and is now < 0
			jumping = false;
		}
		yPos += jumpSpeed;
	}*/


	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		current_animation = &simplePunch;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_Z) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_X) == KEY_IDLE)
		current_animation = &idle;

	
	// Draw everything --------------------------------------
	//SDL_RenderSetScale(App->renderer->renderer, 0.1f, 0.1f);
	//SDL_RenderCopyEx(App->renderer->renderer, graphics, &(current_animation->GetCurrentFrame()), &(current_animation->GetCurrentFrame()), 0, NULL, SDL_FLIP_HORIZONTAL);
	if (destroyed == false) 
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), !facing, 0.2f);

	return UPDATE_CONTINUE;
}

/*bool ModulePlayer::Die()
{
	this->destroyed = true;
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	return true;
}*/