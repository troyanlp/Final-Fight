#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include <iostream>

using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible
	//LOG("El size es: %d", colliders.size());
	std::list<Collider*>::iterator it = colliders.begin();
	
	for (int i = 0; i < colliders.size(); ++i)
	{
		LOG("Colliders size es: %d", colliders.size());
		LOG("i es: %d", i);
		std::advance(it, 1);
		/*Collider* c1 = *it;
		for (list<Collider*>::iterator jt = colliders.begin(); jt != colliders.end();)
		{
			Collider* c2 = *jt;
			if (c1 != c2) {
				if (c1->CheckCollision(c2->rect)) {
					LOG("BOOM!!!");
					c1->to_delete = true;
				}
			}
		}*/
	}


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it) {
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80); //LOG("Las coordenadas del collider son: %d", (*it)->rect.x);
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect rect, const int z, const int depth)
{
	Collider* ret = new Collider(rect);
	ret->z = z;
	ret->depth = depth;

	colliders.push_back(ret);
	//LOG("El size de colliders es: %d", colliders.size());

	return ret;
}

/*void ModuleCollision::RemoveCollider(Collider* c)
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it) {
		if (*it == c) {
			RELEASE(*it);
		}
	}
}*/

// -----------------------------------------------------

bool Collider::CheckCollision(const Collider c) const
{
	if (z > c.z && z < (c.z + c.depth) 
		|| (z + depth) > c.z && (z + depth) < (c.z + c.depth)
		|| z > c.z && (z + depth) > (c.z + c.depth)) {
		
		if (rect.x >= c.rect.x && rect.x < (c.rect.x + c.rect.w)
			|| (rect.x + rect.w) > c.rect.x && (rect.x + rect.w) < (c.rect.x + c.rect.w)
			|| rect.x < c.rect.x && (rect.x + rect.w) > (c.rect.x + c.rect.w)) {

			if (rect.y > c.rect.y && rect.y < (c.rect.y + c.rect.h)
				|| (rect.y + rect.h) > c.rect.y && (rect.y + rect.h) < (c.rect.y + c.rect.h)
				|| rect.y < c.rect.y && (rect.y + rect.h) > (c.rect.y + c.rect.h) ) {

				LOG("HAY COLISION!");

			}

		}

	}


	
	return false;
}
