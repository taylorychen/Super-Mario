#include "Actor.h"
#include "StudentWorld.h"
#include <vector>
using namespace std;

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

void Actor::doSomething() {
	if (m_alive)
		doSomethingAux();
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

void Goal::bonk() {
	if (isAlive()) {
		getWorld()->increaseScore(1000);
		setNotAlive();
		bonkAux();
	}
}

///////////////////////////////FLAG//////////////////////////////////

Flag::Flag(int startX, int startY, StudentWorld* w)
	: Goal(IID_FLAG, startX, startY, w) {}

void Flag::bonkAux() {	
	getWorld()->levelFinished();
}

///////////////////////////////MARIO//////////////////////////////////

Mario::Mario(int startX, int startY, StudentWorld* w)
	: Goal(IID_MARIO, startX, startY, w) {}

void Mario::bonkAux() {
	getWorld()->hasWon();
}

/////////////////////////////////////////////////////////////////////
//////////					   PEACH			 		   //////////
/////////////////////////////////////////////////////////////////////

Peach::Peach(int startX, int startY, StudentWorld* w)
	:Actor(IID_PEACH, startX, startY, w),
	hp(1), m_invinc_time(false), m_recharge_time(0), m_jump_dist(0),
	m_star(false), m_jump(false), m_fire(false){}

void Peach::doSomethingAux() {
	StudentWorld* w = getWorld();

	if (isInvinc())
		m_invinc_time--;
		
	if (isRecharging())
		m_recharge_time--;
	if (m_jump_dist > 0) {
		double targetX = getX();
		double targetY = getY() + 4;
		if (!w->moveOrBonk(this, targetX, targetY))	//something in the way
			m_jump_dist = 0;
		else {
			moveTo(targetX, targetY);
			m_jump_dist--;
		}

	}
	int ch;
	double targetX = getX();
	double targetY = getY();
	
	if (w->getKey(ch))
	{
		// user hit a key during this tick!
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			setDirection(180);
			targetX -= 4;
			/*if(!w->isBlockingActorAt2(targetX, targetY))
				moveTo(targetX, targetY);*/
			w->moveOrBonk(this, targetX, targetY);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			targetX += 4;
			/*if (!w->isBlockingActorAt2(targetX + SPRITE_WIDTH - 1, targetY))
				moveTo(targetX, targetY);*/
			w->moveOrBonk(this, targetX, targetY);
			break;
		case KEY_PRESS_SPACE:
			
			break;
		case KEY_PRESS_UP:
		{
			if (!w->canMove(this, targetX, targetY - 1)) {
				if (m_jump)
					m_jump_dist = 12;
				else
					m_jump_dist = 8;
				w->playSound(SOUND_PLAYER_JUMP);
			}
			
		}
			break;
		}
		/*vector<Actor*> actorsHere = w->overlappingActors(this, getX(), getY());
		for (Actor* ap : actorsHere) {
			ap->bonk();
		}*/
		w->bonkActors(this);
	}
}

bool Peach::tryMove(int targetX, int targetY) {
	bool gotBlocked = false;
	vector<Actor*> actorsHere = getWorld()->overlappingActors(this, getX(), getY());
	for (Actor* ap : actorsHere) {
		if (ap->isBlocking()) {
			gotBlocked = true;
			ap->bonk();
		}
	}
	return !gotBlocked;
}