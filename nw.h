#ifndef NW_H
#define NW_H
#include<windows.h>
#include<qjsonobject.h>
#define NWSHARED_EXPORT __declspec(dllexport)
#ifdef NWSHARED_EXPORT
#else
#define NWSHARED_EXPORT __declspec(dllimport)
#endif
#define NW "01"
//返回结果 
//20：表示农委BG,ED的要素数据
//2：表示终端命令操作成功
//3：表示终端命令操作失败
//4：表示终端命令读取值
//0：表示非法的终端命令
//-1：表示无效数据
//-2：表示非农委数据
EXTERN_C NWSHARED_EXPORT LRESULT Char2Json(QString &buff, QJsonObject &json);
QString Convert2Time(QString strTime);
QString Convert2TimeForm(QString strTime);
//获取业务号
EXTERN_C NWSHARED_EXPORT int GetServiceTypeID();
//获取业务名称
EXTERN_C NWSHARED_EXPORT QString GetServiceTypeName();
//获取版本号
EXTERN_C NWSHARED_EXPORT QString GetVersionNo();
//获取端口号
EXTERN_C NWSHARED_EXPORT int GetPort();
#endif // NW_H
