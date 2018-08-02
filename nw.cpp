#include "nw.h"
#include"dictionary.h"
#include"qdatetime.h"
#include"qfile.h"
#include"qtextstream.h"
#include"qjsondocument.h"
#include "qdebug.h"
#include "qcoreapplication.h"
#include"qdir.h"

//获取业务号
int GetServiceTypeID()
{
    return 01;
}
//获取业务名称
QString GetServiceTypeName()
{
	QString name = QString::fromLocal8Bit("农委气象业务");
	return name;
}

//获取版本号
QString GetVersionNo()
{
	QString Version = QString::fromLocal8Bit("1.0");
	return Version;
}

//获取端口号
int GetPort()
{
	return 9002;
}
//解析数据
LRESULT Char2Json(QString &buff, QJsonObject &json)
{
	int Count = 0;//数据个数
	int Current_P = buff.length();//当前数据指

								  //遍历查找数据
	for (int i = 0; i < buff.length() - 2; i++)
	{
		if (buff[i].toUpper() == 'B' && buff[i + 1].toUpper() == 'G'&&buff[i + 2] == ',')
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 2; j < buff.length() - 2; j++)
			{
				if (buff[j] == ','&&buff[j + 1].toUpper() == 'E'&&buff[j + 2].toUpper() == 'D')
				{
					Current_P = j + 3;//指针移动到帧尾下一个字符
					Count += 2;//数据个数
					Dictionary dic;
					QString strBuff = buff.mid(i, j - i + 3);
					//根据“，”将字符串拆分成各个要素
					QStringList strlist = strBuff.split(",");
				
					 //第一根数据
					QJsonObject json_one;
					//第二根数据
					QJsonObject json_another;
					json_one.insert("DataType", 1);//数据类型 观测数据
					json_another.insert("DataType", 1);//数据类型 观测数据
					//区站号
					json_one.insert("StationID", strlist.at(1));
					json_another.insert("StationID", strlist.at(1));
					//02农委业务
					json_one.insert("ServiceTypeID", NW);
					json_another.insert("ServiceTypeID", NW);
					//设备号
					json_one.insert("DeviceID", "1");
					json_another.insert("DeviceID", "2");
					//时间
					QString time = Convert2Time(strlist.at(3));
					json_one.insert("ObserveTime", time);
					json_another.insert("ObserveTime", time);
					//时间格式2
					QString timeform = Convert2TimeForm(strlist.at(3));
					json_one.insert("UploadTime", timeform);
					json_another.insert("UploadTime", timeform);
					bool ok;
					//观察要素数量
					int CountOfFeature = ((QString)strlist.at(4)).toInt(&ok, 10);
					json_one.insert("CountOfFeature", CountOfFeature);
					json_another.insert("CountOfFeature", CountOfFeature);
					//设备状态要素数量
					int CountOfFacilitiesStatus = ((QString)strlist.at(5)).toInt(&ok, 10);
					json_one.insert("CountOfFacilitiesStatus", CountOfFacilitiesStatus);
					json_another.insert("CountOfFacilitiesStatus", CountOfFacilitiesStatus);
					//观察要素
					QString strFeatureName;
					for (int i = 6; i < CountOfFeature * 2 + 6; i += 2)
					{
						QString SrcKey = QString(strlist.at(i)).toLower();
						QString key = dic.Find(SrcKey);
						if (key != NULL)
						{
							//第二根数据
							if (SrcKey == "abc5" || SrcKey == "abc10" || SrcKey == "abc15" || SrcKey == "abc20" || SrcKey == "arb50" || SrcKey == "arg50" || SrcKey == "arb60" || SrcKey == "arg60" || SrcKey == "arb80" || SrcKey == "arg80" || SrcKey == "arb100" || SrcKey == "arg100")
							{
								json_another.insert(key, strlist.at(i + 1));
							}
							//第一根数据
							else
							{
								json_one.insert(key, strlist.at(i + 1));
							}
							//质量控制码
							if (i == 6)
							{
								strFeatureName = key;
							}
							else
							{
								strFeatureName += ",";
								strFeatureName += key;
							}
						}
					}
					json_one.insert("StatusBitName", strFeatureName);
					json_another.insert("StatusBitName", strFeatureName);
					//状态位
					json_one.insert("StatusBit", strlist.at(CountOfFeature * 2 + 6));
					json_another.insert("StatusBit", strlist.at(CountOfFeature * 2 + 6));

					//设备状态
					for (int i = CountOfFeature * 2 + 7; i < CountOfFeature * 2 + CountOfFacilitiesStatus * 2 + 7; i += 2)
					{
						QString key = dic.Find(QString(strlist.at(i)).toLower());
						if (key != NULL)
						{
							json_one.insert(key, strlist.at(i + 1));
							json_another.insert(key, strlist.at(i + 1));
						}

					}

					json.insert(QString::number(Count-1), json_one);
					json.insert(QString::number(Count), json_another);
					QDateTime current_date_time = QDateTime::currentDateTime();
					QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
					QString current_day = current_date_time.toString("yyyy-MM-dd");
					QString fileName = QCoreApplication::applicationDirPath() + "\\NW\\" + strlist.at(1) + "\\" + current_day;
					QDir dir(fileName);
					if (!dir.exists())
						dir.mkpath(fileName);//创建多级目录
					fileName += "\\data.txt";
					QFile file(fileName);

					if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
					{
					}
					QTextStream in(&file);
					in << current_date << "\r\n" << strBuff<<"\r\n";
					file.close();

					i = j + 2;//当前循环
					break;
				}
			}
		}
		else if (buff[i] == '<')
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 1; j < buff.length(); j++)
			{
				if (buff[j] == '>')
				{
					Current_P = j + 1;//指针移动到帧尾
					Count += 1;//数据个数
					QString subStr = buff.mid(i + 1, j - i - 1);
					QStringList strlist = subStr.split(" ");
					QJsonObject SubJson;
					SubJson.insert("DataType", 2);//数据类型 2操作数据
					i = j;
					switch (strlist.count())
					{
						//单个返回值
					case 1:
					{
						SubJson.insert("ValueCount", 1);
						SubJson.insert("RecvValue1", strlist.at(0));
						json.insert(QString::number(Count), SubJson);
						break;
					}
					//双返回值
					case 2:
					{
						SubJson.insert("ValueCount", 2);
						SubJson.insert("RecvValue1", strlist.at(0));
						SubJson.insert("RecvValue2", strlist.at(1));
						json.insert(QString::number(Count), SubJson);
						break;
					}
					//无效数据
					default:
						break;
					}
					break;
				}
			}
		}
		else if (buff[i].toUpper()=="S"&&buff[i+1].toUpper()=="I"&&buff[i+2].toUpper()=="M")
		{
			Current_P = i;//指针指向帧头
			for (int j = i + 2; j < buff.length(); j++)
			{
				if (buff[j].toUpper()== "X")
				{
					Current_P = j + 1;//指针移动到帧尾下一个字符
					Count++;
					QString subStr = buff.mid(i + 3, j - i - 3);
					QJsonObject SubJson;
					SubJson.insert("DataType", 3);//数据类型 3心跳数据
					SubJson.insert("StationID", subStr);
					json.insert(QString::number(Count), SubJson);
					i = j;
					break;
				}
			}
		}

	}
	json.insert("DataLength", Count);//JSON数据个数
	if (Current_P >= buff.length())//判断当前指针位置
	{
		buff.clear();
	}//清除内存
	else
	{
		buff.remove(0, Current_P);
	}//将剩余字节存入缓存
	return 1;
}

//字符串转成数据库时间格式
QString Convert2Time(QString strTime)
{
    QString tmp;
    tmp="to_date('"+strTime.mid(0,4)+"-"+strTime.mid(4,2)+"-"+strTime.mid(6,2)+" "+strTime.mid(8,2)+":"+strTime.mid(10,2)+":"+strTime.mid(12,2)+"', 'yyyy-mm-dd hh24:mi:ss')";
    return tmp;
}

//字符串转成显示时间格式
QString Convert2TimeForm(QString strTime)
{
    QString tmp;
    tmp=strTime.mid(0,4)+"-"+strTime.mid(4,2)+"-"+strTime.mid(6,2)+" "+strTime.mid(8,2)+":"+strTime.mid(10,2)+":"+strTime.mid(12,2);
    return tmp;
}

