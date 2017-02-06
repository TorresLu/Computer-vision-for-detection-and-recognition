#pragma once

enum DATATYPE { IMAGE, INFO};

int openPort(const char * dev_name);
int configurePort(int fd);
bool sendXYZ(int fd, double * xyz);
bool sendData(int fd, char * data, int size, DATATYPE data_tpye);
