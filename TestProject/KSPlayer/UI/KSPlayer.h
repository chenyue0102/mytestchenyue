#pragma once

#include <QtWidgets/QWidget>
#include "ui_KSPlayer.h"

class KSVideoContainer;
class KSPlayer : public QWidget
{
	Q_OBJECT

public:
	KSPlayer(QWidget *parent = Q_NULLPTR);
	virtual ~KSPlayer();
private:
	Ui::KSPlayerClass ui;
	KSVideoContainer *m_pKSVideoContainer;
};
