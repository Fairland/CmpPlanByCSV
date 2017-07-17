/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QPushButton *pBtnDir1;
    QLineEdit *lEdit1;
    QCheckBox *cbox_utf8;
    QTableView *tableView1;
    QGridLayout *gridLayout_2;
    QPushButton *pBtnDir2;
    QLineEdit *lEdit2;
    QCheckBox *cbox_utf8_2;
    QTableView *tableView2;
    QHBoxLayout *horizontalLayout;
    QLabel *labInfo;
    QSpacerItem *horizontalSpacer;
    QPushButton *pBtnCmp;
    QPushButton *pBtnClose;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pBtnExpDir;
    QLineEdit *lEditExp;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(703, 337);
        gridLayout_3 = new QGridLayout(Dialog);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pBtnDir1 = new QPushButton(Dialog);
        pBtnDir1->setObjectName(QStringLiteral("pBtnDir1"));

        gridLayout->addWidget(pBtnDir1, 0, 0, 1, 1);

        lEdit1 = new QLineEdit(Dialog);
        lEdit1->setObjectName(QStringLiteral("lEdit1"));
        lEdit1->setReadOnly(true);

        gridLayout->addWidget(lEdit1, 0, 1, 1, 1);

        cbox_utf8 = new QCheckBox(Dialog);
        cbox_utf8->setObjectName(QStringLiteral("cbox_utf8"));

        gridLayout->addWidget(cbox_utf8, 0, 2, 1, 1);

        tableView1 = new QTableView(Dialog);
        tableView1->setObjectName(QStringLiteral("tableView1"));

        gridLayout->addWidget(tableView1, 1, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pBtnDir2 = new QPushButton(Dialog);
        pBtnDir2->setObjectName(QStringLiteral("pBtnDir2"));

        gridLayout_2->addWidget(pBtnDir2, 0, 0, 1, 1);

        lEdit2 = new QLineEdit(Dialog);
        lEdit2->setObjectName(QStringLiteral("lEdit2"));
        lEdit2->setReadOnly(true);

        gridLayout_2->addWidget(lEdit2, 0, 1, 1, 1);

        cbox_utf8_2 = new QCheckBox(Dialog);
        cbox_utf8_2->setObjectName(QStringLiteral("cbox_utf8_2"));

        gridLayout_2->addWidget(cbox_utf8_2, 0, 2, 1, 1);

        tableView2 = new QTableView(Dialog);
        tableView2->setObjectName(QStringLiteral("tableView2"));

        gridLayout_2->addWidget(tableView2, 1, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout_2, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labInfo = new QLabel(Dialog);
        labInfo->setObjectName(QStringLiteral("labInfo"));
        labInfo->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout->addWidget(labInfo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pBtnCmp = new QPushButton(Dialog);
        pBtnCmp->setObjectName(QStringLiteral("pBtnCmp"));

        horizontalLayout->addWidget(pBtnCmp);

        pBtnClose = new QPushButton(Dialog);
        pBtnClose->setObjectName(QStringLiteral("pBtnClose"));

        horizontalLayout->addWidget(pBtnClose);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pBtnExpDir = new QPushButton(Dialog);
        pBtnExpDir->setObjectName(QStringLiteral("pBtnExpDir"));

        horizontalLayout_2->addWidget(pBtnExpDir);

        lEditExp = new QLineEdit(Dialog);
        lEditExp->setObjectName(QStringLiteral("lEditExp"));

        horizontalLayout_2->addWidget(lEditExp);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        pBtnDir1->setText(QApplication::translate("Dialog", "\346\257\224\350\276\203\347\233\256\345\275\2251", 0));
        cbox_utf8->setText(QApplication::translate("Dialog", "UTF-8", 0));
        pBtnDir2->setText(QApplication::translate("Dialog", "\346\257\224\350\276\203\347\233\256\345\275\2252", 0));
        cbox_utf8_2->setText(QApplication::translate("Dialog", "UTF-8", 0));
        labInfo->setText(QString());
        pBtnCmp->setText(QApplication::translate("Dialog", "\345\257\271\346\257\224", 0));
        pBtnClose->setText(QApplication::translate("Dialog", "\345\205\263\351\227\255", 0));
        pBtnExpDir->setText(QApplication::translate("Dialog", "\350\276\223\345\207\272\347\233\256\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
