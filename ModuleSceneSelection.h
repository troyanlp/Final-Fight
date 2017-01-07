#ifndef __MODULESCENESELECTION_H__
#define __MODULESCENESELECTION_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneSelection : public Module
{
public:
	ModuleSceneSelection(bool active = true);
	~ModuleSceneSelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* cody = nullptr;
	SDL_Texture* haggar = nullptr;
	SDL_Rect* start = nullptr;
	uint fx = 0;
	bool character = false;
};

#endif // __MODULESCENESELECTION_H__