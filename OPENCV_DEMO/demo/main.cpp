#include "mainwindow.h"
#include <QApplication>


//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

int main(int argc, char *argv[])
{

    cv::Mat image = imread("E:\\1.jpg");
    namedWindow("Display window",WINDOW_AUTOSIZE);
    imshow("Display window",image);
    waitKey(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
