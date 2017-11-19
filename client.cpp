#include "client.h"
#include <stdint.h>
#include <iostream>
#include <QThread>
#include <iostream>

template <typename T, uint8_t F>
static T fixed(float num)
{
	num = std::max<float>(-7.0, std::min<float>(num, 7.0));
	return static_cast<T>(num * static_cast<float>(1 << F));
}

template <typename T, uint8_t F>
static float floating(T fp)
{
	return static_cast<float>(fp / static_cast<float>(1 << F));
}

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

Client::Client()
: mSignModel(this),
  mConnection(this)
{
	qRegisterMetaType<State>("State");
	qRegisterMetaType<ClientError>("ClientError");
}

void Client::apply()
{
	ClientError result = Ok;
	Message textMsg;
	Message wifiMsg;
	auto text = mSignModel.text();
	auto ssid = mSignModel.wifiSSID();
	auto password = mSignModel.wifiPassword();
	auto ip = mSignModel.wifiIP();
	auto subnet = mSignModel.wifiSubnetMask();
	auto br = fixed<uint8_t, 4>(mSignModel.blinkRate());
	auto sr = fixed<int8_t, 4>(mSignModel.slideRate());

	changeState(Connecting);
	if (!mConnection.connect(mHostname)) {
		result = toClientError(mConnection.lastError());
		goto stop;
	}
	changeState(Connected);

	textMsg = Message::createSetTextRequest
					(
					mPassword.toStdString().data(),
					br,
					sr,
					text.toStdString().data()
					);
	wifiMsg = Message::createSetWifiConfigRequest
					(
					mPassword.toStdString().data(),
					ssid.toStdString().data(),
					password.toStdString().data(),
					ip,
					subnet
					);

	result = performInteraction(textMsg);
	if (result == Ok)
		result = performInteraction(wifiMsg);


stop:
	mConnection.disconnect();
	changeState(Disconnected);
	emit done(result);
}

void Client::restore()
{
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
	mSignModel.emitValues();
	mConnection.disconnect();
	changeState(Disconnected);
	emit done(result);
}

void Client::setText(QString text)
{
	mSignModel.setText(text);
}

void Client::setPassword(QString text)
{
	mSignModel.setPassword(text);
}

void Client::setBlinkRate(float blinkRate)
{
	mSignModel.setBlinkRate(blinkRate);
}

void Client::setSlideRate(float slideRate)
{
	mSignModel.setSlideRate(slideRate);
}

void Client::setWorkingPassword(QString password)
{
	mPassword = password;
}

void Client::setHostname(QString hostname)
{
	mHostname = hostname;
}

void Client::setWifiConfig(QString SSID,
			QString wifiPassword,
			quint32 ip,
			quint32 subnetMask)
{
	mSignModel.setWifiSSID(SSID);
	mSignModel.setWifiPassword(wifiPassword);
	mSignModel.setWifiIP(ip);
	mSignModel.setWifiSubnetMask(subnetMask);
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
		break;
	case Message::GetTextResponse:
		mSignModel.setText(QString::fromLatin1(response.text()));
		mSignModel.setBlinkRate(floating<uint8_t, 4>(response.blinkRate()));
		mSignModel.setSlideRate(floating<int8_t, 4>(response.slideRate()));
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
