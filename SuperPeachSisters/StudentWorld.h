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

	Actor* actorAt(int x, int y);
	bool isBlockingActorAt(int x, int y);

	std::vector<Actor*> actorsAt(double x, double y);
	bool isBlockingActorAt2(double x, double y);
	void levelFinished() { m_levelFinished = true; }
	void hasWon() { m_hasWon = true; }

private:
	std::list<Actor*> m_actors;
	Peach* m_peach;
	bool m_levelFinished;
	bool m_hasWon;

};

#endif // STUDENTWORLD_H_
