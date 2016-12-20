#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"


ModuleSceneLevel::ModuleSceneLevel(bool start_enabled) : Module(start_enabled)
{
	// Set up the level
	level.x = 0;
	level.w = 1000;
	level.y = 395;
	level.h = 195;

	background.x = 0;
	background.w = 700;
	background.y = 195;
	background.h = 0;
	
}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading level scene");
	
	graphics = App->textures->Load("Sprites/Niveles/Level1.png");


	App->audio->PlayMusic("Audio/Final Fight Stage 1.mp3", 1.0f);
	
	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading level scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	// Paint the level
	App->renderer->Blit(graphics, 0, 0, &level);

	return UPDATE_CONTINUE;
}