#include "client.h"
#include <stdint.h>
#include <QHostAddress>
#include <iostream>
#include <QThread>

static uint8_t toFixedPoint(float n)
{
	return 0;
}

static uint8_t toFloatingPoint(uint8_t n)
{
	return 0;
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
	if (mSignModel.dirty())	{
		changeState(Connecting);
		if (mConnection.connect(mHostname)) {
			changeState(Connected);
			QString text = mSignModel.text();
			QString ssid = mSignModel.wifiSSID();
			QString password = mSignModel.wifiPassword();
			QHostAddress ip = mSignModel.wifiIP();
			QHostAddress subnet = mSignModel.wifiSubnetMask();
			uint8_t br = toFixedPoint(mSignModel.blinkRate());
			uint8_t sr = toFixedPoint(mSignModel.blinkRate());
			
			Message textMsg;
			textMsg = Message::createSetTextRequest	(
								mPassword.toStdString().data(),
								br,
								sr,
								text.toStdString().data()
								);
			Message wifiMsg;
			wifiMsg = Message::createSetWifiConfigRequest	(
									mPassword.toStdString().data(),
									ssid.toStdString().data(),
									password.toStdString().data(),
									ip.toIPv4Address(),
									subnet.toIPv4Address()
									);
			result = performInteraction(textMsg);
			if (result == Ok)
				result = performInteraction(wifiMsg);
				
		} else {
			result = toClientError(mConnection.lastError());
		}
		
		mConnection.disconnect();
		changeState(Disconnected);

	}
	emit done(result);
}

void Client::restore()
{
	ClientError result;
	changeState(Connecting);
	if (mConnection.connect(mHostname)) {
		changeState(Connected);
		
		Message getTextMsg;
		getTextMsg = Message::createGetTextRequest(mPassword.toStdString().data());
		result = performInteraction(getTextMsg);
		if (result == Ok) {
			Message getWifiMsg;
			getWifiMsg = Message::createGetWifiConfigRequest(mPassword.toStdString().data());
			result = performInteraction(getWifiMsg);
		}
			
	} else {
		result = toClientError(mConnection.lastError());
	}
	
	mConnection.disconnect();
	changeState(Disconnected);
	emit done(result);
}

void Client::setText(QString text, float blinkRate, float slideRate)
{
	mSignModel.setText(text);
	mSignModel.setBlinkRate(blinkRate);
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

void Client::setWifiConfig(QString SSID, QString wifiPassword, QHostAddress ip, QHostAddress subnetMask)
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
	case Message::GetWiFiConfig:
		mSignModel.setWifiSSID(QString::fromLatin1(response.wifiSSID()));
		mSignModel.setWifiPassword(QString::fromLatin1(response.wifiPassword()));
		mSignModel.setWifiIP(QHostAddress(response.wifiIP()));
		mSignModel.setWifiSubnetMask(QHostAddress(response.wifiSubnet()));
		break;
	case Message::GetTextResponse:
		mSignModel.setText(QString::fromLatin1(response.text()));
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
