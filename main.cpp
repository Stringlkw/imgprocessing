#include "imgProcessing.h"
#include <QtWidgets/QApplication>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	imgProcessing w;
	w.show();
	return a.exec();
}


