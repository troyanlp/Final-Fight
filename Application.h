#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;

// Game modules ---
class ModulePlayer;
class ModuleSceneIntro;
class ModuleSceneSelection;
class ModuleSceneLevel1;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;

	// Game modules ---
	ModulePlayer* player;
	ModuleSceneIntro* scene_intro;
	ModuleSceneSelection* scene_selection;
	ModuleSceneLevel1* scene_level1;

private:

	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__