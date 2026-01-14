/********************************************************************************
** Form generated from reading UI file 'driverwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRIVERWINDOW_H
#define UI_DRIVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DriverWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *topWidget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *driverInfoLabel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *onlineBtn;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout_6;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *orderInfoGroup;
    QVBoxLayout *verticalLayout_5;
    QLabel *orderIdLabel;
    QLabel *passengerInfoLabel;
    QLabel *startLocationLabel;
    QLabel *endLocationLabel;
    QLabel *estimatedDistanceLabel;
    QLabel *estimatedTimeLabel;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *acceptOrderBtn;
    QPushButton *rejectOrderBtn;
    QGroupBox *tripControlGroup;
    QVBoxLayout *verticalLayout_6;
    QLabel *tripStatusLabel;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *startTripBtn;
    QPushButton *endTripBtn;
    QProgressBar *tripProgressBar;
    QLabel *drivenDistanceLabel;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *navigationGroup;
    QVBoxLayout *verticalLayout_8;
    QGraphicsView *mapView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DriverWindow)
    {
        if (DriverWindow->objectName().isEmpty())
            DriverWindow->setObjectName("DriverWindow");
        DriverWindow->resize(1200, 800);
        centralwidget = new QWidget(DriverWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        topWidget = new QWidget(centralwidget);
        topWidget->setObjectName("topWidget");
        horizontalLayout_7 = new QHBoxLayout(topWidget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        driverInfoLabel = new QLabel(topWidget);
        driverInfoLabel->setObjectName("driverInfoLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        driverInfoLabel->setFont(font);

        horizontalLayout_7->addWidget(driverInfoLabel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        onlineBtn = new QPushButton(topWidget);
        onlineBtn->setObjectName("onlineBtn");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        onlineBtn->setFont(font1);

        horizontalLayout_7->addWidget(onlineBtn);

        statusLabel = new QLabel(topWidget);
        statusLabel->setObjectName("statusLabel");
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        statusLabel->setFont(font2);

        horizontalLayout_7->addWidget(statusLabel);


        verticalLayout_3->addWidget(topWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setMaximumSize(QSize(350, 16777215));
        verticalLayout_4 = new QVBoxLayout(leftWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        orderInfoGroup = new QGroupBox(leftWidget);
        orderInfoGroup->setObjectName("orderInfoGroup");
        verticalLayout_5 = new QVBoxLayout(orderInfoGroup);
        verticalLayout_5->setObjectName("verticalLayout_5");
        orderIdLabel = new QLabel(orderInfoGroup);
        orderIdLabel->setObjectName("orderIdLabel");

        verticalLayout_5->addWidget(orderIdLabel);

        passengerInfoLabel = new QLabel(orderInfoGroup);
        passengerInfoLabel->setObjectName("passengerInfoLabel");

        verticalLayout_5->addWidget(passengerInfoLabel);

        startLocationLabel = new QLabel(orderInfoGroup);
        startLocationLabel->setObjectName("startLocationLabel");

        verticalLayout_5->addWidget(startLocationLabel);

        endLocationLabel = new QLabel(orderInfoGroup);
        endLocationLabel->setObjectName("endLocationLabel");

        verticalLayout_5->addWidget(endLocationLabel);

        estimatedDistanceLabel = new QLabel(orderInfoGroup);
        estimatedDistanceLabel->setObjectName("estimatedDistanceLabel");

        verticalLayout_5->addWidget(estimatedDistanceLabel);

        estimatedTimeLabel = new QLabel(orderInfoGroup);
        estimatedTimeLabel->setObjectName("estimatedTimeLabel");

        verticalLayout_5->addWidget(estimatedTimeLabel);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        acceptOrderBtn = new QPushButton(orderInfoGroup);
        acceptOrderBtn->setObjectName("acceptOrderBtn");
        acceptOrderBtn->setFont(font1);

        horizontalLayout_4->addWidget(acceptOrderBtn);

        rejectOrderBtn = new QPushButton(orderInfoGroup);
        rejectOrderBtn->setObjectName("rejectOrderBtn");
        rejectOrderBtn->setFont(font1);

        horizontalLayout_4->addWidget(rejectOrderBtn);


        verticalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(orderInfoGroup);

        tripControlGroup = new QGroupBox(leftWidget);
        tripControlGroup->setObjectName("tripControlGroup");
        verticalLayout_6 = new QVBoxLayout(tripControlGroup);
        verticalLayout_6->setObjectName("verticalLayout_6");
        tripStatusLabel = new QLabel(tripControlGroup);
        tripStatusLabel->setObjectName("tripStatusLabel");

        verticalLayout_6->addWidget(tripStatusLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        startTripBtn = new QPushButton(tripControlGroup);
        startTripBtn->setObjectName("startTripBtn");
        startTripBtn->setFont(font1);

        horizontalLayout_5->addWidget(startTripBtn);

        endTripBtn = new QPushButton(tripControlGroup);
        endTripBtn->setObjectName("endTripBtn");
        endTripBtn->setFont(font1);

        horizontalLayout_5->addWidget(endTripBtn);


        verticalLayout_6->addLayout(horizontalLayout_5);

        tripProgressBar = new QProgressBar(tripControlGroup);
        tripProgressBar->setObjectName("tripProgressBar");
        tripProgressBar->setValue(0);

        verticalLayout_6->addWidget(tripProgressBar);

        drivenDistanceLabel = new QLabel(tripControlGroup);
        drivenDistanceLabel->setObjectName("drivenDistanceLabel");

        verticalLayout_6->addWidget(drivenDistanceLabel);


        verticalLayout_4->addWidget(tripControlGroup);


        horizontalLayout_6->addWidget(leftWidget);

        rightWidget = new QWidget(centralwidget);
        rightWidget->setObjectName("rightWidget");
        verticalLayout_7 = new QVBoxLayout(rightWidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        navigationGroup = new QGroupBox(rightWidget);
        navigationGroup->setObjectName("navigationGroup");
        verticalLayout_8 = new QVBoxLayout(navigationGroup);
        verticalLayout_8->setObjectName("verticalLayout_8");
        mapView = new QGraphicsView(navigationGroup);
        mapView->setObjectName("mapView");
        mapView->setMinimumSize(QSize(700, 600));

        verticalLayout_8->addWidget(mapView);


        verticalLayout_7->addWidget(navigationGroup);


        horizontalLayout_6->addWidget(rightWidget);


        verticalLayout_3->addLayout(horizontalLayout_6);

        DriverWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DriverWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 17));
        DriverWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DriverWindow);
        statusbar->setObjectName("statusbar");
        DriverWindow->setStatusBar(statusbar);

        retranslateUi(DriverWindow);

        QMetaObject::connectSlotsByName(DriverWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DriverWindow)
    {
        DriverWindow->setWindowTitle(QCoreApplication::translate("DriverWindow", "\345\217\270\346\234\272\347\253\257", nullptr));
        DriverWindow->setStyleSheet(QCoreApplication::translate("DriverWindow", "QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"    border: none;\n"
"   }\n"
"   \n"
"   QGroupBox {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);\n"
"    border: 1px solid #e8e8e8;\n"
"   }\n"
"   \n"
"   QPushButton {\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);\n"
"   }\n"
"   \n"
"   QPushButton:hover {\n"
"    box-shadow: 0 3px 6px rgba(0, 0, 0, 0.15);\n"
"   }\n"
"   \n"
"   QPushButton:pressed {\n"
"    box-shadow: 0 1px 2px rgba(0, 0, 0, 0.1);\n"
"   }\n"
"   \n"
"   QProgressBar {\n"
"    border-radius: 6px;\n"
"    background-color: #f0f0f0;\n"
"    height: 12px;\n"
"   }\n"
"   \n"
"   QProgressBar::chunk {\n"
"    background-color: #52c41a;\n"
"    border-radius: 6px;\n"
"   }\n"
"   \n"
"   QLabel {\n"
"    color: #333333;\n"
"   }\n"
"   \n"
"   .titleLabel {\n"
"    font-size: 16px;\n"
"    font-weight: bold;\n"
"    col"
                        "or: #333333;\n"
"   }\n"
"   \n"
"   .valueLabel {\n"
"    font-size: 14px;\n"
"    color: #666666;\n"
"   }\n"
"   \n"
"   .statusOnline {\n"
"    color: #52c41a;\n"
"    font-weight: bold;\n"
"   }\n"
"   \n"
"   .statusOffline {\n"
"    color: #ff4d4f;\n"
"    font-weight: bold;\n"
"   }\n"
"   \n"
"   .statusBusy {\n"
"    color: #fa8c16;\n"
"    font-weight: bold;\n"
"   }", nullptr));
        topWidget->setStyleSheet(QCoreApplication::translate("DriverWindow", "QWidget {\n"
"        background-color: white;\n"
"        border-radius: 10px;\n"
"        box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);\n"
"        padding: 15px;\n"
"       }", nullptr));
        driverInfoLabel->setText(QCoreApplication::translate("DriverWindow", "\345\217\270\346\234\272\357\274\232\346\235\216\345\233\233 | \346\271\230A12345 | \345\244\247\344\274\227\346\234\227\351\200\270", nullptr));
        driverInfoLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #52c41a;", nullptr));
        onlineBtn->setStyleSheet(QCoreApplication::translate("DriverWindow", "background-color: #52c41a; color: white;", nullptr));
        onlineBtn->setText(QCoreApplication::translate("DriverWindow", "\344\270\212\347\272\277", nullptr));
        statusLabel->setText(QCoreApplication::translate("DriverWindow", "\345\275\223\345\211\215\347\212\266\346\200\201\357\274\232\347\246\273\347\272\277", nullptr));
        statusLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #ff4d4f;", nullptr));
        orderInfoGroup->setTitle(QCoreApplication::translate("DriverWindow", "\350\256\242\345\215\225\344\277\241\346\201\257", nullptr));
        orderIdLabel->setText(QCoreApplication::translate("DriverWindow", "\350\256\242\345\215\225\347\274\226\345\217\267\357\274\232", nullptr));
        orderIdLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        passengerInfoLabel->setText(QCoreApplication::translate("DriverWindow", "\344\271\230\345\256\242\357\274\232", nullptr));
        passengerInfoLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        startLocationLabel->setText(QCoreApplication::translate("DriverWindow", "\350\265\267\347\202\271\357\274\232", nullptr));
        startLocationLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        endLocationLabel->setText(QCoreApplication::translate("DriverWindow", "\347\273\210\347\202\271\357\274\232", nullptr));
        endLocationLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        estimatedDistanceLabel->setText(QCoreApplication::translate("DriverWindow", "\351\242\204\344\274\260\350\267\235\347\246\273\357\274\232", nullptr));
        estimatedDistanceLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        estimatedTimeLabel->setText(QCoreApplication::translate("DriverWindow", "\351\242\204\344\274\260\346\227\266\351\225\277\357\274\232", nullptr));
        estimatedTimeLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        acceptOrderBtn->setStyleSheet(QCoreApplication::translate("DriverWindow", "background-color: #52c41a; color: white;", nullptr));
        acceptOrderBtn->setText(QCoreApplication::translate("DriverWindow", "\346\216\245\345\215\225", nullptr));
        rejectOrderBtn->setStyleSheet(QCoreApplication::translate("DriverWindow", "background-color: #ff4d4f; color: white;", nullptr));
        rejectOrderBtn->setText(QCoreApplication::translate("DriverWindow", "\346\213\222\345\215\225", nullptr));
        tripControlGroup->setTitle(QCoreApplication::translate("DriverWindow", "\350\241\214\347\250\213\346\216\247\345\210\266", nullptr));
        tripStatusLabel->setText(QCoreApplication::translate("DriverWindow", "\350\241\214\347\250\213\347\212\266\346\200\201\357\274\232\346\234\252\345\274\200\345\247\213", nullptr));
        tripStatusLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #fa8c16; font-weight: bold;", nullptr));
        startTripBtn->setStyleSheet(QCoreApplication::translate("DriverWindow", "background-color: #00b2ff; color: white;", nullptr));
        startTripBtn->setText(QCoreApplication::translate("DriverWindow", "\345\274\200\345\247\213\350\241\214\347\250\213", nullptr));
        endTripBtn->setStyleSheet(QCoreApplication::translate("DriverWindow", "background-color: #fa8c16; color: white;", nullptr));
        endTripBtn->setText(QCoreApplication::translate("DriverWindow", "\347\273\223\346\235\237\350\241\214\347\250\213", nullptr));
        drivenDistanceLabel->setText(QCoreApplication::translate("DriverWindow", "\345\267\262\350\241\214\351\251\266\351\207\214\347\250\213\357\274\2320.0 km", nullptr));
        drivenDistanceLabel->setStyleSheet(QCoreApplication::translate("DriverWindow", "color: #666666;", nullptr));
        rightWidget->setStyleSheet(QCoreApplication::translate("DriverWindow", "QWidget {\n"
"          background-color: white;\n"
"          border-radius: 10px;\n"
"          box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);\n"
"        }", nullptr));
        navigationGroup->setTitle(QCoreApplication::translate("DriverWindow", "\345\257\274\350\210\252\345\234\260\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DriverWindow: public Ui_DriverWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVERWINDOW_H
