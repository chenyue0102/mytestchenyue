#include "TypeCover.h"
#include <assert.h>
#include <QRect>
#include <QSize>
#include <QPoint>
#include <QString>
#include <QPixmap>
#include <QColor>


namespace TypeCover
{
//
void test()
{

}
bool cover(const std::string &value, bool *)
{
	return value == "true";
}

int cover(const std::string &value, int *)
{
	return atoi(value.c_str());
}

unsigned int cover(const std::string &value, unsigned int *)
{
	char *pEnd = nullptr;
	return strtoul(value.c_str(), &pEnd, 10);
}

long long cover(const std::string &value, long long *)
{
	return atoll(value.c_str());
}

unsigned long long cover(const std::string &value, unsigned long long *)
{
	char *pEnd = nullptr;
	return strtoull(value.c_str(), &pEnd, 10);
}

double cover(const std::string &value, double *)
{
	return atof(value.c_str());
}

QString cover(const std::string &value, QString *)
{
	return QString::fromStdString(value);
}

QRect cover(const std::string &value, QRect *)
{
	QRect rc;
	QStringList ls = QString::fromStdString(value).split(QChar(L','));
	if (4 == ls.size())
	{
		int left = ls[0].toInt(), top = ls[1].toInt(), width = ls[2].toInt(), height = ls[3].toInt();
		rc = QRect(left, top, width, height);
	}
	else
	{
		assert(false);
	}
	return rc;
}

QSize cover(const std::string &value, QSize *)
{
	QSize sz;
	QStringList ls = QString::fromStdString(value).split(QChar(L','));
	if (2 == ls.size())
	{
		int width = ls[0].toInt(), height = ls[1].toInt();
		sz = QSize(width, height);
	}
	else
	{
		assert(false);
	}
	return sz;
}

QPoint cover(const std::string &value, QPoint *)
{
	QPoint pt;
	QStringList ls = QString::fromStdString(value).split(QChar(L','));
	if (2 == ls.size())
	{
		int x = ls[0].toInt(), y = ls[1].toInt();
		pt = QPoint(x, y);
	}
	else
	{
		assert(false);
	}
	return pt;
}

QPointF cover(const std::string &value, QPointF *)
{
	QPointF pt;
	QStringList ls = QString::fromStdString(value).split(QChar(L','));
	if (2 == ls.size())
	{
		double x = ls[0].toDouble(), y = ls[1].toDouble();
		pt = QPointF(x, y);
	}
	else
	{
		assert(false);
	}
	return pt;
}

QPixmap cover(const std::string &value, QPixmap *)
{
	return QPixmap(QString::fromStdString(value));
}

QColor cover(const std::string &value, QColor *)
{
	QColor clr;
	QString str = QString::fromStdString(value);
	str.trimmed();
	if (str.startsWith(QChar(L'#')))
	{
		clr.setNamedColor(str);
	}
	else if (str.startsWith("rgb("))
	{
		str.remove("rgb(");
		str.remove(")");
		QStringList ls = str.split(QChar(L','));
		if (3 == ls.size())
		{
			clr.setRed(ls[0].toInt());
			clr.setGreen(ls[1].toInt());
			clr.setBlue(ls[2].toInt());
		}
	}
	else if (str.startsWith("rgba("))
	{
		str.remove("rgba(");
		str.remove(")");
		QStringList ls = str.split(QChar(L','));
		if (4 == ls.size())
		{
			clr.setRed(ls[0].toInt());
			clr.setGreen(ls[1].toInt());
			clr.setBlue(ls[2].toInt());
			clr.setAlpha(ls[3].toInt());
		}
	}
	else
	{
		assert(false);
	}
	return clr;
}

template<typename T>
inline T tcover(const std::string &value)
{
	return cover(value, (T*)nullptr);
}

QVariant cover(QVariant::Type type, const std::string & value)
{
	QVariant v;
	switch (type)
	{
	case QVariant::Bool:
	{
		v = tcover<bool>(value);
		break;
	}
	case QVariant::Int:
	{
		v = tcover<int>(value);
		break;
	}
	case QVariant::UInt:
	{
		v = tcover<unsigned int>(value);
		break;
	}
	case QVariant::LongLong:
	{
		v = tcover<long long>(value);
		break;
	}
	case QVariant::ULongLong:
	{
		v = tcover<unsigned long long>(value);
		break;
	}
	case QVariant::Double:
	{
		v = tcover<double>(value);
		break;
	}
	case QVariant::String:
	{
		v = tcover<QString>(value);
		break;
	}
	case QVariant::Rect:
	{
		v = tcover<QRect>(value);
		break;
	}
	case QVariant::Size:
	{
		v = tcover<QSize>(value);
		break;
	}
	case QVariant::Point:
	{
		v = tcover<QPoint>(value);
		break;
	}
	case QVariant::PointF:
	{
		v = tcover<QPointF>(value);
		break;
	}
	case QVariant::Pixmap:
	{
		v = tcover<QPixmap>(value);
		break;
	}
	case QVariant::Color:
	{
		v = tcover<QColor>(value);
		break;
	}
	default:
	{
		v = QVariant(value.c_str());
		assert(false);
		break;
	}
	}
	return v;
}
};
