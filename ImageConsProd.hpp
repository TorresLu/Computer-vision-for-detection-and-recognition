#pragma once
#include "opencv2/opencv.hpp"
#include "ArmorDetector.hpp"
#include "Settings.hpp"

class ImageConsProd {
public:
    ImageConsProd(Settings * _settings, OtherParam * _other_param, int fd_car){
        settings = _settings;
        other_param = _other_param;
        fd2car = fd_car;
    }
    void ImageProducer();
    void ImageConsumer();

public:
    Settings * settings;
    OtherParam * other_param;
    int fd2car;
};

