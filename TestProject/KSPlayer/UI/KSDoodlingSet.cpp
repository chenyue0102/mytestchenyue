#include "KSDoodlingSet.h"
#include <assert.h>
#include <QPen>
#include "KSDoodling.h"
#include "ui_KSDoodlingSet.h"
#include "SystemConfig.h"
#include "Single.h"

#define PROPERTY_COLOR "penColor"

struct KSDoodlingSetData
{
	Ui::KSDoodlingSet ui;
	QPen pen;
	int nScreen;
	KSDoodling *widgetDoodling;

	KSDoodlingSetData()
		: ui()
		, pen()
		, nScreen(0)
		, widgetDoodling(nullptr)
	{

	}
};
KSDoodlingSet::KSDoodlingSet(QWidget *parent)
	: QWidget(parent)
	, m_pData(new KSDoodlingSetData)
{
	Ui::KSDoodlingSet &ui = m_pData->ui;
	auto &pen = m_pData->pen;
	auto &widgetDoodling = m_pData->widgetDoodling;

	ui.setupUi(this);
	widgetDoodling = new KSDoodling();

	auto &setting = Single<SystemConfig>::Instance();
	int nScreen = setting.getScreen();
	int nPenWidth = setting.getPenWidth();
	const QList<QRgb> clrs = setting.getPenColors();

	pen.setWidth(nPenWidth);
	m_pData->nScreen = nScreen;
	ui.spinBox->setValue(nPenWidth);
	ui.pushButtonHideDoodling->hide();
	
	QAbstractButton *pBtnPenColors[] = { ui.pushButtonPenColor0, ui.pushButtonPenColor1, ui.pushButtonPenColor2, ui.pushButtonPenColor3, ui.pushButtonPenColor4, ui.pushButtonPenColor5 };
	QButtonGroup *pBtnGroup = new QButtonGroup(this);
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

	connect(ui.pushButtonHideDoodling, &QAbstractButton::clicked, this, [this]() {onDoodlingVisilbe(false); });
	connect(ui.pushButtonShowDoodling, &QAbstractButton::clicked, this, [this]() {onDoodlingVisilbe(true); });
	connect(this, SIGNAL(signalPenChanged(const QPen &)), widgetDoodling, SLOT(setPen(const QPen &)));
	connect(this, SIGNAL(signalDoodlingVisilbe(bool)), widgetDoodling, SLOT(setDoodlingVisible(bool)));
	connect(this, SIGNAL(signalScreenChanged(int)), widgetDoodling, SLOT(setScreen(int)));
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(slotPenWidthChanged(int)));
	connect(ui.radioButtonScreen0, SIGNAL(toggled(bool)), this, SLOT(slotScreenToggled(bool)));
	connect(ui.radioButtonScreen1, SIGNAL(toggled(bool)), this, SLOT(slotScreenToggled(bool)));

	widgetDoodling->setPen(pen);
	widgetDoodling->setScreen(nScreen);
	widgetDoodling->hide();
}

KSDoodlingSet::~KSDoodlingSet()
{
	delete m_pData->widgetDoodling;
	m_pData->widgetDoodling = nullptr;
	delete m_pData;
	m_pData = nullptr;
}

void KSDoodlingSet::slotPenWidthChanged(int nWidth)
{
	auto &pen = m_pData->pen;
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
	auto &ui = m_pData->ui;
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
		QPen &pen = m_pData->pen;
		pen.setColor(QColor(rgb));
		emit signalPenChanged(pen);
	}
}
