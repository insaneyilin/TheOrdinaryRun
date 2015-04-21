/**
 * @file PlayScene.h
 * @date 2015/04/01
 *
 * @author Yilin Gui
 * Contact: yilin.gui@gmail.com
 *
 * @brief  Definition of the PlayScene class
 * 
 * TODO: 
 *
 */

#ifndef __THEORDINARYRUN_PLAYSCENE_H__
#define __THEORDINARYRUN_PLAYSCENE_H__

#include "cocos2d.h"
#include "Runner.h"
#include "BaseManager.h"

class PlayScene : public cocos2d::LayerColor
{
public:
	/**
	 * @brief      Create an instance of cocos2d::Scene
	 * @return    the instance pointer
	 */
	static cocos2d::Scene* createScene();

	/**
	 * @brief      Some initialization works
	 * @return    true if initialization succeeds, else return false
	 */
	virtual bool init();

	// implement the "static create()" method by MARCO defined in Cocos2d-x
	CREATE_FUNC(PlayScene);

	/**
	 * @brief      Callback function, using with scheduleUpdate()
	 */
	virtual void update(float delta);

	/**
	 * @brief    Setter of private member "_physicsWorld"
	 * @param [in] world    Pointer of a cocos2d::PhysicsWorld instance
	 */
	void setPhysicsWorld(cocos2d::PhysicsWorld *world)
	{
		_physicsWorld = world;
	}

	/**
	 * @brief    Getter of private member "_physicsWorld"
	 * @return  the _physicsWorld attribute
	 */
	cocos2d::PhysicsWorld* getPhysicsWorld() const
	{
		return _physicsWorld;
	}

	/**
	 * @brief    Pause the game
	 */
	void onGamePause();

	/**
	 * @brief    Resume the game
	 */
	void onGameResume();

	/**
	 * @brief    Start "Super Dash"
	 */
	void startDash();

	/**
	 * @brief    Stop "Super Dash"
	 */
	void stopDash();

	// λ�ñ�����������
	static double POS_X_SCALE_FACTOR;
	static double POS_Y_SCALE_FACTOR;

	// ��λʱ��÷�ֵ
	static int SCORE_PER_SEC;

	// ������ҵ÷�ֵ
	static int SCORE_PER_COIN;

private:
	/**
	 * @brief      Initialization of background
	 */
	void initBG();

	/**
	 * @brief      Build UI componets. (pause button, score label, etc.)
	 */
	void buildUI();

	///@brief ��ʼ����������
	void initPhysicsWorld();   

	///@brief ����¼�������������Ļ�ȣ�
	void addEventListeners();

	///@brief �����ײ����¼�����
	void addContactListeners();

	void startTimer();

	void stopTimer();

	enum BG_SPEED
	{
		NORMAL_SPEED = 4,
		DASH_SPEED = 12
	};

private:
	cocos2d::Size _visibleSize;  // ���ڴ�С

	cocos2d::PhysicsWorld *_physicsWorld;  // ��������

	float _groundHeight;    // ����߶�
	float _runnerPosX;        // ����λ��(X��)

	Runner *_runner;                           // �������
	BaseManager *_baseManager;       // ���߹������

	// �����ĸ���������ʵ�ֱ����͵����ѭ������
	cocos2d::Sprite *_bgSprite1;           // ��������1
	cocos2d::Sprite *_bgSprite2;           // ��������2
	cocos2d::Sprite *_groundSprite1;    // ���澫��1
	cocos2d::Sprite *_groundSprite2;    // ���澫��2

	cocos2d::Sprite *_pauseButton;      // ��ͣ��ť

	// FORTEST, ���ٰ�ť
	cocos2d::Sprite *_dashButton;

	long _remainedDashTime;  // ʣ�����ʱ�䣬���ڿ��Ƽ���
	bool _isDash;  // �Ƿ�Ϊ���״̬

	bool _timerRunning;  // �Ƿ��ʱ�����Ƽ�ʱ��ǩ�������֣�
	long _accumTime;     // �ۼ�ʱ��

    float _bgMoveSpeed;  // �����ٶȣ������ܶ��ٶȣ�

	unsigned int _countCoins;  // ��Ҽ���
	unsigned int _score;  // �÷ּ���

	// ��ʱ��ǩ
	cocos2d::Label *_timeTextLabel;
	cocos2d::Label *_timeLabel;  

	// �÷ֱ�ǩ
	cocos2d::Label *_scoreTextLabel;
	cocos2d::Label *_scoreLabel;
};

#endif