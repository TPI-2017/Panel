#ifndef PANEL_H
#define PANEL_H

#include <QMainWindow>
#include <QApplication>
#include <QThread>
#include <QCloseEvent>
#include "client.h"
#include "signmodel.h"

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
	// Slots de actualización del modelo
	void updateText(QString text);
	// Slot para cuando se termina una operación
	void clientDone(Client::ClientError);
	void updateState(Client::State);
	void showError(Client::ClientError);
	void updateBlinkRate(float);
	void updateSlideRate(float);
protected:
	virtual void closeEvent(QCloseEvent *event);

private slots:
	void showConfigDialog();
	void showPasswordDialog();
	void showAboutDialog();
	void restoreSettings();
	void applySettings();
	void quit();
	void validateText();
	void blinkRateCheckChanged(int state);
	void slideRateCheckChanged(int state);
	void blinkRateWidgetChanged(double value);
	void slideRateWidgetChanged(double value);
	void slideDirectionChanged(int index);
	void updateButtons(bool pendingChanges);

private:
	bool showLoginPrompt();

	Ui::Panel *ui;
	Client *mClient;
	SignModel mModel;
	QThread *mClientThread;
};

#endif // PANEL_H
