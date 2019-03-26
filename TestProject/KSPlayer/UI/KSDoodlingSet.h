#pragma once

#include <QWidget>


struct KSDoodlingSetData;
class QAbstractButton;
class KSDoodlingSet : public QWidget
{
	Q_OBJECT

public:
	KSDoodlingSet(QWidget *parent = Q_NULLPTR);
	~KSDoodlingSet();
public:
	void init();
Q_SIGNALS:
	void signalPenChanged(const QPen &pen);
	void signalDoodlingVisilbe(bool bVisible);
	void signalScreenChanged(int nScreen);
private slots:
	void slotColorToggled(QAbstractButton *pBtn, bool bToggled);
	void slotPenWidthChanged(int nWidth);
	void slotScreenToggled(bool bToggled);
private:
	void onDoodlingVisilbe(bool bVisible);
private:
	KSDoodlingSetData *m_pKSDoodlingSetData;
};
