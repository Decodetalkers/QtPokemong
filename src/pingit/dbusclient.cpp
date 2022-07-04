#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

#include <interface/myinterface.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr,
                "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    //[1] ping the SERVICES
    QDBusInterface iface(SERVICE_NAME, "/", "mime.example.test", QDBusConnection::sessionBus());
    if (iface.isValid()) {
        QDBusReply<QString> reply = iface.call("ping", argc > 1 ? argv[1] : "");
        if (reply.isValid()) {
            printf("Reply was: %s\n", qPrintable(reply.value()));
            return 0;
        }

        fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
        return 1;
    }

    fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
    return 1;
}
