#ifndef OTH_H
#define OTH_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <linux/videodev2.h>
#include <sys/ioctl.h>

int getCameraPrivacy();
int getKeyBright();
int setKeyBright(int level);

#endif