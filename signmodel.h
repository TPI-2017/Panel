#ifndef SIGNMODEL_H
#define SIGNMODEL_H

#include <QObject>
#include <QString>
#include <QReadWriteLock>

class SignModel : public QReadWriteLock
{
public:
	explicit SignModel()
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

	void setPassword(QString text)
	{
		mPassword = text;
		mPasswordDirty = true;
	}

	void setText(QString text)
	{
		mText = text;
		mTextDirty = true;
	}

	void setBlinkRate(float blinkRate)
	{
		mBlinkRate = blinkRate;
		mTextDirty = true;
	}

	void setSlideRate(float slideRate)
	{
		mSlideRate = slideRate;
		mTextDirty = true;
	}

	void setWifiSSID(QString ssid)
	{
		mWifiSSID = ssid;
		mWifiConfigDirty = true;
	}

	void setWifiPassword(QString password)
	{
		mWifiPassword = password;
		mWifiConfigDirty = true;
	}

	void setWifiIP(quint32 ip)
	{
		mWifiIP = ip;
		mWifiConfigDirty = true;
	}

	void setWifiSubnetMask(quint32 subnetMask)
	{
		mWifiSubnetMask = subnetMask;
		mWifiConfigDirty = true;
	}

	bool dirty() const
	{
		return mPasswordDirty || mTextDirty || mWifiConfigDirty;
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
