#pragma once

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	MyGraphicsView(QWidget *parent = 0);
	~MyGraphicsView();
public:
	void setFitSize(int width, int height);
protected:
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private:
	int m_nSceneWidth;
	int m_nSceneHeight;
};
