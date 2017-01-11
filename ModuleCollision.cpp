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
	/*for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		Collider* c1 = *it;
		for (list<Collider*>::iterator jt = colliders.begin(); jt != colliders.end();)
		{
			Collider* c2 = *jt;
			if (c1 != c2) {
				if (c1->CheckCollision(c2->rect)) {
					LOG("BOOM!!!");
					c1->to_delete = true;
				}
			}
		}
	}*/


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
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

Collider* ModuleCollision::AddCollider(const Collider c)
{
	Collider* ret = new Collider(c.rect);
	ret->z = c.z;
	ret->depth = c.depth;

	colliders.push_back(ret);

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

	if (rect.x >= r.x && rect.x <= (rect.x + rect.w)) {
		if (rect.y >= r.y && rect.y <= (rect.y + rect.h)) {
			return true;
		}
	}


	
	return false;
}
