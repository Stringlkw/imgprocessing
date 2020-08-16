#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "imgProcessing.h"
#include "imgMethod.h"
#include "convert.h"

#pragma execution_character_set("utf-8")    // ��������������⣡


//���캯��
imgProcessing::imgProcessing(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	windowInit();
	menuFile();
	imageInit();
}

//����Ӧ���ڴ�С
void imgProcessing::autoSize()
{
	QImage image;
	double ImgRatio = 1.0 * imgLabel->pixmap()->toImage().width() / imgLabel->pixmap()->toImage().height(); // ͼ���߱�
	double WinRatio = 1.0 * (scrollArea->width() - 2) / (scrollArea->height() - 2); // ���ڿ�߱�
	if (ImgRatio > WinRatio) // ͼ���߱ȴ���ͼ���߱�
	{
		image = imgLabel->pixmap()->toImage().scaled((scrollArea->width() - 2), (scrollArea->width() - 2) / ImgRatio,
		                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	else // ͼ���߱�С�ڵ���ͼ���߱�
	{
		image = imgLabel->pixmap()->toImage().scaled((scrollArea->height() - 2) * ImgRatio, (scrollArea->height() - 2),
		                                             Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	imgLabel->setPixmap(QPixmap::fromImage(image)); // ��ʾͼ��
	imgLabel->resize(image.width(), image.height()); //����ͼ���С
}

//Qlabe����¼�
bool imgProcessing::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == imgLabel) //���¼�������Qlabel�ؼ���
	{
		if (event->type() == QEvent::MouseButtonDblClick) //��Ϊ˫���¼�ʱ
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

//���ڳ�ʼ��
void imgProcessing::windowInit()
{
	// ����
	setWindowTitle("ͼ����by_lkw");

	// ���ͼ��
	setWindowIcon(QIcon("image/img.gif"));

	// �����С
	resize(QApplication::desktop()->width() * 0.8, QApplication::desktop()->height() * 0.8);
	move(QApplication::desktop()->width() * 0.05, QApplication::desktop()->height() * 0.01);
	//ɾ���Դ����봰��
	QWidget* p = takeCentralWidget();
	if (p)
	{
		delete p;
	}
	//����Ƕ��dock
	setDockNestingEnabled(true);

	//dockImage
	dockImage = new QDockWidget("ͼ��", this); //ͼ�񴰿�
	dockImage->setFeatures(QDockWidget::NoDockWidgetFeatures); // ����Ϊ�̶�����
	dockImage->setMinimumSize(600, 600); // ������С���
	// 
	//dockEnhance
	dockEnhance = new QDockWidget("ͼ����ǿ", this); // ͼ����ǿ����
	dockEnhance->setMinimumSize(400, 400); // ������С���

	//dockProp
	dockProp = new QDockWidget("����", this); // ���Դ���
	dockProp->setMinimumSize(400, 400); // ������С���

	// ����
	setCentralWidget(dockImage); // ָ��Ϊ���Ĵ���
	addDockWidget(Qt::BottomDockWidgetArea, dockProp);
	addDockWidget(Qt::RightDockWidgetArea, dockEnhance);

	// �ָ��
	splitDockWidget(dockEnhance, dockProp, Qt::Vertical); // ��ֱ

	//Ϊͼ����ǿ����������
	QLabel* label1 = new QLabel("ģ���С", dockEnhance);
	QLabel* label2 = new QLabel("��", dockEnhance);
	QLabel* label3 = new QLabel("��", dockEnhance);
	QLabel* label4 = new QLabel("ģ��ѡ��", dockEnhance);

	combo1 = new QComboBox(dockEnhance); // ģ������ѡ���
	combo1->addItem(tr("3 �� 3")); // ���ѡ��
	combo1->addItem(tr("5 �� 5"));
	combo1->addItem(tr("7 �� 7"));
	connect(combo1, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo1()));

	combo2 = new QComboBox(dockEnhance); //�˲���������ѡ���
	combo2->addItem(tr("1")); // ���ѡ��
	combo2->addItem(tr("2"));
	combo2->addItem(tr("3"));
	connect(combo2, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo2()));

	combo3 = new QComboBox(dockEnhance); // �񻯴�������ѡ���
	combo3->addItem(tr("1")); // ���ѡ��
	combo3->addItem(tr("2"));
	combo3->addItem(tr("3"));
	connect(combo3, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo3()));

	combo4 = new QComboBox(dockEnhance); // ��ģ������ѡ���
	combo4->addItem(tr("Laplacian����������")); // ���ѡ��
	combo4->addItem(tr("Laplacian���Ӱ�����"));
	connect(combo4, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_combo4()));

	button1 = new QPushButton(tr("��ֵ�˲�"), dockEnhance);
	connect(button1, SIGNAL(clicked()), this, SLOT(slot_button1()));

	button2 = new QPushButton(tr("��"), dockEnhance);
	connect(button2, SIGNAL(clicked()), this, SLOT(slot_button2()));

	button3 = new QPushButton(tr("�Ҷ�ͼ"), dockEnhance);
	connect(button3, SIGNAL(clicked()), this, SLOT(slot_button3()));

	button4 = new QPushButton(tr("��ֵ��"), dockEnhance);
	connect(button4, SIGNAL(clicked()), this, SLOT(slot_button4()));

	button5 = new QPushButton(tr("ԭͼ"), dockEnhance);
	connect(button5, SIGNAL(clicked()), this, SLOT(slot_button5()));


	spinbox = new QSpinBox(); // ����΢����
	spinbox->setRange(0, 255); // ���÷�Χ
	spinbox->setValue(100); // ���ó�ʼֵ
	connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(slot_spinbox()));


	//����
	QGridLayout* glayout = new QGridLayout();
	glayout->addWidget(label1, 0, 0); // ��0��0�У���һ������Ϊ�أ��ڶ�������Ϊ�ڼ��У�����������Ϊ�ڼ���
	glayout->addWidget(combo1, 0, 1);
	glayout->addWidget(button1, 1, 0);
	glayout->addWidget(combo2, 1, 1);
	glayout->addWidget(label2, 1, 2);
	glayout->addWidget(label4, 3, 0);
	glayout->addWidget(combo4, 3, 1);
	glayout->addWidget(button2, 4, 0);
	glayout->addWidget(combo3, 4, 1);
	glayout->addWidget(label3, 4, 2);


	QHBoxLayout* hlayout1 = new QHBoxLayout(); //ˮƽ����
	hlayout1->addWidget(button3);

	QHBoxLayout* hlayout2 = new QHBoxLayout(); //ˮƽ����
	hlayout2->addWidget(button4);
	hlayout2->addWidget(spinbox);

	QHBoxLayout* hlayout3 = new QHBoxLayout(); //ˮƽ����
	hlayout3->addWidget(button5);

	QVBoxLayout* pLayout1 = new QVBoxLayout(); // ʹ�ô�ֱ������Ϊ������
	pLayout1->addLayout(glayout);

	pLayout1->addLayout(hlayout1);
	pLayout1->addLayout(hlayout2);
	pLayout1->addLayout(hlayout3);

	QWidget* pWidget1 = new QWidget(dockEnhance);
	pWidget1->setLayout(pLayout1);
	dockEnhance->setWidget(pWidget1);

	//Ϊ���Դ���������
	label5 = new QLabel(tr("ͼ��"), dockProp);
	label6 = new QLabel(tr("����"), dockProp);
	label7 = new QLabel(tr("���"), dockProp);
	label8 = new QLabel(tr("���"), dockProp);


	QFormLayout* flayout = new QFormLayout(); //ʹ�����񲼾�
	flayout->addRow(tr("ͼ��"), label5); // ����У���һ��Ϊ��ǩ���ڶ���Ϊ��ӵĿؼ�QLineEdit
	flayout->addRow(tr("����"), label6);
	flayout->addRow(tr("���"), label7);
	flayout->addRow(tr("���"), label8);
	flayout->setSpacing(20); // ���ü��
	flayout->setMargin(20); // ������߾�
	
	QVBoxLayout* pLayout2 = new QVBoxLayout(); // ʹ�ô�ֱ������Ϊ������
	pLayout2->addStretch();
	pLayout2->addLayout(flayout);
	pLayout2->addStretch();
	
	QWidget* pWidget2 = new QWidget(dockProp); 
	pWidget2->setLayout(pLayout2);
	dockProp->setWidget(pWidget2);
}

//ͼ���ʼ��
void imgProcessing::imageInit()
{
	imgLabel = new QLabel(dockImage);
	imgLabel->setScaledContents(true);
	imgLabel->installEventFilter(this);

	QImage image = QImage(500, 500, QImage::Format_RGB32);//ͼ���ʼ��Ϊһ�����Ϊ500�İ�ɫͼ��
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


//�ļ��˵�
void imgProcessing::menuFile()
{
	//�½�
	ui.actionnew->setIcon(QIcon("image/new.gif"));
	ui.actionnew->setShortcuts(QKeySequence::New); //��ݼ�Ctrl+N
	connect(ui.actionnew, SIGNAL(triggered()), this, SLOT(fileNew()));

	//��
	ui.actionopen->setIcon(QIcon("image/open.gif"));
	ui.actionopen->setShortcuts(QKeySequence::Open); //��ݼ�Ctrl+O
	connect(ui.actionopen, SIGNAL(triggered()), this, SLOT(fileOpen()));

	//����
	ui.actionsave->setShortcuts(QKeySequence::Save); //��ݼ�Ctrl+S
	connect(ui.actionsave, SIGNAL(triggered()), this, SLOT(fileSave()));

	//���Ϊ
	ui.actionsave->setShortcuts(QKeySequence::SaveAs); //��ݼ�Ctrl+S
	connect(ui.actionsaveas, SIGNAL(triggered()), this, SLOT(fileSaveas()));

	//�ر�
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

//���¾�Ϊ�ۺ���ʵ��

void imgProcessing::fileOpen()
{
	QString path = QFileDialog::getOpenFileName(this, "ѡ��ͼ��", ".", "images(*.jpg *.png *.bmp)");
	if (!path.isEmpty())
	{
		srcImg = new QImage();
		if (!(srcImg->load(path)))
		{
			QMessageBox::information(this, "����", "��ͼ��ʧ��!");
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
		QString path = QFileDialog::getSaveFileName(this, "����ͼ��", ".", "images(*.jpg *.png *.bmp)");
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
	QString path = QFileDialog::getSaveFileName(this, "ͼ�����Ϊ", ".", "images(*.jpg *.png *.bmp)");
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
