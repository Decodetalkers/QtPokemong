#pragma once

#include <Qt>
class MyPopWindow;
class QStateMachine;
class QStackedLayout;
class MyPopWindowProxy;
class MyPopWindowDialog;
class MyPopWindowPrivate 
{
	Q_DISABLE_COPY(MyPopWindowPrivate)
	Q_DECLARE_PUBLIC(MyPopWindow)

public:
	MyPopWindowPrivate(MyPopWindow *q);
	~MyPopWindowPrivate();

	void init();

	MyPopWindow *const q_ptr;

	MyPopWindowDialog *dialogWindow;
	QStackedLayout *proxyStack;
	QStateMachine *stateMachine;
	MyPopWindowProxy *proxy;
};
