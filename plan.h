#ifndef PLAN_H
#define PLAN_H

#include <QObject>

class Plan : public QObject
{
    //Q_OBJECT
public:
    explicit Plan(/*QObject *parent = 0*/);

//signals:

//public slots:

public:
    QString FLT;
//    QString RFC;
    QString REG;
//    QString VIP;
//    QString LKE;
//    QString VI1;
//    QString ITY;
//    QString TAR;
//    QString TOF;
//    QString FSA;
//    QString OPE;
//    QString POP;
//    QString RCP;
//    QString NAT;
//    QString SDT;
//    QString FLX;
//    QString MFF;
//    QString SST;
//    QString HDL;
//    QString STD;
//    QString DES;
//    QString STA;
//    QString ORG;
//    QString ETA;
//    QString TDT;
//    QString ATA;
//    QString ABP;
//    QString CAR;
//    QString STP;
    QString Dep;
    QString VI1;
    QString Arr;
    QString STD;
    QString STA;
};

class FilesCmp
{
public:
    //explicit FilesCmp(){;}

    static void Cmp(QStringList lst1, bool bUtf8_1, QStringList lst2, bool bUtf8_2, QString strExpDir);
    static void File2VecPlan(QString strFile, bool bUtf8, QVector<Plan*> &vec);
    static void CmpPlan(QVector<Plan *> vec1, QVector<Plan *> vec2, QVector<Plan *> &vecSame, \
                        QVector<Plan *> &vecDif1, QVector<Plan *> &vecDif2, QVector<Plan *> &vecDif3,QVector<Plan *> &vecDif4,\
                        QVector<Plan *> &vecLeft, QVector<Plan *> &vecRight);
    //ret 1:same 0:unknow error -1:REG -2:RFC -3:STD -4:STA
    static int CmpOnePlan(Plan *plan1, Plan *plan2);
    static void exportCSV(QString strFile, QVector<Plan *> vec);
    static QTime getTmByStr(QString str);
    static QString tackoffQuotes(QString str);

};

#endif // PLAN_H
