#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QWidget>
#include "ui_Server.h"

#include <QtNetwork>
#include <QAbstractSocket>
#include <QTcpSocket> 

#include <QFile>
#include <QFileDialog>

#include <QDateTime>
#include <QDataStream>

class Server : public QWidget
{
	Q_OBJECT

public:
	Server(QWidget *parent = 0);
	~Server();

	QTcpServer *server;
	QTcpSocket *socket;
	QTcpServer *fileserver;
	QTcpSocket *filesocket;

private slots:
	void sendMessage();
	void acceptConnection();
	// 接收客户端发送的数据
	void receiveData();

	void acceptFileConnection();
	void updateFileProgress();
	void displayError(QAbstractSocket::SocketError socketError);

	// 选择发送的文件
	void selectFile();
	void sendFile();
	// 更新文件传送进度
	void updateFileProgress(qint64);

private:
	Ui::ServerClass ui;

	// 传送文件相关变量
	qint64 totalBytes;
	qint64 bytesReceived;
	qint64 bytestoWrite;
	qint64 bytesWritten;
	qint64 filenameSize;
	QString filename;
	// 每次发送数据大小
	qint64 perDataSize;
	QFile *localFile;
	// 本地缓冲区
	QByteArray inBlock;
	QByteArray outBlock;

	// 系统时间
	QDateTime current_date_time;
	QString str_date_time;
};

#endif // SERVER_H
