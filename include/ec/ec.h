#ifndef EC_H
#define EC_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>

int getFanInfos(int fan, int* arr);
int getTemps(int* arr);
int getRAW(int fan);
int setRAW(int fan, int value);
int setAuto();
int command(u_int8_t command, u_int8_t value);
int writexData(u_int16_t addr, u_int8_t value);
int readxData(u_int16_t addr);
void waitIBF(int fd);
void waitOBF(int fd);

#endif