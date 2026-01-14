/********************************************************************************
** Form generated from reading UI file 'passengerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSENGERWINDOW_H
#define UI_PASSENGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PassengerWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *topWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *userInfoLabel;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *rideRequestGroup;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLineEdit *startLocationEdit;
    QLabel *label_2;
    QLineEdit *endLocationEdit;
    QLabel *label_3;
    QComboBox *carTypeCombo;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *requestRideBtn;
    QPushButton *cancelOrderBtn;
    QGroupBox *estimatedInfoGroup;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *distanceLabel;
    QLabel *timeLabel;
    QLabel *costLabel;
    QWidget *rightWidget;
    QVBoxLayout *verticalLayout_31;
    QGroupBox *mapGroup;
    QVBoxLayout *verticalLayout_5;
    QGraphicsView *mapView;
    QGroupBox *orderStatusGroup;
    QVBoxLayout *verticalLayout_6;
    QLabel *orderIdLabel;
    QLabel *statusLabel;
    QProgressBar *tripProgressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PassengerWindow)
    {
        if (PassengerWindow->objectName().isEmpty())
            PassengerWindow->setObjectName("PassengerWindow");
        PassengerWindow->resize(1200, 940);
        centralwidget = new QWidget(PassengerWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topWidget = new QWidget(centralwidget);
        topWidget->setObjectName("topWidget");
        horizontalLayout_4 = new QHBoxLayout(topWidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        userInfoLabel = new QLabel(topWidget);
        userInfoLabel->setObjectName("userInfoLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        userInfoLabel->setFont(font);

        horizontalLayout_4->addWidget(userInfoLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(topWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setMaximumSize(QSize(400, 16777215));
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        rideRequestGroup = new QGroupBox(leftWidget);
        rideRequestGroup->setObjectName("rideRequestGroup");
        rideRequestGroup->setFont(font);
        verticalLayout_3 = new QVBoxLayout(rideRequestGroup);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(rideRequestGroup);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);

        verticalLayout_3->addWidget(label);

        startLocationEdit = new QLineEdit(rideRequestGroup);
        startLocationEdit->setObjectName("startLocationEdit");
        QFont font2;
        font2.setPointSize(12);
        startLocationEdit->setFont(font2);
        startLocationEdit->setMinimumHeight(35);

        verticalLayout_3->addWidget(startLocationEdit);

        label_2 = new QLabel(rideRequestGroup);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        verticalLayout_3->addWidget(label_2);

        endLocationEdit = new QLineEdit(rideRequestGroup);
        endLocationEdit->setObjectName("endLocationEdit");
        endLocationEdit->setFont(font2);
        endLocationEdit->setMinimumHeight(35);

        verticalLayout_3->addWidget(endLocationEdit);

        label_3 = new QLabel(rideRequestGroup);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout_3->addWidget(label_3);

        carTypeCombo = new QComboBox(rideRequestGroup);
        carTypeCombo->addItem(QString());
        carTypeCombo->addItem(QString());
        carTypeCombo->setObjectName("carTypeCombo");
        carTypeCombo->setFont(font2);
        carTypeCombo->setMinimumHeight(35);

        verticalLayout_3->addWidget(carTypeCombo);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        requestRideBtn = new QPushButton(rideRequestGroup);
        requestRideBtn->setObjectName("requestRideBtn");
        requestRideBtn->setFont(font);
        requestRideBtn->setMinimumHeight(45);

        horizontalLayout_2->addWidget(requestRideBtn);

        cancelOrderBtn = new QPushButton(rideRequestGroup);
        cancelOrderBtn->setObjectName("cancelOrderBtn");
        cancelOrderBtn->setFont(font);
        cancelOrderBtn->setMinimumHeight(45);

        horizontalLayout_2->addWidget(cancelOrderBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(rideRequestGroup);

        estimatedInfoGroup = new QGroupBox(leftWidget);
        estimatedInfoGroup->setObjectName("estimatedInfoGroup");
        estimatedInfoGroup->setFont(font);
        verticalLayout_4 = new QVBoxLayout(estimatedInfoGroup);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        distanceLabel = new QLabel(estimatedInfoGroup);
        distanceLabel->setObjectName("distanceLabel");
        distanceLabel->setFont(font2);

        horizontalLayout_5->addWidget(distanceLabel);

        timeLabel = new QLabel(estimatedInfoGroup);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setFont(font2);

        horizontalLayout_5->addWidget(timeLabel);


        verticalLayout_4->addLayout(horizontalLayout_5);

        costLabel = new QLabel(estimatedInfoGroup);
        costLabel->setObjectName("costLabel");
        costLabel->setFont(font);

        verticalLayout_4->addWidget(costLabel);


        verticalLayout_2->addWidget(estimatedInfoGroup);


        horizontalLayout->addWidget(leftWidget);

        rightWidget = new QWidget(centralwidget);
        rightWidget->setObjectName("rightWidget");
        verticalLayout_31 = new QVBoxLayout(rightWidget);
        verticalLayout_31->setObjectName("verticalLayout_31");
        mapGroup = new QGroupBox(rightWidget);
        mapGroup->setObjectName("mapGroup");
        verticalLayout_5 = new QVBoxLayout(mapGroup);
        verticalLayout_5->setObjectName("verticalLayout_5");
        mapView = new QGraphicsView(mapGroup);
        mapView->setObjectName("mapView");
        mapView->setMinimumSize(QSize(700, 500));

        verticalLayout_5->addWidget(mapView);


        verticalLayout_31->addWidget(mapGroup);

        orderStatusGroup = new QGroupBox(rightWidget);
        orderStatusGroup->setObjectName("orderStatusGroup");
        verticalLayout_6 = new QVBoxLayout(orderStatusGroup);
        verticalLayout_6->setObjectName("verticalLayout_6");
        orderIdLabel = new QLabel(orderStatusGroup);
        orderIdLabel->setObjectName("orderIdLabel");

        verticalLayout_6->addWidget(orderIdLabel);

        statusLabel = new QLabel(orderStatusGroup);
        statusLabel->setObjectName("statusLabel");

        verticalLayout_6->addWidget(statusLabel);

        tripProgressBar = new QProgressBar(orderStatusGroup);
        tripProgressBar->setObjectName("tripProgressBar");
        tripProgressBar->setValue(0);

        verticalLayout_6->addWidget(tripProgressBar);


        verticalLayout_31->addWidget(orderStatusGroup);


        horizontalLayout->addWidget(rightWidget);


        verticalLayout->addLayout(horizontalLayout);

        PassengerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PassengerWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 17));
        PassengerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PassengerWindow);
        statusbar->setObjectName("statusbar");
        PassengerWindow->setStatusBar(statusbar);

        retranslateUi(PassengerWindow);

        QMetaObject::connectSlotsByName(PassengerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PassengerWindow)
    {
        PassengerWindow->setWindowTitle(QCoreApplication::translate("PassengerWindow", "\344\271\230\345\256\242\347\253\257", nullptr));
        userInfoLabel->setText(QCoreApplication::translate("PassengerWindow", "\344\271\230\345\256\242\357\274\232\345\274\240\344\270\211", nullptr));
        rideRequestGroup->setTitle(QCoreApplication::translate("PassengerWindow", "\345\217\253\350\275\246\345\212\237\350\203\275", nullptr));
        label->setText(QCoreApplication::translate("PassengerWindow", "\350\265\267\347\202\271\357\274\232", nullptr));
        startLocationEdit->setText(QCoreApplication::translate("PassengerWindow", "0,0", nullptr));
        label_2->setText(QCoreApplication::translate("PassengerWindow", "\347\273\210\347\202\271\357\274\232", nullptr));
        endLocationEdit->setText(QCoreApplication::translate("PassengerWindow", "0,0", nullptr));
        label_3->setText(QCoreApplication::translate("PassengerWindow", "\350\275\246\345\236\213\357\274\232", nullptr));
        carTypeCombo->setItemText(0, QCoreApplication::translate("PassengerWindow", "\345\277\253\350\275\246", nullptr));
        carTypeCombo->setItemText(1, QCoreApplication::translate("PassengerWindow", "\344\270\223\350\275\246", nullptr));

        requestRideBtn->setText(QCoreApplication::translate("PassengerWindow", "\345\217\253\350\275\246", nullptr));
        cancelOrderBtn->setText(QCoreApplication::translate("PassengerWindow", "\345\217\226\346\266\210\350\256\242\345\215\225", nullptr));
        estimatedInfoGroup->setTitle(QCoreApplication::translate("PassengerWindow", "\351\242\204\344\274\260\344\277\241\346\201\257", nullptr));
        distanceLabel->setText(QCoreApplication::translate("PassengerWindow", "\350\267\235\347\246\273\357\274\2320.0 km", nullptr));
        timeLabel->setText(QCoreApplication::translate("PassengerWindow", "\346\227\266\351\225\277\357\274\2320.0 \345\210\206\351\222\237", nullptr));
        costLabel->setText(QCoreApplication::translate("PassengerWindow", "\350\264\271\347\224\250\357\274\232\302\2450.00", nullptr));
        mapGroup->setTitle(QCoreApplication::translate("PassengerWindow", "\345\234\260\345\233\276", nullptr));
        orderStatusGroup->setTitle(QCoreApplication::translate("PassengerWindow", "\350\256\242\345\215\225\347\212\266\346\200\201", nullptr));
        orderIdLabel->setText(QCoreApplication::translate("PassengerWindow", "\350\256\242\345\215\225\347\274\226\345\217\267\357\274\232", nullptr));
        statusLabel->setText(QCoreApplication::translate("PassengerWindow", "\347\212\266\346\200\201\357\274\232\345\276\205\346\264\276\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PassengerWindow: public Ui_PassengerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSENGERWINDOW_H
