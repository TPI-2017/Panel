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
	const QString &password() const
	{
		return mPassword;
	}

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
		mPasswordDirty = true;
		emit passwordChanged(text);
	}

	void setText(QString text)
	{
		mText = text;
		mTextDirty = true;
		emit textChanged(text);
	}

	void setBlinkRate(float blinkRate)
	{
		mBlinkRate = blinkRate;
		mTextDirty = true;
		emit blinkRateChanged(blinkRate);
	}

	void setSlideRate(float slideRate)
	{
		mSlideRate = slideRate;
		mTextDirty = true;
		emit slideRateChanged(slideRate);
	}

	void setWifiSSID(QString ssid)
	{
		mWifiSSID = ssid;
		mWifiConfigDirty = true;
		emit wifiSSIDChanged(ssid);
	}

	void setWifiPassword(QString password)
	{
		mWifiPassword = password;
		mWifiConfigDirty = true;
		emit wifiPasswordChanged(password);
	}

	void setWifiIP(quint32 ip)
	{
		mWifiIP = ip;
		mWifiConfigDirty = true;
		emit wifiIPChanged(ip);
	}

	void setWifiSubnetMask(quint32 subnetMask)
	{
		mWifiSubnetMask = subnetMask;
		mWifiConfigDirty = true;
		emit wifiSubnetMaskChanged(subnetMask);
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

	bool isPasswordDirty() const
	{
		return mPasswordDirty;
	}

	bool isTextDirty() const
	{
		return mTextDirty;
	}

	bool isWifiConfigDirty() const
	{
		return mWifiConfigDirty;
	}

	void clearPassword()
	{
		mPasswordDirty = false;
	}

	void clearText()
	{
		mTextDirty = false;
	}

	void clearWifiConfig()
	{
		mWifiConfigDirty = false;
	}

private:
	QString mPassword;
	QString mText;
	QString mWifiSSID;
	QString mWifiPassword;
	quint32 mWifiIP = 0;
	quint32 mWifiSubnetMask = 0;
	float mBlinkRate = 0.0;
	float mSlideRate = 0.0;
	bool mPasswordDirty = false;
	bool mTextDirty = false;
	bool mWifiConfigDirty = false;
};

#endif
