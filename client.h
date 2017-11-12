#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QSslSocket>
#include <QSslCertificate>
#include <QHostAddress>
#include "protocol/Message.h"

// Esta clase maneja todas las interacciones con el cartel. Tiene slots para
// iniciar una interacción y señales para indicar el resultado.
// Se tiene que usar en un QThread distinto al de UI y sus slots tienen que correrse
// en ese Thread.
class Client : public QObject
{
	Q_OBJECT
public:
	Client();

	enum State {
		NotReady,
		Disconnected,
		Connected,
		AuthSent,
		AuthOk,
		RequestSent,
		ResponseReceived
	};
	Q_ENUM(State)

	enum Error
	{
		BadPassword,
		BadWifiConfig,
		BadTextEncoding,
		CertificateMissing,
		ResponseTimeout,
		WrongResponse,
		Unknown
	};
	Q_ENUM(Error)

	void setHostname(QString hostname);
	void setWorkingPassword(QString password);

public slots:
	void setText(QString text, uint8_t blinkRate, uint8_t slideRate);
	void getText();
	void setPassword(QString password);
	void setWifiConfig(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask);
	void getWifiConfig();

signals:
	void textChanged(QString text);
	void wifiConfigChanged(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask);
	void errorOccurred(Error error);
	void errorOccurred(QString error);
	void stateChanged(State state);

private:
	void loadLocalCertificate();
	void changeState(State newState);
	void performInteraction();
	void disconnect();
	void panic(Error reason);
	void panic(QString reason);
	bool receive(void *data, uint8_t Timeout);

	static constexpr uint8_t Timeout = 5;
	QSslSocket mSocket;
	QString mPassword;
	QString mHostname;
	QSslCertificate mCertificate;
	State mState;
	Message mRequestMessage;
	Message mResponseMessage;
};

#endif // CLIENT_H
