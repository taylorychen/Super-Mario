#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////////////////////////////////
//////////					   ACTOR			 		   //////////
/////////////////////////////////////////////////////////////////////

Actor::Actor(int imageID, int startX, int startY, StudentWorld* w, bool alive, int dir, int depth, double size)
	: GraphObject(imageID, startX, startY, dir, depth, size),
	m_alive(alive),
	m_world(w) {}

bool Actor::inHitbox(double x, double y) const {
	double dx = x - getX();
	double dy = y - getY();
	return (dx < 8 && dx >= 0) && (dy < 8 && dy >= 0);
}

/////////////////////////////////////////////////////////////////////
//////////					STRUCTURE 			 		   //////////
/////////////////////////////////////////////////////////////////////

Structure::Structure(int imageID, int startX, int startY, StudentWorld* w)
	: Actor(imageID, startX, startY, w, true/*alive*/, 0, 2) {}

/////////////////////////////////////////////////////////////////////
//////////					   PIPE 			 		   //////////
/////////////////////////////////////////////////////////////////////

Pipe::Pipe(int startX, int startY, StudentWorld* w)
	: Structure(IID_PIPE, startX, startY, w)
{}

/////////////////////////////////////////////////////////////////////
//////////					   BLOCK			 		   //////////
/////////////////////////////////////////////////////////////////////



Block::Block(int startX, int startY, StudentWorld* w, Goodie g)
	: Structure(IID_BLOCK, startX, startY, w) , m_goodie(g) {

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
	if (getWorld()->getKey(ch))
	{
		// user hit a key during this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(180);
			targetX -= 4;
			if(!getWorld()->isBlockingObjectAt2(targetX, targetY))
				moveTo(targetX, targetY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			targetX += 4;
							//since coord taken from bottom left, add SPRITE_WIDTH - 1
			if (!getWorld()->isBlockingObjectAt2(targetX + SPRITE_WIDTH - 1, targetY))
				moveTo(targetX, targetY);
			break;
		case KEY_PRESS_SPACE:
			
			break;
		case KEY_PRESS_UP:

			break;
		}
	}


}