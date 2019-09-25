#include "Labirynth.h"

using namespace cv;
using namespace std;

Point2f point;//point2f é um array de pontos em float
bool addRemovePt = false;//flag pra saber se pracisa adicionar ou remover algum ponto

static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ ) {
    if( event == EVENT_LBUTTONDOWN )//se clicar com o botão deireito
    {
        point = Point2f((float)x, (float)y);//point recebe as coordenadas da imagem e coloca em point, que é global
        addRemovePt = true;//flag de add ponto fica true
    }
};

static Mat fase2(Mat image2, Mat image3, Mat frame ){
  Mat newFrame = frame.clone();
  int cx = (newFrame.cols + 500) / 2;
  int cx2 = (newFrame.cols - 100) / 2;
  int cx3 = (newFrame.cols - 800) / 2;
  int cx4 = (newFrame.cols + 1079) / 2;
  Mat srcBGR = Mat(image3.size(), CV_8UC3);
  Mat srcBGR2 = Mat(image3.size(), CV_8UC3);
  Mat srcBGR3 = Mat(image3.size(), CV_8UC3);
  Mat srcBGR4 = Mat(image2.size(), CV_8UC3);
  cvtColor(image3, srcBGR, cv::COLOR_GRAY2BGR);
  cvtColor(image3, srcBGR2, cv::COLOR_GRAY2BGR);
  cvtColor(image3, srcBGR3, cv::COLOR_GRAY2BGR);
  cvtColor(image2, srcBGR4, cv::COLOR_GRAY2BGR);
  Rect dstRC = Rect(cx, (newFrame.rows / 2) - 140, 50, 500);
  Rect dstRC2 = Rect(cx2, (newFrame.rows / 2) - 360, 50, 500);
  Rect dstRC3 = Rect(cx3, (newFrame.rows / 2) - 140, 50, 500);
  Rect dstRC4 = Rect(cx4, (newFrame.rows / 2) + 260, 100, 100);
  Mat dstROI = newFrame(dstRC);
  Mat dstROI2 = newFrame(dstRC2);
  Mat dstROI3 = newFrame(dstRC3);
  Mat dstROI4 = newFrame(dstRC4);
  srcBGR.copyTo(dstROI);
  srcBGR2.copyTo(dstROI2);
  srcBGR3.copyTo(dstROI3);
  srcBGR4.copyTo(dstROI4);

  return newFrame;
};

static Mat fase1(Mat image2, Mat image3, Mat frame ){
    Mat newFrame = frame.clone();
    int cx = (newFrame.cols + 500) / 2;
    int cx2 = (newFrame.cols - 100) / 2;
    int cx3 = (newFrame.cols - 800) / 2;
    int cx4 = (newFrame.cols + 1079) / 2;
    Mat srcBGR = Mat(image3.size(), CV_8UC3);
    Mat srcBGR2 = Mat(image3.size(), CV_8UC3);
    Mat srcBGR3 = Mat(image3.size(), CV_8UC3);
    Mat srcBGR4 = Mat(image2.size(), CV_8UC3);
    cvtColor(image3, srcBGR, cv::COLOR_GRAY2BGR);
    cvtColor(image3, srcBGR2, cv::COLOR_GRAY2BGR);
    cvtColor(image3, srcBGR3, cv::COLOR_GRAY2BGR);
    cvtColor(image2, srcBGR4, cv::COLOR_GRAY2BGR);
    Rect dstRC = Rect(cx, (newFrame.rows / 2) - 360, 50, 500);
    Rect dstRC2 = Rect(cx2, (newFrame.rows / 2) - 140, 50, 500);
    Rect dstRC3 = Rect(cx3, (newFrame.rows / 2) - 360, 50, 500);
    Rect dstRC4 = Rect(cx4, (newFrame.rows / 2) - 360, 100, 100);
    Mat dstROI = newFrame(dstRC);
    Mat dstROI2 = newFrame(dstRC2);
    Mat dstROI3 = newFrame(dstRC3);
    Mat dstROI4 = newFrame(dstRC4);
    srcBGR.copyTo(dstROI);
    srcBGR2.copyTo(dstROI2);
    srcBGR3.copyTo(dstROI3);
    srcBGR4.copyTo(dstROI4);

    return newFrame;
};

Labirynth::Labirynth(int argc, char** argv){
    VideoCapture cap;//captura de vídeo
    TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03);//criterio de finalizacao para iteradores
    Size subPixWinSize(10, 10), winSize(31, 31);//tamanhos: subpixel e da janela
    const int MAX_COUNT = 500;//maximo de alguma coisa
    bool needToInit = false;// booleano pra ver se ele precisa detectar automaticamente
    bool nightMode = false;// booleano do nightMode
    //help();
    cv::CommandLineParser parser(argc, argv, "{@input|0|}");//ele passa os argc e argv para a string input
    string input = parser.get<string>("@input");// ó aí, ele fazendo o que eu disse antes
    if (input.size() == 1 && isdigit(input[0]))//se a string de input tiver tamanho 1 e for um número
        cap.open(input[0] - '0');//ele faz essa porra aqui
    else
        cap.open(input);//se não for, ele abre com o input, input provavelmente é o nome de algum arquivo externo, tipo um mp4
    if (!cap.isOpened()) {
        cout << "Could not initialize capturing...\n";//se não abriu, fecha tudo

    }
    namedWindow("Labirynth", 1);//nome da janela que ele abre
    setMouseCallback("Labirynth", onMouse, 0);//void setMouseCallback(const string& winname, MouseCallback onMouse, void* userdata=0 ) ou seja, sei que porra é não
    Mat gray, prevGray, image, frame, newFrame;
    vector<Point2f> points[2];//cria um vetor de coordenadas de pontos, points[0] são os pontos ateriores, points[1] os próximos pontos
    Mat image3 =  imread("projeto.png", 0);
    Mat image2 =  imread("projeto2.png", 0);
    cv::resize(image3, image3, Size(50, 500));
    cv::resize(image2, image2, Size(100, 100));
    int i = 1;
    for (;;) {

        cap >> frame;// passa os frames da captura


        while(1) {
            cap >> frame;

            if(i == 1){
                newFrame = fase1(image2, image3, frame);//Chama a função da fase 1
            }else if(i == 2){
                newFrame = fase2(image2, image3, frame);//Chama a fusão da fase 2
            }

            if (newFrame.empty())//se o frame tiver vazio, acaba o loop e consequentementeo programa
                break;
            newFrame.copyTo(image);//copia o frame para "image", que foi declarado em Mat ali em cima
            cvtColor(image, gray, COLOR_BGR2GRAY);//Converts an image from one color space to another. || image é a imagem normal, gray é o output, o terceiro par é um código que ele quer transformar de BGR pra cinza
            if (nightMode)//deixa tudo preto, ativa o nightmode(a ideia inicial era fazer uma fase no escuro, mas n deu certo)
                image = Scalar::all(0);
            if (needToInit) {//Inicia os pontos (uma grande quantidade de pontos!).
                goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 3, 0, 0.04);
                cornerSubPix(gray, points[1], subPixWinSize, Size(-1, -1), termcrit);
                addRemovePt = false;
            } else if (!points[0].empty()) {
                vector<uchar> status;
                vector<float> err;
                if (prevGray.empty())
                    gray.copyTo(prevGray);//copia o gray(imagem transformada em cinza) para prevGray
                calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
                                     3, termcrit, 0, 0.001);//A mágica do código, ela calcula a posição dos pontos, quando você mexe ela que faz os pontos continuarem no seu rosto ou na mão etc.
                size_t i, k;
                for (i = k = 0; i < points[1].size(); i++) {
                    if (addRemovePt) {
                        if (norm(point - points[1][i]) <= 5) {//Calcula a norma do ponto
                            addRemovePt = false;
                            continue;
                        }
                    }
                    if (!status[i])
                        continue;
                    points[1][k++] = points[1][i];
                    circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);//cria um círculo em image, com as localizaćões que estão em points, de cor verde (0,255,0), preenchido, de tipo 8. A imagem do ponto.
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
            imshow("Labirynth", image);//Abre a janela mostrando a captura da webcam
            char c = (char) waitKey(10);//A função para receber um input do teclado
            if (c == 27)//Se ESC for pressionado ele sai do jogo
                break;


            switch (c) {
                case 'r'://"Seta" pontos em torno e em areas de "interesse"
                    needToInit = true;
                    break;
                case 'c'://Remove todos os pontos
                    points[0].clear();
                    points[1].clear();
                    break;
                case 'n'://Nightmode
                    nightMode = !nightMode;
                    break;

                case '2'://Escolhe a fase 2
                    i = 2;
                    break;
                case '1'://Escolhe a fase 1
                    i = 1;
                    break;

            }


            std::swap(points[1], points[0]);
            cv::swap(prevGray, gray);
        }
        break;
    }
}
