#pragma once
#include <QtGui>
#include <QtWidgets>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;




//
QImage* rgb2Gray(QImage* srcImg);	//rgb图像转灰度图
QImage* thresHold(QImage* inputImage, int thresh, int minValue=0, int maxValue=255);//图像二值化
void makeRepeatBorder(Mat& inputImage, Mat& outputImage, const int& cnBorder);//图像边界填充
void meanBlur(Mat& inputImage, Mat& outputImage, int kernelSize);//均值滤波
void sharpen(Mat& inputImage, Mat& outputImage, int sign);//锐化

