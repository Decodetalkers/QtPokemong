#include "loading.h"
#include <mywidgets/myprogress.h>

#include "mainwindow.h"

#include <QGSettings/QGSettings>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QVBoxLayout>
#include <QtConcurrent>

const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";
QFuture<QList<QByteArray>> downloads(const QList<QUrl> url)
{
    return QtConcurrent::run([=] {
        QNetworkAccessManager qam = QNetworkAccessManager();
        QList<QByteArray> output;
        for (auto url : url) {
            QNetworkRequest request(url);
            auto before = qam.get(request);
            // await , oh ,sorry , cpp does have await now ,:(;
            {
                QEventLoop loop;
                QObject::connect(before, &QNetworkReply::finished, &loop, &QEventLoop::quit);
                loop.exec();
            }
            auto newbefore = QScopedPointer(before);
            auto res = newbefore->readAll();
            if (before->error() != QNetworkReply::NoError) {
                res = nullptr;
            }
            output.push_back(res);
        }
        // QThread::sleep(3);
        return output;
    });
}
Loading::Loading(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel("Loading");
    MyProgress *progress = new MyProgress;

    setFixedSize(300, 100);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(progress);

    setLayout(layout);
    if (QGSettings::isSchemaInstalled("apps.eightplus.pokemongame")) {
        m_gsettings = new QGSettings("apps.eightplus.pokemongame");
        // qDebug() << m_gsettings->get("names").toStringList();
        QStringList names = m_gsettings->get("names").toStringList();
        QStringList list = m_gsettings->get("ids").toStringList();
        QList<QUrl> urls;
        for (QString const &alist : list) {
            urls << QUrl(QString(baseurl).arg(alist.toInt()));
        }
        QFutureWatcher<QList<QByteArray>> *watcher = new QFutureWatcher<QList<QByteArray>>(this);
        QFuture<QList<QByteArray>> getnames = downloads(urls);
        connect(watcher, &QFutureWatcher<QList<QByteArray>>::finished, this, [watcher, this, list, names] {
            watcher->deleteLater();
            auto arrays = watcher->result();
            auto size = list.size();
            for (int i = 0; i < size; ++i) {
                if (list[i].toInt() == 0) {
                    this->m_icons << PokemongIcon();
                } else {
                    this->m_icons << PokemongIcon(QVariant::fromValue(arrays[i]), list[i].toInt());
                }
            }
            QSharedPointer<PokeMonModel> model = QSharedPointer<PokeMonModel>(new PokeMonModel);
            model->populateData(this->m_icons, names);
            MainWindow *mainwindow = new MainWindow(nullptr, model);
            mainwindow->show();
            close();
        });
        watcher->setFuture(getnames);
    } else {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=] {
            if (m_dist > 1000) {
                timer->stop();
                timer->deleteLater();
                MainWindow *window = new MainWindow;
                window->show();
                close();
            }
            m_dist += 1;
        });
        timer->start(15);
    }
}
