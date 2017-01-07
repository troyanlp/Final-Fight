#ifndef __MODULESCENELEVEL1_H__
#define __MODULESCENELEVEL1_H__

#include "Module.h"

struct SDL_Texture;


class ModuleSceneLevel1 : public Module
{
public:
	ModuleSceneLevel1(bool active = true);
	~ModuleSceneLevel1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect level;
	SDL_Rect city;
};

#endif // __MODULESCENELEVEL1_H__