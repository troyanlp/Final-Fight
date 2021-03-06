#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	int z = 0;
	int depth = 0;
	bool to_delete = false;

	// TODO 10: Add a way to notify other classes that a collision happened
	bool collided = false;

	Collider(SDL_Rect rectangle) : // expand this call if you need to
		rect(rectangle)
	{}

	void SetPos(int x, int y, int z)
	{
		rect.x = x;
		rect.y = y;
		Collider::z = z;
	}

	bool CheckCollision(const Collider c) const;

	~Collider() {

	}
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect rect, const int z, const int depth);
	//void RemoveCollider(Collider* c);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__