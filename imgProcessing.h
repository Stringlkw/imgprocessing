#pragma once

// 头文件
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
	void autoSize(); //控制窗口大小
	bool eventFilter(QObject* obj, QEvent* event);


private:
	Ui::imgProcessingClass ui;


	QDockWidget* dockImage; // 图像窗口
	QDockWidget* dockEnhance; // 图像处理窗口
	QDockWidget* dockProp; // 属性窗口

	QString currentPath; // 当前图像的路径
	QLabel* imgLabel; // 图像显示框
	QScrollArea* scrollArea; //滚动条

	QComboBox* combo1; //模板下拉框
	QComboBox* combo2; //滤波次数下拉框
	QComboBox* combo3; //锐化次数下拉框
	QComboBox* combo4; //锐化模板下拉框
	

	QPushButton* button1; //均值滤波
	QPushButton* button2; //锐化
	QPushButton* button3; //灰度图
	QPushButton* button4; //二值图
	QPushButton* button5; //原图

	QSpinBox* spinbox; //阈值微调框

	QLabel* label5;
	QLabel* label6;
	QLabel* label7;
	QLabel* label8;


	void windowInit(); //初始化窗口
	void imageInit(); // 初始化图像
	void menuFile(); // 文件菜单


	QImage* srcImg;
	QImage* dstImg;
	int doubleClickCount = 0; //双击次数
	int kernelSize = 3;//卷积核大小
	int blurcount = 1;//平滑次数
	int sharpensign = 1;//锐化模板
	int sharpencount = 1;//锐化次数
	int imgthresh = 120;//阈值

private slots: // 槽函数
	void fileNew(); // 新建
	void fileOpen(); // 打开
	void fileSave(); // 保存
	void fileSaveas(); // 另存为


	void slot_combo1(); //模板下拉选择
	void slot_combo2(); //均值滤波次数下拉选择
	void slot_combo3(); //锐化次数下拉选择
	void slot_combo4(); //锐化模板选择
	void slot_button1(); //均值滤波按钮
	void slot_button2(); //锐化按钮
	void slot_button3(); //灰度按钮
	void slot_button4(); //二值按钮
	void slot_button5(); //原图按钮
	void slot_spinbox(); //阈值微调框
};
