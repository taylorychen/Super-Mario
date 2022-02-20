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

	Actor* objectAt(int x, int y);
	bool isBlockingObjectAt(int x, int y);

	std::vector<Actor*> objectsAt(double x, double y);
	bool isBlockingObjectAt2(double x, double y);

private:
	std::list<Actor*> m_actors;
	Peach* m_peach;


};

#endif // STUDENTWORLD_H_
