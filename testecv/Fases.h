#ifndef FASES_FASES_H
#define FASES_FASES_H

using namespace cv;

class Fases {
private:
    Mat image3;
    Mat image2;
    Mat newFrame;
public:
    Fases(){}
    Fases(Mat image2, Mat image3, int i, Mat frame){
        if(i){
            newFrame = frame.clone();
            int cx = (newFrame.cols + 500) / 2;
            int cx2 = (newFrame.cols - 100) / 2;
            int cx3 = (newFrame.cols - 800) / 2;
            int cx4 = (newFrame.cols + 1079) / 2;
            // Get a BGR version of the face, since the output is BGR color
            Mat srcBGR = Mat(image3.size(), CV_8UC3);
            Mat srcBGR2 = Mat(image3.size(), CV_8UC3);
            Mat srcBGR3 = Mat(image3.size(), CV_8UC3);
            Mat srcBGR4 = Mat(image2.size(), CV_8UC3);
            cvtColor(image3, srcBGR, cv::COLOR_GRAY2BGR);
            cvtColor(image3, srcBGR2, cv::COLOR_GRAY2BGR);
            cvtColor(image3, srcBGR3, cv::COLOR_GRAY2BGR);
            cvtColor(image2, srcBGR4, cv::COLOR_GRAY2BGR);
            // Get the destination ROI (and make sure it is within the image)
            Rect dstRC = Rect(cx, (newFrame.rows / 2) - 140, 50, 500);
            Rect dstRC2 = Rect(cx2, (newFrame.rows / 2) - 360, 50, 500);
            Rect dstRC3 = Rect(cx3, (newFrame.rows / 2) - 140, 50, 500);
            Rect dstRC4 = Rect(cx4, (newFrame.rows / 2) + 260, 100, 100);
            Mat dstROI = newFrame(dstRC);
            Mat dstROI2 = newFrame(dstRC2);
            Mat dstROI3 = newFrame(dstRC3);
            Mat dstROI4 = newFrame(dstRC4);
            // Copy the pixels from src to dst.
            srcBGR.copyTo(dstROI);
            srcBGR2.copyTo(dstROI2);
            srcBGR3.copyTo(dstROI3);
            srcBGR4.copyTo(dstROI4);
        }else if(i == 2){
            Mat newFrame = frame.clone();
            int cx = (newFrame.cols + 500) / 2;
            int cx2 = (newFrame.cols - 100) / 2;
            int cx3 = (newFrame.cols - 800) / 2;
            int cx4 = (newFrame.cols + 1079) / 2;
            // Get a BGR version of the face, since the output is BGR color
            Mat srcBGR = Mat(image3.size(), CV_8UC3);
            Mat srcBGR2 = Mat(image3.size(), CV_8UC3);
            Mat srcBGR3 = Mat(image3.size(), CV_8UC3);
            Mat srcBGR4 = Mat(image2.size(), CV_8UC3);
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
    };
    Mat retornarFrame(){
        return newFrame;
    }
};

#endif