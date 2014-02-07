#ifndef 	__GW_GAME_STATE_H__
#define		__GW_GAME_STATE_H__
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "gwControl.h"
#include <string>
namespace GW{
class GameState{
public:
    GameState( );
    ~GameState( );
    void createScene (const std::string& scene_name);
    void initControl(Control* controller);


    inline Ogre::SceneManager* getScene( ) const{
        return _scene_manager;
    };
    inline const std::string& getSceneName( ) const{
        return _scene_name;
    };
    inline Control* getController( ) const{
        return _controller;
    };

    virtual void enter() = 0;
    virtual void exit() = 0;
    virtual void update(double timeSinceLastFrame) = 0;
private:
    Control* _controller;
    Ogre::SceneManager* _scene_manager;
    std::string _scene_name;
};

}

#endif	//__GW_GAME_STATE_H__
