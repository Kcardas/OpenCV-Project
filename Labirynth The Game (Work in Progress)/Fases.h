#ifndef FASES_FASES_H
#define FASES_FASES_H

using namespace cv;

class Fases {
private:
  Mat image3;
  Mat image2;
public:
  Fases(Mat* x, Mat* y, int i){
    if(i){
      image3 = imread("projeto.png", 0);
      image2 = imread("projeto2.png", 0);
      cv::resize(image3, image3, Size(50, 500));
      cv::resize(image2, image2, Size(100, 100));

      *x = image3;
      *y = image2;
    }
  };
  /*void fase1(Mat* x, Mat* y) {
    //cap >> frame;
    //Mat image3 = imread("projeto.png", 0);
    //Mat image2 = imread("projeto2.png", 0);
    cv::resize(image3, image3, Size(50, 500));
    cv::resize(image2, image2, Size(100, 100));

    *x = image3;
    *y = image2;
  }*/
};

#endif
