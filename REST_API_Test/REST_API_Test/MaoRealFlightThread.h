#pragma once

#include <Windows.h>
#include <QThread>
#include <QMap>
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "MaoFlight.h"
using namespace std;

class MaoRealFlightThread :	public QThread
{
	Q_OBJECT

signals :
	void FSXupdate(MaoFlightUpdate, MaoFlight*);
	void FSXtimeout(MaoFlight*);
	void debug(qint64);

public:
	MaoRealFlightThread();
	~MaoRealFlightThread();

	void setShutdown();
	void updateFSXcenter(double fsxLat, double fsxLon);

public slots:
	void SHUTDOWN();

protected:
	void run();

private slots:
	void checkFlightTimeout();
	void getDump1090Data();
	void loadDump1090Data(QNetworkReply* reply);
	void getFlightRadar24Data();
	void loadFlightRadar24Data(QNetworkReply* reply);

private:
	LARGE_INTEGER freq, starT, stop;

	bool isExit;

	double latUp, latDown, lonLeft, lonRight;

private:
	CRITICAL_SECTION realFlightCS;
	QMap<QString, MaoFlight*> realFlights;

	QTimer timerCheck;
	QTimer timerDump1090;
	QNetworkAccessManager restDump1090;
	QTimer timerFlightRadar24;
	QNetworkAccessManager restFlightRadar24;
	QTimer timerModeSMixer2;
	QNetworkAccessManager restModeSMixer2;
};
