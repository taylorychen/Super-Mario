#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
//things I added:
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_peach = nullptr;
    m_levelFinished = false;
    m_hasWon = false;
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

int StudentWorld::init()
{
    Level l(assetPath());
    string levelFile = "level01.txt";

    Level::LoadResult result = l.loadLevel(levelFile);

    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "level01.txt is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        m_levelFinished = false;
        cerr << "Successfully loaded level" << endl;

        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                Level::GridEntry actor = l.getContentsOf(x, y);
                switch (actor) {
                case Level::empty:
                    break;
                case Level::block:
                {
                    Actor* b = new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                    m_actors.push_back(b);
                }
                    break;
                case Level::peach:
                {
                    m_peach = new Peach(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                }
                    break;

                case Level::star_goodie_block:
                {
                    Actor* b = new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, star);
                    m_actors.push_back(b);
                }
                    break;
                case Level::mushroom_goodie_block:
                {
                    Actor* b = new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, jump);
                    m_actors.push_back(b);
                }
                    break;
                case Level::flower_goodie_block:
                {
                    Actor* b = new Block(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this, fire);
                    m_actors.push_back(b);
                }
                    break;
                case Level::pipe:
                {
                    Actor* p = new Pipe(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                    m_actors.push_back(p);
                }
                    break;
                case Level::flag:
                {
                    Actor* f = new Flag(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                    m_actors.push_back(f);
                }
                    break;
                case Level::mario:
                {
                    Actor* m = new Mario(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, this);
                    m_actors.push_back(m);
                }
                    break;
                /*case Level::koopa:
                    break;
                case Level::goomba:
                    break;
                case Level::piranha:
                    break;
                
                

                
                */
                }
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    m_peach->doSomething();
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        if (!(*p)->isAlive())
            continue;
            
        (*p)->doSomething();

        /*if (Peach died during this tick) {
            play dying sound
                return GWSTATUS_PLAYER_DIED;
        }
        if (Peach reached Mario) {
            play game over sound
                return GWSTATUS_WON_GAME;
        }
        if (Peach competed the current level) {
            play completed level sound
                return GWSTATUS_FINISHED_LEVEL;
        }*/

        if (m_hasWon) {
            playSound(SOUND_GAME_OVER);
            return GWSTATUS_PLAYER_WON;
        }

        if (m_levelFinished) {
            playSound(SOUND_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
           
    }
    //TODO: can consolidate into function?
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end();) {
        if ((*p)->isAlive()) {
            p++;
            continue;
        }
            
        delete (*p);
        p = m_actors.erase(p);
    }
    // Remove newly-dead actors after each tick
    
    //    // Update the game status line
    //    update display text // update the score/lives/level text at screen top
    //    // the player hasn’t completed the current level and hasn’t died, so
    //    // continue playing the current level
    //    return GWSTATUS_CONTINUE_GAME;

    
    return GWSTATUS_CONTINUE_GAME;
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator p = m_actors.begin();
    while (!m_actors.empty()) {
        delete (*p);
        p = m_actors.erase(p);
    }
    delete m_peach;
    m_peach = nullptr; //set to null to be safe?
}

Actor* StudentWorld::actorAt(int x, int y) {
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        if ((*p)->getX() == x && (*p)->getY() == y)
            return (*p);
    }
    //return nullptr if no object a (x,y)
    return nullptr;
}

bool StudentWorld::isBlockingActorAt(int x, int y) {
    Actor* p = actorAt(x, y);
    if (p == nullptr)
        return false;
    return p->isBlocking();

}

vector<Actor*> StudentWorld::actorsAt(double x, double y) {
    vector<Actor*> out;
    for (list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++) {
        if ((*p)->inHitbox(x, y))
            out.push_back(*p);
    }
    //return empty vecotor if nothing a (x,y)
    return out;
}

bool StudentWorld::isBlockingActorAt2(double x, double y) {
    vector<Actor*> a = actorsAt(x, y);
    for (vector<Actor*>::iterator p = a.begin(); p != a.end(); p++) {
        if ((*p)->isBlocking())
            return true;
    }
    return false;

}