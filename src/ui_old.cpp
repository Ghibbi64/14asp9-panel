#include "ui_old.h"
#include "ec.h"
#include "other.h"

using namespace std;

void showInfo(){
    int f0[6];
    int f1[6];

    getFanInfos(0, f0);
    getFanInfos(1, f1);

    cout<<"RPM\tDUTY\tMAN\tRAW\tPWM\tTACH\n";
    for(int i=0; i<6; i++){
        cout<<f0[i]<<"\t";
    }
    cout<<"\n";
    for(int i=0; i<6; i++){
        cout<<f1[i]<<"\t";
    }
    cout<<"\n";

    int temps[8];

    getTemps(temps);

    cout<<"\tFILTR\tRAW\n";
    cout<<"1 -\t"<<temps[0]<<"\t"<<temps[2]<<"\n";
    cout<<"2 -\t"<<temps[1]<<"\t"<<temps[3]<<"\n";
    // Idk these doesn't seems to be useful
    //cout<<"3 -\t"<<temps[2]<<"\t"<<temps[6]<<"\n"; 
    //cout<<"4 -\t"<<temps[3]<<"\t"<<temps[7]<<"\n\n";

    cout<<"\nCAMERA PRIVACY: "<<getCameraPrivacy()<<"\n";
    cout<<"KEYBOARD BRIGHTNESS: "<<getKeyBright()<<"\n";

}