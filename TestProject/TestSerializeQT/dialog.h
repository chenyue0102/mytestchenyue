#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "EnumSerialize.h"

using namespace SerializeExport;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private slots:
	void OnTestAllType();
	void OnTKType();
	void OnLoss();
private:
	EnumSerializeFormat GetSerializeFormat();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
