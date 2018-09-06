/*
文件名：qthttp.h
时间：2018-05-17 09:12:53
*/
#pragma once

#include "common.h"
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QString>
#include <QByteArray> 

//http请求类
class HttpFun : public QObject
{
	Q_OBJECT
public:
	explicit HttpFun(QObject *parent = 0);
	~HttpFun()
	{
		delete m_pNetworkManager;
	}
	QByteArray httpget(const char *strUrl);//根据url发起http请求
	QByteArray httppost(const char *strUrl,u8 *p,int n);//根据url发起http请求

private:
	QNetworkAccessManager* m_pNetworkManager;//网络管理类
};

