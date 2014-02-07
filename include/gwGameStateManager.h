#ifndef 		_GW_GAME_STATE_MANAGER_H__
#define			_GW_GAME_STATE_MANAGER_H__
#include <gwGameState.h>
#include <OgreRenderWindow.h>
namespace GW{
typedef std::map <const std::string, GameState*> States;
const char MainCameraName[]="Camera";
class StateManager{
private:
    States _states;
    GameState* _current_state;
    GameState* _prev_state;
public:
    StateManager ( );
    ~StateManager( );
    GameState*          createState     ( const std::string& state_name );
    GameState*          changeState     ( const std::string& state_name, Ogre::RenderWindow* window );
    GameState*          getCurrState    ( );
    GameState*          getPrevState    ( );
};
}

#endif			//_GW_GAME_STATE_MANAGER_H__
