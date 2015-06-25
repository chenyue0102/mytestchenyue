#ifndef TKMESSAGEBOX_H
#define TKMESSAGEBOX_H

#include <QWidget>
#include "ui_TKMessageBox.h"
#include "CMyTreeModel.h"

class TKMessageBox : public QWidget
{
	Q_OBJECT

public:
	TKMessageBox(QWidget *parent = 0);
	~TKMessageBox();
public slots:
	void onDestroy(QObject*);
	void onHideButtonClicked();
	void onShowButtonClicked();
	void onGrayButtonClicked();
	void onColorButtonClicked();
	void onSmallButtonClicked();
private:
	Ui::TKMessageBox ui;
	int	m_nResult;
	CMyTreeModel	*m_MyTreeModel;
};

#endif // TKMESSAGEBOX_H
