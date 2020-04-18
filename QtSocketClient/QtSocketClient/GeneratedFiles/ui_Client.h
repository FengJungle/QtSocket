/********************************************************************************
** Form generated from reading UI file 'Client.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_filename;
    QProgressBar *progressBar;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QPushButton *pushButton_send;
    QPushButton *pushButton_openFile;
    QPushButton *pushButton_sendFile;

    void setupUi(QWidget *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QStringLiteral("ClientClass"));
        ClientClass->resize(600, 400);
        textEdit = new QTextEdit(ClientClass);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 10, 391, 291));
        lineEdit = new QLineEdit(ClientClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 310, 391, 31));
        lineEdit_filename = new QLineEdit(ClientClass);
        lineEdit_filename->setObjectName(QStringLiteral("lineEdit_filename"));
        lineEdit_filename->setGeometry(QRect(430, 170, 161, 21));
        progressBar = new QProgressBar(ClientClass);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(430, 240, 161, 23));
        progressBar->setValue(0);
        pushButton_connect = new QPushButton(ClientClass);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(430, 100, 75, 23));
        pushButton_disconnect = new QPushButton(ClientClass);
        pushButton_disconnect->setObjectName(QStringLiteral("pushButton_disconnect"));
        pushButton_disconnect->setGeometry(QRect(510, 100, 75, 23));
        pushButton_send = new QPushButton(ClientClass);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(430, 320, 75, 23));
        pushButton_openFile = new QPushButton(ClientClass);
        pushButton_openFile->setObjectName(QStringLiteral("pushButton_openFile"));
        pushButton_openFile->setGeometry(QRect(430, 210, 75, 23));
        pushButton_sendFile = new QPushButton(ClientClass);
        pushButton_sendFile->setObjectName(QStringLiteral("pushButton_sendFile"));
        pushButton_sendFile->setGeometry(QRect(520, 210, 75, 23));

        retranslateUi(ClientClass);

        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QWidget *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "QtSocketClient", 0));
        pushButton_connect->setText(QApplication::translate("ClientClass", "Connect", 0));
        pushButton_disconnect->setText(QApplication::translate("ClientClass", "Disconnect", 0));
        pushButton_send->setText(QApplication::translate("ClientClass", "Send", 0));
        pushButton_openFile->setText(QApplication::translate("ClientClass", "Select File", 0));
        pushButton_sendFile->setText(QApplication::translate("ClientClass", "Send File", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
