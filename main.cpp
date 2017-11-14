#include "translation.h"
#include "panel.h"
#include <QApplication>
#include <QMessageBox>
#include <Connection.h>
#include <iostream>

static void checkSslSupport()
{
	QString ssl = QSslSocket::sslLibraryBuildVersionString();
	if (!QSslSocket::supportsSsl()) {
		QMessageBox messageBox(	QMessageBox::Warning,
					QObject::tr("TLS not supported."),
					QObject::tr("The program will not run correctly. OpenSSL version required: ") + ssl,
					QMessageBox::StandardButton::Ok);
		messageBox.exec();
	}
}

/*
int main(int argc, char *argv[])
{
	QApplication a(argc,argv);

	checkSslSupport();
	Panel w;
	w.init();
	
	
	
	Translation::translate();
	return a.exec();
}
*/


int main(int argc, char *argv[])
{
	Connection connection;
	Message request = Message::createSetTextRequest("password", 23, 232, "Hola");
	
	if (connection.connect("192.168.0.14")) {
		std::cerr << "Connected." << std::endl;
		QThread::sleep(1);
		if (connection.send(request)) {
			std::cerr << "Request sent." << std::endl;
			QThread::sleep(1);
			Message response;
			/*if(connection.receive(response)) {
				std::cerr << "Response received." << std::endl;
			} else {
				std::cerr << connection.lastError().toStdString() << std::endl;
			}*/
		} else {
			std::cerr << connection.lastError().toStdString() << std::endl;
		}
	} else {
		std::cerr << connection.lastError().toStdString() << std::endl;
	}
	
	return 0;
}
