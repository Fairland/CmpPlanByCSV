#include "plan.h"
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QTextCodec>

bool IsUTF8Text(const void* pBuffer, long size)
{
    bool IsUTF8 = true;
    unsigned char* start = (unsigned char*)pBuffer;
    unsigned char* end = (unsigned char*)pBuffer + size;
    while (start < end)
    {
        if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
        {
            start++;
        }
        else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
        {
            IsUTF8 = false;
            break;
        }
        else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
        {
            if (start >= end - 1)
            {
                break;
            }

            if ((start[1] & (0xC0)) != 0x80)
            {
                IsUTF8 = false;
                break;
            }

            start += 2;
        }
        else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符
        {
            if (start >= end - 2)
            {
                break;
            }

            if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
            {
                IsUTF8 = false;
                break;
            }

            start += 3;
        }
        else
        {
            IsUTF8 = false;
            break;
        }
    }

    return IsUTF8;
}

bool IsUTF8File(const char* pFileName)
{
    FILE *f = NULL;
    fopen_s(&f, pFileName, "rb");
    if (NULL == f)
    {
        return false;
    }

    fseek(f, 0, SEEK_END);
    long lSize = ftell(f);
    fseek(f, 0, SEEK_SET);  //或rewind(f);

    char *pBuff = new char[lSize + 1];
    memset(pBuff, 0, lSize + 1);
    fread(pBuff, lSize, 1, f);
    fclose(f);

    bool bIsUTF8 = IsUTF8Text(pBuff, lSize);
    delete []pBuff;
    pBuff = NULL;

    return bIsUTF8;
}

bool isGBKFile(QString pFileName)
{
//    FILE *f = NULL;
//    fopen_s(&f, pFileName, "rb");
//    if (NULL == f)
//    {
//        return false;
//    }

//    fseek(f, 0, SEEK_END);
//    long lSize = ftell(f);
//    fseek(f, 0, SEEK_SET);  //或rewind(f);

//    char *pBuff = new char[lSize + 1];
//    memset(pBuff, 0, lSize + 1);
//    fread(pBuff, lSize, 1, f);
//    fclose(f);
    QFile csvFile(pFileName);
    if (csvFile.open(QIODevice::ReadOnly) == false)
    {
        return false;
    }
    QDataStream stream(&csvFile);
    //QString strdata = stream.readAll();
    //char *p = NULL;
    QByteArray ba;
    //stream>>p;
    stream>>ba;
    csvFile.close();
    int lSize = ba.size();

    if (lSize%2 != 0)
    {
        return false;
    }
//    for (int i = 0; i < lSize; )
//    {
//        QChar c1 = strdata.at(i);
//        QChar c2 = strdata.at(i+1);
//        if (c1 >= QChar(0x81) && c1 <= QChar(0xFE) && c2 >= QChar(0x40) && c2<= QChar(0xFE))
//        {

//        }
//        else
//        {
//            return false;
//        }
//        i += 2;
//    }
    return true;
}

int IsTextUTF8(const char* str,unsigned long long int length)
{
    int i;
    qint64 nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
    unsigned char chr;
    bool bAllAscii=true; //如果全部都是ASCII, 说明不是UTF-8
    for(i=0;i<length;i++)
    {
        chr= *(str+i);
        if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
            bAllAscii= false;
        if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
        {
            if(chr>=0x80)
            {
                if(chr>=0xFC&&chr<=0xFD)
                    nBytes=6;
                else if(chr>=0xF8)
                    nBytes=5;
                else if(chr>=0xF0)
                    nBytes=4;
                else if(chr>=0xE0)
                    nBytes=3;
                else if(chr>=0xC0)
                    nBytes=2;
                else
                {
                    return false;
                }
                nBytes--;
            }
        }
        else //多字节符的非首字节,应为 10xxxxxx
        {
            if( (chr&0xC0) != 0x80 )
            {
                return false;
            }
            nBytes--;
        }
    }
    if( nBytes > 0 ) //违返规则
    {
        return false;
    }
    if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
    {
        return false;
    }
    return true;
}


Plan::Plan(/*QObject *parent) :
    QObject(parent*/)
{
     FLT = "";
//     RFC = "";
     REG = "";
//     VIP = "";
//     LKE = "";
//     VI1 = "";
//     ITY = "";
//     TAR = "";
//     TOF = "";
//     FSA = "";
//     OPE = "";
//     POP = "";
//     RCP = "";
//     NAT = "";
//     SDT = "";
//     FLX = "";
//     MFF = "";
//     SST = "";
//     HDL = "";
//     STD = "";
//     DES = "";
//     STA = "";
//     ORG = "";
//     ETA = "";
//     TDT = "";
//     ATA = "";
//     ABP = "";
//     CAR = "";
//     STP = "";
     Dep = "";
     VI1 = "";
     Arr = "";
     STD = "";
     STA = "";
}

QString FilesCmp::tackoffQuotes(QString str)
{
    //没有去掉字符串两边的双引号 为什么？
    if ((str.size() > 2) && \
        (str.left(1) == "\"") && \
        (str.right(1) == "\""))
    {
        str = str.mid(1, str.size() - 2);
    }
    return str;

}

void FilesCmp::File2VecPlan(QString strFile, bool bUtf8, QVector<Plan*> &vec)
{
    if (strFile.lastIndexOf(QRegExp("\\d{4}")) == -1)
    {
        return;
    }

    QFile csvFile(strFile);
    QStringList CSVList;
    CSVList.clear();

    if (csvFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream stream(&csvFile);
        if (bUtf8)
        {
            stream.setCodec("UTF-8");
        }

        while (!stream.atEnd())
        {
            QString strTmp = stream.readLine();
            if (strTmp.contains("\""))
            {
                strTmp.remove("\"");
            }

            CSVList.push_back(strTmp);
        }
        csvFile.close();
    }
    bool bFomat = false;
    if (CSVList.size())
    {
        QString strFir = CSVList.at(0);
        if (strFir.contains("FLT") && strFir.contains("REG") && strFir.contains("RFC"))
        {
            bFomat = true;
        }
    }
    else
    {
        return;
    }
    if (!bFomat)
    {
        Q_FOREACH(QString str, CSVList)
        {
            QStringList lst = str.split(",");

            if (lst.size() == 6)
            {
                Plan* pPlan = new Plan;
                pPlan->FLT = lst.at(1).trimmed();
                pPlan->FLT = tackoffQuotes(pPlan->FLT);
                pPlan->REG = lst.at(2).trimmed();
                //pPlan->REG.remove(QRegExp("\""));
                pPlan->REG = tackoffQuotes(pPlan->REG);
                QStringList lstDep = lst.at(3).split("/");
                if (lstDep.size() == 2)
                {
                    pPlan->Dep = lstDep.at(0).trimmed();
                    //pPlan->Dep.remove(QRegExp("\""));
                    pPlan->Dep = tackoffQuotes(pPlan->Dep);
                    pPlan->STD = lstDep.at(1).trimmed();
                    //pPlan->STD.remove(QRegExp("\""));
                    pPlan->STD = tackoffQuotes(pPlan->STD);
                }
                QStringList lstVI1 = lst.at(4).split("/");
                if (lstVI1.size() == 2)
                {
                    pPlan->VI1 = lstVI1.at(0).trimmed();
                    //pPlan->VI1.remove(QRegExp("\""));
                    pPlan->VI1 = tackoffQuotes(pPlan->VI1);
                }
                pPlan->Arr = lst.at(5).trimmed();
                //pPlan->Arr.remove(QRegExp("\""));
                pPlan->Arr = tackoffQuotes(pPlan->Arr);
                if (pPlan->FLT.isEmpty())
                {
                    delete pPlan;
                }
                else
                {
                    vec.push_back(pPlan);

                }
            }
        }
    }
    else
    {
        int iFLT = -1;
        int iREG = -1;
        int iRFC = -1;
        int iSTD = -1;
        int iSTA = -1;
        QString strFir = CSVList.at(0);
        QStringList lstFir = strFir.split(",");
        iFLT = lstFir.indexOf("FLT");
        iREG = lstFir.indexOf("REG");
        iRFC = lstFir.indexOf("RFC");
        iSTD = lstFir.indexOf("STD");
        iSTA = lstFir.indexOf("STA");
        for (int i = 1;i < CSVList.size(); i++)
        {
            Plan* pPlan = new Plan;
            QString strTmp = CSVList.at(i);
            QStringList lst = strTmp.split(",");
            if (iFLT != -1 && iFLT < lst.size())
            {
                pPlan->FLT = lst.at(iFLT);
            }
            if (iREG != -1 && iREG < lst.size())
            {
                pPlan->REG = lst.at(iREG);
            }
            if (iRFC != -1 && iRFC < lst.size())
            {
                QStringList lstPort = lst.at(iRFC).split("-", QString::SkipEmptyParts);
                if (lstPort.size() >= 2)
                {
                    pPlan->Dep = lstPort.first();
                    pPlan->Arr = lstPort.last();
                    if (lstPort.size() > 2)
                    {
                        pPlan->VI1 = lstPort.at(1);
                    }
                }
            }
            if (iSTD != -1 && iSTD < lst.size())
            {
                pPlan->STD = lst.at(iSTD);
            }
            if (iSTA != -1 && iSTA < lst.size())
            {
                pPlan->STA = lst.at(iSTA);
            }
            if (pPlan->FLT.isEmpty())
            {
                delete pPlan;
            }
            else
            {
                vec.push_back(pPlan);
            }
        }
    }
}

void FilesCmp::Cmp(QStringList lst1, bool bUtf8_1, QStringList lst2, bool bUtf8_2, QString strExpDir)
{
    QMap<QString, QVector<Plan*> > map1;
    Q_FOREACH(QString str, lst1)
    {
        QVector<Plan*> vec;
        File2VecPlan(str, bUtf8_1, vec);
        if (vec.size())
        {
            int ipos = str.lastIndexOf(QRegExp("\\d{4}"));
            if (ipos != -1)
            {
                QString strMonthDay = str.mid(ipos, 4);
                QMap<QString, QVector<Plan*> >::iterator iter = map1.find(strMonthDay);
                if (iter != map1.end())
                {
                    iter.value() += vec;
                }
                else
                {
                    map1[strMonthDay] = vec;
                }
            }

        }
    }

    QMap<QString, QVector<Plan*> > map2;
    Q_FOREACH(QString str, lst2)
    {
        QVector<Plan*> vec;
        File2VecPlan(str, bUtf8_2, vec);
        if (vec.size())
        {
            int ipos = str.indexOf(QRegExp("\\d{4}"));
            if (ipos != -1)
            {
                QString strMonthDay = str.mid(ipos, 4);
                QMap<QString, QVector<Plan*> >::iterator iter = map2.find(strMonthDay);
                if (iter != map2.end())
                {
                    iter.value() += vec;
                }
                else
                {
                    map2[strMonthDay] = vec;
                }
            }
        }
    }

    QMap<QString, QVector<Plan*> >::iterator iter1 = map1.begin();
    while (iter1 != map1.end())
    {
        QString strDir = QString("%1/%2").arg(strExpDir).arg(iter1.key());
        QDir dir(strDir);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        else
        {
            dir.setFilter(QDir::Files | QDir::Readable | QDir::Hidden | QDir::NoSymLinks);
            QFileInfoList list = dir.entryInfoList();
            for (int i = 0;i <list.size(); i++)
            {
                QFileInfo info = list.at(i);

                if (info.exists())
                {
                    QString strNm = info.absoluteFilePath();
                    QFile::remove(strNm);
                }
            }
        }

        QMap<QString, QVector<Plan*> >::iterator iter2 = map2.find(iter1.key());
        if (iter2 != map2.end())
        {
            QVector<Plan *> vecSame;
            QVector<Plan *> vecDif1;
            QVector<Plan *> vecDif2;
            QVector<Plan *> vecDif3;
            QVector<Plan *> vecDif4;
            QVector<Plan *> vecLeft;
            QVector<Plan *> vecRight;
            CmpPlan(iter1.value(), iter2.value(), vecSame, vecDif1, vecDif2, vecDif3, vecDif4, vecLeft, vecRight);

            if (vecSame.size())
            {
                QString strFileSame = strDir + QString("/%1same.csv").arg(iter1.key());
                exportCSV(strFileSame, vecSame);
            }
            if (vecDif1.size())
            {
                QString strFileDif = strDir + QString("/%1dif_reg.csv").arg(iter1.key());
                exportCSV(strFileDif, vecDif1);
            }
            if (vecDif2.size())
            {
                QString strFileDif = strDir + QString("/%1dif_rfc.csv").arg(iter1.key());
                exportCSV(strFileDif, vecDif2);
            }
            if (vecDif3.size())
            {
                QString strFileDif = strDir + QString("/%1dif_std.csv").arg(iter1.key());
                exportCSV(strFileDif, vecDif3);
            }
            if (vecDif4.size())
            {
                QString strFileDif = strDir + QString("/%1dif_sta.csv").arg(iter1.key());
                exportCSV(strFileDif, vecDif4);
            }
            if (vecLeft.size())
            {
                QString strFileLeft = strDir + QString("/%1onlyleft.csv").arg(iter1.key());
                exportCSV(strFileLeft, vecLeft);
            }
            if (vecRight.size())
            {
                QString strFileRight = strDir + QString("/%1onlyright.csv").arg(iter1.key());
                exportCSV(strFileRight, vecRight);
            }
        }
        else
        {
            QString strFileLeft = strDir + QString("/%1onlyleft.csv").arg(iter1.key());
            exportCSV(strFileLeft, iter1.value());
        }
        iter1++;
    }

    QMap<QString, QVector<Plan*> >::iterator iter2 = map2.begin();
    while (iter2 != map2.end())
    {


        QMap<QString, QVector<Plan*> >::iterator iter1 = map1.find(iter2.key());
        if (iter1 == map1.end())
        {
            QString strDir = QString("%1/%2").arg(strExpDir).arg(iter2.key());
            QDir dir(strDir);
            if (!dir.exists())
            {
                dir.mkpath(".");
            }
            else
            {
                dir.setFilter(QDir::Files | QDir::Readable | QDir::Hidden | QDir::NoSymLinks);
                QFileInfoList list = dir.entryInfoList();
                for (int i = 0;i <list.size(); i++)
                {
                    QFileInfo info = list.at(i);

                    if (info.exists())
                    {
                        QString strNm = info.absoluteFilePath();
                        QFile::remove(strNm);
                    }
                }
            }
            QString strFileRight = strDir + QString("/%1onlyright.csv").arg(iter2.key());
            exportCSV(strFileRight, iter2.value());
        }
        iter2++;
    }

    iter1 = map1.begin();
    while (iter1 != map1.end())
    {
        qDeleteAll(iter1.value());
        iter1.value().clear();
        iter1++;
    }
    map1.clear();

    iter2 = map2.begin();
    while (iter2 != map2.end())
    {
        qDeleteAll(iter2.value());
        iter2.value().clear();
        iter2++;
    }
    map2.clear();
}

void FilesCmp::CmpPlan(QVector<Plan *> vec1, QVector<Plan *> vec2, QVector<Plan *> &vecSame, \
                       QVector<Plan *> &vecDif1, QVector<Plan *> &vecDif2, QVector<Plan *> &vecDif3, QVector<Plan *> &vecDif4, \
                       QVector<Plan *> &vecLeft, QVector<Plan *> &vecRight)
{
    //QVector<Plan *> vecSame;
    //QVector<Plan *> vecDif;
    //QVector<Plan *> vecLeft;
    //QVector<Plan *> vecRight;

    QVector<Plan *>::iterator iter1 = vec1.begin();
    while(iter1 != vec1.end())
    {
        Plan * pPlan1 = *iter1;
        if (pPlan1)
        {
            if (pPlan1->FLT.isEmpty())
            {
                vecLeft.push_back(pPlan1);
            }
            else
            {
                bool bFind = false;
                QVector<Plan *>::iterator iter2 = vec2.begin();
                while (iter2 != vec2.end())
                {
                    Plan * pPlan2 = *iter2;
                    if (pPlan2/* && !pPlan2->FLT.isEmpty() && pPlan2->FLT == pPlan1->FLT*/)
                    {
                        if (!pPlan2->FLT.isEmpty())
                        {
                            if (pPlan2->FLT == pPlan1->FLT)
                            {
                                bFind = true;
                                int iRet = CmpOnePlan(pPlan1, pPlan2);
                                if (1 == iRet)
                                {

                                    if (pPlan1->VI1.isEmpty() && !pPlan2->VI1.isEmpty())
                                    {
                                        pPlan1->Dep = pPlan2->Dep;
                                        pPlan1->VI1 = pPlan2->VI1;
                                        pPlan1->Arr = pPlan2->Arr;
                                    }
                                    if (pPlan1->STD.isEmpty() && !pPlan2->STD.isEmpty())
                                    {
                                        pPlan1->STD = pPlan2->STD;
                                    }
                                    if (pPlan1->STA.isEmpty() && !pPlan2->STA.isEmpty())
                                    {
                                        pPlan1->STA = pPlan2->STA;
                                    }
                                    vecSame.push_back(pPlan1);
                                }
                                else if (-1 == iRet)
                                {
                                    vecDif1.push_back(pPlan1);
                                    vecDif1.push_back(pPlan2);
                                }
                                else if (-2 == iRet)
                                {
                                    vecDif2.push_back(pPlan1);
                                    vecDif2.push_back(pPlan2);
                                }
                                else if (-3 == iRet)
                                {
                                    vecDif3.push_back(pPlan1);
                                    vecDif3.push_back(pPlan2);
                                }
                                else if (-4 == iRet)
                                {
                                    vecDif4.push_back(pPlan1);
                                    vecDif4.push_back(pPlan2);
                                }
                                vec2.erase(iter2);
                                break;
                            }
                        }
                    }
                    iter2++;
                }
                if (!bFind)
                {
                    vecLeft.push_back(pPlan1);
                }
            }
        }
        iter1++;
    }
    vecRight = vec2;
}

QTime FilesCmp::getTmByStr(QString str)
{
    QTime tm;
    if (str.size() == 3)
    {
        QRegExp reg("\\d{3}");
        if (reg.exactMatch(str))
        {
            tm = QTime::fromString(str, "hmm");
        }
    }
    else if (str.size() == 4)
    {
        QRegExp reg1("\\d{4}");
        QRegExp reg2("\\d\:\\d{2}");
        if (reg1.exactMatch(str))
        {
            tm = QTime::fromString(str, "hhmm");
        }
        else if (reg2.exactMatch(str))
        {
            tm = QTime::fromString(str, "h:mm");
        }
    }
    else if (str.size() == 5)
    {
        QRegExp reg("\\d{2}\:\\d{2}");
        if (reg.exactMatch(str))
        {
            tm = QTime::fromString(str, "hh:mm");
        }
    }
    else if (str.size() > 5)
    {
        int iPos = str.indexOf(QRegExp("\\d{2}\:\\d{2}"));
        if (iPos != -1)
        {
            QString strTmp = str.mid(iPos, 5);
            tm = QTime::fromString(strTmp, "hh:mm");
        }
        else
        {
            iPos = str.indexOf(QRegExp("\\d{1}\:\\d{2}"));
            if (iPos != -1)
            {
                QString strTmp = str.mid(iPos, 4);
                tm = QTime::fromString(strTmp, "h:mm");
            }
        }
    }
    return tm;
}

int FilesCmp::CmpOnePlan(Plan *plan1, Plan *plan2)
{
    if (!plan1 || !plan2)
    {
        return 0;
    }
    if (plan1->FLT != plan2->FLT)
    {
        return 0;
    }
    if (plan1->REG != plan2->REG)
    {
        return -1;
    }
    if (plan1->Dep != plan2->Dep)
    {
        if (plan1->VI1.isEmpty() && plan2->VI1.isEmpty())
        {
            return -2;
        }
        else if (plan1->VI1.isEmpty() && !plan2->VI1.isEmpty())
        {
            if (plan1->Dep != plan2->VI1)
            {
                return -2;
            }
        }
        else if (!plan1->VI1.isEmpty() && plan2->VI1.isEmpty())
        {
            if (plan2->Dep != plan1->VI1)
            {
                return -2;
            }
        }
    }
    if (!plan1->VI1.isEmpty() && !plan2->VI1.isEmpty())
    {
        if (plan1->VI1 != plan2->VI1)
        {
            return -2;
        }

    }
    if (plan1->Arr != plan2->Arr)
    {
        if (plan1->VI1.isEmpty() && plan2->VI1.isEmpty())
        {
            return -2;
        }
        else if (plan1->VI1.isEmpty() && !plan2->VI1.isEmpty())
        {
            if (plan1->Arr != plan2->VI1)
            {
                return -2;
            }
        }
        else if (!plan1->VI1.isEmpty() && plan2->VI1.isEmpty())
        {
            if (plan2->Arr != plan1->VI1)
            {
                return -2;
            }
        }
    }
    if (!plan1->STD.isEmpty() && !plan2->STD.isEmpty())
    {
        QTime tm1 = getTmByStr(plan1->STD);
        QTime tm2 = getTmByStr(plan2->STD);
        if ((!tm1.isValid()) || \
            (!tm2.isValid()) || \
            (tm1.isValid() && tm2.isValid() && tm1 != tm2))
        {
            return -3;
        }
    }
    if (!plan1->STA.isEmpty() && !plan2->STA.isEmpty())
    {
        QTime tm1 = getTmByStr(plan1->STA);
        QTime tm2 = getTmByStr(plan2->STA);
        if ((!tm1.isValid()) || \
            (!tm2.isValid()) || \
            (tm1.isValid() && tm2.isValid() && tm1 != tm2))
        {
            return -4;
        }
    }
    return 1;
}

void FilesCmp::exportCSV(QString strFile, QVector<Plan *> vec)
{
    QFile file(strFile);
    bool openOk = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!openOk)
    {
        return ;
    }
    QTextStream outStream(&file);
    outStream<<QString("FLT,REG,RFC,STD,STA\n");
    QVector<Plan *>::iterator iter = vec.begin();
    while(iter != vec.end())
    {
        Plan *pPlan = *iter;
        if (pPlan)
        {
            outStream<<QString("%1").arg(pPlan->FLT);
            outStream<<QString(",%1").arg(pPlan->REG);
            if (!pPlan->Dep.isEmpty() && !pPlan->Arr.isEmpty())
            {
                QString strRFC = pPlan->VI1.isEmpty()?QString(",%1-%2").arg(pPlan->Dep).arg(pPlan->Arr):\
                                                      QString(",%1-%2-%3").arg(pPlan->Dep).arg(pPlan->VI1).arg(pPlan->Arr);
                outStream<<strRFC;
            }
            else
            {
                outStream<<",";
            }
            outStream<<QString(",%1").arg(pPlan->STD);
            outStream<<QString(",%1").arg(pPlan->STA);
            outStream<<"\n";
        }
        iter++;
    }
    file.close();
}



