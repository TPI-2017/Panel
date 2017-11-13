#ifndef SIGNMODEL_H
#define SIGNMODEL_H

#include <QObject>
#include <QString>
#include <QHostAddress>

class SignModel : public QObject
{
	Q_OBJECT
public:
	explicit SignModel(QObject *parent = 0);
	
signals:
	void textChanged(QString);
	void wifiSSIDChanged(QString);
	void wifiPasswordChanged(QString);
	void wifiIPChanged(QHostAddress);
	void wifiSubnetMaskChanged(QHostAddress);
	void blinkRateChanged(float);
	void slideRateChanged(float);
	
public slots:
	void setText(QString text)
	{
		bool changed = mText != text;
		mText = text;
		if (changed)
			emit textChanged(text);
	};

	void setWifiSSID(QString ssid)
	{
		bool changed = mWifiSSID != ssid;
		mWifiSSID = ssid;
		if (changed)
			emit wifiSSIDChanged(ssid);
	};

	void setWifiPassword(QString password)
	{
		bool changed = mWifiPassword != password;
		mWifiPassword = password;
		if (changed)
			emit wifiPasswordChanged(password);
	};
	
	void setWifiIP(QHostAddress ip)
	{
		bool changed = mWifiIP != ip;
		mWifiIP = ip;
		if (changed)
			emit wifiIPChanged(mWifiIP);
	}

	void setWifiSubnetMask(QHostAddress subnetMask)
	{
		bool changed = mWifiSubnetMask != subnetMask;
		mWifiSubnetMask = subnetMask;
		if (changed)
			emit wifiSubnetMaskChanged(mWifiIP);
	}

	void setBlinkRate(float blinkRate)
	{
		bool changed = mBlinkRate != blinkRate;
		mBlinkRate = blinkRate;
		if (changed)
			emit blinkRateChanged(blinkRate);
	};

	void setSlideRate(float slideRate)
	{
		bool changed = mSlideRate != slideRate;
		mSlideRate = slideRate;	
		if (changed)
			emit slideRateChanged(slideRate);
	};

private:
	QString mText;
	QString mWifiSSID;
	QString mWifiPassword;
	QHostAddress mWifiIP;
	QHostAddress mWifiSubnetMask;
	float mBlinkRate;
	float mSlideRate;
};

#endif // SIGNMODEL_H