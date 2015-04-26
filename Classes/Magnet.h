/**
 *  @Date  2015/04/24 14:55
 *  @File  magnet.h 
 *  
 *  @Author LiangJian Liu
 *  @Contact janestar92@163.com
 *  
 *  @brief
 *	
 */


#ifndef _MAGNET_H_
#define  _MAGNET_H_
#include "cocos2d.h"
#include "Base.h"


/************************************************************************/
/* class Magnet is used to generate magnets which gets the coins with animation                                                                     */
/************************************************************************/

class Magnet : public Base{
public:
  virtual bool init();
  void initBody();
  CREATE_FUNC(Magnet);

};




#endif // !_MAGNET_H_
