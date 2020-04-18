#include "Server.h"
#include <QMessageBox>
#include <QString>
#include <QByteArray>

Server::Server(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->socket = new QTcpSocket(this);
	this->server = new QTcpServer(this);
	this->server->listen(QHostAddress::Any, 6666);
	connect(this->server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	connect(ui.pushButton_send, SIGNAL(clicked()), this, SLOT(sendMessage()));

	// 文件传送套接字
	this->filesocket = new QTcpSocket(this);
	this->fileserver = new QTcpServer(this);
	this->fileserver->listen(QHostAddress::Any, 8888);
	connect(this->fileserver, SIGNAL(newConnection()), this, SLOT(acceptFileConnection()));

	// 文件传送相关变量初始化
	bytesReceived = 0;
	totalBytes = 0;
	filenameSize = 0;
	connect(ui.pushButton_selectFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	connect(ui.pushButton_sendFile, SIGNAL(clicked()), this, SLOT(sendFile()));
}

Server::~Server()
{

}

void Server::acceptConnection()
{
	this->socket = this->server->nextPendingConnection();

	connect(socket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void Server::acceptFileConnection()
{
	bytesWritten = 0;
	// 每次发送数据大小为64kb
	perDataSize = 64 * 1024;
	this->filesocket = this->fileserver->nextPendingConnection();
	// 接受文件
	connect(filesocket, SIGNAL(readyRead()), this, SLOT(updateFileProgress()));
	connect(filesocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(updateFileProgress(qint64)));
	connect(filesocket, SIGNAL(bytesWritten(qint64)), this, SLOT(displayError(QAbstractSocket::SocketError socketError)));
}

void Server::sendMessage()
{
	this->socket->write(ui.lineEdit->text().toLatin1());
	// 显示
	current_date_time = QDateTime::currentDateTime();
	str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
	QString str = "You " + str_date_time + "\n" + ui.lineEdit->text();
	ui.browser->append(str);
}

void Server::receiveData()
{
	// 获取当前时间
	current_date_time = QDateTime::currentDateTime();
	str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss") + "\n";

	// 接收数据
	QString str = this->socket->readAll();

	// 显示
	str = "Client " + str_date_time + str;
	this->ui.browser->append(str);
}

void Server::updateFileProgress()
{
	QDataStream inFile(this->filesocket);
	inFile.setVersion(QDataStream::Qt_4_8);

	// 如果接收到的数据小于16个字节，保存到来的文件头结构
	if (bytesReceived <= sizeof(qint64)* 2)
	{
		if ((filesocket->bytesAvailable() >= (sizeof(qint64)) * 2) && (filenameSize == 0))
		{
			inFile >> totalBytes >> filenameSize;
			bytesReceived += sizeof(qint64)* 2;
		}
		if ((filesocket->bytesAvailable() >= filenameSize) && (filenameSize != 0))
		{
			inFile >> filename;
			bytesReceived += filenameSize;
			localFile = new QFile(filename);
			if (!localFile->open(QFile::WriteOnly))
			{
				qDebug() << "Server::open file error!";
				return;
			}
		}
		else
			return;
	}
	// 如果接收的数据小于总数据，则写入文件
	if (bytesReceived < totalBytes)
	{
		bytesReceived += filesocket->bytesAvailable();
		inBlock = filesocket->readAll();
		localFile->write(inBlock);
		inBlock.resize(0);
	}
	// 更新进度条显示
	this->ui.progressBar_fileProgress->setMaximum(totalBytes);
	this->ui.progressBar_fileProgress->setValue(bytesReceived);
	// 数据接收完成时
	if (bytesReceived == totalBytes)
	{
		this->ui.browser->append("Receive file successfully!");
		bytesReceived = 0;
		totalBytes = 0;
		filenameSize = 0;
		localFile->close();
		//filesocket->close();
	}
}

void Server::displayError(QAbstractSocket::SocketError socketError)
{
	qDebug() << socket->errorString();
	socket->close();
}

void Server::selectFile()
{
	filesocket->open(QIODevice::WriteOnly);
	// 文件传送进度更新
	connect(filesocket, SIGNAL(bytesWritten(qint64)), this, SLOT(updateFileProgress(qint64)));

	this->filename = QFileDialog::getOpenFileName(this, "Open a file", "/", "files (*)");
	ui.lineEdit_fileName->setText(filename);
}

void Server::sendFile()
{
	this->localFile = new QFile(filename);
	if (!localFile->open(QFile::ReadOnly))
	{
		return;
	}
	// 获取文件大小
	this->totalBytes = localFile->size();
	QDataStream sendout(&outBlock, QIODevice::WriteOnly);
	sendout.setVersion(QDataStream::Qt_4_8);
	QString currentFileName = filename.right(filename.size() - filename.lastIndexOf('/') - 1);

	// 保留总代大小信息空间、文件名大小信息空间、文件名
	sendout << qint64(0) << qint64(0) << currentFileName;
	totalBytes += outBlock.size();
	sendout.device()->seek(0);
	sendout << totalBytes << qint64((outBlock.size() - sizeof(qint64)* 2));

	bytestoWrite = totalBytes - filesocket->write(outBlock);
	outBlock.resize(0);
}

void Server::updateFileProgress(qint64 numBytes)
{
	////已经发送的数据大小
	bytesWritten += (int)numBytes;

	////如果已经发送了数据
	if (bytestoWrite > 0)
	{
		outBlock = localFile->read(qMin(bytestoWrite, perDataSize));
		///发送完一次数据后还剩余数据的大小
		bytestoWrite -= ((int)filesocket->write(outBlock));
		///清空发送缓冲区
		outBlock.resize(0);
	}
	else
		localFile->close();

	// 如果发送完毕
	if (bytesWritten == totalBytes)
	{
		localFile->close();
		//filesocket->close();
	}
}