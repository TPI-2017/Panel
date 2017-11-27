#include "translation.h"
#include "panel.h"
#include <QApplication>
#include <QMessageBox>
#include <connection.h>
#include <client.h>
#include <iostream>

static bool sslSupported()
{
	QString ssl = QSslSocket::sslLibraryBuildVersionString();
	if (!QSslSocket::supportsSsl()) {
		QMessageBox messageBox(	QMessageBox::Warning,
					QObject::tr("TLS not supported."),
					QObject::tr("The program will not run correctly. OpenSSL version required: ") + ssl,
					QMessageBox::StandardButton::Ok);
		messageBox.exec();
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	QApplication a(argc,argv);

	if (sslSupported()) {
		Translation::translate(Translation::Spanish);
		Panel w;
		w.init();
		return a.exec();
	} else {
		return -1;
	}
}
