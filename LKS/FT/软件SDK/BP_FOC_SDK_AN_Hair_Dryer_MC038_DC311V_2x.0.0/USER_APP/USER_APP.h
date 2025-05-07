/*******************************************************************************
 * 版权所有 (C)2020, Bright Power Semiconductor Co.ltd
 *
 * 文件名称： USER_APP.h
 * 文件标识：
 * 内容摘要： 
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： BPS IOT TEAM.
 * 完成日期： 2020年1月26日
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
extern u8 hairmode;  //0: 默认风筒模式 1：冷热交替风  2：儿童模式  3： 速干模式
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
#define   LED1_PORT    GPIO1        //LED1端口
#define   LED1_PIN     GPIO_Pin_6   //LED1引脚

#define   LED2_PORT    GPIO0        //LED2端口
#define   LED2_PIN     GPIO_Pin_1   //LED2引脚

#define   LED3_PORT    GPIO0        //LED3端口
#define   LED3_PIN     GPIO_Pin_3   //LED3引脚

#define   LED4_PORT    GPIO0        //LED4端口
#define   LED4_PIN     GPIO_Pin_0   //LED4引脚

#define   LED1_OFF()    GPIO_ResetBits(LED1_PORT, LED1_PIN) //蓝灯置低电平
#define   LED1_ON()   	GPIO_SetBits(LED1_PORT, LED1_PIN)   //蓝灯置高电平

#define   LED2_OFF()    GPIO_ResetBits(LED2_PORT, LED2_PIN) //黄灯置低电平
#define   LED2_ON()   	GPIO_SetBits(LED2_PORT, LED2_PIN)   //黄灯置高电平

#define   LED3_OFF()    GPIO_ResetBits(LED3_PORT, LED3_PIN) //绿灯置低电平
#define   LED3_ON()  	  GPIO_SetBits(LED3_PORT, LED3_PIN)   //绿灯置高电平

#define   LED4_OFF()    GPIO_ResetBits(LED4_PORT, LED4_PIN) //橙灯置低电平
#define   LED4_ON()  	  GPIO_SetBits(LED4_PORT, LED4_PIN)   //橙灯置高电平

#define		LEDB_ON()			{	LED1_OFF();LED2_ON();LED3_OFF();LED4_OFF();}				
#define		LEDY_ON()			{	LED1_OFF();LED2_OFF();LED3_ON();LED4_OFF();}				
#define		LEDO_ON()			{	LED1_OFF();LED2_OFF();LED3_OFF();LED4_ON();}				
#define		LEDG_ON()			{	LED1_ON();LED2_OFF();LED3_OFF();LED4_OFF();}				
#define		LEDALL_OFF()  { LED1_OFF();LED2_OFF();LED3_OFF();LED4_OFF();}				


#define 	KEY_WindTemp_port              GPIO0
#define 	KEY_WindTemp_port_pin          GPIO_Pin_6
#define   KEY_WindTemp()        GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_6) //P0.6  风温按键

#define 	KEY_WindSpeed_port              GPIO0
#define 	KEY_WindSpeed_port_pin          GPIO_Pin_10
#define   KEY_WindSpeed()       GPIO_ReadInputDataBit(GPIO0, GPIO_Pin_10) //P0.10  风速按键

#define led1_port              GPIO0
#define led1_port_pin          GPIO_Pin_5
#define led2_port              GPIO0
#define led2_port_pin          GPIO_Pin_4
#define led3_port              GPIO1
#define led3_port_pin          GPIO_Pin_4

#define Gear_Speed_01                      (1433)                                   // 1档转速               单位：转/min  
#define Gear_Speed_02                      (1800)//(1600)                                  // 2档转速               单位：转/min 
#define Gear_Speed_03                      (834)                                  // 儿童档转速               单位：转/min 
#define Gear_Speed_04                      (2000)                                  // 速干转速               单位：转/min 
#define VDC_SPEED_REDUCTION_COEF                      700

/* Macro Definitions--------------------------------------------------------*/
#define RemoteAddrNum                     (3)
#define NVR_TYPE                          (0)                                                     /* 0x800 NVM,  0 FLASH */
#define Rmt_NVM_Sector_StartAddr          (0x7A00)

#define MemoryMode                                           //屏蔽记忆使能




#define KEY_WindTemp_S                             1							//短按
#define KEY_WindTemp_L                             2							//2s长按
#define KEY_WindTemp_LL                             3							//10s长按


#endif 





