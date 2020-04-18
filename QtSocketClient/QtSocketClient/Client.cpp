#include "Client.h"

Client::Client(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->initTCP();

	// 文件传送相关变量初始化
	// 每次发送数据大小为64kb
	perDataSize = 64 * 1024;
	totalBytes = 0;
	bytestoWrite = 0;
	bytesWritten = 0;
	bytesReceived = 0;
	filenameSize = 0;

	connect(this->ui.pushButton_openFile, SIGNAL(clicked()), this, SLOT(selectFile()));
	connect(this->ui.pushButton_sendFile, SIGNAL(clicked()), this, SLOT(sendFile()));
}

Client::~Client()
{

}

void Client::initTCP()
{
	this->tcpSocket = new QTcpSocket(this);
	connect(ui.pushButton_connect, SIGNAL(clicked()), this, SLOT(connectServer()));
	connect(ui.pushButton_disconnect, SIGNAL(clicked()), this, SLOT(disconnectServer()));
	connect(ui.pushButton_send, SIGNAL(clicked()), this, SLOT(sendData()));
}

void Client::connectServer()
{
	tcpSocket->abort();
	tcpSocket->connectToHost("127.0.0.1", 6666);
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void Client::disconnectServer()
{
	;
}

void Client::receiveData()
{
	// 获取当前时间
	current_date_time = QDateTime::currentDateTime();
	str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss") + "\n";

	// 接收数据
	QString str = tcpSocket->readAll();
	// 显示
	str = "Server " + str_date_time + str;
	this->ui.textEdit->append(str);
}

void Client::sendData()
{
	// 发送数据
	QString str = ui.lineEdit->text();
	this->tcpSocket->write(ui.lineEdit->text().toLatin1());
	// 显示
	current_date_time = QDateTime::currentDateTime();
	str_date_time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
	str = "You " + str_date_time + "\n" + str;
	ui.textEdit->append(str);
}

void Client::selectFile()
{
	this->fileSocket = new QTcpSocket(this);
	fileSocket->abort();
	fileSocket->connectToHost("127.0.0.1", 8888);
	// 文件传送进度更新
	connect(fileSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(updateFileProgress(qint64)));
	connect(fileSocket, SIGNAL(readyRead()), this, SLOT(updateFileProgress()));

	this->ui.progressBar->setValue(0);
	this->filename = QFileDialog::getOpenFileName(this, "Open a file", "/", "files (*)");
	ui.lineEdit_filename->setText(filename);
}

void Client::sendFile()
{
	this->localFile = new QFile(filename);
	if (!localFile->open(QFile::ReadOnly))
	{
		ui.textEdit->append(tr("Client:open file error!"));
		return;
	}
	// 获取文件大小
	this->totalBytes = localFile->size();
	QDataStream sendout(&outBlock, QIODevice::WriteOnly);
	sendout.setVersion(QDataStream::Qt_4_8);
	QString currentFileName = filename.right(filename.size() - filename.lastIndexOf('/') - 1);

	qDebug() << sizeof(currentFileName);
	// 保留总代大小信息空间、文件名大小信息空间、文件名
	sendout << qint64(0) << qint64(0) << currentFileName;
	totalBytes += outBlock.size();
	sendout.device()->seek(0);
	sendout << totalBytes << qint64((outBlock.size() - sizeof(qint64)* 2));

	bytestoWrite = totalBytes - fileSocket->write(outBlock);
	outBlock.resize(0);
}

void Client::updateFileProgress(qint64 numBytes)
{
	// 已经发送的数据大小
	bytesWritten += (int)numBytes;

	// 如果已经发送了数据
	if (bytestoWrite > 0)
	{
		outBlock = localFile->read(qMin(bytestoWrite, perDataSize));
		// 发送完一次数据后还剩余数据的大小
		bytestoWrite -= ((int)fileSocket->write(outBlock));
		// 清空发送缓冲区
		outBlock.resize(0);
	}
	else
		localFile->close();

	// 更新进度条
	this->ui.progressBar->setMaximum(totalBytes);
	this->ui.progressBar->setValue(bytesWritten);

	// 如果发送完毕
	if (bytesWritten == totalBytes)
	{
		localFile->close();
		//fileSocket->close();
	}
}

void Client::updateFileProgress()
{
	QDataStream inFile(this->fileSocket);
	inFile.setVersion(QDataStream::Qt_4_8);

	// 如果接收到的数据小于16个字节，保存到来的文件头结构
	if (bytesReceived <= sizeof(qint64)* 2)
	{
		if ((fileSocket->bytesAvailable() >= (sizeof(qint64)) * 2) && (filenameSize == 0))
		{
			inFile >> totalBytes >> filenameSize;
			bytesReceived += sizeof(qint64)* 2;
		}
		if ((fileSocket->bytesAvailable() >= filenameSize) && (filenameSize != 0))
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
		bytesReceived += fileSocket->bytesAvailable();
		inBlock = fileSocket->readAll();
		localFile->write(inBlock);
		inBlock.resize(0);
	}

	// 数据接收完成时
	if (bytesReceived == totalBytes)
	{
		this->ui.textEdit->append("Receive file successfully!");
		bytesReceived = 0;
		totalBytes = 0;
		filenameSize = 0;
		localFile->close();
		//fileSocket->close();
	}
}