#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnemy.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleEnemy::ModuleEnemy(bool active) : Module(active)
{
	// idle animation 
	idle.frames.push_back({ 515, 176, 61, 80});
	idle.frames.push_back({ 605, 176, 51, 80});
	idle.frames.push_back({ 691, 176, 45, 80});

	idle.speed = 0.2f;

}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading enemy");

	graphics = App->textures->Load("Sprites/Enemigos/Dug.png");

	destroyed = false;
	position.x = 500;
	position.y = 150;

	//collider = new Collider({ position.x, position.y, 30, 10 });
	//free(collider);
	collider = App->collision->AddCollider({ position.x, position.y, 30, 10 }, 0, 0);

	current_animation = &idle;


	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemy");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
		
	// Draw everything --------------------------------------
	//SDL_RenderSetScale(App->renderer->renderer, 0.1f, 0.1f);
	//SDL_RenderCopyEx(App->renderer->renderer, graphics, &(current_animation->GetCurrentFrame()), &(current_animation->GetCurrentFrame()), 0, NULL, SDL_FLIP_HORIZONTAL);
	if (destroyed == false) {
		//LOG("NO ESTOY DESTRUIDO!");
		SDL_Rect f = current_animation->GetCurrentFrame();
		App->renderer->Blit(graphics, position.x, position.y, &(f), true);
		//collider->rect = { position.x, position.y, currentFrame.w, currentFrame.h };
		collider->rect.x = position.x;
		collider->rect.y = position.y;
		collider->rect.w = f.w;
		collider->rect.h = f.h;
	}



	return UPDATE_CONTINUE;
}