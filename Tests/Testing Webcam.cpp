//
// Created by igor on 13/09/2019.
//


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>


#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unistd.h>

using namespace cv;
using namespace std;
static void help()
{
    // print a welcome message, and the OpenCV version
    cout << "\nThis is a demo of Lukas-Kanade optical flow lkdemo(),\n"
            "Using OpenCV version " << CV_VERSION << endl;
    cout << "\nIt uses camera by default, but you can provide a path to video as an argument.\n";
    cout << "\nHot keys: \n"
            "\tESC - quit the program\n"
            "\tr - auto-initialize tracking\n"
            "\tc - delete all the points\n"
            "\tn - switch the \"night\" mode on/off\n"
            "To add/remove a feature point click it\n" << endl;
}

Point2f point;
bool addRemovePt = false;


static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ )
{
    if( event == EVENT_LBUTTONDOWN )
    {
        point = Point2f((float)x, (float)y);
        addRemovePt = true;
    }
}

int main( int argc, char** argv ) {

    VideoCapture cap;
    TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03);
    Size subPixWinSize(10, 10), winSize(31, 31);
    const int MAX_COUNT = 500;
    bool needToInit = false;
    bool nightMode = false;
    help();
    cv::CommandLineParser parser(argc, argv, "{@input|0|}");
    string input = parser.get<string>("@input");
    if (input.size() == 1 && isdigit(input[0]))
        cap.open(input[0] - '0');
    else
        cap.open(input);
    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";
        return 0;
    }
    namedWindow("LK Demo", 1);
    setMouseCallback("LK Demo", onMouse, 0);
    Mat gray, prevGray, image, frame;
    vector<Point2f> points[2];
    for (;;) {


        cap >> frame;
        Mat image3 = imread("projeto.png", 0);
        Mat image2 = imread("projeto2.png", 0);
        cv::resize(image3, image3, Size(50, 500));
        cv::resize(image2, image2, Size(100, 100));

        for (;;) {
            cap >> frame;

            Mat newFrame = frame.clone();

            int cx = (newFrame.cols + 500) / 2;
            int cx2 = (newFrame.cols - 100) / 2;
            int cx3 = (newFrame.cols - 800) / 2;
            int cx4 = (newFrame.cols + 1079) / 2;

            if (!image.empty()) {
                // Get a BGR version of the face, since the output is BGR color
                Mat srcBGR = Mat(image3.size(), CV_8UC4);
                Mat srcBGR2 = Mat(image3.size(), CV_8UC4);
                Mat srcBGR3 = Mat(image3.size(), CV_8UC4);
                Mat srcBGR4 = Mat(image2.size(), CV_8UC4);
                cvtColor(image3, srcBGR, cv::COLOR_GRAY2BGR);
                cvtColor(image3, srcBGR2, cv::COLOR_GRAY2BGR);
                cvtColor(image3, srcBGR3, cv::COLOR_GRAY2BGR);
                cvtColor(image2, srcBGR4, cv::COLOR_GRAY2BGR);
                // Get the destination ROI (and make sure it is within the image)
                Rect dstRC = Rect(cx, (newFrame.rows / 2) - 360, 50, 500);
                Rect dstRC2 = Rect(cx2, (newFrame.rows / 2) - 140, 50, 500);
                Rect dstRC3 = Rect(cx3, (newFrame.rows / 2) - 360, 50, 500);
                Rect dstRC4 = Rect(cx4, (newFrame.rows / 2) - 360, 100, 100);
                Mat dstROI = newFrame(dstRC);
                Mat dstROI2 = newFrame(dstRC2);
                Mat dstROI3 = newFrame(dstRC3);
                Mat dstROI4 = newFrame(dstRC4);
                // Copy the pixels from src to dst.
                srcBGR.copyTo(dstROI);
                srcBGR2.copyTo(dstROI2);
                srcBGR3.copyTo(dstROI3);
                srcBGR4.copyTo(dstROI4);
            }

            if (newFrame.empty())
                break;
            newFrame.copyTo(image);
            cvtColor(image, gray, COLOR_BGR2GRAY);
            if (nightMode)
                image = Scalar::all(0);
            if (needToInit) {
                // automatic initialization
                goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 3, 0, 0.04);
                cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);
                addRemovePt = false;
            } else if (!points[0].empty()) {
                vector<uchar> status;
                vector<float> err;
                if (prevGray.empty())
                    gray.copyTo(prevGray);
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
                                     3, termcrit, 0, 0.001);
                size_t i, k;
                for (i = k = 0; i < points[1].size(); i++) {
                    if (addRemovePt) {
                        if (norm(point - points[1][i]) <= 5) {
                            addRemovePt = false;
                            continue;
                        }
                    }
                    if (!status[i])
                        continue;
                    points[1][k++] = points[1][i];
                    circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
                }
                points[1].resize(k);
            }
            if (addRemovePt && points[1].size() < (size_t) MAX_COUNT) {
                vector<Point2f> tmp;
                tmp.push_back(point);
                cornerSubPix(gray, tmp, winSize, Size(-1, -1), termcrit);
                points[1].push_back(tmp[0]);
                addRemovePt = false;
            }
            needToInit = false;
            imshow("LK Demo", image);
            char c = (char) waitKey(10);
            if (c == 27)
                break;
            switch (c) {
                case 'r':
                    needToInit = true;
                    break;
                case 'c':
                    points[0].clear();
                    points[1].clear();
                    break;
                case 'n':
                    nightMode = !nightMode;
                    break;
            }
            std::swap(points[1], points[0]);
            cv::swap(prevGray, gray);
        }
        return 0;
    }
}
