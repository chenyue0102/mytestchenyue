#include "testedithtml.h"

testedithtml::testedithtml(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonReload, SIGNAL(clicked()), SLOT(onReload()));
}

void testedithtml::onReload()
{
	ui.
}
