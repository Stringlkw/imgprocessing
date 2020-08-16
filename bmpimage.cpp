#include <Windows.h>
#include <stdio.h>

unsigned char* readBmp(char* bmpName, int* bmpWidth, int* bmpHeight)
{
	//二进制读方式打开指定的图像文件
	FILE* fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;

	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);	//moves the file pointer to a specified location

	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//获取图像宽、高等信息
	*bmpWidth = head.biWidth;
	*bmpHeight = head.biHeight;

	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int biBitCount = 8;	//8位灰度图像
	int lineByte = ((*bmpWidth) * biBitCount / 8 + 3) / 4 * 4;

	//灰度图像有颜色表，且颜色表表项为256	
	RGBQUAD* pColorTable = new RGBQUAD[256];	//申请颜色表所需要的空间
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);	//读颜色表进内存

	//申请位图数据所需要的空间，读位图数据进内存
	unsigned char* pBmpBuf = new unsigned char[lineByte * (*bmpHeight)];
	fread(pBmpBuf, 1, lineByte * (*bmpHeight), fp);

	//关闭文件
	fclose(fp);

	return pBmpBuf;
}


int saveBmp(unsigned char* imgBuf, int width, int height, char* bmpName)
{
	//如果位图数据指针为0，则没有数据传入，函数返回
	if (!imgBuf) return 0;

	int biBitCount = 8;	//每个像素所占的位数(bit)

	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节
	int colorTablesize = 1024;

	//待存储图像数据每行字节数为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//以二进制写的方式打开文件
	FILE* fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;

	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;	//bmp类型

	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;

	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER head;
	head.biSize = 40;	//本结构的长度
	head.biWidth = width;	//位图的宽度，以像素为单位
	head.biHeight = height;	//位图的宽度，以像素为单位
	head.biPlanes = 1;	//目标设备的级别，必须是1
	head.biBitCount = biBitCount;	//每个像素所占的位数(bit)，其值必须为1（黑白图像），4（16色图），8（256色），24（真彩色图）
	head.biCompression = 0;	//位图压缩类型，有效的值为BI_RGB（未经压缩）、BI_RLE4，BI_RLE8，BI_BITFIEDS（均为Windows定义常量）。
	head.biSizeImage = lineByte * height;	//实际的位图数据占用的字节数
	head.biXPelsPerMeter = 0;	//指定目标数据的水平分辨率，单位是像素/米。
	head.biYPelsPerMeter = 0;	////指定目标数据的垂直分辨率，单位是像素/米。
	head.biClrUsed = 0;	//位图实际用到的颜色数，如果该值为零，则用到的颜色数为2的biBitCount次幂
	head.biClrImportant = 0;	//位图显示过程中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。

	//写位图信息头进内存
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//申请颜色表所需要的空间，写颜色表进文件
	RGBQUAD* pColorTable = new RGBQUAD[256];
	for (int i = 0; i < 256; i++)
	{
		pColorTable[i].rgbRed = i;
		pColorTable[i].rgbGreen = i;
		pColorTable[i].rgbBlue = i;
		pColorTable[i].rgbReserved = 0;
	}
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

	//写位图数据进文件
	fwrite(imgBuf, height * lineByte, 1, fp);

	//关闭文件
	fclose(fp);
	return 1;
}