/*******************************************************************************
 * 版权所有 (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： fault_detection.h
 * 内容摘要： fault_detection
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： andrew kong
 * 完成日期： 2019年11月28日
 *
 *******************************************************************************/
#ifndef __FAULT_DETECTION_H
#define __FAULT_DETECTION_H

#include "basic.h"
#include "mc_type.h"

typedef struct
{
    s16 nCheckCnt1;
    s16 nCheckCnt2;
    s16 nRecoverCntr;
    s16 nStartDelay;
    s16 nRecoverTime;
} stru_FaultTime_t;

typedef struct
{
    s16 nOverCurrent;            //过流值
    s16 nOverVoltage;            //过压值
    s16 nUnderVoltage;           //欠压值
    s16 nOverVoltageRecover;     //过压恢复值
    s16 nUnderVoltageRecover;    //欠压恢复值
    s16 nEmptyCurrent;           //空转电流值
    s32 wEmptySpeed;             //空转速度值
    s16 nStallCurrent;           //堵转电流值
    s32 wStallSpeedMax;          //堵转高速值
    s32 wStallSpeedMin;          //堵转低速值
    s32 wStallSpeed;             //堵转判断转速
    s16 nStallCurrentIq;         //堵转Q轴判断电流
    s16 nStallFlag;              //堵转判断标志
    s16 nStartFlag;              //二次启动判断标志
    s16 nPhaseLossFlag;          //缺相错误判断标志
} stru_FaultVariable_t;

typedef union
{
    u16 R;
    struct
    {
        u16 SoftCurretError : 1;//软件过流错误标志位
        u16 HardCurretError : 1;//硬件过流错误标志位
        u16 VoltOverError   : 1;//过压错误标志位
        u16 VoltUnderError  : 1;//欠压错误标志位
        u16 StallError      : 1;//堵转错误标志位
        u16 EmptyError      : 1;//离水空转错误标志位
        u16 PhaseLossError  : 1;//缺相错误标志位
        u16 TempOverError   : 1;//过温错误标志位
        u16 OffsetError     : 1;//偏置错误标志位
        u16 StartError      : 1;//启动错误标志位
				u16 ZeroError       : 1;//过零错误标志位
				u16 NTCError   			: 1;//NTC错误标志位
        u16                 : 4;//保留，可根据其他需求来添加错误标志位，注意不要超过16位，否则需要修改u16 R --> u32 R
    } B;
} stru_FaultStatus_t;

typedef struct
{
    u8  bFlag;                //计算标志位
    u16 bTheta;               //转子电角度
    u32 wPhATemp;             //A相电流计算中间值
    u32 wPhBTemp;             //B相电流计算中间值
    u32 wPhCTemp;             //C相电流计算中间值
    u16 nPhA;                 //A相电流
    u16 nPhB;                 //B相电流
    u16 nPhC;                 //C相电流
}stru_CurrentAmplitude_t;

extern u16 g_FluxObsMode;

extern volatile stru_FaultStatus_t stru_Faults;
extern stru_FaultVariable_t        stru_FaultValue;
extern stru_CurrentAmplitude_t     struCurrentAmplitude;
extern stru_CurrPhaseUVW           struImaxCurrent;

extern stru_FaultTime_t struFaultVoltTime;
extern stru_FaultTime_t struFaultEmptyTime;
extern stru_FaultTime_t struFaultStallTime;
extern stru_FaultTime_t struFaultCurrentTime;
extern stru_FaultTime_t struFaultTempTime;
extern stru_FaultTime_t struFaultPhaseTime;



extern void FaultInit(void);
extern void FaultCheck(void);
extern void FaultRecoverInit(void);
extern void FaultRecover(void);
extern void FaultCurrentCheck(INT16 cur,INT16 proThh);
extern void CurrentAmplitudeCalc(stru_CurrPhaseUVW *pstruCurrPhaseUVW, stru_CurrentAmplitude_t *pCurrentAmplitude,stru_CurrPhaseUVW *pstruCurrentMAX);

#endif

