#include "ec.h"
using namespace std;

const char* dev_port = "/dev/port";

// ---- EC MEMORY MAPPING ----
const u_int8_t status_port = 0x6C;
const u_int8_t data_port = 0x68;

u_int16_t f0_rpm_hi = 0x8700;
u_int16_t f0_rpm_low = 0x8701;
u_int16_t f0_duty = 0x8704;
u_int16_t f0_man = 0x870C;
u_int16_t f0_raw = 0x870E;
u_int16_t f0_pwm = 0x1804;
u_int16_t f0_tach_low = 0x181E;
u_int16_t f0_tach_hi = 0x181F;

u_int16_t f1_rpm_hi = 0x8702;
u_int16_t f1_rpm_low = 0x8703;
u_int16_t f1_duty = 0x8705;
u_int16_t f1_man = 0x870D;
u_int16_t f1_raw = 0x870F;
u_int16_t f1_pwm = 0x1805;
u_int16_t f1_tach_low = 0x1820;
u_int16_t f1_tach_hi = 0x1821;

u_int16_t filtered_temp[2] = {0x8721, 0x8725};
u_int16_t raw_temp[2] = {0x8720, 0x8724};


int getFanInfos(int fan, int* arr){
    u_int8_t rpm_hi = readxData(!fan ? f0_rpm_hi : f1_rpm_hi);
    u_int8_t rpm_low = readxData(!fan ? f0_rpm_low : f1_rpm_low);
    arr[0] = (rpm_hi << 8) | rpm_low ;
    arr[1] = readxData(!fan ? f0_duty : f1_duty); 
    arr[2] = readxData(!fan ? f0_man : f1_man); 
    arr[3] = readxData(!fan ? f0_raw : f1_raw); 
    arr[4] = readxData(!fan ? f0_pwm : f1_pwm); 
    u_int8_t tach_hi = readxData(!fan ? f0_tach_hi : f1_tach_hi);
    u_int8_t tach_low = readxData(!fan ? f0_tach_low : f1_tach_low);
    arr[5] = (tach_hi << 8) | tach_low ;

    return 0;
}

int getTemps(int* arr){
    for(int i=0; i<4; i++)
        arr[i] = readxData(filtered_temp[i]);
    for(int i=4; i<8; i++)
        arr[i] = readxData(raw_temp[i]);

    return 0;
}

int setAuto(){
    command(0xD5, 0x10);
    setRAW(0, 0);
    setRAW(1, 0);
    return 1;
}

int setRAW(int fan, int value){
    return writexData(!fan ? f0_raw : f1_raw, value);
}

int getRAW(int fan){
    return readxData(!fan ? f0_raw : f1_raw); 
}

int command(u_int8_t command, u_int8_t value){
    int fd = open(dev_port, O_RDWR);
    if(fd < 0){
        return -1;
    }

    waitIBF(fd);
    pwrite(fd, &command, 1, status_port);
    waitIBF(fd);
    pwrite(fd, &value, 1, data_port);

    close(fd);
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

    close(fd);
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

    close(fd);
    return res;
}

void waitIBF(int fd){
    u_int8_t res;
    bool ibf = 1;
    for(int i=0; i<100000 && ibf; i++){
        pread(fd, &res, 1, status_port);
        ibf = (res >> 1) & 1;
    }
}

void waitOBF(int fd){
    u_int8_t res;
    bool obf = 0;
    for(int i=0; i<100000 && !obf; i++){
        pread(fd, &res, 1, status_port);
        obf = res & 1;
    }
}