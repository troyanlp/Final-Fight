#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSelection.h"

ModuleSceneSelection::ModuleSceneSelection(bool active) : Module(active)
{}

ModuleSceneSelection::~ModuleSceneSelection()
{}

// Load assets
bool ModuleSceneSelection::Start()
{
	LOG("Loading selection");

	cody = App->textures->Load("Sprites/selectionCody.png");
	haggar = App->textures->Load("Sprites/selectionHaggar.png");

	//App->audio->PlayMusic("rtype/intro.ogg", 1.0f);
	//if(fx == 0)
	//	fx = App->audio->LoadFx("rtype/starting.wav");

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneSelection::CleanUp()
{
	LOG("Unloading selection scene");

	App->textures->Unload(cody);
	App->textures->Unload(haggar);

	return true;
}

// Update: draw background
update_status ModuleSceneSelection::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (character) character = false;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (!character) character = true;
	}

	if (!character) {
		App->renderer->Blit(cody, 0, 0, NULL);
	}
	else {
		App->renderer->Blit(haggar, 0, 0, NULL);
	}
	

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && App->fade->isFading() == false && !character)
	{
		App->fade->FadeToBlack((Module*)App->scene_level1, this);
		App->audio->PlayFx(fx);
	}

	return UPDATE_CONTINUE;
}