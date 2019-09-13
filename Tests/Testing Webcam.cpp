#include <opencv2/opencv.hpp>
#include <iostream>

int main(){

  cv::Mat frame;
  cv::VideoCapture myVideo(0);

  //bool choice = false;

  if(!myVideo.isOpened()){
    std::cout << "Unable to open!\n";
    return -1;
  }

  while(myVideo.read(frame)){
    cv::imshow("Webcam", frame);

    //std::cin >> choice; *Buga a webcam, nem abre a janela. Então tem que usar o waitkey mesmo.

    //if(choice){
    //break;
    //}

    if(cv::waitKey(10) >= 0){ //Para a captura de imagem quando digitado qualquer coisa.
      break;
    }
  }

  std::cout << "It worked!\n";

  return 0;
}
