#include "Actor.h"
#include "StudentWorld.h"
#include <vector>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////////////////////////////////
//////////					   ACTOR			 		   //////////
/////////////////////////////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, StudentWorld* w, 
	int depth, int dir, bool alive, double size)
	: GraphObject(imageID, startX, startY, dir, depth, size),
	m_alive(alive),
	m_world(w) {}

//returns true if coordinate is in actor's hitbox
bool Actor::inHitbox(double x, double y) const {
	double dx = x - getX();
	double dy = y - getY();
	return (dx < 8 && dx >= 0) && (dy < 8 && dy >= 0);
}

/////////////////////////////////////////////////////////////////////
//////////					 STRUCTURE 			 		   //////////
/////////////////////////////////////////////////////////////////////

Structure::Structure(int imageID, int startX, int startY, StudentWorld* w)
	: Actor(imageID, startX, startY, w, 2) {}


///////////////////////////////PIPE//////////////////////////////////

Pipe::Pipe(int startX, int startY, StudentWorld* w)
	: Structure(IID_PIPE, startX, startY, w)
{}

///////////////////////////////BLOCK/////////////////////////////////

Block::Block(int startX, int startY, StudentWorld* w, Goodie g)
	: Structure(IID_BLOCK, startX, startY, w) , m_goodie(g) {}

/////////////////////////////////////////////////////////////////////
//////////					   GOAL  			 		   //////////
/////////////////////////////////////////////////////////////////////

Goal::Goal(int imageID, int startX, int startY, StudentWorld* w)
	: Actor(imageID, startX, startY, w, 1) {}

///////////////////////////////FLAG//////////////////////////////////

Flag::Flag(int startX, int startY, StudentWorld* w)
	: Goal(IID_FLAG, startX, startY, w) {}

void Flag::bonk() {
	if (!isAlive())
		return;
	getWorld()->increaseScore(1000);
	setNotAlive();
	getWorld()->levelFinished();
}

///////////////////////////////MARIO//////////////////////////////////

Mario::Mario(int startX, int startY, StudentWorld* w)
	: Goal(IID_MARIO, startX, startY, w) {}

void Mario::bonk() {
	if (!isAlive())
		return;
	getWorld()->increaseScore(1000);
	setNotAlive();
	getWorld()->hasWon();
}

/////////////////////////////////////////////////////////////////////
//////////					   PEACH			 		   //////////
/////////////////////////////////////////////////////////////////////

Peach::Peach(int startX, int startY, StudentWorld* w)
	:Actor(IID_PEACH, startX, startY, w),
	hp(1), m_invinc_time(false), m_recharge_time(0), m_jump_dist(0),
	m_star(false), m_jump(false), m_fire(false){}

void Peach::doSomething() {
	if (!isAlive())
		return;
	if (isInvinc())
		m_invinc_time--;
	if (isRecharging())
		m_recharge_time--;


	int ch;
	double targetX = getX();
	double targetY = getY();
	StudentWorld* w = getWorld();
	if (w->getKey(ch))
	{
		// user hit a key during this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(180);
			targetX -= 4;
			if(!w->isBlockingActorAt2(targetX, targetY))
				moveTo(targetX, targetY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			targetX += 4;
			//since coord taken from bottom left, add SPRITE_WIDTH - 1
			if (!w->isBlockingActorAt2(targetX + SPRITE_WIDTH - 1, targetY))
				moveTo(targetX, targetY);
			break;
		case KEY_PRESS_SPACE:
			
			break;
		case KEY_PRESS_UP:

			break;
		}
		std::vector<Actor*> actors = w->actorsAt(getX(), getY());
		for (Actor* ap : actors) {
			ap->bonk();
		}
	}


}