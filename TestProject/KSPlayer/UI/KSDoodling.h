#pragma once

#include <QtWidgets/QWidget>
#include <vector>
#include <list>
#include <QPen>

class KSDoodling : public QWidget
{
	Q_OBJECT
public:
	enum EnumObject
	{
		EnumObjectNone,
		EnumObjectBitmap,
	};
	struct KSObjectInfo
	{
		EnumObject type;
		QRect rc;
		QPixmap bmp;
	};
public:
	KSDoodling(QWidget *parent = Q_NULLPTR);
public:
	void showDesktop();
	void calcMinRect(const QPoint &dotPos);
public slots:
	void setPen(const QPen &pen);
	void setDoodlingVisible(bool bVisible);
	void setScreen(int nScreen);
protected:
	virtual void paintEvent(QPaintEvent *event)override;
	virtual void mousePressEvent(QMouseEvent *event)override;
	virtual void mouseReleaseEvent(QMouseEvent *event)override;
	virtual void mouseMoveEvent(QMouseEvent *event)override;
private:
	bool m_bMousePressed;
	QPen m_pen;
	std::list<KSObjectInfo> m_objectArray;
	QImage m_tmpImg;
	QPoint m_ptLastPos;
	int m_nLeft, m_nTop, m_nRight, m_nBottom;
	QColor m_bkClr;
	int m_nScreen;
};
