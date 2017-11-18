#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QApplication>
#include <QThread>
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
	void textChanged(QString);
	void wifiConfigChanged(QString SSID, QString wifiPassword, quint32 ip, quint32 subnetMask);
	void modelEmitNeeded();

public slots:
	// Slots de actualización del modelo
	void updateText(QString text);
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

	void on_restoreButton_clicked();

private:
	void applySettings();
	void restoreSettings();
	void errorOccurred(QString);
	bool showLoginPrompt();

	Ui::Panel *ui;
	Client *mClient;
	QThread *mClientThread;
};

#endif // PANEL_H
