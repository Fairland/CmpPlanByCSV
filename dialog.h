#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QStandardItemModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void updateDir1();
    void updateDir2();

public slots:
    void slt_selDir1();
    void slt_selDir2();
    void slt_selExpDir();
    void slt_cmp();

private:
    Ui::Dialog *ui;
    QString regEDir1;
    QString regEDir2;
    QStandardItemModel *model1;
    QStandardItemModel *model2;
};

#endif // DIALOG_H
