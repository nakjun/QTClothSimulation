/********************************************************************************
** Form generated from reading UI file 'qtclothsimulation.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCLOTHSIMULATION_H
#define UI_QTCLOTHSIMULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_QTClothSimulationClass
{
public:
    QWidget *centralWidget;
    QLabel *ReferenceModel_LabelKs;
    QPushButton *pushButton;
    QFrame *frame;
    QLabel *ReferenceModel_LabelN;
    QLabel *ReferenceModel_LabelM;
    QDoubleSpinBox *ReferenceModel_Ks_Structural;
    QDoubleSpinBox *ReferenceModel_Kd;
    QSpinBox *ReferenceModel_N;
    QSpinBox *ReferenceModel_M;
    QLabel *ReferenceModel_LabelKd;
    QLabel *ReferenceModel_LabelKs_2;
    QDoubleSpinBox *ReferenceModel_Ks_Shear;
    QLabel *ReferenceModel_LabelKs_3;
    QDoubleSpinBox *ReferenceModel_Ks_Bend;
    QPushButton *pushButton_3;
    QFrame *frame_2;
    QLabel *SimulationModel_LabelN;
    QLabel *SimulationModel_LabelM;
    QDoubleSpinBox *SimulationModel_Ks_Structural;
    QDoubleSpinBox *SimulationModel_Kd;
    QSpinBox *SimulationModel_N;
    QSpinBox *SimulationModel_M;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_8;
    QDoubleSpinBox *SimulationModel_Ks_Shear;
    QLabel *label_9;
    QDoubleSpinBox *SimulationModel_Ks_Bend;
    QLabel *label_5;
    QPushButton *pushButton_4;
    QLabel *label;
    MyGLwidget *widget;
    QPushButton *BarycentricSimulationFalseBtn;
    QPushButton *resetBtn;
    QPushButton *SimulationStartBtn;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QPushButton *SimulationStopBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTClothSimulationClass)
    {
        if (QTClothSimulationClass->objectName().isEmpty())
            QTClothSimulationClass->setObjectName(QStringLiteral("QTClothSimulationClass"));
        QTClothSimulationClass->resize(1028, 692);
        centralWidget = new QWidget(QTClothSimulationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ReferenceModel_LabelKs = new QLabel(centralWidget);
        ReferenceModel_LabelKs->setObjectName(QStringLiteral("ReferenceModel_LabelKs"));
        ReferenceModel_LabelKs->setGeometry(QRect(741, 33, 61, 16));
        ReferenceModel_LabelKs->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(760, 470, 251, 31));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(740, 0, 281, 231));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        ReferenceModel_LabelN = new QLabel(frame);
        ReferenceModel_LabelN->setObjectName(QStringLiteral("ReferenceModel_LabelN"));
        ReferenceModel_LabelN->setGeometry(QRect(20, 148, 41, 16));
        ReferenceModel_LabelN->setAlignment(Qt::AlignCenter);
        ReferenceModel_LabelM = new QLabel(frame);
        ReferenceModel_LabelM->setObjectName(QStringLiteral("ReferenceModel_LabelM"));
        ReferenceModel_LabelM->setGeometry(QRect(20, 175, 41, 16));
        ReferenceModel_LabelM->setAlignment(Qt::AlignCenter);
        ReferenceModel_Ks_Structural = new QDoubleSpinBox(frame);
        ReferenceModel_Ks_Structural->setObjectName(QStringLiteral("ReferenceModel_Ks_Structural"));
        ReferenceModel_Ks_Structural->setGeometry(QRect(60, 30, 221, 21));
        ReferenceModel_Ks_Structural->setMinimum(0);
        ReferenceModel_Ks_Structural->setMaximum(5000);
        ReferenceModel_Ks_Structural->setSingleStep(0.001);
        ReferenceModel_Ks_Structural->setValue(500);
        ReferenceModel_Kd = new QDoubleSpinBox(frame);
        ReferenceModel_Kd->setObjectName(QStringLiteral("ReferenceModel_Kd"));
        ReferenceModel_Kd->setGeometry(QRect(60, 119, 221, 22));
        ReferenceModel_Kd->setDecimals(10);
        ReferenceModel_Kd->setMaximum(500);
        ReferenceModel_Kd->setSingleStep(0.001);
        ReferenceModel_Kd->setValue(0.01);
        ReferenceModel_N = new QSpinBox(frame);
        ReferenceModel_N->setObjectName(QStringLiteral("ReferenceModel_N"));
        ReferenceModel_N->setGeometry(QRect(60, 145, 221, 22));
        ReferenceModel_N->setMinimum(2);
        ReferenceModel_N->setMaximum(1024);
        ReferenceModel_N->setValue(8);
        ReferenceModel_N->setDisplayIntegerBase(10);
        ReferenceModel_M = new QSpinBox(frame);
        ReferenceModel_M->setObjectName(QStringLiteral("ReferenceModel_M"));
        ReferenceModel_M->setGeometry(QRect(60, 172, 221, 22));
        ReferenceModel_M->setMinimum(2);
        ReferenceModel_M->setMaximum(1024);
        ReferenceModel_M->setValue(8);
        ReferenceModel_LabelKd = new QLabel(frame);
        ReferenceModel_LabelKd->setObjectName(QStringLiteral("ReferenceModel_LabelKd"));
        ReferenceModel_LabelKd->setGeometry(QRect(20, 123, 41, 16));
        ReferenceModel_LabelKd->setAlignment(Qt::AlignCenter);
        ReferenceModel_LabelKs_2 = new QLabel(frame);
        ReferenceModel_LabelKs_2->setObjectName(QStringLiteral("ReferenceModel_LabelKs_2"));
        ReferenceModel_LabelKs_2->setGeometry(QRect(1, 62, 61, 16));
        ReferenceModel_LabelKs_2->setAlignment(Qt::AlignCenter);
        ReferenceModel_Ks_Shear = new QDoubleSpinBox(frame);
        ReferenceModel_Ks_Shear->setObjectName(QStringLiteral("ReferenceModel_Ks_Shear"));
        ReferenceModel_Ks_Shear->setGeometry(QRect(60, 60, 221, 21));
        ReferenceModel_Ks_Shear->setMaximum(5000);
        ReferenceModel_Ks_Shear->setValue(400);
        ReferenceModel_LabelKs_3 = new QLabel(frame);
        ReferenceModel_LabelKs_3->setObjectName(QStringLiteral("ReferenceModel_LabelKs_3"));
        ReferenceModel_LabelKs_3->setGeometry(QRect(0, 92, 61, 16));
        ReferenceModel_LabelKs_3->setAlignment(Qt::AlignCenter);
        ReferenceModel_Ks_Bend = new QDoubleSpinBox(frame);
        ReferenceModel_Ks_Bend->setObjectName(QStringLiteral("ReferenceModel_Ks_Bend"));
        ReferenceModel_Ks_Bend->setGeometry(QRect(60, 90, 221, 21));
        ReferenceModel_Ks_Bend->setMaximum(5000);
        ReferenceModel_Ks_Bend->setValue(300);
        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 200, 251, 31));
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(740, 248, 281, 221));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        SimulationModel_LabelN = new QLabel(frame_2);
        SimulationModel_LabelN->setObjectName(QStringLiteral("SimulationModel_LabelN"));
        SimulationModel_LabelN->setGeometry(QRect(11, 138, 41, 16));
        SimulationModel_LabelN->setAlignment(Qt::AlignCenter);
        SimulationModel_LabelM = new QLabel(frame_2);
        SimulationModel_LabelM->setObjectName(QStringLiteral("SimulationModel_LabelM"));
        SimulationModel_LabelM->setGeometry(QRect(11, 165, 41, 16));
        SimulationModel_LabelM->setAlignment(Qt::AlignCenter);
        SimulationModel_Ks_Structural = new QDoubleSpinBox(frame_2);
        SimulationModel_Ks_Structural->setObjectName(QStringLiteral("SimulationModel_Ks_Structural"));
        SimulationModel_Ks_Structural->setGeometry(QRect(60, 20, 221, 21));
        SimulationModel_Ks_Structural->setDecimals(2);
        SimulationModel_Ks_Structural->setMaximum(5000);
        SimulationModel_Kd = new QDoubleSpinBox(frame_2);
        SimulationModel_Kd->setObjectName(QStringLiteral("SimulationModel_Kd"));
        SimulationModel_Kd->setGeometry(QRect(60, 110, 221, 21));
        SimulationModel_Kd->setDecimals(10);
        SimulationModel_N = new QSpinBox(frame_2);
        SimulationModel_N->setObjectName(QStringLiteral("SimulationModel_N"));
        SimulationModel_N->setGeometry(QRect(60, 135, 221, 22));
        SimulationModel_N->setMinimum(2);
        SimulationModel_N->setMaximum(1024);
        SimulationModel_M = new QSpinBox(frame_2);
        SimulationModel_M->setObjectName(QStringLiteral("SimulationModel_M"));
        SimulationModel_M->setGeometry(QRect(60, 162, 221, 22));
        SimulationModel_M->setMinimum(2);
        SimulationModel_M->setMaximum(1024);
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 0, 151, 16));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(0, 20, 61, 20));
        label_6->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 50, 61, 20));
        label_8->setAlignment(Qt::AlignCenter);
        SimulationModel_Ks_Shear = new QDoubleSpinBox(frame_2);
        SimulationModel_Ks_Shear->setObjectName(QStringLiteral("SimulationModel_Ks_Shear"));
        SimulationModel_Ks_Shear->setGeometry(QRect(60, 50, 221, 21));
        SimulationModel_Ks_Shear->setMaximum(5000);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(0, 80, 61, 20));
        label_9->setAlignment(Qt::AlignCenter);
        SimulationModel_Ks_Bend = new QDoubleSpinBox(frame_2);
        SimulationModel_Ks_Bend->setObjectName(QStringLiteral("SimulationModel_Ks_Bend"));
        SimulationModel_Ks_Bend->setGeometry(QRect(60, 80, 221, 21));
        SimulationModel_Ks_Bend->setMaximum(5000);
        label_5 = new QLabel(frame_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 110, 41, 16));
        label_5->setAlignment(Qt::AlignCenter);
        pushButton_4 = new QPushButton(frame_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(20, 190, 251, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(750, 10, 151, 16));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        widget = new MyGLwidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 731, 661));
        BarycentricSimulationFalseBtn = new QPushButton(centralWidget);
        BarycentricSimulationFalseBtn->setObjectName(QStringLiteral("BarycentricSimulationFalseBtn"));
        BarycentricSimulationFalseBtn->setGeometry(QRect(760, 500, 251, 31));
        resetBtn = new QPushButton(centralWidget);
        resetBtn->setObjectName(QStringLiteral("resetBtn"));
        resetBtn->setGeometry(QRect(760, 630, 131, 31));
        SimulationStartBtn = new QPushButton(centralWidget);
        SimulationStartBtn->setObjectName(QStringLiteral("SimulationStartBtn"));
        SimulationStartBtn->setGeometry(QRect(760, 560, 251, 31));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(760, 540, 81, 16));
        radioButton_2 = new QRadioButton(centralWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(840, 540, 81, 16));
        radioButton_3 = new QRadioButton(centralWidget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(920, 540, 81, 16));
        SimulationStopBtn = new QPushButton(centralWidget);
        SimulationStopBtn->setObjectName(QStringLiteral("SimulationStopBtn"));
        SimulationStopBtn->setGeometry(QRect(760, 596, 251, 31));
        QTClothSimulationClass->setCentralWidget(centralWidget);
        frame->raise();
        widget->raise();
        frame_2->raise();
        ReferenceModel_LabelKs->raise();
        pushButton->raise();
        label->raise();
        BarycentricSimulationFalseBtn->raise();
        resetBtn->raise();
        SimulationStartBtn->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        SimulationStopBtn->raise();
        statusBar = new QStatusBar(QTClothSimulationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTClothSimulationClass->setStatusBar(statusBar);

        retranslateUi(QTClothSimulationClass);
        QObject::connect(pushButton, SIGNAL(clicked(bool)), QTClothSimulationClass, SLOT(setBarycentricFlag()));
        QObject::connect(ReferenceModel_N, SIGNAL(valueChanged(int)), QTClothSimulationClass, SLOT(getReferenceNodeNum1(int)));
        QObject::connect(ReferenceModel_M, SIGNAL(valueChanged(int)), QTClothSimulationClass, SLOT(getReferenceNodeNum2(int)));
        QObject::connect(BarycentricSimulationFalseBtn, SIGNAL(clicked()), QTClothSimulationClass, SLOT(setBarycentricFlagFalse()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), QTClothSimulationClass, SLOT(CreateSimulationModel()));
        QObject::connect(SimulationModel_N, SIGNAL(valueChanged(int)), QTClothSimulationClass, SLOT(getSimulationNodeNum1(int)));
        QObject::connect(SimulationModel_M, SIGNAL(valueChanged(int)), QTClothSimulationClass, SLOT(getSimulationNodeNum2(int)));
        QObject::connect(pushButton_3, SIGNAL(clicked()), QTClothSimulationClass, SLOT(CreateReferenceModel()));
        QObject::connect(resetBtn, SIGNAL(clicked()), QTClothSimulationClass, SLOT(ResetParam()));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), QTClothSimulationClass, SLOT(setReferenceTag(bool)));
        QObject::connect(radioButton_3, SIGNAL(toggled(bool)), QTClothSimulationClass, SLOT(setBothTag(bool)));
        QObject::connect(radioButton_2, SIGNAL(toggled(bool)), QTClothSimulationClass, SLOT(setSimulationTag(bool)));
        QObject::connect(ReferenceModel_Ks_Structural, SIGNAL(valueChanged(double)), QTClothSimulationClass, SLOT(setReferenceStructuralKs(double)));
        QObject::connect(ReferenceModel_Ks_Shear, SIGNAL(valueChanged(double)), QTClothSimulationClass, SLOT(setReferenceShearKs(double)));
        QObject::connect(ReferenceModel_Ks_Bend, SIGNAL(valueChanged(double)), QTClothSimulationClass, SLOT(setReferenceBendKs(double)));
        QObject::connect(ReferenceModel_Kd, SIGNAL(valueChanged(double)), QTClothSimulationClass, SLOT(setReferenceKd(double)));
        QObject::connect(SimulationModel_Kd, SIGNAL(valueChanged(double)), QTClothSimulationClass, SLOT(setSimulationKd(double)));
        QObject::connect(SimulationStartBtn, SIGNAL(clicked()), QTClothSimulationClass, SLOT(setupdateTag()));
        QObject::connect(SimulationStopBtn, SIGNAL(clicked()), QTClothSimulationClass, SLOT(setupdateTagFalse()));

        QMetaObject::connectSlotsByName(QTClothSimulationClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTClothSimulationClass)
    {
        QTClothSimulationClass->setWindowTitle(QApplication::translate("QTClothSimulationClass", "QTClothSimulation", 0));
        ReferenceModel_LabelKs->setText(QApplication::translate("QTClothSimulationClass", "Structural", 0));
        pushButton->setText(QApplication::translate("QTClothSimulationClass", "Optimize KS [Start]", 0));
        ReferenceModel_LabelN->setText(QApplication::translate("QTClothSimulationClass", "N", 0));
        ReferenceModel_LabelM->setText(QApplication::translate("QTClothSimulationClass", "M", 0));
        ReferenceModel_LabelKd->setText(QApplication::translate("QTClothSimulationClass", "Kd", 0));
        ReferenceModel_LabelKs_2->setText(QApplication::translate("QTClothSimulationClass", "Shear", 0));
        ReferenceModel_LabelKs_3->setText(QApplication::translate("QTClothSimulationClass", "Bend", 0));
        pushButton_3->setText(QApplication::translate("QTClothSimulationClass", "Create Reference Model", 0));
        SimulationModel_LabelN->setText(QApplication::translate("QTClothSimulationClass", "N", 0));
        SimulationModel_LabelM->setText(QApplication::translate("QTClothSimulationClass", "M", 0));
        label_7->setText(QApplication::translate("QTClothSimulationClass", "Simulation Model", 0));
        label_6->setText(QApplication::translate("QTClothSimulationClass", "Structural", 0));
        label_8->setText(QApplication::translate("QTClothSimulationClass", "Shear", 0));
        label_9->setText(QApplication::translate("QTClothSimulationClass", "Bend", 0));
        label_5->setText(QApplication::translate("QTClothSimulationClass", "Kd", 0));
        pushButton_4->setText(QApplication::translate("QTClothSimulationClass", "Create Simulation Model", 0));
        label->setText(QApplication::translate("QTClothSimulationClass", "Reference Model", 0));
        BarycentricSimulationFalseBtn->setText(QApplication::translate("QTClothSimulationClass", "Optimize KS [Stop]", 0));
        resetBtn->setText(QApplication::translate("QTClothSimulationClass", "Clear", 0));
        SimulationStartBtn->setText(QApplication::translate("QTClothSimulationClass", "Simulation START", 0));
        radioButton->setText(QApplication::translate("QTClothSimulationClass", "Scene 1", 0));
        radioButton_2->setText(QApplication::translate("QTClothSimulationClass", "Scene 2", 0));
        radioButton_3->setText(QApplication::translate("QTClothSimulationClass", "Scene 3", 0));
        SimulationStopBtn->setText(QApplication::translate("QTClothSimulationClass", "Simulation STOP", 0));
    } // retranslateUi

};

namespace Ui {
    class QTClothSimulationClass: public Ui_QTClothSimulationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCLOTHSIMULATION_H
