#include "testLinearGradient.h"
#include <assert.h>
#include <regex>
#include <memory>
#include <QPainter>
#include <QLinearGradient>

enum EGradient
{
	EGradientNone,
	EGradientLinear,
};
void parseGradientBackgroundColor(/*const QString &text, std::shared_ptr<QGradient> &pGradient*/)
{
	//pGradient.reset();

	do
	{
		//linear-gradient(to left top, rgba(255,0,0,255), rgba(0,255,0,100))
		std::string strText = " linear-gradient( to top left  , rgba(255,0,0,255), rgba(0,255,0,100)  )     ";
		//strText.erase(std::remove(strText.begin(), strText.end(), ' '), strText.end());

		std::string strRegex = R"(^\s*(linear-gradient)\s*\((.+)\)\s*$)";
		std::smatch matched;
		std::regex expr(strRegex);

		std::string gradient;
		if (!std::regex_search(strText, matched, expr))
		{
			assert(false);
			break;
		}
		if (matched.size() != 3)
		{
			assert(false);
			break;
		}
		//0是原始字符串，1是匹配到的第一个()内容
		gradient = matched.str(1);
		if (gradient != "linear-gradient")
		{
			assert(false);
			break;
		}

		std::string strDirectionAndColor(matched.str(2));
		std::smatch matchedDirection;
		std::regex exprDirection(R"(^\s*to\s*(left|right|top|bottom)\s*((left|right)|(top|bottom))\s*,(.+)$)");
		if (!std::regex_search(strDirectionAndColor, matchedDirection, exprDirection))
		{
			assert(false);
			break;
		}
		assert(6 == matchedDirection.size());
		for (int i = 1; i < matchedDirection.size(); i++)
		{
			std::ssub_match  s = matchedDirection[i];
			std::string pi = s.str();
		}
		
	} while (false);
	
}


testLinearGradient::testLinearGradient(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	parseGradientBackgroundColor();
}

void testLinearGradient::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	QRect rc = rect();
	QLinearGradient linearGradient(0.0, 0.0, 1.0, 1.0);
	linearGradient.setColorAt(0.0, Qt::red);
	linearGradient.setColorAt(1.0, Qt::yellow);
	linearGradient.setCoordinateMode(QGradient::StretchToDeviceMode);

	painter.setBrush(QBrush(linearGradient));
	painter.drawRect(rc);
}
