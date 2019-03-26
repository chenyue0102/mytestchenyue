#include "KSDoodlingSet.h"
#include <assert.h>
#include <QPen>
#include "ui_KSDoodlingSet.h"
#include "SystemConfig.h"
#include "Single.h"

#define PROPERTY_COLOR "penColor"

struct KSDoodlingSetData
{
	Ui::KSDoodlingSet ui;
	QPen pen;
	int nScreen;

	KSDoodlingSetData()
		: ui()
		, pen()
		, nScreen(0)
	{

	}
};
KSDoodlingSet::KSDoodlingSet(QWidget *parent)
	: QWidget(parent)
	, m_pKSDoodlingSetData(new KSDoodlingSetData)
{
	Ui::KSDoodlingSet &ui = m_pKSDoodlingSetData->ui;
	ui.setupUi(this);
}

KSDoodlingSet::~KSDoodlingSet()
{
	delete m_pKSDoodlingSetData;
	m_pKSDoodlingSetData = nullptr;
}

void KSDoodlingSet::init()
{
	auto &setting = Single<SystemConfig>::Instance();
	int nScreen = setting.getScreen();
	int nPenWidth = setting.getPenWidth();
	const QList<QRgb> clrs = setting.getPenColors();
	auto &ui = m_pKSDoodlingSetData->ui;
	auto &pen = m_pKSDoodlingSetData->pen;
	QAbstractButton *pBtnPenColors[] = { ui.pushButtonPenColor0, ui.pushButtonPenColor1, ui.pushButtonPenColor2, ui.pushButtonPenColor3, ui.pushButtonPenColor4, ui.pushButtonPenColor5 };
	QButtonGroup *pBtnGroup = new QButtonGroup(this);

	pen.setWidth(nPenWidth);
	m_pKSDoodlingSetData->nScreen = nScreen;
	ui.spinBox->setValue(nPenWidth);
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(slotPenWidthChanged(int)));
	if (clrs.size() == _countof(pBtnPenColors))
	{
		for (unsigned int i = 0; i < clrs.size(); i++)
		{
			QRgb clr = clrs[i];
			pBtnGroup->addButton(pBtnPenColors[i], i);
			pBtnPenColors[i]->setStyleSheet(QStringLiteral("QPushButton{background-color:rgba(%1,%2,%3,%4);}")
				.arg(qRed(clr)).arg(qGreen(clr)).arg(qBlue(clr)).arg(qAlpha(clr)));
			pBtnPenColors[i]->setProperty(PROPERTY_COLOR, clr);
		}
		connect(pBtnGroup, SIGNAL(buttonToggled(QAbstractButton *, bool)), SLOT(slotColorToggled(QAbstractButton *, bool)));
		pen.setColor(clrs[0]);
	}
	else
	{
		assert(false);
	}
	ui.pushButtonHideDoodling->hide();
	connect(ui.pushButtonHideDoodling, &QAbstractButton::clicked, this, [this]() {onDoodlingVisilbe(false); });
	connect(ui.pushButtonShowDoodling, &QAbstractButton::clicked, this, [this]() {onDoodlingVisilbe(true); });

	switch (nScreen)
	{
		case 0:
		{
			ui.radioButtonScreen0->setChecked(true);
			break;
		}
		case 1:
		{
			ui.radioButtonScreen1->setChecked(true);
			break;
		}
		default:
		{
			break;
		}
	}
	connect(ui.radioButtonScreen0, SIGNAL(toggled(bool)), this, SLOT(slotScreenToggled(bool)));
	connect(ui.radioButtonScreen1, SIGNAL(toggled(bool)), this, SLOT(slotScreenToggled(bool)));

	emit signalPenChanged(pen);
	emit signalScreenChanged(nScreen);
}

void KSDoodlingSet::slotPenWidthChanged(int nWidth)
{
	auto &pen = m_pKSDoodlingSetData->pen;
	pen.setWidth(nWidth);
	emit signalPenChanged(pen);

	auto &setting = Single<SystemConfig>::Instance();
	setting.setPenWidth(nWidth);
}

void KSDoodlingSet::slotScreenToggled(bool bToggled)
{
	if (bToggled)
	{
		auto pSender = sender();
		if (nullptr != pSender)
		{
			int nScreen = pSender->property("Screen").toInt();
			emit signalScreenChanged(nScreen);

			auto &setting = Single<SystemConfig>::Instance();
			setting.setScreen(nScreen);
		}
	}
}

void KSDoodlingSet::onDoodlingVisilbe(bool bVisible)
{
	auto &ui = m_pKSDoodlingSetData->ui;
	ui.pushButtonHideDoodling->setVisible(bVisible);
	ui.pushButtonShowDoodling->setVisible(!bVisible);
	emit signalDoodlingVisilbe(bVisible);
}

void KSDoodlingSet::slotColorToggled(QAbstractButton *pBtn, bool bToggled)
{
	if (bToggled
		&& nullptr != pBtn)
	{
		QRgb rgb = pBtn->property(PROPERTY_COLOR).toUInt();
		QPen &pen = m_pKSDoodlingSetData->pen;
		pen.setColor(QColor(rgb));
		emit signalPenChanged(pen);
	}
}
