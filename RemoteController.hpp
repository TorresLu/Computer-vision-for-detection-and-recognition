#pragma once
#include "Settings.hpp"
#include "cmdline.h"

class RemoteController {
public:
    RemoteController(Settings * setting, OtherParam * _other_param, int fd2car){
        settings = setting;
        other_param = _other_param;
        fd_car = fd2car;
    }
    void paraReceiver();
    void praseDatafromCar();
    void praseData(const char * data, int size);
    int fd_car;
    Settings * settings;
    OtherParam * other_param;
};

