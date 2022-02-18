#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////////////////////////////////
//////////					   ACTOR			 		   //////////
/////////////////////////////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, bool alive, int dir, int depth, double size)
	: GraphObject(imageID, startX, startY, dir, depth, size),
	m_alive(alive) {}


/////////////////////////////////////////////////////////////////////
//////////					   BLOCK			 		   //////////
/////////////////////////////////////////////////////////////////////



Block::Block(int startX, int startY)
	: Actor(IID_BLOCK, startX, startY, true /*alive*/, 0, 2) {

}

void Block::doSomething() { }


/////////////////////////////////////////////////////////////////////
//////////					   PEACH			 		   //////////
/////////////////////////////////////////////////////////////////////

Peach::Peach(int startX, int startY)
	:Actor(IID_PEACH, startX, startY, true /*alive*/),
	hp(1),
	m_star(false), m_jump(false), m_fire(false){}

void Peach::doSomething() {
	if (!isAlive())
		return;
}