#ifndef DBUSSERVER_H
#define DBUSSERVER_H
#include <QScopedPointer>
#include <QtCore/QObject>
class PongPrivate;

class Pong : public QObject
{
    Q_OBJECT
	Q_CLASSINFO("D-Bus Interface","mime.example.test")
public:
    Pong();
	~Pong();
    QString tag{"MainWindow"};
public slots:
    Q_SCRIPTABLE QString ping(const QString &arg);

protected:
    QScopedPointer<PongPrivate> d_ptr;


private:
    Q_DECLARE_PRIVATE(Pong)
};
#endif  // !DBUSSERVER_H
