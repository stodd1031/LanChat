/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *home;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *chatRoom;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QWidget *connect;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_username;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 800, 600));
        home = new QWidget();
        home->setObjectName(QString::fromUtf8("home"));
        pushButton = new QPushButton(home);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(304, 93, 123, 30));
        pushButton_2 = new QPushButton(home);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(304, 180, 123, 40));
        stackedWidget->addWidget(home);
        chatRoom = new QWidget();
        chatRoom->setObjectName(QString::fromUtf8("chatRoom"));
        textEdit = new QTextEdit(chatRoom);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(5, 6, 788, 547));
        textEdit->setReadOnly(true);
        lineEdit = new QLineEdit(chatRoom);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(3, 557, 791, 38));
        stackedWidget->addWidget(chatRoom);
        connect = new QWidget();
        connect->setObjectName(QString::fromUtf8("connect"));
        pushButton_3 = new QPushButton(connect);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(327, 337, 113, 23));
        lineEdit_ip = new QLineEdit(connect);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
        lineEdit_ip->setGeometry(QRect(327, 220, 113, 23));
        lineEdit_port = new QLineEdit(connect);
        lineEdit_port->setObjectName(QString::fromUtf8("lineEdit_port"));
        lineEdit_port->setGeometry(QRect(324, 268, 113, 23));
        label = new QLabel(connect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(330, 244, 104, 23));
        label_2 = new QLabel(connect);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(328, 198, 104, 23));
        label_3 = new QLabel(connect);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(334, 142, 104, 23));
        lineEdit_username = new QLineEdit(connect);
        lineEdit_username->setObjectName(QString::fromUtf8("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(329, 170, 113, 23));
        stackedWidget->addWidget(connect);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Host Lobby", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Join lobby", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "connect", nullptr));
        lineEdit_ip->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        lineEdit_port->setPlaceholderText(QCoreApplication::translate("MainWindow", "8080", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "port", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ip", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "username", nullptr));
        lineEdit_username->setPlaceholderText(QCoreApplication::translate("MainWindow", "username", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
