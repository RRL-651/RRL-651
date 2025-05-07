/*******************************************************************************
 * ��Ȩ���� (C)2022, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� HeatControl.h
 * �ļ���ʶ��
 * ����ժҪ�� ����˿����
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� Robin Chen
 * ������ڣ� 2022��12��13��
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
	u8  ACFrequencyDetectFinishFlag;  //������50Hz����60Hz�����ɱ�־   1��������  0��δ������
  u16 ACFrequencyDetectCnt;         //������50Hz����60Hz������
	u8  ACFrequency;                  //������50Hz����60HzƵ��
  u16 AC50HzFrequencyDetectCntMax;  //������50Hz����60Hz���������ֵ
  u16 AC50HzFrequencyDetectCntMin;  //������50Hz����60Hz��������Сֵ
  u16 AC60HzFrequencyDetectCntMax;  //������50Hz����60Hz���������ֵ
  u16 AC60HzFrequencyDetectCntMin;  //������50Hz����60Hz��������Сֵ
	
	u8  ACDetectErrorFlag;            //������Ƶ�ʼ������־   1������  0������
	u8  CrossZeroErrorFlag;           //���������������־   1������  0������
	
	u16 TurnOnDelayCnt;          //����˿�ӳٹ�������
	u8 TurnOnOffFlag;            //����˿������������־    1������˿������������  0������˿�ر�
	u8 CrossZeroState;           //��ǰ���������״̬
	u8 CrossZeroStateLast;       //�ϴν��������״̬
	s16 CrossZeroVoltage;				//��ǰADC��ѹֵ
	s16 CrossZeroVoltageLast;		//�ϴ�ADC��ѹֵ
	u8 CrossZeroVoltageCnt;			//ADC����
	u8 CrossZeroVoltageCnt1;
	u8 CrossZeroVoltageCnt2;		
	
	u8 CrossZeroMsCnt;					//������ʱ��
	u8 CrossDownAcState;			//����״̬,
	u8 CrossDownAcStateLast;			//����״̬,
	u8 CrossDownToUpAcState			;				//�ϵ絽�ϵ�
	u8 ThrowWaveFlag;            //������־   1��������������  0�����ܶ���
	u8 CrossZeroCnt;             //�������
  u16 AC50HzThrowWaveDelayCnt; //������50Hz�����ӳ�ֵ
  u16 AC60HzThrowWaveDelayCnt; //������60Hz�����ӳ�ֵ
  u8 activecnt;
	u8 ThrowWaveMode;          //����ģʽ
	u8 ThrowWaveCnt;           //��������
	u8 ThrowWaveTabIndex;      //����������
	u32 ThrowWaveDelayCnt;     //������ʱ����
	
	u8  CrossZeroPosedge;  //�����ź�   1��������  0����ȷ��
	u8  CrossZeroPosedgeFlag;  //�����źű�־   1��������  0����ȷ��
	s16 TargetTemperature;     //����˿Ŀ���¶�ֵ
	s16 HEATER_NTCTemperature; //�ɼ�����˿ʵ���¶�ֵ
	s16 IPM_OTPTemperature;    //�ɼ�IPM(MOS)ʵ���¶�ֵ	

	u32 ThrowWaveBase;         //��������ֵ
	u32 ThrowWaveLimitMax;     //��󶪲�����ֵ
	u32 ThrowWaveLimitMin;     //��С��������ֵ

} HEAT_CONTROL;

#define  ZERO_SCR()    GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_8)//(GET_AC_ZERO_CHEAK_CHANNEL)//GPIO_ReadInputDataBit(GPIO1, GPIO_Pin_4)      //��ȡ�����źŵ�ƽ

#define  HEATER_CONTROL_ON()     GPIO_ResetBits(GPIO1, GPIO_Pin_4)   //������˿  ��Ϊ�͵�ƽ
#define  HEATER_CONTROL_OFF()    GPIO_SetBits(GPIO1, GPIO_Pin_4)     //�ط���˿  ��Ϊ�ߵ�ƽ

#define  ThrowFullWave   0     //�����¶ȿ��ƶ�ȫ��
#define  ThrowHalfWave   1     //�����¶ȿ��ƶ��벨
#define  HEATER_DELAY_ON_TIME     (2000)          // ����˿�ӳٿ���ʱ�� ��λms

//50Hz/60Hz������Ĺ����źż������ֵ����λ us��1s/22K = 45.4545us��
#define  AC50HzMax          240    //50Hz�����������ֵ  
#define  AC50HzMin          200    //50Hz����������Сֵ 
#define  AC60HzMax          200    //60Hz�����������ֵ 
#define  AC60HzMin          170    //60Hz����������Сֵ 

#define  AC50Hz          50    //50Hz������  ��׼ֵ200 = 10ms/45.4545
#define  AC60Hz          60    //60Hz������  ��׼ֵ183 = 8.33msms/45.4545

#define  Delay50Hz       11    //50Hz�ɿع��ӳٵ�ͨ 10 11 12   
#define  Delay60Hz       9     //60Hz�ɿع��ӳٵ�ͨ 8  9  10

#define  TEMP_CONSTANT_FUNCTION   (FUNCTION_ON)   // FUNCTION_ON������˿���¹���ʹ�ܣ�FUNCTION_OFF������˿���¹��ܲ�ʹ��

#define  NTC100C   973.5       //NTC�¶ȶ�Ӧ����ֵ
#define  NTC90C    1266.06     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC80C    1668.02     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC70C    2228.22     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC60C    3020.93     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC50C    4161        //NTC�¶ȶ�Ӧ����ֵ
#define  NTC40C    5829.24     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC30C    8313        //NTC�¶ȶ�Ӧ����ֵ
#define  NTC20C    12095.7     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC10C    17963.8     //NTC�¶ȶ�Ӧ����ֵ
#define  NTC00C    27280       //NTC�¶ȶ�Ӧ����ֵ
#define  NTCn10C   42428.7     //NTC�¶ȶ�Ӧ����ֵ
#define  NTCn20C   67699.6     //NTC�¶ȶ�Ӧ����ֵ

#define  NTC100CAD   1430      //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC90CAD    1842     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC80CAD    2397     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC70CAD    3146     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC60CAD    4163     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC50CAD    5543     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC40CAD    7404     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC30CAD    9874     //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC20CAD    13076    //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC10CAD    17044    //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTC00CAD    21674    //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTCn10CAD   26659    //NTC�¶ȶ�Ӧ�Ĳ���ֵ
#define  NTCn20CAD   31535    //NTC�¶ȶ�Ӧ�Ĳ���ֵ

extern HEAT_CONTROL FRSControl;                      /* ����˿���Ʋ��� */
extern void HeaterTemperature_Control(void);
void HeaterControlProcess(void);
extern void HeaterControl(void);
#endif

