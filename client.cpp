#include "client.h"
#include <stdint.h>
#include <iostream>
#include <QThread>
#include <iostream>

Client::ClientError Client::toClientError(QAbstractSocket::SocketError error)
{
	std::cerr << error << std::endl;
	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
		return ConnectionRefused;
	case QAbstractSocket::RemoteHostClosedError:
		return RemoteHostClosed;
	case QAbstractSocket::HostNotFoundError:
		return HostNotFound;
	case QAbstractSocket::NetworkError:
		return NetworkError;
	case QAbstractSocket::SslHandshakeFailedError:
		return SslHandshakeFailed;
	case QAbstractSocket::SslInternalError:
		return SslInternalError;
	case QAbstractSocket::SslInvalidUserDataError:
		return SslInvalidData;
	case QAbstractSocket::SocketTimeoutError:
		return Timeout;
	default:
		return Unknown;
	}
}

Client::Client(SignModel &signModel)
: mSignModel(signModel),
  mConnection(this)
{
	qRegisterMetaType<State>("State");
	qRegisterMetaType<ClientError>("ClientError");
}

void Client::setHostname(QString hostname)
{
	mHostname = hostname;
}

void Client::setWorkingPassword(QString password)
{
	mPassword = password;
}

void Client::apply()
{
	QReadLocker locker(&mSignModel);
	ClientError result;
	changeState(Connecting);
	if (!mConnection.connect(mHostname)) {
		result = toClientError(mConnection.lastError());
		goto stop;
	}
	changeState(Connected);

	if (mSignModel.isTextDirty()) {
		Message textMsg;
		auto text = mSignModel.text();
		auto br = mSignModel.blinkRate();
		auto sr = mSignModel.slideRate();

		textMsg = Message::createSetTextRequest
						(
						mPassword.toStdString().data(),
						br,
						sr,
						text.toStdString().data()
						);

		result = performInteraction(textMsg);
		if (result != Ok)
			goto stop;
		else
			mSignModel.clearText();
	}

	if (mSignModel.isWifiConfigDirty()) {
		Message wifiMsg;
		auto ssid = mSignModel.wifiSSID();
		auto wifiPassword = mSignModel.wifiPassword();
		auto ip = mSignModel.wifiIP();
		auto subnet = mSignModel.wifiSubnetMask();
		wifiMsg = Message::createSetWifiConfigRequest
						(
						mPassword.toStdString().data(),
						ssid.toStdString().data(),
						wifiPassword.toStdString().data(),
						ip,
						subnet
						);

		result = performInteraction(wifiMsg);
		if (result != Ok)
			goto stop;
		else
			mSignModel.clearWifiConfig();
	}

	if (mSignModel.isPasswordDirty()) {
		Message passwordMsg;
		passwordMsg = Message::createSetPasswordRequest
				(mPassword.toStdString().data(),
				 mSignModel.password().toStdString().data());
		result = performInteraction(passwordMsg);
		if (result != Ok)
			goto stop;
		else
			mSignModel.clearPassword();

	}

stop:
	mConnection.disconnect();
	changeState(Disconnected);
	emit done(result);
}

void Client::restore()
{
	QReadLocker locker(&mSignModel);
	ClientError result;
	Message getTextMsg;
	Message getWifiMsg;

	auto password = mPassword.toStdString();
	getTextMsg = Message::createGetTextRequest(password.data());
	getWifiMsg = Message::createGetWifiConfigRequest(password.data());

	changeState(Connecting);
	if (!mConnection.connect(mHostname)) {
		result = toClientError(mConnection.lastError());
		goto stop;
	}

	changeState(Connected);


	result = performInteraction(getTextMsg);

	if (result == Ok)
		result = performInteraction(getWifiMsg);

stop:
	mConnection.disconnect();
	changeState(Disconnected);
	emit done(result);
}

Client::ClientError Client::performInteraction(const Message &request)
{
	ClientError result;
	if (mConnection.send(request)) {
		changeState(RequestSent);
		Message response;
		if(mConnection.receive(response)) {
			changeState(ResponseReceived);
			result = handleResponse(response);
		} else {
			result = toClientError(mConnection.lastError());
		}
	} else {
		result = toClientError(mConnection.lastError());
	}
	return result;
}

Client::ClientError Client::handleResponse(const Message &response)
{
	if (response.empty())
		return WrongResponse;

	if (response.responseCode() != Message::OK) {
		switch (response.responseCode()) {
		case Message::MalformedPacket:
			return ServerMalformedPacket;
		case Message::BadPassword:
			return ServerBadPassword;
		case Message::BadProtocolVersion:
			return ServerBadProtocolVersion;
		case Message::BadIP:
			return ServerBadIP;
		case Message::BadSubnetMask:
			return ServerBadSubnetMask;
		}
	}

	switch (response.type()) {
	case Message::GetWiFiConfigResponse:
		mSignModel.setWifiSSID(QString::fromLatin1(response.wifiSSID()));
		mSignModel.setWifiPassword(QString::fromLatin1(response.wifiPassword()));
		mSignModel.setWifiIP(quint32(response.wifiIP()));
		mSignModel.setWifiSubnetMask(quint32(response.wifiSubnet()));
		mSignModel.clearWifiConfig();
		break;
	case Message::GetTextResponse:
		mSignModel.setText(QString::fromLatin1(response.text()));
		mSignModel.setBlinkRate(response.blinkRate());
		mSignModel.setSlideRate(response.slideRate());
		mSignModel.clearText();
		break;
	default:
		break;
	}

	return Ok;
}

void Client::changeState(State state)
{
	mState = state;
	emit stateChanged(mState);
}
