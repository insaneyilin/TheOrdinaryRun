/**
 *  @Date  2015/04/23 10:44
 *  @File  Accelerator.h 
 *  
 *  @Author LiangJian Liu
 *  @Contact janestar92@163.com
 *  
 *  @brief
 *	
 */

#ifndef __ACCELERATOR__H__
#define __ACCELERATOR__H__

#include "Base.h"
#include "cocos2d.h"


class Accelerator : public Base{
public:
	virtual bool init();
	void initBody();
	cocos2d::Animate* createAnimate(cocos2d::SpriteFrameCache* frameCache);
	CREATE_FUNC(Accelerator);

}; 



#endif