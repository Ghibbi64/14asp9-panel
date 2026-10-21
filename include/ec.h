#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>

int getRAW(int fan);
int setRAW(int fan, int value);
int writexData(u_int16_t addr, u_int8_t value);
int readxData(u_int16_t addr);
void waitIBF(int fd);
void waitOBF(int fd);