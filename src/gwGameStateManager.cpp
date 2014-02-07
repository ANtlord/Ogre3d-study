#include "gwGameStateManager.h"
#include <stddef.h>
namespace GW{
StateManager::StateManager ( ){
    _current_state  = NULL;
    _prev_state     = NULL;
}

StateManager::~StateManager( ){
    for (auto it = _states.begin(); it != _states.end(); ++it)
        delete (it->second);
    _states.clear();
}

GameState*          StateManager::createState( const std::string& state_name ){
    return  _states[state_name] = new GameState;
}

GameState*          StateManager::changeState     ( const std::string& state_name, Ogre::RenderWindow* window ){
    _prev_state = _current_state;
    _current_state = _states[state_name];
    window->removeAllViewports();
    Ogre::Camera* camera = _current_state->getScene()->getCamera(MainCameraName);
    Ogre::Viewport* vp = _window->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));
    camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    return _current_state
}

GameState*          StateManager::getPrevState    ( ){
    return _prev_state;
}
}
