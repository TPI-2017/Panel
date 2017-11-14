#ifndef SIGNMODEL_H
#define SIGNMODEL_H

#include <QObject>
#include <QString>
#include <QHostAddress>

template<typename T>
class Field
{
public:
	const T& get() const
	{
		return mObject;
	};

	bool update(const T &newValue)
	{
		bool equal = mObject == newValue;
		committed = committed && equal;
		mObject = newValue;
		return !equal;
	};

	void commit()
	{
		committed = true;
	};

private:
	bool committed = false;
	T mObject;
};

class SignModel : public QObject
{
	Q_OBJECT
public:
	explicit SignModel(QObject *parent = 0);
	
	void commit()
	{
		mText.commit();
		mWifiSSID.commit();
		mWifiPassword.commit();
		mWifiIP.commit();
		mWifiSubnetMask.commit();
		mBlinkRate.commit();
		mSlideRate.commit();
	};

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
		if(mText.update(text))
			emit textChanged(text);
	};

	void setWifiSSID(QString ssid)
	{
		if(mWifiSSID.update(ssid))
			emit wifiSSIDChanged(ssid);
	};

	void setWifiPassword(QString password)
	{
		if(mWifiPassword.update(password))
			emit wifiPasswordChanged(password);
	};
	
	void setWifiIP(QHostAddress ip)
	{
		if(mWifiIP.update(ip))
			emit wifiIPChanged(ip);
	}

	void setWifiSubnetMask(QHostAddress subnetMask)
	{
		if(mWifiSubnetMask.update(subnetMask))
			emit wifiSubnetMaskChanged(subnetMask);
	}

	void setBlinkRate(float blinkRate)
	{
		if(mBlinkRate.update(blinkRate))
			emit blinkRateChanged(blinkRate);
	};

	void setSlideRate(float slideRate)
	{
		if(mSlideRate.update(slideRate))
			emit slideRateChanged(slideRate);
	};

private:
	Field<QString> mText;
	Field<QString> mWifiSSID;
	Field<QString> mWifiPassword;
	Field<QHostAddress> mWifiIP;
	Field<QHostAddress> mWifiSubnetMask;
	Field<float> mBlinkRate;
	Field<float> mSlideRate;
};

#endif