/********************************************************************************
** Form generated from reading UI file 'Server.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

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

class Ui_ServerClass
{
public:
    QTextEdit *browser;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_fileName;
    QProgressBar *progressBar_fileProgress;
    QPushButton *pushButton_close;
    QPushButton *pushButton_selectFile;
    QPushButton *pushButton_sendFile;
    QPushButton *pushButton_send;

    void setupUi(QWidget *ServerClass)
    {
        if (ServerClass->objectName().isEmpty())
            ServerClass->setObjectName(QStringLiteral("ServerClass"));
        ServerClass->resize(600, 400);
        browser = new QTextEdit(ServerClass);
        browser->setObjectName(QStringLiteral("browser"));
        browser->setGeometry(QRect(20, 10, 341, 251));
        lineEdit = new QLineEdit(ServerClass);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 270, 341, 31));
        lineEdit_fileName = new QLineEdit(ServerClass);
        lineEdit_fileName->setObjectName(QStringLiteral("lineEdit_fileName"));
        lineEdit_fileName->setGeometry(QRect(380, 150, 201, 20));
        progressBar_fileProgress = new QProgressBar(ServerClass);
        progressBar_fileProgress->setObjectName(QStringLiteral("progressBar_fileProgress"));
        progressBar_fileProgress->setGeometry(QRect(380, 60, 118, 23));
        progressBar_fileProgress->setValue(0);
        pushButton_close = new QPushButton(ServerClass);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(380, 20, 75, 23));
        pushButton_selectFile = new QPushButton(ServerClass);
        pushButton_selectFile->setObjectName(QStringLiteral("pushButton_selectFile"));
        pushButton_selectFile->setGeometry(QRect(370, 110, 75, 23));
        pushButton_sendFile = new QPushButton(ServerClass);
        pushButton_sendFile->setObjectName(QStringLiteral("pushButton_sendFile"));
        pushButton_sendFile->setGeometry(QRect(480, 110, 75, 23));
        pushButton_send = new QPushButton(ServerClass);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));
        pushButton_send->setGeometry(QRect(400, 280, 75, 23));

        retranslateUi(ServerClass);

        QMetaObject::connectSlotsByName(ServerClass);
    } // setupUi

    void retranslateUi(QWidget *ServerClass)
    {
        ServerClass->setWindowTitle(QApplication::translate("ServerClass", "Server", 0));
        pushButton_close->setText(QApplication::translate("ServerClass", "Close", 0));
        pushButton_selectFile->setText(QApplication::translate("ServerClass", "Select File", 0));
        pushButton_sendFile->setText(QApplication::translate("ServerClass", "Send", 0));
        pushButton_send->setText(QApplication::translate("ServerClass", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class ServerClass: public Ui_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
