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


/////////////////////////////////////////////////////////////////////
//////////					   BLOCK			 		   //////////
/////////////////////////////////////////////////////////////////////



Block::Block(int startX, int startY, StudentWorld* w, int imageID , Goodie g)
	: Actor(imageID, startX, startY, w, true /*alive*/, 0, 2) , m_goodie(g) {

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
	int targetX = getX();
	int targetY = getY();
	if (getWorld()->getKey(ch))
	{
		// user hit a key during this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(180);
			targetX -= 4;

			moveTo(targetX, targetY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			targetX += 4;
			
			moveTo(targetX, targetY);
			break;
		case KEY_PRESS_SPACE:
			
			break;
		case KEY_PRESS_UP:

			break;
		}
	}


}