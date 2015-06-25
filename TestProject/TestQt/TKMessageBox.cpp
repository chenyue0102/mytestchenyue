#include "TKMessageBox.h"
#include "CMyDelegate.h"

TKMessageBox::TKMessageBox(QWidget *parent)
	: QWidget(parent)
	, m_MyTreeModel(new CMyTreeModel(this))
{
	ui.setupUi(this);
	ui.treeView->setModel(m_MyTreeModel);
	auto *pCMyDelegate = new CMyDelegate(this);
	ui.treeView->setItemDelegate(pCMyDelegate);
	ui.treeView->setIndentation(0);

	auto *p = ui.treeView->viewport();
	p->installEventFilter(pCMyDelegate);

	connect(ui.treeView, SIGNAL(myCurrentChanged(const QModelIndex &, const QModelIndex &)), 
		pCMyDelegate, SLOT(MyCurrentChanged(const QModelIndex &, const QModelIndex &)));
	//auto *pmodel = ui.treeView->selectionModel();
	//connect(pmodel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
	//	pCMyDelegate, SLOT(MyCurrentChanged(QModelIndex,QModelIndex)));

	connect(ui.pushButton, SIGNAL(clicked(bool)), this, SLOT(onHideButtonClicked()));
	connect(ui.pushButton_2, SIGNAL(clicked(bool)), this, SLOT(onShowButtonClicked()));

	connect(ui.pushButton_3, SIGNAL(clicked(bool)), this, SLOT(onGrayButtonClicked()));
	connect(ui.pushButton_4, SIGNAL(clicked(bool)), this, SLOT(onColorButtonClicked()));
	connect(ui.pushButton_5, SIGNAL(clicked(bool)), this, SLOT(onSmallButtonClicked()));
	//connect(ui.treeView, SIGNAL((int)
	setProperty("exitcode", 1);
}

TKMessageBox::~TKMessageBox()
{

}

void TKMessageBox::onDestroy(QObject*)
{
}

void TKMessageBox::onHideButtonClicked()
{
	auto index = ui.treeView->currentIndex();
	if (index.isValid())
	{
		m_MyTreeModel->setData(index, false, Qt::UserRole + EnumUserPropertyVisiable);
	}
}

void TKMessageBox::onShowButtonClicked()
{
	QModelIndex rootIndex;
	int nCount = m_MyTreeModel->rowCount(rootIndex);
	for (int nIndex = 0; nIndex < nCount; nIndex++)
	{
		QModelIndex groupIndex = m_MyTreeModel->index(nIndex, 0, rootIndex);
		int nGroupCount = m_MyTreeModel->rowCount(groupIndex);
		for (int nItemIndex = 0; nItemIndex < nGroupCount; nItemIndex++)
		{
			QModelIndex itemIndex = m_MyTreeModel->index(nItemIndex, 0, groupIndex);
			QVariant vtVisible = m_MyTreeModel->data(itemIndex, Qt::UserRole + EnumUserPropertyVisiable);
			if (!vtVisible.toBool())
			{
				m_MyTreeModel->setData(itemIndex, true, Qt::UserRole + EnumUserPropertyVisiable);
			}
		}
	}
}

void TKMessageBox::onGrayButtonClicked()
{
	auto index = ui.treeView->currentIndex();
	if (index.isValid())
	{
		m_MyTreeModel->setData(index, true, Qt::UserRole + EnumUserPropertyGray);
	}
}

void TKMessageBox::onColorButtonClicked()
{
	auto index = ui.treeView->currentIndex();
	if (index.isValid())
	{
		m_MyTreeModel->setData(index, false, Qt::UserRole + EnumUserPropertyGray);
	}
}

void TKMessageBox::onSmallButtonClicked()
{
	m_MyTreeModel->setProperty("SmallHeadImage", true);
	emit m_MyTreeModel->layoutChanged();
}
