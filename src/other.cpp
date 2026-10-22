#include "other.h"
#include "ec.h"

int getCameraPrivacy(){

    int fd = open("/dev/video0", O_RDWR);

    v4l2_control ctrl{};
    ctrl.id = V4L2_CID_PRIVACY;

    ioctl(fd, VIDIOC_G_CTRL, &ctrl);

    close(fd);
    return ctrl.value;
}

int getKeyBright(){
    u_int8_t res = readxData(0x83AB);

    switch(res){
        case 0x03: return 0; break;
        case 0x13: return 1; break;
        case 0x23: return 2; break;
        case 0x33: return 3; break;
        default: return -1;
    }
}

int setKeyBright(int level){
    writexData(0x83AB, 0x03 + (0x10 * level));
    return 1;
}