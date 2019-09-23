
#include "Labirynth.h"
#include "Menu.h"
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using std::cout;
using std::cin;
using namespace std;
using namespace cv;

int main( int argc, char** argv ){
    VideoCapture cap;
    char key;

    while(1){
        Menu(key, cap);

        if (key == 49){
            cap.release();
            //destroyWindow("Labirynth");
            Labirynth(argc, argv);
        }else break;
    }

    return 0;
}