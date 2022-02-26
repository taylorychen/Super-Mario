#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

/////////////////////////////////////////////////////////////////////
//////////					   ACTOR			 		   //////////
/////////////////////////////////////////////////////////////////////

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, StudentWorld* w, 
		int depth = 0, int dir = 0, bool alive = true, double size = 1.0);
	
	void doSomething();
	virtual void bonk() = 0;
	
	StudentWorld* getWorld() { return m_world; };
	bool isAlive() const;
	void setNotAlive();
	bool inHitbox(double x, double y) const;

	virtual bool isBlocking() const { return false; };

private:
	bool m_alive;
	StudentWorld* m_world;

	virtual void doSomethingAux() = 0;
};

//not sure if this is right
inline
bool Actor::isAlive() const { return m_alive; }

inline
void Actor::setNotAlive() { m_alive = false; }

/////////////////////////////////////////////////////////////////////
//////////					STRUCTURE 			 		   //////////
/////////////////////////////////////////////////////////////////////

class Structure : public Actor {
public:
	Structure(int imageID, int startX, int startY, StudentWorld* w);
	virtual void doSomethingAux() {};
	virtual void bonk() = 0;
	bool isBlocking() const { return true; };
};

///////////////////////////////PIPE//////////////////////////////////

class Pipe : public Structure {
public:
	Pipe(int startX, int startY, StudentWorld* w);
	
	virtual void bonk() {};
};

///////////////////////////////BLOCK/////////////////////////////////

enum Goodie {
	empty, star, fire, jump
};

class Block : public Structure {
public:
	
	Block(int startX, int startY, StudentWorld* w, Goodie g = empty);
	virtual void bonk() {};

private:
	Goodie m_goodie;
};

/////////////////////////////////////////////////////////////////////
//////////					   GOAL  			 		   //////////
/////////////////////////////////////////////////////////////////////

class Goal : public Actor {
public:
	Goal(int imageID, int startX, int startY, StudentWorld* w);
	virtual void doSomethingAux() {};
	void bonk();
	bool isBlocking() const { return false; };
private:
	virtual void bonkAux() = 0;
};

///////////////////////////////FLAG//////////////////////////////////

class Flag : public Goal {
public:
	Flag(int startX, int startY, StudentWorld* w);
	virtual void bonkAux();
};

///////////////////////////////MARIO//////////////////////////////////

class Mario : public Goal {
public:
	Mario(int startX, int startY, StudentWorld* w);
	virtual void bonkAux();
};

/////////////////////////////////////////////////////////////////////
//////////					   PEACH			 		   //////////
/////////////////////////////////////////////////////////////////////

class Peach : public Actor {
public:
	Peach(int startX, int startY, StudentWorld* w);

	virtual void doSomethingAux();
	virtual void bonk() {};

	bool isInvinc() const;
	bool isRecharging() const;

	bool tryMove(int targetX, int targetY);

private:
	int hp;
	bool m_star;
	bool m_jump;
	bool m_fire;

	int m_invinc_time;
	int m_recharge_time;
	int m_jump_dist;
};

inline
bool Peach::isInvinc() const { return m_invinc_time > 0; }

inline
bool Peach::isRecharging() const { return m_recharge_time > 0; }

#endif // ACTOR_H_