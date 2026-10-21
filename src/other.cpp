#include "other.h"

int getCameraPrivacy(){

    int fd = open("/dev/video0", O_RDWR);

    v4l2_control ctrl{};
    ctrl.id = V4L2_CID_PRIVACY;

    ioctl(fd, VIDIOC_G_CTRL, &ctrl);

    return ctrl.value;
}