#pragma once

#include <QGraphicsScene>

class MyGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MyGraphicsScene(QObject *parent = 0);
	~MyGraphicsScene();
};
