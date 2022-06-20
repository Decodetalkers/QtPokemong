#include "game.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

Player::Player(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *panel = new QHBoxLayout();
  QGridLayout *buttons = new QGridLayout();
  buttons->addWidget(new QPushButton("A"), 0, 0, 1, 1);
  buttons->addWidget(new QPushButton("B"), 0, 1, 1, 1);
  buttons->addWidget(new QPushButton("C"), 1, 0, 1, 1);
  buttons->addWidget(new QPushButton("D"), 1, 1, 1, 1);
  panel->addLayout(buttons);
  QPushButton *button1 = new QPushButton("Shaoxi");
  button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  panel->addWidget(button1);
  setLayout(panel);
}
Enermy::Enermy(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *panel = new QHBoxLayout();
  QGridLayout *buttons = new QGridLayout();
  buttons->addWidget(new QPushButton("A"), 0, 0, 1, 1);
  buttons->addWidget(new QPushButton("B"), 0, 1, 1, 1);
  buttons->addWidget(new QPushButton("C"), 1, 0, 1, 1);
  buttons->addWidget(new QPushButton("D"), 1, 1, 1, 1);
  QPushButton *button1 = new QPushButton("Shaoxi");
  button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  panel->addWidget(button1);
  panel->addLayout(buttons);
  setLayout(panel);
}
