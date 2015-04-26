/**
 *  @Date  2015/04/04 12:35
 *  @File  BaseManager.cpp 
 *  
 *  @Author LiangJian Liu
 *  @Contact janestar92@163.com
 *  
 *  @brief
 *	
 */

#include "BaseManager.h"


USING_NS_CC;

/************************************************************************/
/* shape 数组用于设定几种金币的摆放形状                                                                     */
/************************************************************************/
int shape[5][4][4] = 
{
	{ 0, 0, 0, 0,
	  0, 1, 1, 0,
	  0, 1, 1, 0,
	  0, 0, 0, 0 },

	{ 0, 1, 1, 1,
      0, 0, 1, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 },

    { 0, 1, 1, 0,
      0, 0, 1, 0,
      0, 0, 1, 0,
      0, 0, 0, 0},

    { 0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 },
	{ 0, 0, 0, 0,
	  0, 0, 0, 0,
	  0, 0, 0, 0,
	  1, 1, 1, 1 }

};

bool BaseManager::init()
{
	if ( !Node::init() )
	{
		return false;
	}
	auto size=Director::getInstance()->getVisibleSize();
	auto origin=Director::getInstance()->getVisibleOrigin();

	manageObject(size, origin);
	this->setCoinCount(0);
	this->setRockCount(0);
	this->scheduleUpdate();

	return true;
}



void BaseManager::manageObject(Size &size, Vec2 &origin)
{
	srand((unsigned int)time(0)); //设置随机种子
	//设置加速器的初始位置
    _acclerator = Accelerator::create();
	_acclerator->setTag(accleratorTag);
	auto acclerator_width =_acclerator->getConSize().width;
	auto acclerator_height = _acclerator->getConSize().height;
	float _initposx = origin.x + size.width*3 +random(0,(int)size.width);
	float _initposy = ground_hight + acclerator_height/2 + random(0,50);
	_acclerator->setPosition(Vec2(_initposx,_initposy));
	this->addChild(_acclerator);

    //设置障碍物的初始位置
	int xcoordinate = origin.x + size.width;
	for (int i = 1; i <= rockNum; ++i)
	{   Rock *rock = nullptr;
		rock = Rock::create();
		rock->setTag(rockTag);
		rock->setPosition( xcoordinate,ground_hight+
			rock->getConSize().height/2);
		this->addChild(rock);
		int gap = random(0,static_cast<int>(size.width)) +size.width/3;
		xcoordinate += gap;
		_rockVec.pushBack(rock);
		
	}

	//设置金币的初始位置
	Coin *coin = Coin::create();
	auto _coinx = coin->getConSize().width;
	auto _coiny = coin->getConSize().height;
	//设置金币锚点的随机x y坐标
	int randx = (int)(size.width + random(0,static_cast<int>(size.width*4/3)));
	int randy = (int)( random(0,10)+ ground_hight+_coiny/2);

	int rock_x = _rockVec.at(0)->getPositionX(); //第一个障碍物的x坐标
	int rock_x2 = _rockVec.at(1)->getPositionX(); //第二个障碍物的x坐标
	int rock_height =_rockVec.at(0)->getConSize().height;
	
	//如果金币的锚点的x坐标使得整个金币范围与障碍物的x坐标有可能重叠，
	//则将金币的y坐标设为障碍物y坐标之上
	if ( !( ( randx + 4 * _coinx *1.5 < ( rock_x - _rockVec.at(0)->getConSize().width / 2 ) ) || 
		      randx>rock_x2+_rockVec.at(1)->getConSize().width/2 ) )
	{
		randy = ground_hight + 
			_rockVec.at(1)->getConSize().height + coin->getConSize().height / 2+random(0,10);
	} 
	
	int num = random(0,4);
	//CCLOG("the num is %d",num);
	for (int j = 3; j >= 0; --j)
	{
		for (int k = 0; k <= 3; ++k)
		{
			if ( shape[num][j][k] )
			{
				Coin* _coin = Coin::create();
				_coin->setPosition( 
					Vec2(randx + k * _coinx *1.5, randy + (3 - j)*_coiny * 1.5) );
				_coin->setTag(coinTag);
				this->addChild(_coin);
				_coinVec.pushBack(_coin);
		
			}
		}
	}
	//设置磁铁的位置
	_magnet = Magnet::create();
	_magnet->setTag(magnetTag);
	auto _magnet_height = _magnet->getConSize().height;
	_magnet->setPosition(Vec2(randx-50,ground_hight + rock_height+ _magnet_height/2
		+random(0,10) ));
	this->addChild(_magnet);
	

}


void BaseManager::getCoinsByMagnet(Runner* runner){

	for(auto coin : _coinVec){
		if(coin->getPositionX()>coin->getConSize().width/2){
			Vec2 pos = runner->getPhysicsBody()->getPosition();
			auto actionTo = MoveTo::create(0.6,pos);
			coin->runAction(actionTo);
		}
	}
}

void BaseManager::update(float dt)
{  
	auto size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	if(_acclerator->getPositionX() < _acclerator->getConSize().width/2 * (-1))
	{
		_acclerator->setVisible(false);
		_acclerator->setPosition(Vec2(LARGE_NUM,320));
	}
	else{
		_acclerator->setPositionX(_acclerator->getPositionX() - _bgMoveSpeed);
	}

	if(_magnet->getPositionX() < _magnet->getConSize().width/2 * (-1))
	{
		_magnet->setVisible(false);
		_magnet->setPosition(Vec2(LARGE_NUM,320));
	}
	else{
		_magnet->setPositionX(_magnet->getPositionX() - _bgMoveSpeed);
	}


	for (auto coin : _coinVec)
	{
		if ( coin->getPositionX() < coin->getConSize().width / 2 * (-1) )
		{
			coin->setVisible(false);
			coin->setPosition( Vec2(LARGE_NUM, 320) );

			if (_coinCount < 4)
			{
				++_coinCount;
			}
		}
		else
		{
			coin->setPositionX(coin->getPositionX() - _bgMoveSpeed);
		}
	}

	for(auto rock : _rockVec)
	{
		if( rock->getPositionX() < rock->getConSize().width / 2 * (-1) )
		{
			rock->setVisible(false);
			rock->setPosition( Vec2(LARGE_NUM, 300) );
			if(_rockCount<2)
				_rockCount++;
		}
		else
		{
			rock->setPositionX(rock->getPositionX() - _bgMoveSpeed);
		}
	}
	//如果金币和障碍物还有加速器全部都移出屏幕外了，再重新开始设置他们的位置
	if (_rockCount == 2 && _coinCount == 4&&!_acclerator->isVisible())
	{
		int xcoordinate = size.width + size.width / 2;
		for (auto rock : _rockVec)
		{
			rock->setPosition(xcoordinate,ground_hight+rock->getConSize().height/2);
			int gap = CCRANDOM_0_1() *size.width + size.width/3;
			xcoordinate+=gap;
			rock->setVisible(true);
		}
		int rock_x = _rockVec.at(0)->getPositionX();
		int rock_x2 = _rockVec.at(1)->getPositionX();
		
		int rock_height = _rockVec.at(0)->getConSize().height;
		int rock_width = _rockVec.at(0)->getConSize().width;
		
		auto coin_height = _coinVec.at(0)->getConSize().height;
		auto coin_width = _coinVec.at(0)->getConSize().width;
		auto randx = (int)(CCRANDOM_0_1() * size.width + size.width);
		auto randy = (int)( CCRANDOM_0_1() * 20 + ground_hight + coin_height/2);
		
		if ( !( ( randx + 4 * coin_width*1.5 < (rock_x-rock_width/2 )) || 
			      randx > rock_x2 + rock_width / 2 ) )
		{
			randy = ground_hight + rock_height+ coin_height/2 +CCRANDOM_0_1()*10;

		} 
		int num = CCRANDOM_0_1() * 4;
		int cnt = 0;
		for (int j = 3; j >= 0; --j)
		{
			for (int k = 0; k <= 3; ++k)
			{
				if ( shape[num][j][k] )
				{
					auto coin = _coinVec.at(cnt);
					coin->setPosition( 
						Vec2(randx + k * coin_width*1.5, randy + (3 - j)*coin_height*1.5) );
					coin->setVisible(true);
					++cnt;
				}
			}
		}
		auto magnet_height = _magnet->getConSize().height;
		auto flag = CCRANDOM_0_1();
		if(flag>0.5)
		{
		_magnet->setPosition(Vec2(randx-40,ground_hight+magnet_height/2+rock_height+CCRANDOM_0_1()*10));
		_magnet->setVisible(true);
		}
	    else{
			_magnet->setPosition(Vec2(randx+coin_width*6+40,ground_hight+magnet_height/2+rock_height+CCRANDOM_0_1()*10));
			_magnet->setVisible(true);

	     }

		auto acclerator_height = _acclerator->getConSize().height;
		float _initposx = origin.x + size.width*4 +random(0,(int)size.width);
		float _initposy = ground_hight + acclerator_height/2 + random(0,50);
		_acclerator->setPosition(Vec2(_initposx,_initposy));
		_acclerator->setVisible(true);

		_rockCount = 0;
		_coinCount = 0;
	}
	

}
