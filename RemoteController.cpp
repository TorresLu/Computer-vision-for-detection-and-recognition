#include "RemoteController.hpp"
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void RemoteController::paraReceiver(){
    while(1){
        praseDatafromCar();
        usleep(1000);
    }
}

void RemoteController::praseDatafromCar(){
    char buf[255]={0};
    size_t bytes = 0;
    ioctl(fd_car, FIONREAD, &bytes);
    if(bytes > 0 && bytes < 255)
        bytes = read(fd_car, buf, bytes);
    else if(bytes >= 255)
        bytes = read(fd_car, buf, 255);
    else
        return;

    praseData(buf, bytes);
}

void RemoteController::praseData(const char * data, int size){
    if(size < 4)
        return;
    int start = 0;
    while(1){
        if (start >= size - 3)
            return;
        if(data[start] == 0xFF && data[start+3] == 0xFE){
            break;
        }
        ++start;
    }
    ++start;

    uchar cmd1 = (uchar) data[start];
    uchar cmd2 = (uchar) data[start+1];

    switch(cmd1){
    case 0:{
        settings->mode = ARMOR_MODE; // armor
        settings->armor.enemy_color = cmd2;
        std::cout << "para->enemy_color:" << (int)settings->armor.enemy_color << "\tmode:" << settings->mode << '\n';
        break;
    }
    case 1:{
        settings->mode = RUNE_MODE; // rune
        break;
    }
    case 2:{                        // pitch angle
        int a = 0;
        a |= (0x7f & cmd2);
        a = (0x80 & (cmd2)) == 0 ? a : a | 0xffffff80;
        other_param->angle_pitch = (int)a / 4.0;
        //std::cout << "angle_pitch:" << other_param->angle_pitch << '\n';
        break;
    }
    case 3:{
        settings->mode = 2; // stop
        break;
    }
    default:
        settings->mode = 2; // stop
    }


    ++start;  // idx of FE
    if (start + 1 < size){
        praseData(data + start + 1, size - start - 1);
    }
}
