#pragma once
#include <QElapsedTimer>
#include <QScopedPointer>
#include <QtCore/QObject>
class PongPrivate;

class Pong : public QObject
{
    Q_OBJECT
    // define the interface name
    Q_CLASSINFO("D-Bus Interface", "mime.example.test")
public:
    Pong();
    ~Pong();
    QString tag{"MainWindow"};
public slots:
    Q_SCRIPTABLE QString Ping(const QString &arg);

private:
    QScopedPointer<QElapsedTimer> timer;
    void timerEvent(QTimerEvent *event) override;
Q_SIGNALS:
    Q_SCRIPTABLE void Weather(const QString);
    Q_SCRIPTABLE void MeetEnermy();

protected:
    // scopepointer
    QScopedPointer<PongPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(Pong)
};
