#include "connection.h"
#include <cassert>

Connection::Connection(QObject *parent)
: QObject(parent),
  mSocket(this)
{
	qRegisterMetaType<Connection::Error>("Connection::Error");
	loadLocalCertificate();
}

bool Connection::connect(QString hostname)
{
	mSocket.connectToHostEncrypted(hostname, 443);
	if (mSocket.waitForConnected(TIMEOUT_MS))
		return mSocket.waitForEncrypted(TIMEOUT_MS);
	else
		return false;
}

bool Connection::send(const Message &msg)
{
	const char *data = static_cast<const char*>(msg.data());
	if (mSocket.write(data , Message::MESSAGE_SIZE) == -1)
		return false;

	return mSocket.waitForBytesWritten(TIMEOUT_MS);
}

bool Connection::receive(Message &msg)
{
	// TODO: contemplar paquetes fragmentados.
	// Este método posiblemente necesite ser bastante mas complejo
	char data[Message::MESSAGE_SIZE];
	if (!mSocket.waitForReadyRead(TIMEOUT_MS))
		return false;
	bool success = (mSocket.read(data, Message::MESSAGE_SIZE) != -1);

	if (success)
		msg = Message::createMessage(data);

	return success;
}

void Connection::disconnect()
{
	if (mSocket.isOpen()
		&& mSocket.state() != QAbstractSocket::UnconnectedState) {
		mSocket.close();
		mSocket.waitForDisconnected(TIMEOUT_MS);
	}
}

QAbstractSocket::SocketError Connection::lastError()
{
	return mSocket.error();
}

void Connection::loadLocalCertificate()
{
	QString path = ":/ssl/res/TLS.ca_x509.cer";

	auto list = QSslCertificate::fromPath(path, QSsl::Der);
	assert(!list.empty());

	mSocket.addCaCertificate(list.front());
}
