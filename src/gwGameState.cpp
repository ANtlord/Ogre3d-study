#include "gwGameState.h"
namespace GW{
GameState::GameState( ){
    _controller = NULL;
    _scene_manager = NULL;
    _scene_name.clear();
}

GameState::~GameState( ){
    Ogre::Root::getSingletonPtr()->destroySceneManager(_scene_manager);
}

void GameState::createScene (const std::string& scene_name){
    _scene_manager = Ogre::Root::getSingletonPtr()->createSceneManager("DefaultSceneManager", _scene_name = scene_name );
}

void GameState::initControl(Control* controller){
    _controller = controller;
}
}
