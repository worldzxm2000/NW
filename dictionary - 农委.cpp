#include "dictionary.h"

Dictionary::Dictionary()
{
//观察要素
   

	//第一根数据
	//土壤温度第一层
	map.insert("ab5", "ST_ST1");
	//土壤温度第二层
	map.insert("ab10", "ST_ST2");
	//土壤温度第二层
	map.insert("ab15", "ST_ST3");
	//土壤温度第二层
	map.insert("ab20", "ST_ST4");
	//土壤体积含水量第一层
	map.insert("arb10", "SoilVolume10");
	//土壤体积含水量第二层
	map.insert("arb20", "SoilVolume20");
	//土壤体积含水量第三层
	map.insert("arb30", "SoilVolume30");
	//土壤体积含水量第四层
	map.insert("arb40", "SoilVolume40");
	//土壤水分频率第一层
	map.insert("arg10", "SoilFrequency10");
	//土壤水分频率第二层
	map.insert("arg20", "SoilFrequency20");
	//土壤水分频率第三层
	map.insert("arg30", "SoilFrequency30");
	//土壤水分频率第四层
	map.insert("arg40", "SoilFrequency40");




	//第二根数据
	//土壤温度第一层
	map.insert("abc5", "ST_ST1");
	//土壤温度第二层
	map.insert("abc10", "ST_ST2");
	//土壤温度第二层
	map.insert("abc15", "ST_ST3");
	//土壤温度第二层
	map.insert("abc20", "ST_ST4");
	//土壤体积含水量第一层
	map.insert("arb50", "SoilVolume50");
	//土壤水分频率第一层
	map.insert("arg50", "SoilFrequency50");
	//60cm体积含水量
	map.insert("arb60", "SoilVolume60");
	//60cm频率
	map.insert("arg60", "SoilFrequency60");
	//80cm体积含水量
	map.insert("arb80", "SoilVolume80");
	//80cm频率
	map.insert("arg80", "SoilFrequency80");
	//100cm体积含水量
	map.insert("arb100", "SoilVolume100");
	//100cm频率
	map.insert("arg100", "SoilFrequency100");



	//当前时刻瞬时风向
	map.insert("aea", "WD_IWD");
	//当前时刻瞬时风速
	map.insert("afa", "WS_IWS1");
	//第一层气温
	map.insert("aaa", "AT_AT1");
	//第一层相对湿度
	map.insert("ada", "AH_RH1");
	//第二层气湿
	map.insert("aaa1", "AT_AT2");
	//第二层相对湿度
	map.insert("ada1", "AH_RH2");
	//第二层气湿
	map.insert("aaa2", "AT_AT3");
	//第二层相对湿度
	map.insert("ada2", "AH_RH3");
	//分钟降水
	map.insert("aha", "MntRnfl");
	//光合有效
	map.insert("aja", "R_PERI");
	//CO2浓度
	map.insert("asa", "CO2IC");


	//设备自检状态
	map.insert("z", "AutoCheckSts1");
	//风向传感器状态
	map.insert("y_aea", "WndDrctSensorSts");
	//风速传感器状态
	map.insert("y_afa", "WndSpdSensorSts1");
    //第一层温度传感器状态
	map.insert("y_aaa", "AirTmprtSensorSts1");
	//第一层湿度传感器状态
	map.insert("y_ada", "AirHmdSensorSts1");
	//第二层温度传感器状态
	map.insert("y_aaa1", "AirTmprtSensorSts2");
	//第二层湿度传感器状态
	map.insert("y_ada1", "AirHmdSensorSts2");
	//第三层温度传感器状态
	map.insert("y_aaa2", "AirTmprtSensorSts3");
	//第二层湿度传感器状态
	map.insert("y_ada2", "AirHmdSensorSts3");
	//土壤水分传感器1状态
	map.insert("y_ara1", "SoilHmdSensorSts1");
	//土壤水分传感器2状态
	map.insert("y_ara2", "SoilHmdSensorSts2");
	//雨量传感器状态
	map.insert("y_aha", "RnflSensorSts");
	//光和有效传感器状态
	map.insert("y_aji", "PhticEfcnySensorSts");
	//CO2浓度传感器状态
	map.insert("y_asa", "CO2CntrSensorSts");
	//蓄电池电压状态
	map.insert("xd", "BtryVltgSts1");
	//主采主板温度
	map.insert("wa", "MainClctrTmprtVal");
	//外存储卡剩余容量
	map.insert("rq", "CFSpaceSts");
}

QString Dictionary::Find(QString key)
{
    QMap<QString,QString>::const_iterator mi=map.find(key);
    if(mi!=map.end())
        return map[key];
    return NULL;
}
