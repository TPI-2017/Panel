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

public slots:
	void textChanged(QString text);
	void errorOccurred(Client::ClientError error);
	void errorOccurred(QString error);
	void clientDone(Client::ClientError);

private slots:
	void on_applyButton_clicked();
	void on_actionQuit_triggered();
	void on_actionEspaniol_triggered();
	void on_actionEnglish_triggered();
	void on_actionDisconnect_triggered();
	void on_actionAbout_triggered();
	void on_actionChange_token_triggered();
private:
	void applySettings();
	void restoreSettings();

	Ui::Panel *ui;
	Client *mClient;
	QThread *mClientThread;
};

#endif // PANEL_H
