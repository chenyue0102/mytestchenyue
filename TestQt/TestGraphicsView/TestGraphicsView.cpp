#include <assert.h>
#include "TestGraphicsView.h"
#include "MyGraphicsScene.h"
#include <QGraphicsTextItem>
#include "MyGraphicsObject.h"

TestGraphicsView::TestGraphicsView(QWidget *parent)
	: QWidget(parent)
	, scene(0)
{
	ui.setupUi(this);

	scene = new MyGraphicsScene();
	scene->setSceneRect(-400, -300, 800, 600);
	ui.graphicsView->setScene(scene);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing);
	ui.graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	ui.graphicsView->setBackgroundBrush(QColor(230, 200, 167));

	onAddObj();
	connect(ui.pushButtonAddText, SIGNAL(clicked()), SLOT(onAddText()));
	connect(ui.pushButtonRefresh, SIGNAL(clicked()), SLOT(onRefresh()));
	connect(ui.pushButtonAddObj, SIGNAL(clicked()), SLOT(onAddObj()));
}

void TestGraphicsView::onAddText()
{
	QGraphicsTextItem *textItem = new QGraphicsTextItem();
	textItem->setPlainText("abc");
	textItem->setPos(0, 0);
	textItem->setFlag(QGraphicsItem::ItemIsMovable, true);
	textItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
	textItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	QFont ft = font();
	ft.setPixelSize(24);
	textItem->setFont(ft);
	scene->addItem(textItem);
}

void TestGraphicsView::onRefresh()
{
	QString str = ui.lineEditScale->text();
	double d = str.toDouble() / 100;

	QMatrix oldMatrix = ui.graphicsView->matrix();
	ui.graphicsView->resetMatrix();
	ui.graphicsView->translate(oldMatrix.dx(), oldMatrix.dy());
	ui.graphicsView->scale(d, d);
}

void TestGraphicsView::onAddObj()
{
	MyGraphicsObject *pObj = new MyGraphicsObject;
	pObj->setPos(-200, -150);
	pObj->setSize(QSizeF(400, 300));
	pObj->setFlag(QGraphicsItem::ItemIsMovable, true);
	pObj->setFlag(QGraphicsItem::ItemIsSelectable, true);
	pObj->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	scene->addItem(pObj);
}
