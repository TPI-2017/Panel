#include "client.h"
#include <stdint.h>
#include <QHostAddress>

Client::Client()
{
	qRegisterMetaType<Client::State>("Client::State");
	qRegisterMetaType<Client::Error>("Client::Error");
}

void Client::apply()
{
}

void Client::restore()
{

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
	emit interactionFinished();
}

void Client::handleResponse(const Message &response)
{
	// TODO: aca se maneja cualquier respuesta negativa del micro

}
