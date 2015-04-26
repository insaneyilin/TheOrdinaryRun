/**
 *  @Date  2015/04/04 10:55
 *  @File  BaseManager.h 
 *  
 *  @Author LiangJian Liu
 *  @Contact janestar92@163.com
 *  
 *  @brief
 *	
 */
#ifndef __BaseManager__H__
#define __BaseManager__H__

#include "cocos2d.h"
#include "Coin.h"
#include "Rock.h"
#include "Accelerator.h"
#include "magnet.h"
#include "Runner.h"


USING_NS_CC;


enum PROPERTY
{
	coinNum = 4,
	coinTag = 2,
	rockNum = 2,
	rockTag = 3,
	accleratorTag = 4,
	magnetTag = 5,
	ground_hight = 59,
	LARGE_NUM = 1000000,//用于将移出屏幕的障碍物 金币等设置为不可见
};



/************************************************************************/
/* 基本管理类，用于管理各类道具，包括障碍物 金币 加速器等                                                                     */
/************************************************************************/
class BaseManager : public cocos2d::Node
{
public:
	CREATE_FUNC(BaseManager);
	virtual bool init();
	virtual void update(float dt);

private:
	/**
	 * @brief 道具的初始化
	 * @note 
	 */
	void manageObject(Size&,Vec2&);
	
	Vector<Coin*> _coinVec;
	Vector<Rock*> _rockVec;
	Accelerator* _acclerator;
	Magnet* _magnet;
	Runner* runner;
	float _randTime;
	int _coinCount;
	int _rockCount;

	float _bgMoveSpeed;

public:

	/**
	 * @brief   use magnet to get the coins
	 */
	void getCoinsByMagnet(Runner* runner);


	void setBgMoveSpeed(float speed)
	{
		_bgMoveSpeed = speed;
	}

	float getBgMoveSpeed() const
	{
		return _bgMoveSpeed;
	}

	void setCoinCount(int x)
	{
		this->_coinCount=x;
	}

	int getCoinCount() const
	{
		return this->_coinCount;
	}

	void setRockCount(int x)
	{
		this->_rockCount=x;
	}

	int getRockCount() const
	{
		return this->_rockCount;
	}

};

#endif