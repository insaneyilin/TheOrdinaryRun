#include "Magnet.h"

USING_NS_CC;

bool Magnet::init(){
	if(!Node::init()){
		return false;
	}
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("gamesource.plist","gamesource.png");
	auto sprite = Sprite::createWithSpriteFrameName("good3.png");
	setSprite(sprite);
	initBody();
	return true;

}

void Magnet::initBody(){
	Vec2 points[] ={Vec2(-33.1,-19.5),Vec2(-33.6,2.5),Vec2(-15.3,31.3),
		Vec2(33.5,11.9),Vec2(35.4,-11.5), Vec2(12.1,-36.6),Vec2(-19.9,-37.9)};
	auto phyBody = PhysicsBody::createEdgePolygon(points,7); 
	phyBody->setDynamic(false);
	phyBody->setCategoryBitmask(1);
	phyBody->setCollisionBitmask(1);
	phyBody->setContactTestBitmask(1);

	this->setPhysicsBody(phyBody);




}