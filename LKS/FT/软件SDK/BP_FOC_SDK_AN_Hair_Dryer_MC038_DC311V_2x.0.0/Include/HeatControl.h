/*******************************************************************************
 * 版权所有 (C)2022, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： HeatControl.h
 * 文件标识：
 * 内容摘要： 发热丝控制
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Robin Chen
 * 完成日期： 2022年12月13日
 *
 *******************************************************************************/
#ifndef __HEATCONTORL_H
#define __HEATCONTORL_H

#include "basic.h"
#include "lks32mc03x.h"
#include "lks32mc03x_gpio.h"
#include "basic.h"
#include "lks32mc03x.h"
#include "lks32mc03x_gpio.h"
//#include "LED.h"
#include "KeyScan.h"
#include "state_machine.h"
#include "Global_Variable.h"
#include "fault_detection.h"
typedef struct
{
	u8  ACFrequencyDetectFinishFlag;  //交流电50Hz或者60Hz检测完成标志   1：检测完成  0：未检测完成
  u16 ACFrequencyDetectCnt;         //交流电50Hz或者60Hz检测计数
	u8  ACFrequency;                  //交流电50Hz或者60Hz频率
  u16 AC50HzFrequencyDetectCntMax;  //交流电50Hz或者60Hz检测计数最大值
  u16 AC50HzFrequencyDetectCntMin;  //交流电50Hz或者60Hz检测计数最小值
  u16 AC60HzFrequencyDetectCntMax;  //交流电50Hz或者60Hz检测计数最大值
  u16 AC60HzFrequencyDetectCntMin;  //交流电50Hz或者60Hz检测计数最小值
	
	u8  ACDetectErrorFlag;            //交流电频率检测错误标志   1：错误  0：正常
	u8  CrossZeroErrorFlag;           //交流电过零检测错误标志   1：错误  0：正常
	
	u16 TurnOnDelayCnt;          //发热丝延迟工作计数
	u8 TurnOnOffFlag;            //发热丝可以允许工作标志    1：发热丝允许正常工作  0：发热丝关闭
	u8 CrossZeroState;           //当前交流电过零状态
	u8 CrossZeroStateLast;       //上次交流电过零状态
	s16 CrossZeroVoltage;				//当前ADC电压值
	s16 CrossZeroVoltageLast;		//上次ADC电压值
	u8 CrossZeroVoltageCnt;			//ADC计数
	u8 CrossZeroVoltageCnt1;
	u8 CrossZeroVoltageCnt2;		
	
	u8 CrossZeroMsCnt;					//过零检测时间
	u8 CrossDownAcState;			//掉电状态,
	u8 CrossDownAcStateLast;			//掉电状态,
	u8 CrossDownToUpAcState			;				//断电到上电
	u8 ThrowWaveFlag;            //丢波标志   1：可以正常丢波  0：不能丢波
	u8 CrossZeroCnt;             //过零计数
  u16 AC50HzThrowWaveDelayCnt; //交流电50Hz丢波延迟值
  u16 AC60HzThrowWaveDelayCnt; //交流电60Hz丢波延迟值
  u8 activecnt;
	u8 ThrowWaveMode;          //丢波模式
	u8 ThrowWaveCnt;           //丢波计数
	u8 ThrowWaveTabIndex;      //丢波表索引
	u32 ThrowWaveDelayCnt;     //丢波延时计数
	
	u8  CrossZeroPosedge;  //过零信号   1：上升沿  0：不确定
	u8  CrossZeroPosedgeFlag;  //过零信号标志   1：上升沿  0：不确定
	s16 TargetTemperature;     //发热丝目标温度值
	s16 HEATER_NTCTemperature; //采集发热丝实际温度值
	s16 IPM_OTPTemperature;    //采集IPM(MOS)实际温度值	

	u32 ThrowWaveBase;         //丢波基础值
	u32 ThrowWaveLimitMax;     //最大丢波限制值
	u32 ThrowWaveLimitMin;     //最小丢波限制值

} HEAT_CONTROL;

#define  ZERO_SCR()    GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_8)//(GET_AC_ZERO_CHEAK_CHANNEL)//GPIO_ReadInputDataBit(GPIO1, GPIO_Pin_4)      //读取过零信号电平

#define  HEATER_CONTROL_ON()     GPIO_ResetBits(GPIO1, GPIO_Pin_4)   //开发热丝  置为低电平
#define  HEATER_CONTROL_OFF()    GPIO_SetBits(GPIO1, GPIO_Pin_4)     //关发热丝  置为高电平

#define  ThrowFullWave   0     //发热温度控制丢全波
#define  ThrowHalfWave   1     //发热温度控制丢半波
#define  HEATER_DELAY_ON_TIME     (2000)          // 发热丝延迟开启时间 单位ms

//50Hz/60Hz交流电的过零信号检测区间值（单位 us：1s/22K = 45.4545us）
#define  AC50HzMax          240    //50Hz交流电检测最大值  
#define  AC50HzMin          200    //50Hz交流电检测最小值 
#define  AC60HzMax          200    //60Hz交流电检测最大值 
#define  AC60HzMin          170    //60Hz交流电检测最小值 

#define  AC50Hz          50    //50Hz交流电  标准值200 = 10ms/45.4545
#define  AC60Hz          60    //60Hz交流电  标准值183 = 8.33msms/45.4545

#define  Delay50Hz       11    //50Hz可控硅延迟导通 10 11 12   
#define  Delay60Hz       9     //60Hz可控硅延迟导通 8  9  10

#define  TEMP_CONSTANT_FUNCTION   (FUNCTION_ON)   // FUNCTION_ON：发热丝恒温功能使能，FUNCTION_OFF：发热丝恒温功能不使能

#define  NTC100C   973.5       //NTC温度对应的阻值
#define  NTC90C    1266.06     //NTC温度对应的阻值
#define  NTC80C    1668.02     //NTC温度对应的阻值
#define  NTC70C    2228.22     //NTC温度对应的阻值
#define  NTC60C    3020.93     //NTC温度对应的阻值
#define  NTC50C    4161        //NTC温度对应的阻值
#define  NTC40C    5829.24     //NTC温度对应的阻值
#define  NTC30C    8313        //NTC温度对应的阻值
#define  NTC20C    12095.7     //NTC温度对应的阻值
#define  NTC10C    17963.8     //NTC温度对应的阻值
#define  NTC00C    27280       //NTC温度对应的阻值
#define  NTCn10C   42428.7     //NTC温度对应的阻值
#define  NTCn20C   67699.6     //NTC温度对应的阻值

#define  NTC100CAD   1430      //NTC温度对应的采样值
#define  NTC90CAD    1842     //NTC温度对应的采样值
#define  NTC80CAD    2397     //NTC温度对应的采样值
#define  NTC70CAD    3146     //NTC温度对应的采样值
#define  NTC60CAD    4163     //NTC温度对应的采样值
#define  NTC50CAD    5543     //NTC温度对应的采样值
#define  NTC40CAD    7404     //NTC温度对应的采样值
#define  NTC30CAD    9874     //NTC温度对应的采样值
#define  NTC20CAD    13076    //NTC温度对应的采样值
#define  NTC10CAD    17044    //NTC温度对应的采样值
#define  NTC00CAD    21674    //NTC温度对应的采样值
#define  NTCn10CAD   26659    //NTC温度对应的采样值
#define  NTCn20CAD   31535    //NTC温度对应的采样值

extern HEAT_CONTROL FRSControl;                      /* 发热丝控制参数 */
extern void HeaterTemperature_Control(void);
void HeaterControlProcess(void);
extern void HeaterControl(void);
#endif

