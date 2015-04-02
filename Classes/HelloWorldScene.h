/**
 * @file HelloWorldScene.h
 * @date 2015/04/01
 *
 * @author Yilin Gui
 * Contact: yilin.gui@gmail.com
 *
 * @brief  Definition of the "Main Menu" Scene class
 * 
 * TODO: 
 *
 */

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
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
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _centerPoint;

	/**
	 * @brief    Load an image and create the background
	 */
	void createBackGround();

	/**
	 * @brief    Create buttons of the main menu
	 * @param [in] pt    Position of the button to be created
	 */
	void createButton(const cocos2d::Vec2& pt);

	/**
	 * @brief    Load background music and other sound files
	 */
	void preLoadMusic();

	/**
	 * @brief    start the game
	 */
	void startGame();
};

#endif // __HELLOWORLD_SCENE_H__
