#pragma once
#include <QDebug>
#include <QImage>
#include <opencv2/opencv.hpp>
using namespace cv;
Mat QImage2cvMat(QImage image);
QImage cvMat2QImage(Mat& mat);