/********************************************************************************
** Form generated from reading UI file 'platformwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLATFORMWINDOW_H
#define UI_PLATFORMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlatformWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *statsGroup;
    QGridLayout *gridLayout;
    QWidget *totalOrdersCard;
    QVBoxLayout *verticalLayout_stats1;
    QLabel *totalOrdersLabel;
    QWidget *pendingOrdersCard;
    QVBoxLayout *verticalLayout_stats2;
    QLabel *pendingOrdersLabel;
    QWidget *acceptedOrdersCard;
    QVBoxLayout *verticalLayout_stats3;
    QLabel *acceptedOrdersLabel;
    QWidget *inProgressOrdersCard;
    QVBoxLayout *verticalLayout_stats4;
    QLabel *inProgressOrdersLabel;
    QWidget *completedOrdersCard;
    QVBoxLayout *verticalLayout_stats5;
    QLabel *completedOrdersLabel;
    QWidget *onlineDriversCard;
    QVBoxLayout *verticalLayout_stats6;
    QLabel *onlineDriversLabel;
    QHBoxLayout *horizontalLayout_6;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *listTabWidget;
    QWidget *ordersTab;
    QVBoxLayout *verticalLayout;
    QListWidget *orderListWidget;
    QWidget *driversTab;
    QVBoxLayout *verticalLayout_2;
    QListWidget *driverListWidget;
    QGroupBox *logGroup;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *logTextEdit;
    QGroupBox *mapGroup;
    QVBoxLayout *verticalLayout_7;
    QGraphicsView *mapView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlatformWindow)
    {
        if (PlatformWindow->objectName().isEmpty())
            PlatformWindow->setObjectName("PlatformWindow");
        PlatformWindow->resize(1400, 900);
        centralwidget = new QWidget(PlatformWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        statsGroup = new QGroupBox(centralwidget);
        statsGroup->setObjectName("statsGroup");
        gridLayout = new QGridLayout(statsGroup);
        gridLayout->setObjectName("gridLayout");
        totalOrdersCard = new QWidget(statsGroup);
        totalOrdersCard->setObjectName("totalOrdersCard");
        verticalLayout_stats1 = new QVBoxLayout(totalOrdersCard);
        verticalLayout_stats1->setObjectName("verticalLayout_stats1");
        totalOrdersLabel = new QLabel(totalOrdersCard);
        totalOrdersLabel->setObjectName("totalOrdersLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        totalOrdersLabel->setFont(font);
        totalOrdersLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats1->addWidget(totalOrdersLabel);


        gridLayout->addWidget(totalOrdersCard, 0, 0, 1, 1);

        pendingOrdersCard = new QWidget(statsGroup);
        pendingOrdersCard->setObjectName("pendingOrdersCard");
        verticalLayout_stats2 = new QVBoxLayout(pendingOrdersCard);
        verticalLayout_stats2->setObjectName("verticalLayout_stats2");
        pendingOrdersLabel = new QLabel(pendingOrdersCard);
        pendingOrdersLabel->setObjectName("pendingOrdersLabel");
        pendingOrdersLabel->setFont(font);
        pendingOrdersLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats2->addWidget(pendingOrdersLabel);


        gridLayout->addWidget(pendingOrdersCard, 0, 1, 1, 1);

        acceptedOrdersCard = new QWidget(statsGroup);
        acceptedOrdersCard->setObjectName("acceptedOrdersCard");
        verticalLayout_stats3 = new QVBoxLayout(acceptedOrdersCard);
        verticalLayout_stats3->setObjectName("verticalLayout_stats3");
        acceptedOrdersLabel = new QLabel(acceptedOrdersCard);
        acceptedOrdersLabel->setObjectName("acceptedOrdersLabel");
        acceptedOrdersLabel->setFont(font);
        acceptedOrdersLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats3->addWidget(acceptedOrdersLabel);


        gridLayout->addWidget(acceptedOrdersCard, 0, 2, 1, 1);

        inProgressOrdersCard = new QWidget(statsGroup);
        inProgressOrdersCard->setObjectName("inProgressOrdersCard");
        verticalLayout_stats4 = new QVBoxLayout(inProgressOrdersCard);
        verticalLayout_stats4->setObjectName("verticalLayout_stats4");
        inProgressOrdersLabel = new QLabel(inProgressOrdersCard);
        inProgressOrdersLabel->setObjectName("inProgressOrdersLabel");
        inProgressOrdersLabel->setFont(font);
        inProgressOrdersLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats4->addWidget(inProgressOrdersLabel);


        gridLayout->addWidget(inProgressOrdersCard, 0, 3, 1, 1);

        completedOrdersCard = new QWidget(statsGroup);
        completedOrdersCard->setObjectName("completedOrdersCard");
        verticalLayout_stats5 = new QVBoxLayout(completedOrdersCard);
        verticalLayout_stats5->setObjectName("verticalLayout_stats5");
        completedOrdersLabel = new QLabel(completedOrdersCard);
        completedOrdersLabel->setObjectName("completedOrdersLabel");
        completedOrdersLabel->setFont(font);
        completedOrdersLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats5->addWidget(completedOrdersLabel);


        gridLayout->addWidget(completedOrdersCard, 0, 4, 1, 1);

        onlineDriversCard = new QWidget(statsGroup);
        onlineDriversCard->setObjectName("onlineDriversCard");
        verticalLayout_stats6 = new QVBoxLayout(onlineDriversCard);
        verticalLayout_stats6->setObjectName("verticalLayout_stats6");
        onlineDriversLabel = new QLabel(onlineDriversCard);
        onlineDriversLabel->setObjectName("onlineDriversLabel");
        onlineDriversLabel->setFont(font);
        onlineDriversLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_stats6->addWidget(onlineDriversLabel);


        gridLayout->addWidget(onlineDriversCard, 0, 5, 1, 1);


        verticalLayout_3->addWidget(statsGroup);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        leftWidget = new QWidget(centralwidget);
        leftWidget->setObjectName("leftWidget");
        leftWidget->setMaximumSize(QSize(400, 16777215));
        verticalLayout_4 = new QVBoxLayout(leftWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        listTabWidget = new QTabWidget(leftWidget);
        listTabWidget->setObjectName("listTabWidget");
        ordersTab = new QWidget();
        ordersTab->setObjectName("ordersTab");
        verticalLayout = new QVBoxLayout(ordersTab);
        verticalLayout->setObjectName("verticalLayout");
        orderListWidget = new QListWidget(ordersTab);
        orderListWidget->setObjectName("orderListWidget");

        verticalLayout->addWidget(orderListWidget);

        listTabWidget->addTab(ordersTab, QString());
        driversTab = new QWidget();
        driversTab->setObjectName("driversTab");
        verticalLayout_2 = new QVBoxLayout(driversTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        driverListWidget = new QListWidget(driversTab);
        driverListWidget->setObjectName("driverListWidget");

        verticalLayout_2->addWidget(driverListWidget);

        listTabWidget->addTab(driversTab, QString());

        verticalLayout_4->addWidget(listTabWidget);

        logGroup = new QGroupBox(leftWidget);
        logGroup->setObjectName("logGroup");
        verticalLayout_5 = new QVBoxLayout(logGroup);
        verticalLayout_5->setObjectName("verticalLayout_5");
        logTextEdit = new QTextEdit(logGroup);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);

        verticalLayout_5->addWidget(logTextEdit);


        verticalLayout_4->addWidget(logGroup);


        horizontalLayout_6->addWidget(leftWidget);

        mapGroup = new QGroupBox(centralwidget);
        mapGroup->setObjectName("mapGroup");
        verticalLayout_7 = new QVBoxLayout(mapGroup);
        verticalLayout_7->setObjectName("verticalLayout_7");
        mapView = new QGraphicsView(mapGroup);
        mapView->setObjectName("mapView");
        mapView->setMinimumSize(QSize(900, 700));

        verticalLayout_7->addWidget(mapView);


        horizontalLayout_6->addWidget(mapGroup);


        verticalLayout_3->addLayout(horizontalLayout_6);

        PlatformWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlatformWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1400, 17));
        PlatformWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlatformWindow);
        statusbar->setObjectName("statusbar");
        PlatformWindow->setStatusBar(statusbar);

        retranslateUi(PlatformWindow);

        listTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PlatformWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlatformWindow)
    {
        PlatformWindow->setWindowTitle(QCoreApplication::translate("PlatformWindow", "\345\271\263\345\217\260\347\233\221\346\216\247\347\253\257", nullptr));
        PlatformWindow->setStyleSheet(QCoreApplication::translate("PlatformWindow", "QMainWindow {\n"
"    background-color: #f5f7fa;\n"
"    border: none;\n"
"   }\n"
"   \n"
"   QGroupBox {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);\n"
"    border: 1px solid #e8e8e8;\n"
"    margin-bottom: 15px;\n"
"   }\n"
"   \n"
"   QTabWidget {\n"
"    background-color: white;\n"
"    border-radius: 10px;\n"
"    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);\n"
"    border: 1px solid #e8e8e8;\n"
"   }\n"
"   \n"
"   QTabBar::tab {\n"
"    background-color: white;\n"
"    border: 1px solid #e8e8e8;\n"
"    border-bottom: none;\n"
"    border-top-left-radius: 8px;\n"
"    border-top-right-radius: 8px;\n"
"    padding: 10px 20px;\n"
"    margin-right: 5px;\n"
"    color: #666666;\n"
"    font-weight: 500;\n"
"   }\n"
"   \n"
"   QTabBar::tab:selected {\n"
"    background-color: #00b2ff;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"   }\n"
"   \n"
"   QTabWidget::pane {\n"
"    border: 1px solid #e8e8e8;\n"
"    border-top: none;\n"
""
                        "    border-radius: 0 0 10px 10px;\n"
"    background-color: white;\n"
"   }\n"
"   \n"
"   QListWidget {\n"
"    border: 1px solid #e8e8e8;\n"
"    border-radius: 6px;\n"
"    background-color: white;\n"
"   }\n"
"   \n"
"   QTextEdit {\n"
"    border: 1px solid #e8e8e8;\n"
"    border-radius: 6px;\n"
"    background-color: white;\n"
"    font-family: 'Courier New', Courier, monospace;\n"
"    font-size: 12px;\n"
"   }\n"
"   \n"
"   QLabel {\n"
"    color: #333333;\n"
"   }\n"
"   \n"
"   .statLabel {\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    color: #00b2ff;\n"
"   }\n"
"   \n"
"   .statValue {\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"    color: #333333;\n"
"    margin-top: 5px;\n"
"   }\n"
"   \n"
"   .statCard {\n"
"    background-color: white;\n"
"    border-radius: 8px;\n"
"    box-shadow: 0 2px 4px rgba(0, 0, 0, 0.08);\n"
"    padding: 15px;\n"
"    text-align: center;\n"
"    border: 1px solid #e8e8e8;\n"
"   }", nullptr));
        statsGroup->setTitle(QCoreApplication::translate("PlatformWindow", "\350\277\220\350\220\245\346\214\207\346\240\207", nullptr));
        totalOrdersCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        totalOrdersLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        totalOrdersLabel->setText(QCoreApplication::translate("PlatformWindow", "\346\200\273\350\256\242\345\215\225\346\225\260\357\274\2320", nullptr));
        pendingOrdersCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        pendingOrdersLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        pendingOrdersLabel->setText(QCoreApplication::translate("PlatformWindow", "\345\276\205\346\264\276\345\215\225\357\274\2320", nullptr));
        acceptedOrdersCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        acceptedOrdersLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        acceptedOrdersLabel->setText(QCoreApplication::translate("PlatformWindow", "\345\267\262\346\216\245\345\215\225\357\274\2320", nullptr));
        inProgressOrdersCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        inProgressOrdersLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        inProgressOrdersLabel->setText(QCoreApplication::translate("PlatformWindow", "\350\241\214\347\250\213\344\270\255\357\274\2320", nullptr));
        completedOrdersCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        completedOrdersLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        completedOrdersLabel->setText(QCoreApplication::translate("PlatformWindow", "\345\267\262\345\256\214\346\210\220\357\274\2320", nullptr));
        onlineDriversCard->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statCard;", nullptr));
        onlineDriversLabel->setStyleSheet(QCoreApplication::translate("PlatformWindow", ".statLabel;", nullptr));
        onlineDriversLabel->setText(QCoreApplication::translate("PlatformWindow", "\345\234\250\347\272\277\345\217\270\346\234\272\357\274\2320", nullptr));
        listTabWidget->setTabText(listTabWidget->indexOf(ordersTab), QCoreApplication::translate("PlatformWindow", "\350\256\242\345\215\225\345\210\227\350\241\250", nullptr));
        listTabWidget->setTabText(listTabWidget->indexOf(driversTab), QCoreApplication::translate("PlatformWindow", "\345\217\270\346\234\272\345\210\227\350\241\250", nullptr));
        logGroup->setTitle(QCoreApplication::translate("PlatformWindow", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        mapGroup->setTitle(QCoreApplication::translate("PlatformWindow", "\345\205\250\345\261\200\345\234\260\345\233\276\347\233\221\346\216\247", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlatformWindow: public Ui_PlatformWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLATFORMWINDOW_H
