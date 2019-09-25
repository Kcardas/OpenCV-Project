
#ifndef LABIRYNTH_LABIRYNTH_H
#define LABIRYNTH_LABIRYNTH_H

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

//#include "Fases.h"

using namespace cv;
using namespace std;

static Mat fase1(Mat image2, Mat image3, Mat frame );

static Mat fase2(Mat image2, Mat image3, Mat frame );

static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ );

class Labirynth {
public:
    Labirynth(int argc, char** argv);
};

#endif
