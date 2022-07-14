#include "myprogress_internal.h"

MyProgressDelegate::MyProgressDelegate(MyProgress *parent)
    : QObject(parent)
    , m_progress(parent)
    , m_offset(0)
{
    Q_ASSERT(parent);
}
MyProgressDelegate::~MyProgressDelegate() {}
