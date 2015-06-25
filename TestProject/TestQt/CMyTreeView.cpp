#include "CMyTreeView.h"

CMyTreeView::CMyTreeView(QWidget *parent)
	: QTreeView(parent)
{
	ui.setupUi(this);
}

CMyTreeView::~CMyTreeView()
{

}

void CMyTreeView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
	__super::currentChanged(current, previous);
	emit myCurrentChanged(current, previous);
}
