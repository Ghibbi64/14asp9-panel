#include "ec.h"
using namespace std;

const char* dev_port = "/dev/port";

// ---- EC MEMORY MAPPING ----
const u_int8_t status_port = 0x6C;
const u_int8_t data_port = 0x68;

u_int16_t f0_raw = 0x870E;
u_int16_t f1_raw = 0x870F;

int getRAW(int fan){
    return readxData(!fan ? f0_raw : f1_raw); 
}

int setRAW(int fan, int value){
    if(value < 0 || value > 100){
        return -1;
    }

    return 1;
}

int writexData(u_int16_t addr, u_int8_t value){

    int fd = open(dev_port, O_RDWR);
    if(fd < 0){
        return -1;
    }

    u_int8_t addr_high = (addr >> 8) & 0xFF;
    u_int8_t addr_low  =  addr & 0xFF;
    u_int8_t com = 0x93;

    waitIBF(fd);
    pwrite(fd, &com, 1, status_port);
    waitIBF(fd);
    pwrite(fd, &addr_high, 1, data_port);
    waitIBF(fd);
    pwrite(fd, &addr_low, 1, data_port);
    waitIBF(fd);
    pwrite(fd, &value, 1, data_port);

    return 1;
}

int readxData(u_int16_t addr){
    int fd = open(dev_port, O_RDWR);
    if(fd < 0){
        return -1;
    }

    u_int8_t addr_high = (addr >> 8) & 0xFF;
    u_int8_t addr_low  =  addr & 0xFF;
    u_int8_t com = 0x92;
    u_int8_t res;

    waitIBF(fd);
    pwrite(fd, &com, 1, status_port);
    waitIBF(fd);
    pwrite(fd, &addr_high, 1, data_port);
    waitIBF(fd);
    pwrite(fd, &addr_low, 1, data_port);

    waitOBF(fd);
    pread(fd, &res, 1, data_port);

    return res;
}

void waitIBF(int fd){
    u_int8_t res;
    bool ibf;
    do{
        pread(fd, &res, 1, status_port);
        ibf = (res >> 1) & 1;
    }while(ibf); 
}

void waitOBF(int fd){
    u_int8_t res;
    bool obf;
    do{
        pread(fd, &res, 1, status_port);
        obf = res & 1;
    }while(!obf);
}