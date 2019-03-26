#pragma once

#include <QtWidgets/QWidget>
#include "ui_KSPlayer.h"

class KSDoodling;
class KSPlayerContainer;
class KSPlayer : public QWidget
{
	Q_OBJECT

public:
	KSPlayer(QWidget *parent = Q_NULLPTR);
	virtual ~KSPlayer();
private:
	Ui::KSPlayerClass ui;
	KSDoodling *m_pKSDoodling;
	KSPlayerContainer *m_pKSPlayerContainer;
};
