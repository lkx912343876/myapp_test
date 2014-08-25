#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include <QObject>
#include <QScopedPointer>

/// HelloWorld

class HelloWorld : public QObject
{
    Q_OBJECT

public:
    HelloWorld();

private slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);
};
/// Responder

class Responder : public QObject
{
    Q_OBJECT

public:
    Responder(QHttpRequest *req, QHttpResponse *resp);
    ~Responder();

signals:
    void done();

private slots:
    void accumulate(const QByteArray &data);
    void reply();

private:
    QScopedPointer<QHttpRequest> m_req;
    QHttpResponse *m_resp;
};
