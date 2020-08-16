#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "imgProcessing.h"
#include "imgMethod.h"
#include "convert.h"

#pragma execution_character_set("utf-8")    // 解决汉字乱码问题！


//构造函数
imgProcessing::imgProcessing(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	windowInit();
	menuFile();
	imageInit();
}

//自适应窗口大小
void imgProcessing::autoSize()
{
	QImage image;
	double ImgRatio = 1.0 * imgLabel->pixmap()->toImage().width() / imgLabel->pixmap()->toImage().height(); // 图像宽高比
	double WinRatio = 1.0 * (scrollArea->width() - 2) / (scrollArea->height() - 2); // 窗口宽高比
	if (ImgRatio > WinRatio) // 图像宽高比大于图像宽高比
	{
		image = imgLabel->pixmap()->toImage().scaled((scrollArea->width() - 2), (scrollArea->width() - 2) / ImgRatio,
		                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	else // 图像宽高比小于等于图像宽高比
	{
		image = imgLabel->pixmap()->toImage().scaled((scrollArea->height() - 2) * ImgRatio, (scrollArea->height() - 2),
		                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	imgLabel->setPixmap(QPixmap::fromImage(image)); // 显示图像
	imgLabel->resize(image.width(), image.height()); //调整图像大小
}

//Qlabe点击事件
bool imgProcessing::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == imgLabel) //当事件发生在Qlabel控件上
	{
		if (event->type() == QEvent::MouseButtonDblClick) //当为双击事件时
		{
			doubleClickCount++;
			if (doubleClickCount % 2 != 0)
			{
				autoSize();
			}
			else
			{
				imgLabel->resize(srcImg->width(), srcImg->height());
			}
		}
	}
	return QObject::eventFilter(obj, event);
}

//窗口初始化
void imgProcessing::windowInit()
{
	// 标题
	setWindowTitle("图像处理by_lkw");

	// 软件图标
	setWindowIcon(QIcon("image/img.gif"));

	// 界面大小
	resize(QApplication::desktop()->width() * 0.8, QApplication::desktop()->height() * 0.8);
	move(QApplication::desktop()->width() * 0.05, QApplication::desktop()->height() * 0.01);
	//删除自带中央窗体
	QWidget* p = takeCentralWidget();
	if (p)
	{
		delete p;
	}
	//允许嵌套dock
	setDockNestingEnabled(true);

	//dockImage
	dockImage = new QDockWidget("图像", this); //图像窗口
	dockImage->setFeatures(QDockWidget::NoDockWidgetFeatures); // 设置为固定窗口
	dockImage->setMinimumSize(600, 600); // 设置最小宽高
	// 
	//dockEnhance
	dockEnhance = new QDockWidget("图像增强", this); // 图像增强窗口
	dockEnhance->setMinimumSize(400, 400); // 设置最小宽高

	//dockProp
	dockProp = new QDockWidget("属性", this); // 属性窗口
	dockProp->setMinimumSize(400, 400); // 设置最小宽高

	// 布局
	setCentralWidget(dockImage); // 指定为中心窗口
	addDockWidget(Qt::BottomDockWidgetArea, dockProp);
	addDockWidget(Qt::RightDockWidgetArea, dockEnhance);

	// 分割窗口
	splitDockWidget(dockEnhance, dockProp, Qt::Vertical); // 垂直

	//为图像增强窗口添加组件
	QLabel* label1 = new QLabel("模板大小", dockEnhance);
	QLabel* label2 = new QLabel("次", dockEnhance);
	QLabel* label3 = new QLabel("次", dockEnhance);
	QLabel* label4 = new QLabel("模板选择", dockEnhance);

	combo1 = new QComboBox(dockEnhance); // 模板下拉选择框
	combo1->addItem(tr("3 × 3")); // 添加选项
	combo1->addItem(tr("5 × 5"));
	combo1->addItem(tr("7 × 7"));
	connect(combo1, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo1()));

	combo2 = new QComboBox(dockEnhance); //滤波次数下拉选择框
	combo2->addItem(tr("1")); // 添加选项
	combo2->addItem(tr("2"));
	combo2->addItem(tr("3"));
	connect(combo2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo2()));

	combo3 = new QComboBox(dockEnhance); // 锐化次数下拉选择框
	combo3->addItem(tr("1")); // 添加选项
	combo3->addItem(tr("2"));
	combo3->addItem(tr("3"));
	connect(combo3, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo3()));

	combo4 = new QComboBox(dockEnhance); // 锐化模板下拉选择框
	combo4->addItem(tr("Laplacian算子四邻域")); // 添加选项
	combo4->addItem(tr("Laplacian算子八邻域"));
	connect(combo4, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo4()));

	button1 = new QPushButton(tr("均值滤波"), dockEnhance);
	connect(button1, SIGNAL(clicked()), this, SLOT(slot_button1()));

	button2 = new QPushButton(tr("锐化"), dockEnhance);
	connect(button2, SIGNAL(clicked()), this, SLOT(slot_button2()));

	button3 = new QPushButton(tr("灰度图"), dockEnhance);
	connect(button3, SIGNAL(clicked()), this, SLOT(slot_button3()));

	button4 = new QPushButton(tr("二值化"), dockEnhance);
	connect(button4, SIGNAL(clicked()), this, SLOT(slot_button4()));

	button5 = new QPushButton(tr("原图"), dockEnhance);
	connect(button5, SIGNAL(clicked()), this, SLOT(slot_button5()));


	spinbox = new QSpinBox(); // 创建微调框
	spinbox->setRange(0, 255); // 设置范围
	spinbox->setValue(100); // 设置初始值
	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(slot_spinbox()));


	//布局
	QGridLayout* glayout = new QGridLayout();
	glayout->addWidget(label1, 0, 0); // 第0行0列，第一个参数为控，第二个参数为第几行，第三个参数为第几列
	glayout->addWidget(combo1, 0, 1);
	glayout->addWidget(button1, 1, 0);
	glayout->addWidget(combo2, 1, 1);
	glayout->addWidget(label2, 1, 2);
	glayout->addWidget(label4, 3, 0);
	glayout->addWidget(combo4, 3, 1);
	glayout->addWidget(button2, 4, 0);
	glayout->addWidget(combo3, 4, 1);
	glayout->addWidget(label3, 4, 2);


	QHBoxLayout* hlayout1 = new QHBoxLayout(); //水平布局
	hlayout1->addWidget(button3);

	QHBoxLayout* hlayout2 = new QHBoxLayout(); //水平布局
	hlayout2->addWidget(button4);
	hlayout2->addWidget(spinbox);

	QHBoxLayout* hlayout3 = new QHBoxLayout(); //水平布局
	hlayout3->addWidget(button5);

	QVBoxLayout* pLayout1 = new QVBoxLayout(); // 使用垂直布局作为主布局
	pLayout1->addLayout(glayout);

	pLayout1->addLayout(hlayout1);
	pLayout1->addLayout(hlayout2);
	pLayout1->addLayout(hlayout3);

	QWidget* pWidget1 = new QWidget(dockEnhance);
	pWidget1->setLayout(pLayout1);
	dockEnhance->setWidget(pWidget1);

	//为属性窗口添加组件
	label5 = new QLabel(tr("图像"), dockProp);
	label6 = new QLabel(tr("长度"), dockProp);
	label7 = new QLabel(tr("宽度"), dockProp);
	label8 = new QLabel(tr("深度"), dockProp);


	QFormLayout* flayout = new QFormLayout(); //使用网格布局
	flayout->addRow(tr("图像"), label5); // 添加行，第一列为标签，第二列为添加的控件QLineEdit
	flayout->addRow(tr("长度"), label6);
	flayout->addRow(tr("宽度"), label7);
	flayout->addRow(tr("深度"), label8);
	flayout->setSpacing(20); // 设置间距
	flayout->setMargin(20); // 设置外边距
	
	QVBoxLayout* pLayout2 = new QVBoxLayout(); // 使用垂直布局作为主布局
	pLayout2->addStretch();
	pLayout2->addLayout(flayout);
	pLayout2->addStretch();
	
	QWidget* pWidget2 = new QWidget(dockProp); 
	pWidget2->setLayout(pLayout2);
	dockProp->setWidget(pWidget2);
}

//图像初始化
void imgProcessing::imageInit()
{
	imgLabel = new QLabel(dockImage);
	imgLabel->setScaledContents(true);
	imgLabel->installEventFilter(this);

	QImage image = QImage(500, 500, QImage::Format_RGB32);//图像初始化为一个宽高为500的白色图像
	image.fill(qRgb(255, 255, 255));
	srcImg = new QImage(image);
	dstImg = new QImage(image);
	imgLabel->setPixmap(QPixmap::fromImage(image));
	imgLabel->resize(image.width(), image.height());
	scrollArea = new QScrollArea(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	scrollArea->setWidget(imgLabel);
	dockImage->setWidget(scrollArea);
}


//文件菜单
void imgProcessing::menuFile()
{
	//新建
	ui.actionnew->setIcon(QIcon("image/new.gif"));
	ui.actionnew->setShortcuts(QKeySequence::New); //快捷键Ctrl+N
	connect(ui.actionnew, SIGNAL(triggered()), this, SLOT(fileNew()));

	//打开
	ui.actionopen->setIcon(QIcon("image/open.gif"));
	ui.actionopen->setShortcuts(QKeySequence::Open); //快捷键Ctrl+O
	connect(ui.actionopen, SIGNAL(triggered()), this, SLOT(fileOpen()));

	//保存
	ui.actionsave->setShortcuts(QKeySequence::Save); //快捷键Ctrl+S
	connect(ui.actionsave, SIGNAL(triggered()), this, SLOT(fileSave()));

	//另存为
	ui.actionsave->setShortcuts(QKeySequence::SaveAs); //快捷键Ctrl+S
	connect(ui.actionsaveas, SIGNAL(triggered()), this, SLOT(fileSaveas()));

	//关闭
	connect(ui.actionclose, SIGNAL(triggered()), this, SLOT(close()));
}

void imgProcessing::fileNew()
{
	QImage image = QImage(500, 500, QImage::Format_RGB32);
	image.fill(qRgb(0, 0, 0));
	imgLabel->setPixmap(QPixmap::fromImage(image));
	imgLabel->resize(image.width(), image.height());
	label5->setText("New image");
	label6->setNum(image.height());
	label7->setNum(image.width());
	label8->setNum(image.depth());
	currentPath = "";
}

//以下均为槽函数实现

void imgProcessing::fileOpen()
{
	QString path = QFileDialog::getOpenFileName(this, "选择图像", ".", "images(*.jpg *.png *.bmp)");
	if (!path.isEmpty())
	{
		srcImg = new QImage();
		if (!(srcImg->load(path)))
		{
			QMessageBox::information(this, "错误", "打开图像失败!");
			delete(srcImg);
			return;
		}

		imgLabel->resize(srcImg->width(), srcImg->height());
		imgLabel->setPixmap(QPixmap::fromImage(*srcImg));

		label5->setText(path);
		label6->setNum(srcImg->height());
		label7->setNum(srcImg->width());
		label8->setNum(srcImg->depth());
		currentPath = path;
	}
}


void imgProcessing::fileSave()
{
	if (currentPath.isEmpty())
	{
		QString path = QFileDialog::getSaveFileName(this, "保存图像", ".", "images(*.jpg *.png *.bmp)");
		if (!path.isEmpty())
		{
			currentPath = path;
		}
	}
	QImage img = imgLabel->pixmap()->toImage();
	img.save(currentPath);
}


void imgProcessing::fileSaveas()
{
	QString path = QFileDialog::getSaveFileName(this, "图像另存为", ".", "images(*.jpg *.png *.bmp)");
	if (!path.isEmpty())
	{
		QImage img = imgLabel->pixmap()->toImage();
		img.save(path);
	}
}


void imgProcessing::slot_combo1()
{
	if (combo1->currentIndex() == 0)
	{
		kernelSize = 3;
	}
	else if (combo1->currentIndex() == 1)
	{
		kernelSize = 5;
	}
	else if (combo1->currentIndex() == 2)
	{
		kernelSize = 7;
	}
}

void imgProcessing::slot_combo2()
{
	if (combo2->currentIndex() == 0)
	{
		blurcount = 1;
	}
	else if (combo2->currentIndex() == 1)
	{
		blurcount = 2;
	}
	else if (combo2->currentIndex() == 2)
	{
		blurcount = 3;
	}
}

void imgProcessing::slot_combo3()
{
	if (combo3->currentIndex() == 0)
	{
		sharpencount = 1;
	}
	else if (combo3->currentIndex() == 1)
	{
		sharpencount = 2;
	}
	else if (combo3->currentIndex() == 2)
	{
		sharpencount = 3;
	}
}

void imgProcessing::slot_combo4()
{
	if (combo4->currentIndex() == 0)
	{
		sharpensign = 1;
	}
	else if (combo4->currentIndex() == 1)
	{
		sharpensign = 2;
	}
}

void imgProcessing::slot_button1()
{
	Mat src = QImage2cvMat(*srcImg);
	Mat dst;
	for (int i = 0; i < blurcount; i++)
	{
		meanBlur(src, dst, kernelSize);
		*dstImg = cvMat2QImage(dst);
		src = QImage2cvMat(*dstImg);
	}

	imgLabel->setPixmap(QPixmap::fromImage(*dstImg));
	imgLabel->resize(dstImg->width(), dstImg->height());
}

void imgProcessing::slot_button2()
{
	Mat src = QImage2cvMat(*srcImg);
	Mat dst;
	for (int i = 0; i < sharpencount; i++)
	{
		sharpen(src, dst, sharpensign);
		*dstImg = cvMat2QImage(dst);
		src = QImage2cvMat(*dstImg);
	}
	imgLabel->setPixmap(QPixmap::fromImage(*dstImg));
	imgLabel->resize(dstImg->width(), dstImg->height());
}

void imgProcessing::slot_button3()
{
	if (srcImg->isGrayscale())
	{
		return;
	}
	dstImg = rgb2Gray(srcImg);
	imgLabel->setPixmap(QPixmap::fromImage(*dstImg));
	imgLabel->resize(dstImg->width(), dstImg->height());
}

void imgProcessing::slot_button4()
{
	dstImg = thresHold(srcImg, imgthresh);
	imgLabel->setPixmap(QPixmap::fromImage(*dstImg));
	imgLabel->resize(dstImg->width(), dstImg->height());
}


void imgProcessing::slot_button5()
{
	imgLabel->setPixmap(QPixmap::fromImage(*srcImg));
	imgLabel->resize(srcImg->width(), srcImg->height());
}

void imgProcessing::slot_spinbox()
{
	imgthresh = spinbox->value();
}
