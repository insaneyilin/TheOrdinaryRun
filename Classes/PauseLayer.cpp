#include "PauseLayer.h"
#include "PlayScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool PauseLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(162, 162, 162, 128)))
	{
		return false;
	}

	buildUI();
	addEventListeners();

	return true;
}

void PauseLayer::buildUI()
{   
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("gamesource.plist","gamesource.png");
	auto to_home = Sprite::createWithSpriteFrameName("to_home.png");
	auto to_home_selected = Sprite::createWithSpriteFrameName("to_home_selected.png");
	auto homeItem = MenuItemSprite::create(
		to_home, to_home_selected, 
		CC_CALLBACK_1(PauseLayer::home, this));
	auto continued = Sprite::createWithSpriteFrameName("continue.png");
	auto continue_selected = Sprite::createWithSpriteFrameName("continue_selected.png");
	auto continueItem = MenuItemSprite::create(
		continued, continue_selected, 
		CC_CALLBACK_1(PauseLayer::back, this));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	homeItem->setPosition(visibleSize.width / 3, visibleSize.height / 2);
	continueItem->setPosition(visibleSize.width * 2 / 3, visibleSize.height / 2);

	auto menu = Menu::create(homeItem, continueItem, NULL);
	menu->setPosition(origin);

	addChild(menu);
}

void PauseLayer::addEventListeners()
{
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = [&](Touch *t, Event *e)
	{
		return true;
	};
	_listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(_listener, this);
}

void PauseLayer::home(cocos2d::Ref *ref)
{
	Director::getInstance()->getEventDispatcher()->
		removeEventListener(_listener);

	// �������ִ��һ�� Director::getInstance()->resume();
	// ����ص����ⳡ�������
	Director::getInstance()->resume();

	Director::getInstance()->replaceScene(HelloWorld::createScene());

	// �رձ�������
	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->playEffect("pickup_coin.wav");

	removeFromParent();
}

void PauseLayer::back(cocos2d::Ref *ref)
{
	Director::getInstance()->getEventDispatcher()->
		removeEventListener(_listener);
	auto playScene = (PlayScene*)this->getParent();
	playScene->onGameResume();

	removeFromParent();
}
