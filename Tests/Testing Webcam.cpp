#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){
    VideoCapture cap;
    cap.open(0);

    if(!cap.isOpened()){
        cerr << "Error opening the webcam!" << endl;
        return -1;
    }
    Mat image = imread("projeto.png",0);
    Mat image2 = imread("projeto2.png",0);
    cv::resize(image,image,Size(50,500));
    cv::resize(image2,image2,Size(100,100));
    Mat frame;
    for(;;){
        cap>>frame;

        Mat newFrame=frame.clone();


        int cx = (newFrame.cols + 500) / 2;
        int cx2 = (newFrame.cols - 100) / 2;
        int cx3 = (newFrame.cols - 800) / 2;
        int cx4 = (newFrame.cols + 1079) / 2;

        if (!image.empty()) {
            // Get a BGR version of the face, since the output is BGR color
            Mat srcBGR = Mat(image.size(), CV_8UC4);
            Mat srcBGR2 = Mat(image.size(), CV_8UC4);
            Mat srcBGR3 = Mat(image.size(), CV_8UC4);
            Mat srcBGR4 = Mat(image2.size(), CV_8UC4);
            cvtColor(image, srcBGR, cv::COLOR_GRAY2BGR);
            cvtColor(image, srcBGR2, cv::COLOR_GRAY2BGR);
            cvtColor(image, srcBGR3, cv::COLOR_GRAY2BGR);
            cvtColor(image2, srcBGR4, cv::COLOR_GRAY2BGR);
            // Get the destination ROI (and make sure it is within the image)
            Rect dstRC = Rect(cx, (newFrame.rows/2) - 360, 50, 500);
            Rect dstRC2 = Rect(cx2, (newFrame.rows/2) - 140, 50, 500);
            Rect dstRC3 = Rect(cx3, (newFrame.rows/2) - 360, 50, 500);
            Rect dstRC4 = Rect(cx4, (newFrame.rows/2) - 360, 100, 100);
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

        imshow("frame", newFrame);
        char key = (char) waitKey(30);
        // Exit this loop on escape:
        if(key == 27)
            break;
    }

    return 0;
}
