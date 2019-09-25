#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using namespace std;

class Menu {
public:
    Menu(char &key, cv::VideoCapture &cap);
};

#endif
