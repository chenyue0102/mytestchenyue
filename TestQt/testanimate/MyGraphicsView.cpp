#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
	, m_nSceneWidth(0)
	, m_nSceneHeight(0)
{
}

MyGraphicsView::~MyGraphicsView()
{
}

void MyGraphicsView::setFitSize(int width, int height)
{
	m_nSceneWidth = width;
	m_nSceneHeight = height;
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
	__super::resizeEvent(event);
	if (m_nSceneWidth > 0 && m_nSceneHeight > 0)
	{
		fitInView(0, 0, m_nSceneWidth, m_nSceneHeight, Qt::KeepAspectRatio);
	}
}