#include "engine.h"
#include "levelmanager.h"

int getNumberSize(int x)
{
	std::string s;
	std::stringstream sout;
	sout<<x;
	s = sout.str();

	return s.size();
}

std::string numberToString(int x)
{
	std::string s;
	std::stringstream sout;
	sout<<x;
	s = sout.str();
	return s;
}

int getNumber(std::string s, int i)
{
    if(i>s.size())
	{
		//error handling
		std::runtime_error("getNumber: requested digit not present");
	}
	char c = s[s.size()-i];
	return atoi(&c);
	//return strtol(&c, NULL, 10);
}

int getNumber(int x, int i)
{
    if(i<0) std::runtime_error("getNumber: input less than zero");
	std::string s;
	std::stringstream sout;
	sout<<x;
	s = sout.str();

	return getNumber(s, i);
}

void cHUDCounter::update(SDL_Surface *Screen)
{
    std::string counterString = numberToString(counter);
    //counterString = numberToString(counter);
    //std::string counterString = numberToString(123);
    //std::string counterString = "123";
    for(int i=1; i<=counterString.size(); ++i)
    {
        SDL_Rect SourceRct;
        //SourceRct.x = getNumber(counter, i) * 40;       // works when not optimized
        SourceRct.x = getNumber(counterString, i) * 40;     //works when optimized
        SourceRct.y = 0;
        SourceRct.h = 40;
        SourceRct.w = 40;

        SDL_Rect DestRct;
        DestRct.x = levelSize * 40 - (5 + i*40);
        DestRct.y = 5;
        DestRct.h = 40;
        DestRct.w = 40;

        SDL_BlitSurface(getHUDTexture(), &SourceRct, Screen, &DestRct);
    }
}

void initBasic1()
{

    cLevel* l = new cLevel("basic1");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -160;
    l->cameraY = -160;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(8);

    std::vector<int> row;

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));

    // set starting locations
    Point a(2,5);
    Point b(5,5);
    Point c(5,2);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);

    Point p(2,2);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);

}

void initBasic2()
{

    cLevel* l = new cLevel("basic2");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -200;
    l->cameraY = -160;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(7);

    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));

    // set starting locations
    Point a(2,4);

    l->startPts.push_back(a);

    Point p(1,4);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);

}

void initBasic3()
{

    cLevel* l = new cLevel("basic3");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -140;
    l->cameraY = -160;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(9);

    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->addDest();
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::WALL);
    l->addDest();
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));
    l->addBlock(g_SpriteManager.getBlock(3));

    // set starting locations
    Point a(2,3);
    Point b(6,3);
    Point c(2,5);
    Point d(6,5);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);
    l->startPts.push_back(d);

    Point p(4,4);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);

}

void initArrow1()
{

    cLevel* l = new cLevel("arrow1");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -180;
    l->cameraY = -180;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(7);

    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::WALL);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);

    l->staticIndex.push_back(row);
    row.clear();


    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));

    // set starting locations
    Point a(3,2);
    Point b(4,3);
    Point c(5,4);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);

    Point p(1,1);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);

}

void initArrow2()
{

    cLevel* l = new cLevel("arrow2");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -220;
    l->cameraY = -160;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(8);

    std::vector<int> row;

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();


    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));

    // set starting locations
    Point a(2,5);
    Point b(3,5);

    l->startPts.push_back(a);
    l->startPts.push_back(b);

    Point p(1,5);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);
}

void initArrow3()
{

    cLevel* l = new cLevel("arrow3");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->cameraX = -130;
    l->cameraY = -130;

    // set music track
    l->setMusicTrack(0);

    // set level layout

    l->setLevelSize(10);

    std::vector<int> row;

    //row 1
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 2
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_RIGHT);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 3
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 4
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::ARROW_RIGHT);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::BLANK);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    //row 5
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 6
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_RIGHT);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 7
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::DEST);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);
    l->addDest();

    l->staticIndex.push_back(row);
    row.clear();

    //row 8
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 9
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    //row 10
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);

    l->staticIndex.push_back(row);
    row.clear();

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));
    l->addBlock(g_SpriteManager.getBlock(3));

    // set starting locations
    Point a(3,7);
    Point b(6,3);
    Point c(6,6);
    Point d(7,6);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);
    l->startPts.push_back(d);

    Point p(7,7);

    l->playerStartPt = p;

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);
}

void initArrowTest()
{
    cLevel* l = new cLevel("Arrow1");
    l->setLevelTiles(g_TextureManager2.getSurface(1));
    l->setMusicTrack(0);
    l->setLevelSize(6);
    l->cameraX = -200;
    l->cameraY = -200;
    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    l->addEnemyPt(Point(4,1));
    l->addEnemy(g_SpriteManager.getKnight(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    l->playerStartPt = Point(4,3);
    l->addPlayer(g_SpriteManager.getPlayer(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_LEFT);
    l->startPts.push_back(Point(3,4));
    l->addBlock(g_SpriteManager.getBlock(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    g_LevelManager.addLevel(l);
}

void initWhack2()
{
    cLevel* l = new cLevel("whack2");
    l->setLevelTiles(g_TextureManager2.getSurface(1));
    l->setMusicTrack(1);
    l->setLevelSize(10);
    l->cameraX = -140;
    l->cameraY = -140;
    std::vector<int> row;

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    l->startPts.push_back(Point(5,5));
    l->addBlock(g_SpriteManager.getBlock(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::ARROW_UP);
    l->startPts.push_back(Point(7,5));
    l->addBlock(g_SpriteManager.getBlock(1));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    l->startPts.push_back(Point(6,6));
    l->addBlock(g_SpriteManager.getBlock(2));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    l->playerStartPt = Point(8,6);
    l->addPlayer(g_SpriteManager.getPlayer(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    g_LevelManager.addLevel(l);

}

void initPawn1()
{
    cLevel* l = new cLevel("pawn1");
    l->setLevelTiles(g_TextureManager2.getSurface(1));
    l->setMusicTrack(0);
    l->setLevelSize(6);
    l->cameraX = -200;
    l->cameraY = -200;
    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::DEST);
    l->addDest();
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    l->addEnemyPt(Point(4,1));
    l->addEnemy(g_SpriteManager.getPawn(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_DOWN);
    l->playerStartPt = Point(4,3);
    l->addPlayer(g_SpriteManager.getPlayer(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_LEFT);
    l->startPts.push_back(Point(3,4));
    l->addBlock(g_SpriteManager.getBlock(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    g_LevelManager.addLevel(l);
}

void initPawn2()
{
    cLevel* l = new cLevel("pawn1");
    l->setLevelTiles(g_TextureManager2.getSurface(1));
    l->setMusicTrack(0);
    l->setLevelSize(6);
    l->cameraX = -200;
    l->cameraY = -200;
    std::vector<int> row;

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::DEST);
    l->addDest();
    l->addEnemyPt(Point(3,1));
    l->addEnemy(g_SpriteManager.getPawn(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    l->playerStartPt = Point(1,2);
    l->addPlayer(g_SpriteManager.getPlayer(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::GROUND);
    l->startPts.push_back(Point(3,2));
    l->addBlock(g_SpriteManager.getBlock(0));
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::ARROW_DOWN);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::GROUND);
    row.push_back(cLevel::ARROW_UP);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::ARROW_LEFT);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    row.push_back(cLevel::WALL);
    l->staticIndex.push_back(row);
    row.clear();

    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    row.push_back(cLevel::BLANK);
    l->staticIndex.push_back(row);
    row.clear();

    g_LevelManager.addLevel(l);
}

void initPawn3()
{
    cLevel* l = new cLevel("pawn3");
	l->setLevelTiles(g_TextureManager2.getSurface(1));
	l->setMusicTrack(1);
	l->setLevelSize(9);
	l->cameraX = -140;
	l->cameraY = -140;
	std::vector<int> row;

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::DEST);
	l->addDest();
	l->addEnemyPt(Point(2,1));
	l->addEnemy(g_SpriteManager.getPawn(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->addEnemyPt(Point(6,1));
	l->addEnemy(g_SpriteManager.getPawn(1));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::DEST);
	l->addDest();
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(3,3));
	l->addBlock(g_SpriteManager.getBlock(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(5,3));
	l->addBlock(g_SpriteManager.getBlock(1));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->playerStartPt = Point(4,4);
	l->addPlayer(g_SpriteManager.getPlayer(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(3,5));
	l->addBlock(g_SpriteManager.getBlock(2));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(5,5));
	l->addBlock(g_SpriteManager.getBlock(3));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::DEST);
	l->addDest();
	l->addEnemyPt(Point(2,7));
	l->addEnemy(g_SpriteManager.getPawn(2));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->addEnemyPt(Point(6,7));
	l->addEnemy(g_SpriteManager.getPawn(3));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::DEST);
	l->addDest();
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	g_LevelManager.addLevel(l);
}

void initKnight1()
{
	cLevel* l = new cLevel("knight2");
	l->setLevelTiles(g_TextureManager2.getSurface(1));
	l->setMusicTrack(1);
	l->setLevelSize(10);
	l->cameraX = -120;
	l->cameraY = -120;
	std::vector<int> row;

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->addEnemyPt(Point(3,1));
	l->addEnemy(g_SpriteManager.getKnight(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::DEST);
	l->addDest();
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	l->playerStartPt = Point(2,3);
	l->addPlayer(g_SpriteManager.getPlayer(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(5,4));
	l->addBlock(g_SpriteManager.getBlock(0));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	l->startPts.push_back(Point(4,5));
	l->addBlock(g_SpriteManager.getBlock(1));
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::DEST);
	l->addDest();
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::GROUND);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	row.push_back(cLevel::WALL);
	l->staticIndex.push_back(row);
	row.clear();

	g_LevelManager.addLevel(l);

}

void initKing()
{
    cLevel* l = new cLevel("king");
l->setLevelTiles(g_TextureManager2.getSurface(1));
l->setMusicTrack(1);
l->setLevelSize(14);
l->cameraX = -160;
l->cameraY = -40;
std::vector<int> row;

row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
l->playerStartPt = Point(3,2);
l->addPlayer(g_SpriteManager.getPlayer(0));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
l->startPts.push_back(Point(2,3));
l->addBlock(g_SpriteManager.getBlock(0));
row.push_back(cLevel::GROUND);
l->startPts.push_back(Point(3,3));
l->addBlock(g_SpriteManager.getBlock(1));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
l->startPts.push_back(Point(5,3));
l->addBlock(g_SpriteManager.getBlock(2));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
l->startPts.push_back(Point(3,7));
l->addBlock(g_SpriteManager.getBlock(3));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
l->startPts.push_back(Point(2,9));
l->addBlock(g_SpriteManager.getBlock(4));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::ARROW_DOWN);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
l->addEnemyPt(Point(2,11));
l->addEnemy(g_SpriteManager.getKing(0));
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::GROUND);
row.push_back(cLevel::WALL);
row.push_back(cLevel::DEST);
l->addDest();
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::WALL);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
row.push_back(cLevel::BLANK);
l->staticIndex.push_back(row);
row.clear();

g_LevelManager.addLevel(l);

}

void initLevel1()
{
    cLevel* l = new cLevel("level1");

    l->setLevelSize(10);

    int sizeDiff = (levelSize - l->getLevelSize()) / 2;
    int space = sizeDiff-1;

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->setMusicTrack(0);
    //l->ms = *g_SoundManager.getStream(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i<space || i>=levelSize-space || j<space || j>=levelSize-space)
                row.push_back(cLevel::BLANK);
            else if(i == space || i==levelSize-sizeDiff || j==space || j==levelSize-sizeDiff)
                row.push_back(1);
            else if(i==4 && j==4)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(4,4);
            }
            else if(i==4 && j==levelSize-5)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(levelSize-5,4);
            }
            else
                row.push_back(0);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));


    l->addEnemy(g_SpriteManager.getPawn(0));
    l->addEnemy(g_SpriteManager.getPawn(1));


    // set starting locations
    Point a(3 + sizeDiff, 4 + sizeDiff);

    Point b(6 + sizeDiff, 4 + sizeDiff);

    l->startPts.push_back(a);
    l->startPts.push_back(b);

    //Point p(4 + sizeDiff, 5 + sizeDiff);
    Point p(4 + sizeDiff, 1 + sizeDiff);
    l->playerStartPt = p;


    Point e(9 + sizeDiff,9 + sizeDiff);
    l->addEnemyPt(e);

    Point e2(0 + sizeDiff, 9 + sizeDiff);
    l->addEnemyPt(e2);

    //first core
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);

    //second core
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);
}

void initLevel2()
{
    cLevel* l = new cLevel("level2");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    //l->ms = *g_SoundManager.getStream(1);
    l->setMusicTrack(0);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i==0 || i==levelSize-1 || j==0 || j==levelSize-1)
                row.push_back(1);
            else if(i==7 && j==4)
            {
                row.push_back(2);
                l->addDestPt(4,7);
            }
            else if(i==4 && j==levelSize-3)
            {
                row.push_back(2);
                l->addDestPt(levelSize-3,4);
            }
            else if(i==4 && j == levelSize-4 || i==4 && j == levelSize-5)
            {
                row.push_back(cLevel::ARROW_RIGHT);
            }
            else if(i==5 && j == levelSize-5 || i==6 && j == levelSize-5)
            {
                row.push_back(cLevel::ARROW_UP);
            }
            else if(i==6 && j == levelSize-9  || i==6 && j == levelSize-8  || i==6 && j == levelSize-7  || i==6 && j == levelSize-6)
            {
                row.push_back(cLevel::ARROW_RIGHT);
            }
            else if(i==9 && j==2 || i==10 && j==2 || i==11 && j==2)
            {
                row.push_back(1);
            }

            //else if(i==9 && j==1) row.push_back(1);
            else
                row.push_back(0);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));

    //l->addEnemy(g_SpriteManager.getKnight(0));
    //l->addEnemy(g_SpriteManager.getKnight2(0));

    // set starting locations
    Point a(3,2);
    Point b(2,3);
    Point c(6,6);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);

    Point p(10,10);

    l->playerStartPt = p;

    Point p1(1,9);
    Point p2(1,11);

    l->addEnemyPt(p1);
    l->addEnemyPt(p2);

    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::UP);
    l->addMove(cSprite::PASS);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::LEFT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::DOWN);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::UP);

    //l->autoPlayOn();

    g_LevelManager.addLevel(l);
}

void initLevel3()
{
    cLevel* l = new cLevel("level3");

    l->setLevelSize(10);

    int sizeDiff = (levelSize - l->getLevelSize()) / 2;
    int space = sizeDiff-1;

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    //l->ms = *g_SoundManager.getStream(2);
    l->setMusicTrack(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i<space || i>=levelSize-space || j<space || j>=levelSize-space)
                row.push_back(cLevel::BLANK);
            else if(i == space || i==levelSize-sizeDiff || j==space || j==levelSize-sizeDiff || (i == 8 && j != 8 && j!=7))
                row.push_back(1);
            else if(i==4 + sizeDiff && j==4 + sizeDiff)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(4 + sizeDiff,4 + sizeDiff);
            }
            else if(i==4 + sizeDiff && j==5 + sizeDiff)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(5 + sizeDiff,4 + sizeDiff);
            }
            else if(i==8 + sizeDiff && j==3 + sizeDiff)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(3 + sizeDiff,8 + sizeDiff);
            }
            else if(i==8 + sizeDiff && j==6 + sizeDiff)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(6 + sizeDiff,8 + sizeDiff);
            }
            else
                row.push_back(0);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));
    l->addBlock(g_SpriteManager.getBlock(3));

    l->addEnemy(g_SpriteManager.getBishop(0));
    l->addEnemy(g_SpriteManager.getBishop2(0));
    l->addEnemy(g_SpriteManager.getRook(0));
    l->addEnemy(g_SpriteManager.getRook2(0));

    // set starting locations
    Point a(3 + sizeDiff, 4 + sizeDiff);
    Point b(6 + sizeDiff, 4 + sizeDiff);
    Point c(2 + sizeDiff, 8 + sizeDiff);
    Point d(7 + sizeDiff, 8 + sizeDiff);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);
    l->startPts.push_back(d);

    Point p(2 + sizeDiff, 2 + sizeDiff);

    l->playerStartPt = p;

    Point p1(5+sizeDiff, 8 + sizeDiff);
    Point p2(4+sizeDiff, 8 + sizeDiff);
    Point p3(7+sizeDiff, 4+sizeDiff);
    Point p4(2+sizeDiff, 4+sizeDiff);

    l->addEnemyPt(p1);
    l->addEnemyPt(p2);
    l->addEnemyPt(p3);
    l->addEnemyPt(p4);

    g_LevelManager.addLevel(l);
}

void initLevel4()
{
    cLevel* l = new cLevel("level4");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->ms = *g_SoundManager.getStream(2);
    l->setMusicTrack(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i==0 || i==levelSize-1 || j==0 || j==levelSize-1)
                row.push_back(1);
            else if(i==3 && j==2)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(2,3);
            }
            else if(i==4 && j==3)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(3,4);
            }
            else if(i==5 && j==4)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(4,5);
            }
            else if(i==9 && j==2 || i==10 && j==2 || i==11 && j==2)
            {
                row.push_back(1);
            }

            //else if(i==9 && j==1) row.push_back(1);
            else
                row.push_back(0);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));
    l->addBlock(g_SpriteManager.getBlock(2));

    l->addEnemy(g_SpriteManager.getKing(0));

    // set starting locations
    Point a(3,2);
    Point b(2,3);
    Point c(6,6);

    l->startPts.push_back(a);
    l->startPts.push_back(b);
    l->startPts.push_back(c);

    Point p(10,10);

    l->playerStartPt = p;

    Point p1(1,9);

    l->addEnemyPt(p1);

    g_LevelManager.addLevel(l);
}

void initLevel5()
{
    cLevel* l = new cLevel("level5");

    l->setLevelSize(10);

    int sizeDiff = (levelSize - l->getLevelSize()) / 2;
    int space = sizeDiff-1;

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    l->setMusicTrack(0);
    //l->ms = *g_SoundManager.getStream(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i<space || i>=levelSize-space || j<space || j>=levelSize-space)
                row.push_back(cLevel::BLANK);
            else if(i == space || i==levelSize-sizeDiff || j==space || j==levelSize-sizeDiff)
                row.push_back(1);
            else if(i==4 && j==4)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(4,4);
            }
            else if(i==4 && j==levelSize-5)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(levelSize-5,4);
            }
            else if(i == 5 + sizeDiff && j == 3 + sizeDiff)
                row.push_back(cLevel::ARROW_DOWN);
            else if(i == 4 + sizeDiff && j == 3 + sizeDiff)
                row.push_back(cLevel::ARROW_DOWN);

            else
                row.push_back(0);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));
    l->addBlock(g_SpriteManager.getBlock(1));


    l->addEnemy(g_SpriteManager.getPawn(0));
    //l->addEnemy(g_SpriteManager.getPawn(1));


    // set starting locations
    Point a(3 + sizeDiff, 3 + sizeDiff);

    Point b(6 + sizeDiff, 4 + sizeDiff);

    l->startPts.push_back(a);
    l->startPts.push_back(b);

    //Point p(4 + sizeDiff, 5 + sizeDiff);
    Point p(4 + sizeDiff, 1 + sizeDiff);
    l->playerStartPt = p;


    Point e(9 + sizeDiff,9 + sizeDiff);
    //l->addEnemyPt(e);

    Point e2(0 + sizeDiff, 9 + sizeDiff);
    l->addEnemyPt(e2);


    //l->autoPlayOn();

    g_LevelManager.addLevel(l);
}


void loadLevel(cLevelManager& lm, int x)
{
    cLevel* l = lm.getLevel(x);
    lm.setCurrentLevel(x);

    camera.x = l->cameraX;
    camera.y = l->cameraY;

    l->resetLost();

    g_InputManager.clearObjects();

    g_InputManager.addInputObject(l->getPlayer(0));

    l->getPlayer(0)->clearMoves();
    l->getPlayer(0)->reset();

    if(l->autoPlay())
    {
        for(int i=0;i<l->solutionMovesSize();++i)
        {
            l->getPlayer(0)->addMove(l->getSolutionMove(i));
        }
    }

    //first add player to react queu
    g_InputManager.addReactPiece(l->getPlayer(0));

    //then add enemies
    for(int i=0;i<l->enemiesSize();++i)
    {
        g_InputManager.addReactPiece(l->getEnemy(i));
    }

    //then add boxes
    for(int i=0;i<l->blocksSize();++i)
    {
        g_InputManager.addReactPiece(l->getBlock(i));
    }

    //add level tiles to render queue
    g_RenderManager.addRenderObject(l);

    for(int i=0;i<l->playersSize();++i)
    {
        l->getPlayer(0)->m_XPos = l->playerStartPt.x * l->getPlayer(i)->m_Size;
        l->getPlayer(0)->m_YPos = l->playerStartPt.y * l->getPlayer(i)->m_Size;

        l->getPlayer(0)->m_displayX = l->playerStartPt.x * l->getPlayer(i)->m_Size;
        l->getPlayer(0)->m_displayY = l->playerStartPt.y * l->getPlayer(i)->m_Size;

        g_RenderManager.addRenderObject(l->getPlayer(i));
        l->getPlayer(i)->reset();
    }

    if(l->getEnemyPtsSize()>0 && l->enemiesSize()>0)
    {
        for(int i=0;i<l->enemiesSize();++i)
        {
            l->getEnemy(i)->m_XPos = l->getEnemyPt(i).x * l->getEnemy(i)->m_Size;
            l->getEnemy(i)->m_YPos = l->getEnemyPt(i).y * l->getEnemy(i)->m_Size;

            l->getEnemy(i)->m_displayX = l->getEnemyPt(i).x * l->getEnemy(i)->m_Size;
            l->getEnemy(i)->m_displayY = l->getEnemyPt(i).y * l->getEnemy(i)->m_Size;

            g_RenderManager.addRenderObject(l->getEnemy(i));
            l->getEnemy(i)->reset();
        }
    }

    for(int i=0;i<l->blocksSize();++i)
    {
        l->getBlock(i)->m_XPos = l->startPts[i].x * l->getBlock(i)->m_Size;
        l->getBlock(i)->m_YPos = l->startPts[i].y * l->getBlock(i)->m_Size;

        l->getBlock(i)->m_displayX = l->startPts[i].x * l->getBlock(i)->m_Size;
        l->getBlock(i)->m_displayY = l->startPts[i].y * l->getBlock(i)->m_Size;

        g_RenderManager.addRenderObject(l->getBlock(i));
        l->getBlock(i)->reset();

    }

    //add hud to render queue
    //g_RenderManager.addRenderObject(&lm);
    g_RenderManager.addHUDElement(&lm);

    g_SoundManager.playStream(lm.activeLevel()->musicTrack());
}


void loadLevel(int x)
{
    loadLevel(g_LevelManager, x);
}

void cLevelManager::update(SDL_Surface* Screen)
{
    HUDCounter.update(Screen);
    if(autoPlay())
    {
        SDL_Surface* title = g_TextureManager2.getSurface(0);

        SDL_Rect destRct;
        destRct.x = 0;
        destRct.y = 0;
        destRct.w = 250;
        destRct.h = 250;

        SDL_BlitSurface(title,0,Screen,&destRct);
    }
}

bool cLevelManager::checkWin()
{
    if(activePlayer()->state() == cPiece::DEAD)
        g_SoundManager.playStream(2);

    //handle lose condition
    if(getCounter() == 0 || activeLevel()->levelLost())
    {
        activePlayer()->setState(2);
    }

    else if(activeLevel()->won())
    {
        bool gameWon = false;
        activePlayer()->setState(1);
        g_RenderManager.addRenderObject(activePlayer());        //add player on top of render queue

        if(currentLevel == levels.size()-1)
        {
            gameWon = true;
            g_SoundManager.playStream(4);
        }

        int delay;

        if(gameWon) delay = 5000;
        else delay = 1500;

        if(wintimer == -1)
            wintimer = SDL_GetTicks();
        else
        {
            if(SDL_GetTicks() - wintimer >= delay)
            {
                wintimer = -1;
                endLevel();
                if(gameWon)
                {
                    g_LevelManager.stop();
                    return true;
                }
                if(getCurrentLevel() + 1 == numberOfLevels())
                    loadLevel(*this, 0);

                else
                    loadLevel(*this, getCurrentLevel() + 1);
            }
        }
    }
    return false;
}

cBlock* getCurrentLevelBlock(int x)
{
    return g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->getBlock(x);
}

int getCurrentLevelObjectSize()
{
    return g_LevelManager.getLevel(g_LevelManager.getCurrentLevel())->blocksSize();
}

cLevel* getCurrentLevel()
{
    return g_LevelManager.getLevel(g_LevelManager.getCurrentLevel());
}

bool cLevel::won()
{
    int counter = 0;

    for(int i=0;i<blocksSize();++i)
    {
        if(getIndex(getBlock(i)->m_XPos/40, getBlock(i)->m_YPos/40) == cLevel::DEST)
            ++counter;
    }
    if (counter == dests)
        return true;
    return false;
}

void nextLevel()
{
    g_LevelManager.endLevel();
    if(g_LevelManager.getCurrentLevel() + 1 == g_LevelManager.numberOfLevels())
        loadLevel(0);

    else
        loadLevel(g_LevelManager.getCurrentLevel() + 1);
}

void prevLevel()
{
    g_LevelManager.endLevel();
    if(g_LevelManager.getCurrentLevel() == 0)
        loadLevel(g_LevelManager.numberOfLevels() - 1);

    else
        loadLevel(g_LevelManager.getCurrentLevel() - 1);
}

void initDemoLevel1()
{
    cLevel* l = new cLevel("demo1");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    //l->ms = *g_SoundManager.getStream(2);
    //l->setMusicTrack(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i == levelSize/2 + 1 && j == levelSize/2 + 2)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(levelSize/2 + 2,levelSize/2 + 1);
            }
            else if(i < levelSize/2 - 2 || j < 2 || j > levelSize - 3 || i > levelSize - 3)
                row.push_back(cLevel::BLANK);
            else if(i == levelSize/2 + 1 && j == levelSize/2 + 1)
                row.push_back(cLevel::ARROW_RIGHT);
            else
                row.push_back(cLevel::GROUND);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));

    // add enemies


    // set starting locations
    // for blocks
    Point a(levelSize/2 - 1,levelSize/2 + 1);

    l->startPts.push_back(a);

    // for player
    Point p(levelSize/2 - 4, levelSize/2 + 1);

    l->playerStartPt = p;

    // for enemies


    // add moves
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);

    // add to level manager
    g_LevelManager.addLevel(l);
}

void initDemoLevel2()
{
    cLevel* l = new cLevel("demo2");

    l->setLevelTiles(g_TextureManager2.getSurface(1));

    //l->ms = *g_SoundManager.getStream(2);
    //l->setMusicTrack(1);

    // set level layout
    for(int i=0;i<levelSize;++i)
    {
        std::vector<int> row;
        for(int j=0;j<levelSize;++j)
        {
            if(i == levelSize/2 + 1 && j == levelSize/2 + 2)
            {
                row.push_back(cLevel::DEST);
                l->addDestPt(levelSize/2 + 2,levelSize/2 + 1);
            }
            else if(i < levelSize/2 - 2 || j < 2 || j > levelSize - 3 || i > levelSize - 3)
                row.push_back(cLevel::BLANK);
            else
                row.push_back(cLevel::GROUND);
        }
        l->staticIndex.push_back(row);
    }

    // add player/core sprites to level
    l->addPlayer(g_SpriteManager.getPlayer(0));

    l->addBlock(g_SpriteManager.getBlock(0));

    // add enemies


    // set starting locations
    // for blocks
    Point a(levelSize/2 - 1,levelSize/2 + 1);

    l->startPts.push_back(a);

    // for player
    Point p(levelSize/2 - 4, levelSize/2);

    l->playerStartPt = p;

    // for enemies


    // add moves
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);
    l->addMove(cSprite::RIGHT);

    // add to level manager
    g_LevelManager.addLevel(l);
}

void initDemoLevelManager()
{
    g_LevelManager.clear();
    initDemoLevel1();
    initDemoLevel2();
    g_LevelManager.autoPlayOn();

}

void initHUD()
{
    g_LevelManager.setCounter(300);
    g_LevelManager.HUDCounter.setHUDTexture(g_TextureManager2.getSurface(2));
    g_LevelManager.HUDCounter.enableColorKey();
}

void clearHUD()
{
    g_LevelManager.setCounter(-1);
    g_LevelManager.HUDCounter.setHUDTexture(NULL);
}

void initLevelManager()
{
    g_LevelManager.clear();
    initBasic1();
    initBasic2();
    initBasic3();
    initArrow1();
    initArrow2();
    initArrow3();
    initWhack2();
    //initArrowTest();
    initPawn1();
    initPawn2();
    initPawn3();
    initKnight1();
    initKing();
}
