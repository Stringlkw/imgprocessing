#include "imgMethod.h"

//rgb图像转灰度图
QImage* rgb2Gray(QImage* inputImage)
{
	QImage* GrayImage = new QImage(inputImage->width(), inputImage->height(), QImage::Format_Grayscale8);
	QRgb* line;
	for (int row = 0; row < GrayImage->height(); row++)
	{
		QRgb* line = (QRgb*)inputImage->scanLine(row);

		for (int column = 0; column < GrayImage->width(); column++)
		{
			// 灰度  grayValue=(R30+G59+B11)/100
			int grayValue = (qRed(line[column]) * 30 + qGreen(line[column]) * 59 + qBlue(line[column]) * 11) / 100;
			GrayImage->setPixel(column, row, qRgb(grayValue, grayValue, grayValue));
		}
	}
	return GrayImage;
}

//图像二值化
QImage* thresHold(QImage* inputImage, int thresh, int minValue, int maxValue)
{
	int grayValue;
	int value;
	QColor oldColor;
	QImage* outputImage = new QImage(inputImage->width(), inputImage->height(), inputImage->format());
	if (!inputImage->isGrayscale())
	{
		inputImage = rgb2Gray(inputImage);
	}
	for (int row = 0; row < inputImage->height(); row++)
	{
		for (int column = 0; column < inputImage->width(); column++)
		{
			oldColor = QColor(inputImage->pixel(column, row));
			grayValue = oldColor.red();
			if (grayValue < thresh)
			{
				value = minValue;
			}
			else
			{
				value = maxValue;
			}
			outputImage->setPixel(column, row, qRgb(value, value, value));
		}
	}
	return outputImage;
}

//图像边界填充
void makeRepeatBorder(Mat& inputImage, Mat& outputImage, const int& cnBorder)
{
	//构造输出图像
	outputImage = Mat::zeros(inputImage.rows + cnBorder * 2, inputImage.cols + cnBorder * 2, inputImage.type());

	uchar *pSrc = NULL, *pDst = NULL;

	//拷贝原始图像数据
	for (int m = 0; m < inputImage.rows; m++)
	{
		//源地址
		pSrc = inputImage.data + m * inputImage.step[0];
		//目的地址
		pDst = outputImage.data + (m + cnBorder) * outputImage.step[0] + cnBorder;
		memcpy(pDst, pSrc, inputImage.step[0]);
	}
	//边界处理
	for (int m = 0; m < cnBorder; m++)
	{
		//顶部
		pSrc = outputImage.data + cnBorder * outputImage.step[0];
		pDst = outputImage.data + m * outputImage.step[0];
		memcpy(pDst, pSrc, outputImage.step[0]);
		//底部
		pSrc = outputImage.data + (cnBorder + inputImage.rows - 1) * outputImage.step[0];
		pDst = outputImage.data + (cnBorder + inputImage.rows + m) * outputImage.step[0];
		memcpy(pDst, pSrc, outputImage.step[0]);
	}

	for (int m = 0; m < outputImage.rows; m++)
		for (int n = 0; n < cnBorder; n++)
		{
			//左边
			outputImage.at<uchar>(m, n) = outputImage.at<uchar>(m, cnBorder);
			//右边
			outputImage.at<uchar>(m, n + inputImage.cols + cnBorder) = outputImage.at<uchar>(
				m, outputImage.cols - cnBorder - 1);
		}
}


//均值滤波
void meanBlur(Mat& inputImage, Mat& outputImage, int kernelSize)
{
	//如果是多通道图片则分离为三张单通道图片
	Mat srcMat, dstMat;
	vector<Mat> inputChannels, outputChannels;

	//构造输出图像
	outputImage = Mat::zeros(inputImage.rows, inputImage.cols, inputImage.type());

	//分离色彩通道
	split(inputImage, inputChannels);
	split(outputImage, outputChannels);

	//对每个单通道图片做滤波处理
	for (int i = 0; i < inputImage.channels(); i++)
	{
		srcMat = inputChannels.at(i);
		dstMat = outputChannels.at(i);


		//确保卷积核大小为奇数
		assert(kernelSize % 2 == 1);

		int nAnchor = kernelSize / 2;

		//边界处理
		Mat matMakeBorder;
		makeRepeatBorder(srcMat, matMakeBorder, nAnchor);

		//计算积分图
		Mat matIntegral;
		integral(matMakeBorder, matIntegral);

		//使用行首地址存储法遍历滤波
		int** pRow = new int*[matIntegral.rows];
		for (int row = 0; row < matIntegral.rows; row++)
		{
			pRow[row] = (int*)(matIntegral.data + row * matIntegral.step[0]);
		}

		//均值
		float fAve = 1.0f / (kernelSize * kernelSize);

		//滤波操作
		for (int row = 0; row < matMakeBorder.rows - kernelSize + 1; row++)
		{
			unsigned char* pOut = dstMat.data + row * dstMat.step[0];
			for (int column = 0; column < matMakeBorder.cols - kernelSize + 1; column++)
			{
				//求和
				float fSum = pRow[row][column] + pRow[row + kernelSize][column + kernelSize] -
					pRow[row + kernelSize][column] - pRow[row][column + kernelSize];
				//求均值输出
				pOut[column] = uchar(fSum * fAve);
			}
		}
		delete[] pRow;
	}
	//合并通道
	merge(outputChannels, outputImage);
}

//锐化
void sharpen(Mat& inputImage, Mat& outputImage, int sign)
{
	outputImage = Mat::zeros(inputImage.rows, inputImage.cols, inputImage.type());
	int channels = inputImage.channels(); /// 获得通道数
	for (int row = 1; row < inputImage.rows - 1; row++)
	{
		uchar* previous = inputImage.ptr<uchar>(row - 1); /// 上一行
		uchar* current = inputImage.ptr<uchar>(row); /// 当前行
		uchar* next = inputImage.ptr<uchar>(row + 1); ///下一行
		uchar* output = outputImage.ptr<uchar>(row); /// 输出行
		//在这里，将每个像素的三个通道合并成一个矩阵
		if (sign == 1)
		{
			for (int i = channels; i < (inputImage.cols - 1) * channels; i++)
			{
				/// 循环三个通道，进行相应的处理
				*output++ = saturate_cast<uchar>(
					5 * current[i] - current[i - channels] - current[i + channels] - previous[i] - next[i]);
				// 该值的4倍 减去 上下左右四个数
			}
		}
		else if (sign == 2)
		{
			for (int i = channels; i < (inputImage.cols - 1) * channels; i++)
			{
				/// 循环三个通道，进行相应的处理
				*output++ = saturate_cast<uchar>(
					9 * current[i] - current[i - channels] - current[i + channels] - previous[i] - previous[i - channels
					] -
					previous[i + channels] - next[i] - next[i - channels] - next[i + channels]);
			}
		}
	}
	// 接下来将未处理的像素都设为0
	outputImage.row(0).setTo(Scalar(0));
	outputImage.row(outputImage.rows - 1).setTo(Scalar(0));
	outputImage.col(0).setTo(Scalar(0));
	outputImage.col(outputImage.cols - 1).setTo(Scalar(0));
}
