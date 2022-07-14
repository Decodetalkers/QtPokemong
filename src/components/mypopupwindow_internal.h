#pragma once
#include <QAbstractTransition>
#include <QEvent>
#include <QtWidgets/QWidget>
class QStackedLayout;
class MyPopWindow;
class MyPopWindowDialog;

/*! 
 * @class MyTransitionType
 *
 * About the transiton of popupwindow
 *
 */
enum class MyTransitionType {
    ShowDialog,
    HideDialog,
};

struct MyTransitionEvent : public QEvent
{
    MyTransitionEvent(MyTransitionType type)
        : QEvent(QEvent::Type(QEvent::User + 1))
        , type(type)
    {
    }
    MyTransitionType type;
};

class MyPopWindowProxy : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)
    enum class TransparencyMode {
        Transparent,
        SemiTransparent,
        Opaque,
    };

public:
    MyPopWindowProxy(MyPopWindowDialog *source, QStackedLayout *layout, MyPopWindow *dialog, QWidget *parent = nullptr);
    ~MyPopWindowProxy();

    void setOpacity(qreal opacity);
    inline qreal opacity() const;

public slots:
    void makeOpaque();
    void makeTransparent();

    QSize sizeHint() const override;

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(MyPopWindowProxy)

    MyPopWindowDialog *const m_source;
    QStackedLayout *const m_layout;
    MyPopWindow *const m_dialog;
    qreal m_opacity;
    TransparencyMode m_mode;
};
inline qreal MyPopWindowProxy::opacity() const
{
    return m_opacity;
}
class MyPopWindowDialog : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int offset WRITE setOffset READ offset)

public:
    explicit MyPopWindowDialog(MyPopWindow *dialog, QWidget *parent = nullptr);
    ~MyPopWindowDialog();

    void setOffset(int offset);
    int offset() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(MyPopWindowDialog)

    MyPopWindow *const m_dialog;
};

class MyStateTransition : public QAbstractTransition
{
    Q_OBJECT
public:
    MyStateTransition(MyTransitionType type);

protected:
    bool eventTest(QEvent *event) override;
    void onTransition(QEvent *) override;

private:
    MyTransitionType m_type;
};
