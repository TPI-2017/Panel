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

int main(int argc, char *argv[])
{
	QApplication a(argc,argv);

	checkSslSupport();
	Panel w;
	w.init();
	
	
	
	Translation::translate();
	return a.exec();
}
