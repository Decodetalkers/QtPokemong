#include "game.h"
#include <QDebug>
#include <QFutureWatcher>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QWidget>
#include <QtConcurrent>
const QString baseurl = "https://raw.githubusercontent.com/PokeAPI/sprites/"
                        "master/sprites/pokemon/%1.png";
const QString loadinged = ":/resources/yousaki.jpg";
QFuture<QByteArray> downloads(const QUrl url) {
  return QtConcurrent::run([=] {
    QNetworkAccessManager qam = QNetworkAccessManager();
    QNetworkRequest request(url);
    auto before = qam.get(request);
    // await , oh ,sorry , cpp does have await now ,:(;
    QEventLoop loop;
    QObject::connect(before, &QNetworkReply::finished, &loop,
                     &QEventLoop::quit);
    loop.exec();
    auto res = before->readAll();
    if (before->error() != QNetworkReply::NoError) {
      qDebug() << "error";
    }
    before->deleteLater();
    QThread::sleep(1);
    return res;
  });
}
Player::Player(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *panel = new QHBoxLayout();

  QGridLayout *buttons = new QGridLayout();

  QPushButton *beta = new QPushButton("A", this);

  buttons->addWidget(beta, 0, 0, 1, 1);
  QPushButton *gamma = new QPushButton("B", this);
  buttons->addWidget(gamma, 0, 1, 1, 1);

  buttons->addWidget(new QPushButton("C", this), 1, 0, 1, 1);
  buttons->addWidget(new QPushButton("D", this), 1, 1, 1, 1);

  panel->addLayout(buttons);
  QImage image = QImage(loadinged);
  player = new QLabel(this);
  player->setPixmap(QPixmap::fromImage(image));
  panel->addWidget(player);
  setLayout(panel);

  connect(beta, &QPushButton::clicked, this, [&] {
    auto a = QRandomGenerator::global()->bounded(100);
    download(QUrl(QString(baseurl).arg(a)));
  });
  // auto a = QRandomGenerator::global()->bounded(100);
  // download(QUrl(QString(baseurl).arg(a)));
}
void Player::download(const QUrl url) {
  QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>(this);
  QFuture<QByteArray> t1 = downloads(url);
  QImage image = QImage(loadinged);
  // player = new QLabel();
  player->setPixmap(QPixmap::fromImage(image));
  // panel->addWidget(player);
  connect(watcher, &QFutureWatcher<QByteArray>::finished, this,
          [watcher, this] {
            watcher->deleteLater();
            auto array = watcher->result();
            QPixmap image;
            image.loadFromData(array);
            player->setPixmap(image);
          });
  watcher->setFuture(t1);
}
Enermy::Enermy(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *panel = new QHBoxLayout();
  QGridLayout *buttons = new QGridLayout();
  buttons->addWidget(new QPushButton("A"), 0, 0, 1, 1);
  buttons->addWidget(new QPushButton("B"), 0, 1, 1, 1);
  buttons->addWidget(new QPushButton("C"), 1, 0, 1, 1);
  buttons->addWidget(new QPushButton("D"), 1, 1, 1, 1);
  // QPushButton *button1 = new QPushButton("Shaoxi");
  enermy = new QLabel(this);
  enermy->setPixmap(QPixmap::fromImage(QImage(loadinged)));
  panel->addWidget(enermy);
  panel->addLayout(buttons);
  setLayout(panel);
  loading();
}

void Enermy::loading() {
  auto a = QRandomGenerator::global()->bounded(100);
  QFutureWatcher<QByteArray> *watcher = new QFutureWatcher<QByteArray>(this);
  QFuture<QByteArray> get = downloads(QUrl(QString(baseurl).arg(a)));
  connect(watcher, &QFutureWatcher<QByteArray>::finished, this,
          [watcher, this] {
            watcher->deleteLater();
            auto array = watcher->result();
            QPixmap image;
            image.loadFromData(array);
            enermy->setPixmap(image);
          });
  watcher->setFuture(get);
}
