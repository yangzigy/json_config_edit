
#include "qthttp.h"
#include <QEventLoop>

HttpFun::HttpFun(QObject *parent) :
	QObject(parent)
{
	m_pNetworkManager = new QNetworkAccessManager(this);
}

//发起请求
QByteArray HttpFun::httpget(const char *strUrl)
{
	QNetworkRequest netRequest;
	netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
	//setRawHeader(QByteArray("Connection"), QByteArray("keep-alive"));
	netRequest.setUrl(QUrl(strUrl)); //地址信息

	QNetworkReply *reply = m_pNetworkManager->get(netRequest);
	QByteArray responseData;
	QEventLoop eventLoop;
	connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish
	responseData = reply->readAll();
	return responseData;
}
QByteArray HttpFun::httppost(const char *strUrl,u8 *p,int n)
{
	QNetworkRequest netRequest;
	netRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
	netRequest.setHeader(QNetworkRequest::ContentLengthHeader,n);
	netRequest.setUrl(QUrl(strUrl)); //地址信息

	QByteArray senddata((const char*)p,n);
	QNetworkReply *reply = m_pNetworkManager->post(netRequest,senddata);
	QByteArray responseData;
	QEventLoop eventLoop;
	connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish
	responseData = reply->readAll();
	return responseData;
}
