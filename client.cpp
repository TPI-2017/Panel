#include "client.h"
#include <stdint.h>
#include <QHostAddress>
#include <QThread>

static uint8_t toFixedPoint(float n)
{
	#warning No implementado
	return 0;
}

static uint8_t toFloatingPoint(uint8_t n)
{
	#warning No implementado
	return 0;
}

Client::Client()
{
	qRegisterMetaType<State>("State");
	qRegisterMetaType<ClientError>("ClientError");
}

void Client::apply()
{
	if (mSignModel.dirty())	{
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
	}
	emit done(Ok);
}

void Client::restore()
{
	QThread::sleep(3);
	emit done(Ok);
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

void Client::performInteraction(const Message &request)
{
	if (mConnection.connect(mHostname)) {
		if (mConnection.send(request)) {
			Message response;
			if(mConnection.receive(response)) {
				handleResponse(response);
			} else {
				// TODO manejar fallo de recepción
			}
		} else {
			// TODO manejar fallo de transmisión
		}
	} else {
		// TODO manejar fallo de conexión	
	}
	
	mConnection.disconnect();
}

void Client::handleResponse(const Message &response)
{
	// TODO: aca se maneja cualquier respuesta negativa del micro

}
