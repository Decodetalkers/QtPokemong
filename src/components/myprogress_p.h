#pragma once
#include <Qt>
class MyProgress;
class MyProgressDelegate;
class MyProgressPrivate {
	Q_DISABLE_COPY(MyProgressPrivate)
	Q_DECLARE_PUBLIC(MyProgress)


public:
	MyProgressPrivate(MyProgress *q);
	~MyProgressPrivate();
	
	void init();

	MyProgress *const q_ptr;
	MyProgressDelegate *delegate;
};
