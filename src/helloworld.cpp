#include "helloworld.h"

#include <QCoreApplication>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

/// HelloWorld

HelloWorld::HelloWorld()
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    if(qEnvironmentVariableIsSet("PORT") && !qEnvironmentVariableIsEmpty("PORT")) {
        server->listen(QHostAddress::Any, qgetenv("PORT").toInt());
    } else {
        server->listen(QHostAddress::Any, 8080);
    }

}

void HelloWorld::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
//    Q_UNUSED(req);

//    QByteArray body = "{\"message\": \"Hello Qt World\"}";
//    resp->setHeader("Content-Type", QString::fromUtf8("application/json"));
//    resp->setHeader("Content-Length", QString::number(body.size()));
//    resp->writeHead(200);
//    resp->end(body);
    new Responder(req, resp);
}
/// Responder

Responder::Responder(QHttpRequest *req, QHttpResponse *resp)
    : m_req(req)
    , m_resp(resp)
{
    QRegExp exp("^/user/([a-z]+$)");
    if (exp.indexIn(req->path()) == -1)
    {
        resp->writeHead(403);
        resp->end(QByteArray("You aren't allowed here!"));
        /// @todo There should be a way to tell request to stop streaming data
        return;
    }
    resp->setHeader("Access-Control-Allow-Origin", "*");
    resp->setHeader("Content-Type", "text/html");
    resp->writeHead(200);

    QString name = exp.capturedTexts()[1];
    QString bodyStart = tr("<html><head><title>BodyData App</title></head><body><h1>Hello %1!</h1><p>port:%2</><p>").arg(name).arg(qgetenv("PORT"));
    resp->write(bodyStart.toUtf8());

    connect(req, SIGNAL(data(const QByteArray&)), this, SLOT(accumulate(const QByteArray&)));
    connect(req, SIGNAL(end()), this, SLOT(reply()));
    connect(m_resp, SIGNAL(done()), this, SLOT(deleteLater()));
}

Responder::~Responder()
{
}

void Responder::accumulate(const QByteArray &data)
{
    m_resp->write(data);
}

void Responder::reply()
{
    m_resp->end(QByteArray("</p></body></html>"));
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    HelloWorld hello;
    app.exec();
}
