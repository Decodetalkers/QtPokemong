#ifndef DBUSSERVER_H
#define DBUSSERVER_H
#include <QScopedPointer>
#include <QtCore/QObject>
class PongPrivate;

class Pong : public QObject
{
    Q_OBJECT
	// define the interface name
	Q_CLASSINFO("D-Bus Interface","mime.example.test")
public:
    Pong();
	~Pong();
    QString tag{"MainWindow"};
public slots:
    Q_SCRIPTABLE QString ping(const QString &arg);
Q_SIGNALS:
	Q_SCRIPTABLE void weather(const QString);
protected:
	// scopepointer 
    QScopedPointer<PongPrivate> d_ptr;


private:
    Q_DECLARE_PRIVATE(Pong)
};
#endif  // !DBUSSERVER_H
