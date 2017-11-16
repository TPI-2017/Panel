#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QApplication>
#include <QThread>
#include <QHostAddress>
#include "client.h"

namespace Ui {
	class Panel;
}

class Panel : public QMainWindow
{
	Q_OBJECT
public:
	explicit Panel(QWidget *parent = 0);
	~Panel();
	void init();

signals:
	void applyRequested();
	void restoreRequested();
	void hostnameChanged(QString);
	void passwordChanged(QString);
	void wifiConfigChanged(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask);

public slots:
	// Slots de actualización del modelo
	void textChanged(QString text);
	// Slot para cuando se termina una operación
	void clientDone(Client::ClientError);
	void clientStateChanged(Client::State);
	void errorOccurred(Client::ClientError);

private slots:
	void on_applyButton_clicked();
	void on_actionQuit_triggered();
	void on_actionEspaniol_triggered();
	void on_actionEnglish_triggered();
	void on_actionAbout_triggered();
	void on_actionChange_token_triggered();
	void on_textMessageField_textChanged();
	void on_actionChange_configuration_triggered();

private:
	void applySettings();
	void restoreSettings();
	void errorOccurred(QString);
	bool promptPassword();

	Ui::Panel *ui;
	Client *mClient;
	QThread *mClientThread;
};

#endif // PANEL_H
