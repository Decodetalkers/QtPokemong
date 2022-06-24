#ifndef BATTLELINE_H
#define BATTLELINE_H

#include <QListView>
#include <QStringListModel>

class Battleline : public QWidget
{
    Q_OBJECT
public:
    Battleline(QWidget *parent = nullptr);
private:
    QStringListModel *chatline;
};

#endif  // !BATTLELINE_H
