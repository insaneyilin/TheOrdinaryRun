/**
 *  @Date  2015/04/04 10:56
 *  @File  Rock.cpp 
 *  
 *  @Author LiangJian Liu
 *  @Contact janestar92@163.com
 *  
 *  @brief
 *	
 */
#include "Rock.h"

USING_NS_CC;

bool Rock::init()
{
	if( !Node::init() )
	{
		return false;
	}

	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("gamesource.plist","gamesource.png");

	auto sprite = Sprite::createWithSpriteFrameName("barrier.png");
	setSprite(sprite);

	initBody();

	return true;
}

void Rock::initBody()
{   
	Vec2 points[]={Vec2(25.8,-23.7),Vec2(14.7,-26.8),Vec2(-23.8,-26.2),Vec2(-0.6,26.9)};
	auto phyBody = PhysicsBody::createEdgePolygon(points,4);
	phyBody->setCategoryBitmask(1);
	phyBody->setCollisionBitmask(1);
	phyBody->setContactTestBitmask(1);

	this->setPhysicsBody(phyBody);
}
