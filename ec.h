#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>

char* dev_port = "/dev/port";

// ---- EC MEMORY MAPPING ----
u_int8_t status_port = 0x6C;
u_int8_t data_port = 0x68;

u_int16_t f0_raw = 0x870E;
u_int16_t f1_raw = 0x870F;

int setRAW(int fan, int value);
int writexData(u_int16_t addr, u_int8_t value);
int readxData(u_int16_t addr);
void waitIBF(int fd);
void waitOBF(int fd);