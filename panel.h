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
	void disconnect();

public slots:
	void textChanged(QString text);
	void stateChanged(Client::State state);
	void errorOccurred(Client::Error error);
	void errorOccurred(QString error);

private slots:
	void on_applyButton_clicked();
	void on_actionQuit_triggered();
	void on_actionEspaniol_triggered();
	void on_actionEnglish_triggered();
	void on_actionDisconnect_triggered();
	void on_actionAbout_triggered();
	void on_actionChange_token_triggered();
private:
	void requestViewUpdate();

	Ui::Panel *ui;
	Client *mClient;
	QThread *mClientThread;
};

#endif // PANEL_H
