#include <Windows.h>
#include <stdio.h>

unsigned char* readBmp(char* bmpName, int* bmpWidth, int* bmpHeight)
{
	//�����ƶ���ʽ��ָ����ͼ���ļ�
	FILE* fp = fopen(bmpName, "rb");
	if (fp == 0) return 0;

	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);	//moves the file pointer to a specified location

	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//��ȡͼ����ߵ���Ϣ
	*bmpWidth = head.biWidth;
	*bmpHeight = head.biHeight;

	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int biBitCount = 8;	//8λ�Ҷ�ͼ��
	int lineByte = ((*bmpWidth) * biBitCount / 8 + 3) / 4 * 4;

	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256	
	RGBQUAD* pColorTable = new RGBQUAD[256];	//������ɫ������Ҫ�Ŀռ�
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);	//����ɫ����ڴ�

	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	unsigned char* pBmpBuf = new unsigned char[lineByte * (*bmpHeight)];
	fread(pBmpBuf, 1, lineByte * (*bmpHeight), fp);

	//�ر��ļ�
	fclose(fp);

	return pBmpBuf;
}


int saveBmp(unsigned char* imgBuf, int width, int height, char* bmpName)
{
	//���λͼ����ָ��Ϊ0����û�����ݴ��룬��������
	if (!imgBuf) return 0;

	int biBitCount = 8;	//ÿ��������ռ��λ��(bit)

	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ����ɫ��Ϊ1024�ֽ�
	int colorTablesize = 1024;

	//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;

	//�Զ�����д�ķ�ʽ���ļ�
	FILE* fp = fopen(bmpName, "wb");
	if (fp == 0) return 0;

	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;	//bmp����

	//bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;

	//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
	fileHead.bfOffBits = 54 + colorTablesize;

	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	BITMAPINFOHEADER head;
	head.biSize = 40;	//���ṹ�ĳ���
	head.biWidth = width;	//λͼ�Ŀ�ȣ�������Ϊ��λ
	head.biHeight = height;	//λͼ�Ŀ�ȣ�������Ϊ��λ
	head.biPlanes = 1;	//Ŀ���豸�ļ��𣬱�����1
	head.biBitCount = biBitCount;	//ÿ��������ռ��λ��(bit)����ֵ����Ϊ1���ڰ�ͼ�񣩣�4��16ɫͼ����8��256ɫ����24�����ɫͼ��
	head.biCompression = 0;	//λͼѹ�����ͣ���Ч��ֵΪBI_RGB��δ��ѹ������BI_RLE4��BI_RLE8��BI_BITFIEDS����ΪWindows���峣������
	head.biSizeImage = lineByte * height;	//ʵ�ʵ�λͼ����ռ�õ��ֽ���
	head.biXPelsPerMeter = 0;	//ָ��Ŀ�����ݵ�ˮƽ�ֱ��ʣ���λ������/�ס�
	head.biYPelsPerMeter = 0;	////ָ��Ŀ�����ݵĴ�ֱ�ֱ��ʣ���λ������/�ס�
	head.biClrUsed = 0;	//λͼʵ���õ�����ɫ���������ֵΪ�㣬���õ�����ɫ��Ϊ2��biBitCount����
	head.biClrImportant = 0;	//λͼ��ʾ��������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�

	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head, sizeof(BITMAPINFOHEADER), 1, fp);

	//������ɫ������Ҫ�Ŀռ䣬д��ɫ����ļ�
	RGBQUAD* pColorTable = new RGBQUAD[256];
	for (int i = 0; i < 256; i++)
	{
		pColorTable[i].rgbRed = i;
		pColorTable[i].rgbGreen = i;
		pColorTable[i].rgbBlue = i;
		pColorTable[i].rgbReserved = 0;
	}
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);

	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height * lineByte, 1, fp);

	//�ر��ļ�
	fclose(fp);
	return 1;
}