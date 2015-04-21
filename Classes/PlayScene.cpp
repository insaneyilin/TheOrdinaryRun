/**
 * @file PlayScene.cpp
 * @date 2015/04/01
 *
 * @author Yilin Gui
 * Contact: yilin.gui@gmail.com
 *
 * @brief  Implementation of the PlayScene class
 * 
 * TODO: 
 *
 */

#include "PlayScene.h"
#include "SimpleAudioEngine.h"
#include "BaseManager.h"
#include "GameOverScene.h"
#include "PauseLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

double PlayScene::POS_X_SCALE_FACTOR = 0.068;
double PlayScene::POS_Y_SCALE_FACTOR = 0.04;

int PlayScene::SCORE_PER_SEC = 20;
int PlayScene::SCORE_PER_COIN = 100;

/************************************************************************/
/*                               Public Methods                                           */
/************************************************************************/
Scene* PlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->
	//	setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1200));

	auto layer = PlayScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool PlayScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	_visibleSize = Director::getInstance()->getVisibleSize();

	_countCoins = 0;  // ��ʼ�����Ϊ 0
	_score = 0;  // ��ʼ�÷�Ϊ 0
	_accumTime = 0;  // ��ʼ�ۻ�ʱ��Ϊ 0
	_groundHeight = 57;  // ����߶�
	_runnerPosX = 144;   // ��ɫx����λ��
	_bgMoveSpeed = NORMAL_SPEED;  // ���������ٶ�

	_timerRunning = false;  // ��ʼʱ��ʱ���ر�

	// FORTEST�����Գ����
	_isDash = false;  // Ĭ�Ϲرճ��

	// ���ű�������
	SimpleAudioEngine::getInstance()->
		playBackgroundMusic("putong_disco.wav", true);

	initPhysicsWorld();  // ��ʼ����������

	initBG();  // ��ʼ������

	buildUI();  // ���� UI �������ť��������߹�������

	addEventListeners();  // ��Ӵ����¼�����
	addContactListeners();  // �����ײ������

	//scheduleUpdate();  // ������ʱ��
	startTimer();
	
	return true;
}

void PlayScene::update(float delta)
{
	// ���¼�ʱ��ǩ�͵÷ֱ�ǩ
	if (_timerRunning)
	{
		_accumTime += 1000;
		int secs = _accumTime / 100000;
		_timeLabel->setString(StringUtils::format("%ld", _accumTime / 100000));

		_score = SCORE_PER_SEC * secs + SCORE_PER_COIN * _countCoins;
		_scoreLabel->setString(StringUtils::format("%u", _score));
	}

	if (_isDash)
	{
		_remainedDashTime -= 200;
		if (_remainedDashTime <= 0)
		{
			_isDash = false;
			stopDash();
		}
	}

	/* ����������ѭ������ */
	int posX1 = _bgSprite1->getPositionX();
	int posX2 = _bgSprite2->getPositionX();

	// �����������������
	posX1 -= _bgMoveSpeed;
	posX2 -= _bgMoveSpeed;

	auto mapSize = _bgSprite1->getContentSize();
	if (posX1 < -mapSize.width / 2)
	{
		posX1 = mapSize.width + mapSize.width / 2;
		posX2 = mapSize.width / 2;
	}

	if (posX2 < -mapSize.width / 2)
	{  
		posX2 = mapSize.width + mapSize.width / 2;  
		posX1 = mapSize.width / 2;  
	}  

	_bgSprite1->setPositionX(posX1);  
	_bgSprite2->setPositionX(posX2);  
	_groundSprite1->setPositionX(posX1);  
	_groundSprite2->setPositionX(posX2);  
}

void PlayScene::onGamePause()
{
	_timerRunning  = false;

	Director::getInstance()->pause();
	// ��ʱ����������壬��ֹ��ͣ��������������Ӱ��
	_runner->getPhysicsBody()->setEnable(false);

	// ��ͣ��������
	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->pauseBackgroundMusic();

	auto pauseLayer = PauseLayer::create();
	addChild(pauseLayer, 10000);
}

void PlayScene::onGameResume()
{
	_timerRunning  = true;

	// �������ű�������
	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->resumeBackgroundMusic();

	Director::getInstance()->resume();
	_runner->getPhysicsBody()->setEnable(true);
}

void PlayScene::startDash()
{
	// ��ͣ��������
	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->pauseBackgroundMusic();

	// ������Ч����
	audioEngine->playEffect("dash_sound.wav");

	_bgMoveSpeed = DASH_SPEED;
	_baseManager->setBgMoveSpeed(_bgMoveSpeed);
}

void PlayScene::stopDash()
{
	// �������ű�������
	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->resumeBackgroundMusic();

	_bgMoveSpeed = NORMAL_SPEED;
	_baseManager->setBgMoveSpeed(_bgMoveSpeed);
}

/************************************************************************/
/*                               Private Methods                                          */
/************************************************************************/
void PlayScene::initPhysicsWorld()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();  
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto groundBody = PhysicsBody::createEdgeSegment(origin, 
		Vec2(visibleSize.width, 0), PHYSICSBODY_MATERIAL_DEFAULT, 1);

	auto groundNode = Node::create();
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(0, _groundHeight);

	addChild(groundNode);
}

void PlayScene::initBG()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// ����ͼƬ1
	_bgSprite1 = Sprite::create("Map00.png");
	_bgSprite1->setPosition(visibleSize/2);
	addChild(_bgSprite1);

	// ����ͼƬ1
	_groundSprite1 = Sprite::create("Ground00.png");
	_groundSprite1->setPosition(visibleSize.width / 2, 
		_groundSprite1->getContentSize().height / 2);
	addChild(_groundSprite1);

	// ����ͼƬ2
	_bgSprite2 = Sprite::create("Map01.png");
	_bgSprite2->setPosition(
		_bgSprite1->getContentSize().width + visibleSize.width / 2, 
		visibleSize.height / 2);
	addChild(_bgSprite2);

	// ����ͼƬ2
	_groundSprite2 = Sprite::create("Ground01.png");
	_groundSprite2->setPosition(
		_groundSprite1->getContentSize().width + visibleSize.width / 2, 
		_groundSprite2->getContentSize().height / 2);
	addChild(_groundSprite2);
}

void PlayScene::buildUI()
{
	// �������ܽ�ɫ����
	_runner = Runner::create();
	_runner->setPosition(_runnerPosX, _groundHeight + 26);
	_runner->Run();
	addChild(_runner);

	// �������߹������
	_baseManager =BaseManager::create();
	_baseManager->setBgMoveSpeed(_bgMoveSpeed);
	addChild(_baseManager);

	// �����ͣ��ť
	_pauseButton = Sprite::create("pause_1.png");
	_pauseButton->setPosition(
		_visibleSize.width - _pauseButton->getContentSize().width / 2, 
		_visibleSize.height - _pauseButton->getContentSize().height / 2);
	addChild(_pauseButton);

	/*******************
	* FORTEST:
	* ���ٰ�ť�����ڲ��Լ�����Ч��
	*******************/
	_dashButton = Sprite::create("speed_shoes_40x40.png");
	_dashButton->setPosition(
		_visibleSize.width / 2, 
		_visibleSize.height - _dashButton->getContentSize().height / 2);
	addChild(_dashButton);

	// �����ʱ��ǩλ�ã��������Ͻǣ�
	unsigned int leftTopPosX = _visibleSize.width * POS_X_SCALE_FACTOR;
	unsigned int leftTopPosY = _visibleSize.height - 
		_visibleSize.height * POS_Y_SCALE_FACTOR;

	// ��Ӽ�ʱ���ֱ�ǩ
	_timeTextLabel = Label::create();
	_timeTextLabel->setTextColor(Color4B::BLUE);
	_timeTextLabel->setSystemFontSize(20);
	_timeTextLabel->setPosition(
		leftTopPosX, 
		leftTopPosY);
	_timeTextLabel->setString("TIME: ");
	addChild(_timeTextLabel);

	// ��Ӽ�ʱ��ǩ
	_timeLabel = Label::create();
	_timeLabel->setTextColor(Color4B::BLUE);
	_timeLabel->setSystemFontSize(20);
	_timeLabel->setPosition(
		leftTopPosX + _timeTextLabel->getContentSize().width * 2 / 3, 
		leftTopPosY);
	_timeLabel->setString("0");
	addChild(_timeLabel);

	// ����÷ֱ�ǩλ�ã��������½ǣ�
	unsigned int rightBottomPosX = _visibleSize.width * POS_X_SCALE_FACTOR;
	unsigned int rightBottomPosY = _visibleSize.height * POS_Y_SCALE_FACTOR;

	// ��ӵ÷����ֱ�ǩ
	_scoreTextLabel = Label::create();
	_scoreTextLabel->setTextColor(Color4B::BLUE);
	_scoreTextLabel->setSystemFontSize(20);
	_scoreTextLabel->setPosition(
		rightBottomPosX, 
		rightBottomPosY);
	_scoreTextLabel->setString("SCORE: ");
	addChild(_scoreTextLabel);

	// ��ӵ÷ֱ�ǩ
	_scoreLabel = Label::create();
	_scoreLabel->setTextColor(Color4B::BLUE);
	_scoreLabel->setSystemFontSize(20);
	_scoreLabel->setPosition(
		rightBottomPosX + _scoreTextLabel->getContentSize().width * 3 / 4, 
		rightBottomPosY);
	_scoreLabel->setString("0");
	addChild(_scoreLabel);
}

void PlayScene::addEventListeners()
{
	// ��Ӵ����¼�����
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *t, Event *e)
	{
		if (_pauseButton->
			getBoundingBox().containsPoint(t->getLocation()))
		{
			onGamePause();
		}
		else if (_dashButton->
			getBoundingBox().containsPoint(t->getLocation()))
		{
			//_isDash ? stopDash() : startDash();
			//_isDash = !_isDash;
			_isDash = true;
			startDash();  // �����ť��ʼ��̣������Ϊ�Ե��ߺ���
			_remainedDashTime = 100000;
		}
		else
		{
            _runner->Jump();
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(touchListener, this);
}

void PlayScene::addContactListeners()
{
	auto contactListenner = EventListenerPhysicsContact::create();  
	contactListenner->onContactBegin = [this](PhysicsContact &contact)
	{
		auto b_1 = (Sprite* )contact.getShapeA()->getBody()->getNode();  
		auto b_2 = (Sprite* )contact.getShapeB()->getBody()->getNode();

		// ������ײ
		if (b_1->getTag() == coinTag || b_2->getTag() == coinTag)
		{  
			// �رձ�������
			auto audioEngine = SimpleAudioEngine::getInstance();
			audioEngine->playEffect("pickup_coin.wav");
			b_1->setVisible(false); 
			++_countCoins;
		}

		/*******************
		* FIXME:
		* ��һ���ϰ�����ֵ�̫�磬������������Ծ
		* ����ʹ�ϰ�����ֵ�ʱ���Ӻ�
		*******************/
		// ���ϰ�����ײ
		//if (b_1->getTag() == rockTag || b_2->getTag() == rockTag)
		//{  
		//	// ֹͣ��ʱ��
		//	//this->unscheduleUpdate();
		//	this->stopTimer();
		//	auto audioEngine = SimpleAudioEngine::getInstance();
		//	audioEngine->stopBackgroundMusic();
		//	Director::getInstance()->
		//			replaceScene(GameOver::createScene());
		//}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(contactListenner, this);
}

void PlayScene::startTimer()
{
	if (!_timerRunning)
	{
		scheduleUpdate();
		_accumTime = 0;
		_timerRunning = true;
	}
}

void PlayScene::stopTimer()
{
	if (_timerRunning)
	{
		unscheduleUpdate();
		_timerRunning = false;
	}
}