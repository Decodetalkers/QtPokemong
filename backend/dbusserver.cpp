#include "dbusserver.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QtDBus/QtDBus>
#include <interface/myinterface.h>
#include <stdio.h>
#include <stdlib.h>
class PongPrivate
{
public:
    PongPrivate(Pong *q)
        : q_ptr(q){};
    ~PongPrivate(){};

    QString GetQptrTag() const { return QString("%1 from %2").arg(q_ptr->tag, tag); }

private:
    Q_DECLARE_PUBLIC(Pong)
    Pong *const q_ptr;
    QString tag{"PongPrivate"};
};
Pong::Pong()
    : d_ptr(new PongPrivate(this))
{
    startTimer(20000);
}
// TODO: need log
void Pong::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    auto a = QRandomGenerator::global()->bounded(100);
    if (a > 70) {
        emit meetenermy();
    } else if (a > 50) {
        emit weather("SandStorm");
    } else if (a > 40) {
        emit weather("Rain");
    }
}

Pong::~Pong() {}
QString Pong::ping(const QString &arg)
{
    Q_D(const Pong);
    qDebug() << d->GetQptrTag();
    printf("has get\n");
    qDebug() << arg;
    emit weather(arg);
    // QMetaObject::invokeMethod(QCoreApplication::instance(), "quit");
    return QString("ping %1 get called").arg(arg);
}
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Connect error");
        return 1;
    }
    if (!QDBusConnection::sessionBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "This has been registered");
        exit(1);
    }
    Pong pong;
    // QDBusConnection::sessionBus().registerObject("/", &pong, QDBusConnection::ExportAllSlots);
    QDBusConnection::sessionBus().registerObject("/", &pong, QDBusConnection::ExportAllContents);
    app.exec();
    return 0;
}
