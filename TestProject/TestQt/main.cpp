#include "testqt.h"
#include <QtWidgets/QApplication>
#include "TKMessageBox.h"
#include "CloseActionTemplate.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//TestQt w;
	//w.show();

	TKMessageBox *p = new TKMessageBox;
	p->setAttribute(Qt::WA_DeleteOnClose);
	p->show();
	CCloseActionFunction *s = new CCloseActionFunction(p);

	s->m_CallbackFun = [=](int nResult)->void
	{
		int a =  nResult;
		a++;
	};

	return a.exec();
}
