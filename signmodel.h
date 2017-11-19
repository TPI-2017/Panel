#ifndef SIGNMODEL_H
#define SIGNMODEL_H

#include <QObject>
#include <QString>

class SignModel : public QObject
{
	Q_OBJECT
public:
	explicit SignModel(QObject *parent = 0)
	: QObject(parent)
	{
	}

	// Getters
	const QString &text() const
	{
		return mText;
	}

	const QString &wifiSSID() const
	{
		return mWifiSSID;
	}

	const QString &wifiPassword() const
	{
		return mWifiPassword;
	}

	const quint32 &wifiIP() const
	{
		return mWifiIP;
	}

	const quint32 &wifiSubnetMask() const
	{
		return mWifiSubnetMask;
	}

	float blinkRate() const
	{
		return mBlinkRate;
	}

	float slideRate() const
	{
		return mSlideRate;
	}

signals:
	void passwordChanged(QString);
	void textChanged(QString);
	void wifiSSIDChanged(QString);
	void wifiPasswordChanged(QString);
	void wifiIPChanged(quint32);
	void wifiSubnetMaskChanged(quint32);
	void blinkRateChanged(float);
	void slideRateChanged(float);

public slots:
	void setPassword(QString text)
	{
		mPassword = text;
		emit passwordChanged(text);
	}

	void setText(QString text)
	{
		mText = text;
		emit textChanged(text);
	}

	void setWifiSSID(QString ssid)
	{
		mWifiSSID = ssid;
		emit wifiSSIDChanged(ssid);
	}

	void setWifiPassword(QString password)
	{
		mWifiPassword = password;
		emit wifiPasswordChanged(password);
	}

	void setWifiIP(quint32 ip)
	{
		mWifiIP = ip;
		emit wifiIPChanged(ip);
	}

	void setWifiSubnetMask(quint32 subnetMask)
	{
		mWifiSubnetMask = subnetMask;
		emit wifiSubnetMaskChanged(subnetMask);
	}

	void setBlinkRate(float blinkRate)
	{
		mBlinkRate = blinkRate;
		emit blinkRateChanged(blinkRate);
	}

	void setSlideRate(float slideRate)
	{
		mSlideRate = slideRate;
		emit slideRateChanged(slideRate);
	}

	void emitValues()
	{
		emit textChanged(mPassword);
		emit textChanged(mText);
		emit wifiSSIDChanged(mWifiSSID);
		emit wifiPasswordChanged(mWifiPassword);
		emit wifiIPChanged(mWifiIP);
		emit wifiSubnetMaskChanged(mWifiSubnetMask);
		emit blinkRateChanged(mBlinkRate);
		emit slideRateChanged(mSlideRate);
	}

private:
	QString mPassword;
	QString mText;
	QString mWifiSSID;
	QString mWifiPassword;
	quint32 mWifiIP;
	quint32 mWifiSubnetMask;
	float mBlinkRate;
	float mSlideRate;
};

#endif
