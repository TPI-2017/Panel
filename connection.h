#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSslSocket>
#include <QObject>
#include "protocol/Message.h"

class Connection : public QObject
{
	Q_OBJECT
public:
	explicit Connection(QObject *parent);

	enum Error {
		Timeout,
		CertificateLoadFailed,
		Other
	};
	Q_ENUM(Connection::Error)
	
	QAbstractSocket::SocketError lastError();
public slots:
	bool connect(const QString hostname);
	void disconnect();
	bool send(const Message &msg);
	bool receive(Message &msg);
signals:
	void messageReceived(Message msg);
	void errorOccurred(Connection::Error error, QString errorString);
private:
	QSslSocket mSocket;
	void loadLocalCertificate();

	static constexpr unsigned TIMEOUT_MS = 5000;
};

#endif