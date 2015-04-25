#include "Accelerator.h"
USING_NS_CC;

bool Accelerator::init(){
	if(!Node::init()){
        return false;
	}
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("gamesource.plist","gamesource.png");
	auto sprite = Sprite::createWithSpriteFrameName("good5.png");
	setSprite(sprite);
	//getSprite()->runAction(createAnimate(frameCache));
	initBody();
	return true;

}


Animate* Accelerator::createAnimate(SpriteFrameCache* frameCache)
{
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameArray;
	for(int i = 1; i <= 4; i++) 
	{
		frame = frameCache->spriteFrameByName(
			String::createWithFormat("s%d.png", i)->getCString());
		frameArray.pushBack(frame);
	} 

	auto animation = Animation::createWithSpriteFrames(frameArray);

	animation->setLoops(-1);

	animation->setDelayPerUnit(0.1f);

	auto action = Animate::create(animation);

	return action;
}

void Accelerator::initBody(){
	Vec2 points[] ={Vec2(-39.1,-1.8),Vec2(6.4,36.7),Vec2(43.6,7.4),
		Vec2(42.5,-16.2),Vec2(4.8,-37.5), Vec2(-22.9,-23.0)};
	auto phyBody = PhysicsBody::createEdgePolygon(points,6); 
	phyBody->setCategoryBitmask(1);
	phyBody->setCollisionBitmask(1);
	phyBody->setContactTestBitmask(1);

	this->setPhysicsBody(phyBody);

}
