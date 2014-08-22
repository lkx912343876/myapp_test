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
    Q_UNUSED(req);

    QByteArray body = "{\"message\": \"Hello Qt World\"}";
    resp->setHeader("Content-Type", QString::fromUtf8("application/json"));
    resp->setHeader("Content-Length", QString::number(body.size()));
    resp->writeHead(200);
    resp->end(body);
}

/// main

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    HelloWorld hello;
    app.exec();
}
