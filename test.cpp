/*#include <iostream>
#include "client.h"


class ClientTest : public Client
{
public:
	ClientTest()
	: Client()
	{

	}

	virtual ~ClientTest()
	{

	}

	void test(const char *hostname, const char *password);
};

void ClientTest::test(const char *hostname, const char *password)
{

	{
		mConnection.connect(QString(hostname));
		qDebug("\nGet-Set-Get Text");
		auto m = Message::createGetTextRequest(password);
		if (performInteraction(m) != Ok)
			goto finish;
		auto m1 = Message::createSetTextRequest(password, 0,0, "Adios mundo cruel.");
		if (performInteraction(m1) != Ok)
			goto finish;
		auto m2 = Message::createGetTextRequest(password);
		if (performInteraction(m2) != Ok)
			goto finish;
		mConnection.disconnect();
	}
	{
		mConnection.connect(QString(hostname));
		qDebug("\nGet-Set-Get WifiConfig");
		auto m = Message::createGetWifiConfigRequest(password);
		if (performInteraction(m) != Ok)
			goto finish;
		auto m1 = Message::createSetWifiConfigRequest(password, "Ramiro", "queimbeciljeje", 0xDEADBEEF, 0xFF000000);
		if (performInteraction(m1) != Ok)
			goto finish;
		auto m2 = Message::createGetWifiConfigRequest(password);
		if (performInteraction(m2) != Ok)
			goto finish;
		mConnection.disconnect();
	}

finish:
	mConnection.disconnect();

}

int test_main()
{
	ClientTest tester;
	const char *hostname = "192.168.0.14";
	const char *password = "1234";

	tester.test(hostname, password);

	return 0;
}
*/
