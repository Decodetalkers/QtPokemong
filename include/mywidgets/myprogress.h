#pragma once

#include <QtWidgets/QProgressBar>

class MyProgressPrivate;

class MyProgress : public QProgressBar
{
    Q_OBJECT

public:
    explicit MyProgress(QWidget *parent = nullptr);
    ~MyProgress();

protected:
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<MyProgressPrivate> d_ptr;

private:
    Q_DISABLE_COPY(MyProgress)
    Q_DECLARE_PRIVATE(MyProgress)
};
