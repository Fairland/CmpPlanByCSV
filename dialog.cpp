#include "dialog.h"
#include "ui_dialog.h"

#include "plan.h"
#include <QDebug>

//#include <QAxObject>
//#include <QMessageBox>
#include <QSettings>

#include <QFileDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    regEDir1 = QString("*.csv");
    regEDir2 = QString("*.csv");

    model1 = new QStandardItemModel;
    model1->setHorizontalHeaderLabels(QStringList()<<QString("文件名") \
                                                     <<QString("启用"));

    ui->tableView1->setModel(model1);

    model2 = new QStandardItemModel;
    model2->setHorizontalHeaderLabels(QStringList()<<QString("文件名") \
                                                    <<QString("启用"));

    ui->tableView2->setModel(model2);

    QSettings ini("./set.ini",QSettings::IniFormat);
    ini.setIniCodec("UTF-8");
    QString strDir1 = ini.value("ALL/CompareDirectory1", "").toString();
    QDir dir1(strDir1);
    if (dir1.exists())
    {
        ui->lEdit1->setText(dir1.absolutePath());
    }
    updateDir1();

    QString strDir2 = ini.value("ALL/CompareDirectory2", "").toString();
    QDir dir2(strDir2);
    if (dir2.exists())
    {
        ui->lEdit2->setText(dir2.absolutePath());
    }
    updateDir2();

    QString strExpDir = ini.value("ALL/ExportDirectory", ".").toString();
    QDir dirExp(strExpDir);
    if (!dirExp.exists())
    {
        dirExp.mkpath(".");
    }
    ui->lEditExp->setText(dirExp.absolutePath());


    connect(ui->pBtnDir1, SIGNAL(clicked()), this, SLOT(slt_selDir1()));
    connect(ui->pBtnDir2, SIGNAL(clicked()), this, SLOT(slt_selDir2()));
    connect(ui->pBtnExpDir, SIGNAL(clicked()), this, SLOT(slt_selExpDir()));
    connect(ui->pBtnCmp, SIGNAL(clicked()), this, SLOT(slt_cmp()));
    connect(ui->pBtnClose, SIGNAL(clicked()), this, SLOT(close()));
}

void Dialog::updateDir1()
{
    if (!model1)
    {
        return;
    }
    model1->removeRows(0, model1->rowCount());

    QDir dir;
    dir.setPath(ui->lEdit1->text());
    dir.setFilter(QDir::Files | QDir::Readable | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(QStringList()<<regEDir1);
    dir.setSorting(QDir::Name);
    dir.refresh();
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0;i <list.size(); i++)
    {
        QFileInfo info = list.at(i);
        if (info.exists())
        {
            QString strNm = info.fileName();
            int iRow = model1->rowCount();
            QStandardItem *pItem = new QStandardItem(strNm);
            model1->setItem(iRow,0,pItem);
            QStandardItem *pItem1 = new QStandardItem();
            pItem1->setCheckable(true);
            pItem1->setCheckState(Qt::Checked);
            model1->setItem(iRow,1,pItem1);
        }
    }
}

void Dialog::slt_selDir1()
{
    QString strbase = ".";
    if (!ui->lEdit1->text().isEmpty())
    {
        strbase = ui->lEdit1->text();
    }
    ui->lEdit1->setText(QFileDialog::getExistingDirectory(NULL, QString("请选择路径"),strbase));
    updateDir1();
}

void Dialog::updateDir2()
{
    if (!model2)
    {
        return;
    }
    model2->removeRows(0, model2->rowCount());

    QDir dir;
    dir.setPath(ui->lEdit2->text());
    dir.setFilter(QDir::Files | QDir::Readable | QDir::Hidden | QDir::NoSymLinks);
    dir.setNameFilters(QStringList()<<regEDir1);
    dir.setSorting(QDir::Name);
    dir.refresh();
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0;i <list.size(); i++)
    {
        QFileInfo info = list.at(i);
        if (info.exists())
        {
            QString strNm = info.fileName();
            int iRow = model2->rowCount();
            QStandardItem *pItem = new QStandardItem(strNm);
            model2->setItem(iRow,0,pItem);
            QStandardItem *pItem1 = new QStandardItem();
            pItem1->setCheckable(true);
            pItem1->setCheckState(Qt::Checked);
            model2->setItem(iRow,1,pItem1);
        }
    }
}

void Dialog::slt_selDir2()
{
    QString strbase = ".";
    if (!ui->lEdit2->text().isEmpty())
    {
        strbase = ui->lEdit2->text();
    }

    ui->lEdit2->setText(QFileDialog::getExistingDirectory(NULL, QString("请选择路径"),strbase));
    updateDir2();
}

void Dialog::slt_selExpDir()
{
    QString strbase = ".";
    if (!ui->lEditExp->text().isEmpty())
    {
        strbase = ui->lEditExp->text();
    }

    ui->lEditExp->setText(QFileDialog::getExistingDirectory(NULL, QString("请选择路径"),strbase));
}

void Dialog::slt_cmp()
{
    ui->labInfo->setText("waiting...");
    if (!model1 || !model2)
    {
        ui->labInfo->setText("model is null");
        return;
    }
    if (ui->lEdit1->text() == ui->lEdit2->text())
    {
        ui->labInfo->setText("dir1 and dir2 is same");
        return;
    }
    if (ui->lEditExp->text().isEmpty())
    {
        ui->labInfo->setText("dirExp is empty");
        return;
    }
    QStringList strDirFile1;
    QStringList strDirFile2;
    for (int i = 0; i < model1->rowCount(); i++)
    {
        QStandardItem *pItem0 = model1->item(i, 0);
        QStandardItem *pItem = model1->item(i, 1);
        if (pItem0 && pItem && pItem->isCheckable() && pItem->checkState() == Qt::Checked)
        {
            strDirFile1<<ui->lEdit1->text() + "/" + pItem0->text();
        }
    }
    if (strDirFile1.size() <= 0)
    {
        ui->labInfo->setText("dir1 has no files");
        return;
    }

    for (int i = 0; i < model2->rowCount(); i++)
    {
        QStandardItem *pItem0 = model2->item(i, 0);
        QStandardItem *pItem = model2->item(i, 1);
        if (pItem0 && pItem && pItem->isCheckable() && pItem->checkState() == Qt::Checked)
        {
            strDirFile2<<ui->lEdit2->text() + "/" + pItem0->text();
        }
    }
    if (strDirFile2.size() <= 0)
    {
        ui->labInfo->setText("dir2 has no files");
        return;
    }

    FilesCmp::Cmp(strDirFile1, ui->cbox_utf8->isChecked(), strDirFile2, ui->cbox_utf8_2->isChecked(), ui->lEditExp->text());
    ui->labInfo->setText("success");
}

Dialog::~Dialog()
{
    delete ui;
}
