#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleSceneLevel1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel1::ModuleSceneLevel1(bool active) : Module(active)
{}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading Level 1 scene");
	
	graphics = App->textures->Load("Sprites/Niveles/FF_Stage1.png");

	level.x = 265;
	level.y = 4;
	level.h = 194;
	level.w = 991;

	city.x = 4;
	city.y = 4;
	city.h = 194;
	city.w = 255;

	App->player->Enable();
	//App->particles->Enable();
	App->collision->Enable();

	//App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);
	
	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}

	return true;
}

// UnLoad assets
bool ModuleSceneLevel1::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(graphics);
	App->player->Disable();
	//App->collision->Disable();
	//App->particles->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	//App->player->position.x += 1;
	//App->player->collider->SetPos(App->player->position.x, App->player->position.y);
	//App->renderer->camera.x -= 3;
	
	// Draw everything --------------------------------------
	for (int i = 0; i < 4; i++) App->renderer->Blit(graphics, 0 + (i * city.w)-1, 0, &city,false, 0.75f);
	App->renderer->Blit(graphics, 0, SCREEN_HEIGHT - level.h, &level,false, 0.75f);
	
	//App->renderer->Blit(graphics, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}