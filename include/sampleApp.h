#ifndef		_SAMPLE_APP_H__
#define		_SAMPLE_APP_H__
#include "gwApp.h"

class sampleApp : GW::App{
public:
    inline static sampleApp*	getSingleton(){
        if (_self) return reinterpret_cast<sampleApp*>(_self);
        else {
            _self = new char[sizeof(sampleApp)];
            new (_self) sampleApp();
            return reinterpret_cast<sampleApp*>(_self);
        }
    }
    void createScene();
};

#endif		//_SAMPLE_APP_H__
