#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QSslSocket>
#include <QSslCertificate>
#include <QHostAddress>

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
		CertificateMissing
	};
	Q_ENUM(Error)

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
	void stateChanged(State state);

private slots:
	void connected();
	void disconnected();
	void error(QAbstractSocket::SocketError err);
	void readyToRead();
	void sslErrors(const QList<QSslError> &errors);
private:
	void loadLocalCertificate();
	void changeState(State newState);

	QSslSocket mSocket;
	QString mPassword;
	QSslCertificate mCertificate;
	State mState;
    // Message mRequestMessage;
    // Message mResponseMessage;
};

#endif // CLIENT_H
