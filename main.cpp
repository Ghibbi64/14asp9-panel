#include<iostream>
#include<cstdlib>
#include <cstring>
#include <sys/wait.h>
#include "ec/ec.h"
#include "ui_old.h"
#include "ec/other.h"

using namespace std;

int main(int argc, char** argv){

    // Lenovo Yoga Pro 7 14asp9 EC Debug Utility (ITE5571)

    if(!strcmp(argv[1], "--help") || !strcmp(argv[1], "help") || !strcmp(argv[1], "-help")){
        cout<<"Lenovo Yoga Pro 7 Debug Utility\n";
        cout<<"Usage:\n";
        cout<<"FAN SPEED: fan speed can be manually set for both fans\n";
        cout<<"--fan0 speed\t\tSet speed of fan0 [0-100]\n";
        cout<<"--fan1 speed\t\tSet speed of fan0 [0-100]\n";
        cout<<"--fans speed\t\tSet speed of both fans [0-100]\n";
        cout<<"--auto\t\t\tReturn control to the EC\n";
    }
    else if(!strcmp(argv[1], "--fans")){
        if(argc<=2)
            cout<<"Sintax error: did you specify the speed?\n";
        else{
            setRAW(0, atoi(argv[2]));
            setRAW(1, atoi(argv[2]));
        }
    }
    else if(!strcmp(argv[1], "--auto")){
        setAuto();
    }
    else if(!strcmp(argv[1], "--probe")){
        showInfo();
    }
    else if(!strcmp(argv[1], "--backlight")){
        setKeyBright(atoi(argv[2]));
    }
    else{
        cout<<"Sintax error: use --help to guide yourself\n";
    }

}