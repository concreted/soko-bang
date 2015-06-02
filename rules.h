#ifndef RULES_H
#define RULES_H

#include "engine.h"

bool ruleMoveCheck(Point& index, cSprite::DIRECTION dir);

bool ruleMoveCheckBool(cRenderObject* o, cSprite::DIRECTION dir);

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1);

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2);

int ruleMoveCheck(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2, cSprite::DIRECTION dir3);

bool ruleBlockMove(cRenderObject* o, cSprite::DIRECTION dir);

bool ruleMove(cRenderObject* o, cSprite::DIRECTION dir);

bool ruleMove(cRenderObject* o, cSprite::DIRECTION dir1, cSprite::DIRECTION dir2, cSprite::DIRECTION dir3);

bool ruleMove(cRenderObject* o, unsigned int indexX, unsigned int indexY);

bool ruleMoveKnight(cRenderObject* o, cSprite::DIRECTION dir);

bool rulePushBox(cRenderObject* o, cSprite::DIRECTION pd);

bool ruleWhack(cRenderObject* o, cSprite::DIRECTION pd);

bool ruleSokobanPlayerBox(cRenderObject* o, SDLKey Key);

#endif
