#ifndef CMYTREEVIEW_H
#define CMYTREEVIEW_H

#include <QTreeView>
#include "ui_CMyTreeView.h"

class CMyTreeView : public QTreeView
{
	Q_OBJECT

public:
	CMyTreeView(QWidget *parent = 0);
	~CMyTreeView();
Q_SIGNALS:
	void myCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
public:
	void currentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
	Ui::CMyTreeView ui;
};

#endif // CMYTREEVIEW_H
