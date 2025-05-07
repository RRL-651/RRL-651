/*******************************************************************************
 * ��Ȩ���� (C)2020, Bright Power Semiconductor Co.ltd
 *
 * �ļ����ƣ� USER_APP.h
 * �ļ���ʶ��
 * ����ժҪ�� 
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� BPS IOT TEAM.
 * ������ڣ� 2020��1��26��
 *
 *
 *******************************************************************************/

/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __USE_APP__
#define __USE_APP__

 /****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "basic.h"
#include "lks32mc03x_gpio.h"
extern void USER_GPIO_Init(void);
extern void cheak_50hz(void);
extern void USER_Init(void);
extern void USER_APP_vTick1ms(void);
extern void GetVdcSpeed(void);
extern void vLoadForFlashing(void);
#define hzcheck_port              GPIO0
#define hzcheck_port_pin          GPIO_Pin_8
extern  u8 Flag_50HZ ;
extern u8 iTargetGear;
#define maxgear                              4
extern s32 powerfreqcmd[maxgear];

extern u32 Memorymsg;
extern u8 TempGear;
extern u8 iTargetGear; 
extern u8 hairmode;  //0: Ĭ�Ϸ�Ͳģʽ 1�����Ƚ����  2����ͯģʽ  3�� �ٸ�ģʽ
struct appcmdkey 
{
	u8 cmd_exe;
	u8 cmd_exeorg;
	u8 sts;
	//u8 longshrotpress;
};//app cmd key..

#define key1_port              GPIO0
#define key1_port_pin          GPIO_Pin_9
#define key2_port              GPIO1
#define key2_port_pin          GPIO_Pin_9
#define key3_port              GPIO1
#define key3_port_pin          GPIO_Pin_8
#define key1_scan() 						 GPIO_ReadInputDataBit(key1_port, key1_port_pin)
#define key2_scan() 						 GPIO_ReadInputDataBit(key2_port, key2_port_pin)
#define key3_scan() 						 GPIO_ReadInputDataBit(key3_port, key3_port_pin)
#define   LED1_PORT    GPIO1        //LED1�˿�
#define   LED1_PIN     GPIO_Pin_6   //LED1����

#define   LED2_PORT    GPIO0        //LED2�˿�
#define   LED2_PIN     GPIO_Pin_1   //LED2����

#define   LED3_PORT    GPIO0        //LED3�˿�
#define   LED3_PIN     GPIO_Pin_3   //LED3����

#define   LED4_PORT    GPIO0        //LED4�˿�
#define   LED4_PIN     GPIO_Pin_0   //LED4����

#define   LED1_OFF()    GPIO_ResetBits(LED1_PORT, LED1_PIN) //�����õ͵�ƽ
#define   LED1_ON()   	GPIO_SetBits(LED1_PORT, LED1_PIN)   //�����øߵ�ƽ

#define   LED2_OFF()    GPIO_ResetBits(LED2_PORT, LED2_PIN) //�Ƶ��õ͵�ƽ
#define   LED2_ON()   	GPIO_SetBits(LED2_PORT, LED2_PIN)   //�Ƶ��øߵ�ƽ

#define   LED3_OFF()    GPIO_ResetBits(LED3_PORT, LED3_PIN) //�̵��õ͵�ƽ
#define   LED3_ON()  	  GPIO_SetBits(LED3_PORT, LED3_PIN)   //�̵��øߵ�ƽ

#define   LED4_OFF()    GPIO_ResetBits(LED4_PORT, LED4_PIN) //�ȵ��õ͵�ƽ
#define   LED4_ON()  	  GPIO_SetBits(LED4_PORT, LED4_PIN)   //�ȵ��øߵ�ƽ

#define		LEDB_ON()			{	LED1_OFF();LED2_ON();LED3_OFF();LED4_OFF();}				
#define		LEDY_ON()			{	LED1_OFF();LED2_OFF();LED3_ON();LED4_OFF();}				
#define		LEDO_ON()			{	LED1_OFF();LED2_OFF();LED3_OFF();LED4_ON();}				
#define		LEDG_ON()			{	LED1_ON();LED2_OFF();LED3_OFF();LED4_OFF();}				
#define		LEDALL_OFF()  { LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();}				


#define 	KEY_WindTemp_port              GPIO0
#define 	KEY_WindTemp_port_pin          GPIO_Pin_6
#define   KEY_WindTemp()        GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_6) //P0.6  ���°���

#define 	KEY_WindSpeed_port              GPIO0
#define 	KEY_WindSpeed_port_pin          GPIO_Pin_10
#define   KEY_WindSpeed()       GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_10) //P0.10  ���ٰ���

#define led1_port              GPIO0
#define led1_port_pin          GPIO_Pin_5
#define led2_port              GPIO0
#define led2_port_pin          GPIO_Pin_4
#define led3_port              GPIO1
#define led3_port_pin          GPIO_Pin_4

#define Gear_Speed_01                      (1433)                                   // 1��ת��               ��λ��ת/min  
#define Gear_Speed_02                      (1800)//(1600)                                  // 2��ת��               ��λ��ת/min 
#define Gear_Speed_03                      (834)                                  // ��ͯ��ת��               ��λ��ת/min 
#define Gear_Speed_04                      (2000)                                  // �ٸ�ת��               ��λ��ת/min 
#define VDC_SPEED_REDUCTION_COEF                      700

/* Macro Definitions--------------------------------------------------------*/
#define RemoteAddrNum                     (3)
#define NVR_TYPE                          (0)                                                     /* 0x800 NVM,  0 FLASH */
#define Rmt_NVM_Sector_StartAddr          (0x7A00)

#define MemoryMode                                           //���μ���ʹ��




#define KEY_WindTemp_S                             1							//�̰�
#define KEY_WindTemp_L                             2							//2s����
#define KEY_WindTemp_LL                             3							//10s����


#endif 





