#include "connection.h"
#include <cassert>

Connection::Connection()
{
	qRegisterMetaType<Connection::Error>("Client::Error");
	loadLocalCertificate();
}

bool Connection::connect(QString hostname)
{
	mSocket.connectToHostEncrypted(hostname, 443);
	return mSocket.waitForEncrypted(TIMEOUT_MS);
}

bool Connection::send(const Message &msg)
{
	if (mSocket.write(static_cast<const char*>(msg.data()), Message::MESSAGE_SIZE) == -1)
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
	bool success = mSocket.read(data, Message::MESSAGE_SIZE) == Message::MESSAGE_SIZE;
	
	if (success)
		msg = Message::createMessage(data);
	
	return success;
}

void Connection::disconnect()
{
	if (mSocket.isOpen()) {
		mSocket.close();
		mSocket.waitForDisconnected(TIMEOUT_MS);
	}
}

QString Connection::lastError()
{
	return mSocket.errorString();
}

void Connection::loadLocalCertificate()
{
	QString path = ":/ssl/res/TLS.ca_x509.cer";

	auto list = QSslCertificate::fromPath(path, QSsl::Der);
	assert(!list.empty());

	mSocket.addCaCertificate(list.front());
}
