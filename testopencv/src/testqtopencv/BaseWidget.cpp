#include "BaseWidget.h"
#include <assert.h>


static std::map<int, CREATE_FUN>& getCreateFuns()
{
	static std::map<int, CREATE_FUN> ins;
	return ins;
}
BaseWidget::BaseWidget(QWidget * parent)
	: QWidget(parent)
{
}

BaseWidget::~BaseWidget()
{
}

void BaseWidget::addCreateFun(int id, std::function<QWidget*()> fun)
{
	auto &ins = getCreateFuns();
	auto r = ins.insert(std::make_pair(id, fun));
	assert(r.second);
}

QWidget * BaseWidget::createWidget(int id)
{
	auto &ins = getCreateFuns();
	QWidget *w = nullptr;
	auto iter = ins.find(id);
	if (iter != ins.end())
	{
		w = (iter->second)();
	}
	assert(nullptr != w);
	return w;
}
