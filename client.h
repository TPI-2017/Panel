#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QList>
#include <QSslSocket>
#include <QSslCertificate>
#include <QHostAddress>
#include "protocol/Message.h"
#include "connection.h"
#include "signmodel.h"

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
		Connecting,
		Connected,
		RequestSent,
		ResponseReceived
	};
	Q_ENUM(Client::State)

	enum ClientError
	{
		Ok,
		BadPassword,
		BadWifiConfig,
		BadTextEncoding,
		CertificateMissing,
		ResponseTimeout,
		WrongResponse,
		IncompleteWrite,
		Unknown
	};
	Q_ENUM(Client::ClientError)

public slots:
	void setHostname(QString hostname);
	
	void setWorkingPassword(QString password);
	
	// Aplica los cambios del modelo actual al cartel.
	void apply();
	// Actuaiza el modelo con el estado actual del cartel.
	void restore();
	// Estos getters actualizan el modelo. No mandan cambios al cartel.
	void setText(QString text, float blinkRate, float slideRate);
	void setWifiConfig(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask);
signals:
	void stateChanged(State state);
	void errorOccurred(QString errorString);
	void done(ClientError status);
private:
	SignModel mSignModel;
	Connection mConnection;
	State mState;
	QString mHostname;
	QString mPassword;
	
	void changeState(State state);
	void performInteraction(const Message &request);
	void handleResponse(const Message &response);
};

#endif
