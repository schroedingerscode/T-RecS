/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *primaryCamera;
    QPushButton *switchStreamButton;
    QGraphicsView *secondaryCamera;
    QFrame *controlFrame;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *upDirButton;
    QPushButton *downDirButton;
    QPushButton *leftDirButton;
    QPushButton *rightDirButton;
    QLabel *label;
    QLabel *x_freq_disp;
    QLabel *y_freq_disp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 502);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(960, 502));
        MainWindow->setMaximumSize(QSize(960, 502));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(85, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(106, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(42, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(56, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        MainWindow->setPalette(palette);
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        primaryCamera = new QGraphicsView(centralWidget);
        primaryCamera->setObjectName(QStringLiteral("primaryCamera"));
        primaryCamera->setGeometry(QRect(0, 0, 640, 480));
        primaryCamera->setFocusPolicy(Qt::NoFocus);
        switchStreamButton = new QPushButton(centralWidget);
        switchStreamButton->setObjectName(QStringLiteral("switchStreamButton"));
        switchStreamButton->setGeometry(QRect(760, 250, 80, 21));
        switchStreamButton->setFocusPolicy(Qt::NoFocus);
        switchStreamButton->setCheckable(false);
        switchStreamButton->setAutoRepeat(false);
        secondaryCamera = new QGraphicsView(centralWidget);
        secondaryCamera->setObjectName(QStringLiteral("secondaryCamera"));
        secondaryCamera->setGeometry(QRect(640, 0, 320, 240));
        secondaryCamera->setFocusPolicy(Qt::NoFocus);
        controlFrame = new QFrame(centralWidget);
        controlFrame->setObjectName(QStringLiteral("controlFrame"));
        controlFrame->setGeometry(QRect(640, 308, 320, 171));
        controlFrame->setFocusPolicy(Qt::NoFocus);
        controlFrame->setFrameShape(QFrame::Box);
        controlFrame->setLineWidth(3);
        gridLayoutWidget = new QWidget(controlFrame);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 27, 261, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        upDirButton = new QPushButton(gridLayoutWidget);
        upDirButton->setObjectName(QStringLiteral("upDirButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(upDirButton->sizePolicy().hasHeightForWidth());
        upDirButton->setSizePolicy(sizePolicy1);
        upDirButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(upDirButton, 0, 1, 1, 1);

        downDirButton = new QPushButton(gridLayoutWidget);
        downDirButton->setObjectName(QStringLiteral("downDirButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(downDirButton->sizePolicy().hasHeightForWidth());
        downDirButton->setSizePolicy(sizePolicy2);
        downDirButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(downDirButton, 1, 1, 1, 1);

        leftDirButton = new QPushButton(gridLayoutWidget);
        leftDirButton->setObjectName(QStringLiteral("leftDirButton"));
        sizePolicy1.setHeightForWidth(leftDirButton->sizePolicy().hasHeightForWidth());
        leftDirButton->setSizePolicy(sizePolicy1);
        leftDirButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(leftDirButton, 1, 0, 1, 1);

        rightDirButton = new QPushButton(gridLayoutWidget);
        rightDirButton->setObjectName(QStringLiteral("rightDirButton"));
        sizePolicy1.setHeightForWidth(rightDirButton->sizePolicy().hasHeightForWidth());
        rightDirButton->setSizePolicy(sizePolicy1);
        rightDirButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(rightDirButton, 1, 2, 1, 1);

        label = new QLabel(controlFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 3, 261, 20));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAutoFillBackground(false);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        x_freq_disp = new QLabel(centralWidget);
        x_freq_disp->setObjectName(QStringLiteral("x_freq_disp"));
        x_freq_disp->setGeometry(QRect(660, 290, 125, 15));
        y_freq_disp = new QLabel(centralWidget);
        y_freq_disp->setObjectName(QStringLiteral("y_freq_disp"));
        y_freq_disp->setGeometry(QRect(810, 290, 125, 15));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        switchStreamButton->setText(QApplication::translate("MainWindow", "Switch", 0));
        upDirButton->setText(QApplication::translate("MainWindow", "Up", 0));
        downDirButton->setText(QApplication::translate("MainWindow", "Down", 0));
        leftDirButton->setText(QApplication::translate("MainWindow", "Left", 0));
        rightDirButton->setText(QApplication::translate("MainWindow", "Right", 0));
        label->setText(QApplication::translate("MainWindow", "Telescope Direction Controls", 0));
        x_freq_disp->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        y_freq_disp->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
