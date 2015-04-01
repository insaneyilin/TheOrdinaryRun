/**
 * @file Runner.cpp
 * @date 2015/04/01
 *
 * @author Yilin Gui
 * Contact: yilin.gui@gmail.com
 *
 * @brief  Implementation of the Runner class
 * 
 * TODO: 
 *
 */

#include "Runner.h"
#include "FlashTool.h"

USING_NS_CC;

bool Runner::init()
{
	_runnerSprite = Sprite::create();
	_runnerSprite->setContentSize(Size(44, 52));

	addChild(_runnerSprite);
	_state = running;
	initBody();

	return true;
}

void Runner::initActionSet(cocos2d::SpriteFrameCache *frameCache)
{

}

void Runner::doAction(const std::string &actionName)
{
	if (actionName == "running")
	{
		auto runningAction = RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json", 0.3f));
		_runnerSprite->runAction(runningAction);
	}
}

void Runner::initBody()
{
	auto runnerBody = PhysicsBody::createBox(Size(44, 52), PHYSICSBODY_MATERIAL_DEFAULT);  
	_runnerSprite->setPhysicsBody(runnerBody);  
}

void Runner::Run()
{
	_state = running;
	doAction("running");
}
