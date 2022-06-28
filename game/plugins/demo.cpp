#include "demo.h"
#include <QPushButton>
QWidget *pluginDemo::thebutton()
{
    auto temp =  new QPushButton("Beta");
	temp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	return temp;
}
