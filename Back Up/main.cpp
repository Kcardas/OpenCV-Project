#include "Labirynth.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using std::cout;
using std::cin;
using namespace std;
using namespace cv;

int main( int argc, char** argv ){
  VideoCapture cap;
    cap.open(0);
    char key;

    if(!cap.isOpened()){
        cerr << "Erro ao abrir webcam" << endl;
        return -1;
    }

    Mat image = imread("projeto3.png", 0);
    cv::resize(image, image, Size(1280, 720));
    Mat frame;

    while(1){

            cap >> frame;
            Mat newFrame = frame.clone();

            if (!image.empty()) {

                Mat srcBGR = Mat(image.size(), CV_8UC3);

                cvtColor(image, srcBGR, cv::COLOR_GRAY2BGR);

                Rect dstRC = Rect(0, 0, 1280, 720);

                Mat dstROI = newFrame(dstRC);

                srcBGR.copyTo(dstROI);
            }

            imshow("frame", newFrame);

            key = (char) waitKey(30);

        // Exit this loop on escape:
        if(key == 27)
            break;

        if (key == 49)
            break;

        if(key == 48)
            break;

    }

    if (key == 49){
        cap.release();
        destroyWindow("frame");
        Labirynth(argc, argv);
    }

  return 0;
}
