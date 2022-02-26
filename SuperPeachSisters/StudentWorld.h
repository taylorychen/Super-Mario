#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Peach;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	std::vector<Actor*> actorsAt(double x, double y);
	bool isBlockingActorAt2(double x, double y);

	
	std::vector<Actor*> overlappingActors(Actor* a, double x, double y);

	// If actor can move to (targetX,targetY), move it and return true; otherwise
	// bonk the object that's blocking it and return false.
	bool moveOrBonk(Actor* a, double targetX, double targetY) const;


	bool canMove(Actor* a, double targetX, double targetY) const;

	//bonk the actors overlapping with a
	void bonkActors(Actor* a) const;

	void giveStar() const { /*m_peach->gainStar();*/ };
	void giveFlower() const { /*m_peach->gainFlower();*/ };
	void giveJump() const { /*m_peach->gainJump();*/ };

	void levelFinished() { m_levelFinished = true; }
	void hasWon() { m_hasWon = true; }

private:
	std::list<Actor*> m_actors;
	Peach* m_peach;
	bool m_levelFinished;
	bool m_hasWon;

	//all actors that overlap with an actor at x and y put in the vector
	void overlappingActors(Actor* a, double x, double y, std::vector<Actor*>& actors) const;
};

#endif // STUDENTWORLD_H_
