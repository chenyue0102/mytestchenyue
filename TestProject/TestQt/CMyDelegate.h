#ifndef CMYDELEGATE_H
#define CMYDELEGATE_H

#include <QItemDelegate>

class CMyDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CMyDelegate(QObject *parent);
	~CMyDelegate();
public:
	virtual bool eventFilter(QObject *, QEvent *);
	virtual QSize sizeHint(const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void paint(QPainter *painter,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
		const QRect &rect, const QString &text) const;

	virtual void drawBackground(QPainter *painter,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
	virtual QVector<int> paintingRoles() const;
public slots:
	void MyCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
};

#endif // CMYDELEGATE_H
