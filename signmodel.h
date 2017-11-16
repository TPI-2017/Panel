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
	
	bool dirty() const
	{
		return !committed;
	};

private:
	bool committed = false;
	T mObject;
};

class SignModel : public QObject
{
	Q_OBJECT
public:
	explicit SignModel(QObject *parent = 0)
	: QObject(parent)
	{
	};
	
	// Marca todo el contenido como 
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
	
	// Devuelve verdadero si hay algún cambio no mandado al cartel
	bool dirty() const
	{
		return mDirty;
	}

	// Getters
	const QString &text() const
	{
		return mText.get();
	};

	const QString &wifiSSID() const
	{
		return mWifiSSID.get();
	};

	const QString &wifiPassword() const
	{
		return mWifiPassword.get();
	};

	const QHostAddress &wifiIP() const
	{
		return mWifiIP.get();
	};

	const QHostAddress &wifiSubnetMask() const
	{
		return mWifiSubnetMask.get();
	};

	float blinkRate() const
	{
		return mBlinkRate.get();
	};

	float slideRate() const
	{
		return mSlideRate.get();
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
		if(mText.update(text)) {
			mDirty = true;
			emit textChanged(text);
			qDebug(mText.get().toStdString().data());
		}
    }

	void setWifiSSID(QString ssid)
	{
		if(mWifiSSID.update(ssid)) {
			mDirty = true;
			emit wifiSSIDChanged(ssid);
			qDebug(mWifiSSID.get().toStdString().data());
		}
    }

	void setWifiPassword(QString password)
	{
		if(mWifiPassword.update(password)) {
			mDirty = true;
			emit wifiPasswordChanged(password);
			qDebug(mWifiPassword.get().toStdString().data());
		}
    }
	
	void setWifiIP(QHostAddress ip)
    {
		if(mWifiIP.update(ip)) {
			mDirty = true;
			emit wifiIPChanged(ip);
			qDebug(mWifiIP.get().toString().toStdString().data());
		}
    }

	void setWifiSubnetMask(QHostAddress subnetMask)
	{
		if(mWifiSubnetMask.update(subnetMask)) {
			mDirty = true;
			emit wifiSubnetMaskChanged(subnetMask);
			qDebug(mWifiSubnetMask.get().toString().toStdString().data());
		}
    }

	void setBlinkRate(float blinkRate)
	{
		if(mBlinkRate.update(blinkRate)) {
			mDirty = true;
			emit blinkRateChanged(blinkRate);
			qDebug(QString::number(blinkRate).toStdString().data());
		}
    }

	void setSlideRate(float slideRate)
	{
		if(mSlideRate.update(slideRate)) {
			mDirty = true;
			emit slideRateChanged(slideRate);
			qDebug(QString::number(slideRate).toStdString().data());
		}
    }

    void emitValues()
    {
        emit textChanged(mText.get());
        emit wifiSSIDChanged(mWifiSSID.get());
        emit wifiPasswordChanged(mWifiPassword.get());
        emit wifiIPChanged(mWifiIP.get());
        emit wifiSubnetMaskChanged(mWifiSubnetMask.get());
        emit blinkRateChanged(mBlinkRate.get());
        emit slideRateChanged(mSlideRate.get());
    }
	

private:
	Field<QString> mText;
	Field<QString> mWifiSSID;
	Field<QString> mWifiPassword;
	Field<QHostAddress> mWifiIP;
	Field<QHostAddress> mWifiSubnetMask;
	Field<float> mBlinkRate;
	Field<float> mSlideRate;
	bool mDirty = true;
};

#endif
