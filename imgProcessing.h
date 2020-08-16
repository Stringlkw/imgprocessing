#pragma once

// ͷ�ļ�
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "ui_imgProcessing.h"

class imgProcessing : public QMainWindow
{
Q_OBJECT

public:
	imgProcessing(QWidget* parent = Q_NULLPTR);
	void autoSize(); //���ƴ��ڴ�С
	bool eventFilter(QObject* obj, QEvent* event);


private:
	Ui::imgProcessingClass ui;


	QDockWidget* dockImage; // ͼ�񴰿�
	QDockWidget* dockEnhance; // ͼ������
	QDockWidget* dockProp; // ���Դ���

	QString currentPath; // ��ǰͼ���·��
	QLabel* imgLabel; // ͼ����ʾ��
	QScrollArea* scrollArea; //������

	QComboBox* combo1; //ģ��������
	QComboBox* combo2; //�˲�����������
	QComboBox* combo3; //�񻯴���������
	QComboBox* combo4; //��ģ��������
	

	QPushButton* button1; //��ֵ�˲�
	QPushButton* button2; //��
	QPushButton* button3; //�Ҷ�ͼ
	QPushButton* button4; //��ֵͼ
	QPushButton* button5; //ԭͼ

	QSpinBox* spinbox; //��ֵ΢����

	QLabel* label5;
	QLabel* label6;
	QLabel* label7;
	QLabel* label8;


	void windowInit(); //��ʼ������
	void imageInit(); // ��ʼ��ͼ��
	void menuFile(); // �ļ��˵�


	QImage* srcImg;
	QImage* dstImg;
	int doubleClickCount = 0; //˫������
	int kernelSize = 3;//����˴�С
	int blurcount = 1;//ƽ������
	int sharpensign = 1;//��ģ��
	int sharpencount = 1;//�񻯴���
	int imgthresh = 120;//��ֵ

private slots: // �ۺ���
	void fileNew(); // �½�
	void fileOpen(); // ��
	void fileSave(); // ����
	void fileSaveas(); // ���Ϊ


	void slot_combo1(); //ģ������ѡ��
	void slot_combo2(); //��ֵ�˲���������ѡ��
	void slot_combo3(); //�񻯴�������ѡ��
	void slot_combo4(); //��ģ��ѡ��
	void slot_button1(); //��ֵ�˲���ť
	void slot_button2(); //�񻯰�ť
	void slot_button3(); //�ҶȰ�ť
	void slot_button4(); //��ֵ��ť
	void slot_button5(); //ԭͼ��ť
	void slot_spinbox(); //��ֵ΢����
};
