#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////////////////////////////////
//////////					   ACTOR			 		   //////////
/////////////////////////////////////////////////////////////////////

class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, bool alive, int dir = 0, int depth = 0, double size = 1.0);
	
	virtual void doSomething() { };
	bool isAlive() const;

private:
	bool m_alive;
};

inline
bool Actor::isAlive() const { return m_alive; }

/////////////////////////////////////////////////////////////////////
//////////					   BLOCK			 		   //////////
/////////////////////////////////////////////////////////////////////

class Block : public Actor {
public:
	Block(int startX, int startY);

	virtual void doSomething();

private:
	
};

/////////////////////////////////////////////////////////////////////
//////////					   PEACH			 		   //////////
/////////////////////////////////////////////////////////////////////

class Peach : public Actor {
public:
	Peach(int startX, int startY);

	virtual void doSomething();

private:
	int m_hp;
	bool m_star;
	bool m_jump;
	bool m_fire;
};


#endif // ACTOR_H_