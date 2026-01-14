/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QWidget *buttonWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *passengerBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *driverBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *platformBtn;
    QSpacerItem *horizontalSpacer_4;
    QLabel *infoLabel;
    QWidget *registerWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *registerPassengerBtn;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *registerDriverBtn;
    QSpacerItem *horizontalSpacer_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        titleLabel->setFont(font);

        verticalLayout->addWidget(titleLabel);

        buttonWidget = new QWidget(centralwidget);
        buttonWidget->setObjectName("buttonWidget");
        horizontalLayout = new QHBoxLayout(buttonWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        passengerBtn = new QPushButton(buttonWidget);
        passengerBtn->setObjectName("passengerBtn");
        passengerBtn->setMinimumSize(QSize(220, 180));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        passengerBtn->setFont(font1);

        horizontalLayout->addWidget(passengerBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        driverBtn = new QPushButton(buttonWidget);
        driverBtn->setObjectName("driverBtn");
        driverBtn->setMinimumSize(QSize(220, 180));
        driverBtn->setFont(font1);

        horizontalLayout->addWidget(driverBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        platformBtn = new QPushButton(buttonWidget);
        platformBtn->setObjectName("platformBtn");
        platformBtn->setMinimumSize(QSize(220, 180));
        platformBtn->setFont(font1);

        horizontalLayout->addWidget(platformBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(buttonWidget);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setAlignment(Qt::AlignCenter);
        QFont font2;
        font2.setPointSize(12);
        infoLabel->setFont(font2);

        verticalLayout->addWidget(infoLabel);

        registerWidget = new QWidget(centralwidget);
        registerWidget->setObjectName("registerWidget");
        horizontalLayout_2 = new QHBoxLayout(registerWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        registerPassengerBtn = new QPushButton(registerWidget);
        registerPassengerBtn->setObjectName("registerPassengerBtn");
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        registerPassengerBtn->setFont(font3);

        horizontalLayout_2->addWidget(registerPassengerBtn);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        registerDriverBtn = new QPushButton(registerWidget);
        registerDriverBtn->setObjectName("registerDriverBtn");
        registerDriverBtn->setFont(font3);

        horizontalLayout_2->addWidget(registerDriverBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout->addWidget(registerWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\273\264\346\273\264\345\207\272\350\241\214\346\250\241\346\213\237\347\263\273\347\273\237", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"    border: none;\n"
"   }", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\346\273\264\346\273\264\345\207\272\350\241\214\346\250\241\346\213\237\347\263\273\347\273\237", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"        color: #00b2ff;\n"
"        text-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);\n"
"       }", nullptr));
        passengerBtn->setText(QCoreApplication::translate("MainWindow", "\344\271\230\345\256\242\347\253\257", nullptr));
        passengerBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"           background-color: #00b2ff;\n"
"           color: white;\n"
"           border-radius: 15px;\n"
"           box-shadow: 0 4px 12px rgba(0, 178, 255, 0.3);\n"
"           border: none;\n"
"          }\n"
"          QPushButton:hover {\n"
"           background-color: #0099cc;\n"
"           box-shadow: 0 6px 16px rgba(0, 178, 255, 0.4);\n"
"           transform: translateY(-2px);\n"
"          }\n"
"          QPushButton:pressed {\n"
"           background-color: #0088b3;\n"
"           box-shadow: 0 2px 8px rgba(0, 178, 255, 0.2);\n"
"           transform: translateY(0);\n"
"          }", nullptr));
        driverBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\270\346\234\272\347\253\257", nullptr));
        driverBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"           background-color: #52c41a;\n"
"           color: white;\n"
"           border-radius: 15px;\n"
"           box-shadow: 0 4px 12px rgba(82, 196, 26, 0.3);\n"
"           border: none;\n"
"          }\n"
"          QPushButton:hover {\n"
"           background-color: #43a047;\n"
"           box-shadow: 0 6px 16px rgba(82, 196, 26, 0.4);\n"
"           transform: translateY(-2px);\n"
"          }\n"
"          QPushButton:pressed {\n"
"           background-color: #388e3c;\n"
"           box-shadow: 0 2px 8px rgba(82, 196, 26, 0.2);\n"
"           transform: translateY(0);\n"
"          }", nullptr));
        platformBtn->setText(QCoreApplication::translate("MainWindow", "\345\271\263\345\217\260\347\233\221\346\216\247\347\253\257", nullptr));
        platformBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"           background-color: #fa8c16;\n"
"           color: white;\n"
"           border-radius: 15px;\n"
"           box-shadow: 0 4px 12px rgba(250, 140, 22, 0.3);\n"
"           border: none;\n"
"          }\n"
"          QPushButton:hover {\n"
"           background-color: #f57c00;\n"
"           box-shadow: 0 6px 16px rgba(250, 140, 22, 0.4);\n"
"           transform: translateY(-2px);\n"
"          }\n"
"          QPushButton:pressed {\n"
"           background-color: #ef6c00;\n"
"           box-shadow: 0 2px 8px rgba(250, 140, 22, 0.2);\n"
"           transform: translateY(0);\n"
"          }", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\346\202\250\347\232\204\350\247\222\350\211\262\350\277\233\345\205\245\347\233\270\345\272\224\345\212\237\350\203\275\347\225\214\351\235\242", nullptr));
        infoLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "QLabel {\n"
"        color: #666666;\n"
"        font-weight: 500;\n"
"       }", nullptr));
        registerWidget->setStyleSheet(QCoreApplication::translate("MainWindow", "QWidget {\n"
"        background-color: transparent;\n"
"       }", nullptr));
        registerPassengerBtn->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214\344\271\230\345\256\242", nullptr));
        registerPassengerBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"           background-color: #52c41a;\n"
"           color: white;\n"
"           border-radius: 8px;\n"
"           padding: 8px 20px;\n"
"           box-shadow: 0 2px 4px rgba(82, 196, 26, 0.2);\n"
"           border: none;\n"
"          }\n"
"          QPushButton:hover {\n"
"           background-color: #43a047;\n"
"           box-shadow: 0 3px 6px rgba(82, 196, 26, 0.3);\n"
"          }\n"
"          QPushButton:pressed {\n"
"           background-color: #388e3c;\n"
"           box-shadow: 0 1px 2px rgba(82, 196, 26, 0.2);\n"
"          }", nullptr));
        registerDriverBtn->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214\345\217\270\346\234\272", nullptr));
        registerDriverBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton {\n"
"           background-color: #fa8c16;\n"
"           color: white;\n"
"           border-radius: 8px;\n"
"           padding: 8px 20px;\n"
"           box-shadow: 0 2px 4px rgba(250, 140, 22, 0.2);\n"
"           border: none;\n"
"          }\n"
"          QPushButton:hover {\n"
"           background-color: #f57c00;\n"
"           box-shadow: 0 3px 6px rgba(250, 140, 22, 0.3);\n"
"          }\n"
"          QPushButton:pressed {\n"
"           background-color: #ef6c00;\n"
"           box-shadow: 0 1px 2px rgba(250, 140, 22, 0.2);\n"
"          }", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
