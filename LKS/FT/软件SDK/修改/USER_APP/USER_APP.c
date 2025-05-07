/****************************************************************************
 *

 *
 ****************************************************************************
 *
 * THE SOFTWARE IS PROVIDED “AS IS”. BPS DISCLAIMS ALL WARRANTIES WHETHER EXPRESS, IMPLIED OR 
 * STATUTORY, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.? IN NO EVENT SHALL BPS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, ENHANCED, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING LOSS OF PROFITS AND LOSS OF USE) RESULTING FROM, BASED UPON, ARISING OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE.
 *
 * Copyright BPSEMI. 2021. All rights reserved
 *
 ****************************************************************************/
 /****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
/* Standard includes */
#include "Global_Variable.h"
#include "hardware_config.h"
#include "lks32mc03x_Gpio.h"
#include "USER_APP.h"
#include "lks32MC03x_Flash.h"
#include "HeatControl.h"

void USER_APP_vTick1ms(void);
void USER_GPIO_Init(void);
void USER_Init(void);
void zero_cheak(void);
struct appcmdkey AppCmdKey;
s32 powerfreqcmd[maxgear]={0,0,0,0};

void MemoryRestore(void);
void EraseWriteFlash(void);
void vLoadForFlashing(void);
void SpecialGPIOInit(void);
/****************************************************************************/
/***        END OF FILE                                                   ***/
/****************************************************************************/


u8 TempGear = 0;
u8 iTargetGear=0; 
u8 AutoTemp =0;		
u8 hairmode = 0;  //0: 默认风筒模式 1：冷热交替风  2：儿童模式  3： 速干模式


u32 Memorymsg;
u8 TempGear_memory;
u32 remotor_memory;
u8 Memorymessag_eraseflg;
void USER_GPIO_Init(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_StructInit(&GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Pin = hzcheck_port_pin;
//	GPIO_Init(hzcheck_port, &GPIO_InitStruct);
//	GPIO0_PFLT |=0x200;
//	GPIO_ResetBits(GPIO0,GPIO_Pin_6);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);

	    /*P1.6 LED1  */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin =   LED1_PIN;
    GPIO_Init(LED1_PORT, &GPIO_InitStruct);

    /* P0.3 LED3  P0.1 LED2 */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin =  LED2_PIN | LED3_PIN;
    GPIO_Init(LED2_PORT, &GPIO_InitStruct);

//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//    GPIO_InitStruct.GPIO_Pin =  LED4_PIN;
//    GPIO_Init(LED4_PORT, &GPIO_InitStruct);	
			LEDALL_OFF();		
			
	/* P0.6 SW_TEMP */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin =  KEY_WindTemp_port_pin | KEY_WindSpeed_port_pin;
    GPIO_Init(KEY_WindTemp_port, &GPIO_InitStruct);
		
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 ;
	GPIO_Init(GPIO1, &GPIO_InitStruct);
			HEATER_CONTROL_OFF();   //上电默认关闭发热丝
	/* down AC cheak
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = led1_port_pin ;
	GPIO_Init(led1_port, &GPIO_InitStruct);
	*/
}

void USER_Init(void)
{
   //DataUpdateRT();
//	powerfreqcmd[0] = App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_01)); //
//	
//	powerfreqcmd[1] = App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_02));
//	
//	powerfreqcmd[2] = App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_03));
		
	remotor_memory = *((u32 *) Rmt_NVM_Sector_StartAddr);
	//Read_Flash(Rmt_NVM_Sector_StartAddr, (u32 *)&remotor_memory, 1, NVR_TYPE);
//	remotor_memory =      NVR_UserRoomRead((UINT32)200<<2);   //light_fan
#ifdef  MemoryMode
    MemoryRestore();
#endif	
}


/* adc 22300为调节风速  adc 为14800为调节温度，长时间低为0，点按风速190，点按温度140*/
u8 key1cnt=0;
u8 key2cnt=0;
u8 key3cnt=0;
u8 u8key1cnt=0;
u8 u8key2cnt=0;
u8 u8key3cnt=0;


u8 speed2=0;
u8 temp2=0;

u8	KEY_WindSpeedCnt	=	0;
u8	WindSpeedKeyStateLast	=	0;
u8	WindSpeedKeyState	=	0	;
u16 KEY_WindTempONCnt=0;					//风温按下时间
u16 KEY_WindTempOFFCnt=0;					//风温松开时间
//void RemtCmdAns(void)
void Key_Refresh(void)
{
	//**********************风速检测******************************//
	if(hairmode<=1)
	{
		if(KEY_WindSpeedCnt < 15 )    //50Hz 10=10ms  60Hz 8.33=8.33ms
    {
        KEY_WindSpeedCnt ++;
    }
    else
    {
        KEY_WindSpeedCnt = 15; //15=15ms
        iTargetGear = 0;   //低档风速
    }

    WindSpeedKeyState = KEY_WindSpeed();  //读取档位信号电平

    if((WindSpeedKeyState == 1) && (WindSpeedKeyStateLast == 0))
    {
        if(KEY_WindSpeedCnt < 15)
        {
            iTargetGear = 1;  //高档风速
        }

        KEY_WindSpeedCnt = 0;
    }
    WindSpeedKeyStateLast = WindSpeedKeyState;   //记录档位信号电平
	}
	else if(hairmode==2)
	{
		iTargetGear = 2;  //儿童档风速
	}
	else if(hairmode==3)
	{
		iTargetGear = 3;  //速干档风速
	}
	//**********************风速检测******************************//
	//**********************风温检测******************************//		
	if(!KEY_WindTemp())
	{
		if(KEY_WindTempONCnt<10000)
		{
			KEY_WindTempONCnt++;
		}
		else
		{
			KEY_WindTempONCnt=10000;
		}
		if(KEY_WindTempONCnt>10)KEY_WindTempOFFCnt=0;
	}
	else 
	{
		if(KEY_WindTempOFFCnt<100)
		{
			KEY_WindTempOFFCnt++;
		}
		if((KEY_WindTempOFFCnt>50)&&(KEY_WindTempONCnt>50)&&(KEY_WindTempONCnt<2000))			//短按风温
		{
			AppCmdKey.sts = 1;
			AppCmdKey.cmd_exe = KEY_WindTemp_S;
			KEY_WindTempONCnt = 0;
		}
		else if((KEY_WindTempOFFCnt>50)&&(KEY_WindTempONCnt>=2000)&&(KEY_WindTempONCnt<=10000))			//长按风温
		{
			AppCmdKey.sts = 1;
			AppCmdKey.cmd_exe = KEY_WindTemp_L;
			KEY_WindTempONCnt = 0;
		}
//		else if((KEY_WindTempOFFCnt>50)&&(KEY_WindTempONCnt>=10000))			//长按风温
//		{
//			AppCmdKey.sts = 1;
//			AppCmdKey.cmd_exe = KEY_WindTemp_LL;
//			KEY_WindTempONCnt = 0;
//		}
		else if((KEY_WindTempOFFCnt>50)&&(KEY_WindTempONCnt<50))
		{
			KEY_WindTempONCnt = 0;
		}
	}
	//**********************风温检测******************************//	
}
u8 FRS_FLAG=0;
u8 SPEED_on1,SPEED_on2;
void RemtCmdAns(void)
{
	static u16 AutoTempLED1S=0;
	static u16 FastTempLED1S=0;
	static u16 FastTempCnt=0;
	static u8 TempTran=0;
	if(AppCmdKey.sts)
	{
		 AppCmdKey.sts = 0;
		switch  (AppCmdKey.cmd_exe)
			{
				case  KEY_WindTemp_S:												//短按功能
					
						if(hairmode>=2)
						{
							TempGear=TempTran;
							hairmode=0;
						}
						else if(hairmode==1)
						{
							TempGear=0;
							hairmode=0;
						}
						else
						{
						if(TempGear<2)TempGear++;
						else if(TempGear==2)
							{
								hairmode=1;
								AutoTempLED1S=0;
							}
						}
						

				 break;
				case KEY_WindTemp_L:												//2s长按按功能
					FRS_FLAG=1;
				
				
					if(hairmode<=1)
					{
						TempTran=TempGear;
						hairmode=2;
					}

				
				 break;		
				
				case KEY_WindTemp_LL:												//10s长按按功能
					
					if(hairmode==2)
					{
						FastTempLED1S=0;
						hairmode=3;
					}

				
				 break;	
		
				 default:

					break;		
			}
	}

	//*********************LED********************//

	if(!FRSControl.CrossDownAcState)
	{                                     //LED查重显示
		if(hairmode==0)   //默认风筒状态
		{
			LED_view();
			
//			if(TempGear==0)
//			{
//					LEDB_ON(); //LED2亮
//			}
//			else	if(TempGear==1)
//			{
//					LEDY_ON();  //LED3
//			}
//			else	if(TempGear==2)
//			{
//					LEDO_ON(); //LED4
//			}
//			else
//			{
//					LEDALL_OFF();
//			}
			
		
			
			
		}
		else if(hairmode==1)
		{
			AutoTempLED1S++;
			if(AutoTempLED1S==14000)AutoTempLED1S=0;
			if(AutoTempLED1S<7000)
			{
				TempGear=2;
				LEDO_ON();
			}
			else
			{
				TempGear=0;
				LEDB_ON();
			}
		}
		else if(hairmode==2)
		{
				LEDG_ON();
		}
		else if(hairmode==3)
		{
				FastTempLED1S++;
			if(FastTempLED1S==7000)
				{
					FastTempCnt++;
					FastTempLED1S=0;
					if(FastTempCnt==3)FastTempCnt=0;
				}
			if(FastTempCnt==0)
			{
				LEDB_ON();
			}
			else if(FastTempCnt==1)
			{
				LEDY_ON();
			}
			else if(FastTempCnt==2)
			{
				LEDO_ON();
			}
		}
	}
	else 
	{
		LEDALL_OFF();
	}
}
void LED_view(void){
	u8 LEDcnt;
	switch (LEDcnt)
    {  //LED1:P1.6  LED2:P0.1  LED:P0.3
    	case 0:
				if(SPEED_on1==1)       //LED3
				{
					GPIO0_POE &= ~(GPIO_Pin_3); //P0.3高阻态 P1.6流向P0.1
					GPIO0_POE |= (GPIO_Pin_1);
					GPIO1_POE |= (GPIO_Pin_6);
					
					GPIO1_BSRR |= (GPIO_Pin_6);
					GPIO0_BSRR |= (GPIO_Pin_1<<16);
				}
				else
				{
					GPIO0_POE &= ~(GPIO_Pin_1 | GPIO_Pin_3);
					GPIO1_POE &= ~(GPIO_Pin_6);
				}
    		break;
    	case 1:
				if(SPEED_on2==1)			//LED1
				{
					GPIO0_POE &= ~(GPIO_Pin_3); //P0.3高阻态 P0.1流向P1.6
					GPIO0_POE |= (GPIO_Pin_1);
					GPIO1_POE |= (GPIO_Pin_6);
					
					GPIO1_BSRR |= (GPIO_Pin_6<<16);
					GPIO0_BSRR |= (GPIO_Pin_1);
				}
				else
				{
					GPIO0_POE &= ~(GPIO_Pin_1 | GPIO_Pin_3);
					GPIO1_POE &= ~(GPIO_Pin_6);
				}
    		break;
			case 2:
				if(TempGear==0)			//LED2
				{
					GPIO1_POE &=~(GPIO_Pin_6); //P1.6高阻态 P0.1流向P0.3
					GPIO0_POE |= (GPIO_Pin_1);
					GPIO0_POE |= (GPIO_Pin_3);

					
					GPIO0_BSRR |= (GPIO_Pin_1);
					GPIO0_BSRR |= (GPIO_Pin_3<<16);
				}
				else
				{
					GPIO0_POE &= ~(GPIO_Pin_1 | GPIO_Pin_3);
					GPIO1_POE &= ~(GPIO_Pin_6);
				}
    		break;
    	case 3:
				if(TempGear==1)			//LED4
				{
					GPIO1_POE &=~(GPIO_Pin_6); //P1.6高阻态 P0.3流向P0.1
					GPIO0_POE |= (GPIO_Pin_1);
					GPIO0_POE |= (GPIO_Pin_3);

					
					GPIO0_BSRR |= (GPIO_Pin_3);
					GPIO0_BSRR |= (GPIO_Pin_1<<16);
				}
				else
				{
					GPIO0_POE &= ~(GPIO_Pin_1 | GPIO_Pin_3);
					GPIO1_POE &= ~(GPIO_Pin_6);
				}
    		break;
			case 4:
				if(TempGear==2)       //LED5
				{
					GPIO0_POE &= ~(GPIO_Pin_1); //P0.1高阻态 P1.6流向P0.3
					GPIO0_POE |= (GPIO_Pin_3);
					GPIO1_POE |= (GPIO_Pin_6);
					
					GPIO1_BSRR |= (GPIO_Pin_6);
					GPIO0_BSRR |= (GPIO_Pin_3<<16);
				}
				else
				{
					GPIO0_POE &= ~(GPIO_Pin_1 | GPIO_Pin_3);
					GPIO1_POE &= ~(GPIO_Pin_6);
				}
    		break;
    	  default:
    		break;
    }	
		LEDcnt++;
		if(LEDcnt==5)LEDcnt = 0;
	//**************LED***************//
}

void USER_APP_vTick1ms(void)
{
//  cheak_50hz();
	Key_Refresh();  //按键
  RemtCmdAns();   //风速
//		SpecialGPIOInit();
	
//	zero_cheak();
  HeaterControl();  //发热丝
	
		EraseWriteFlash(); //记忆
}

void zero_cheak(void)
{

}
extern u8 TempOverErrorstate;
void ErrorLed(void)
{
	static u8 ErrorLedstate=0;
	static u8 LEDCnt=0;
	static u16 LEDTimeMs=0;
	if(stru_Faults.R==0)
	{
		ErrorLedstate=0;				//没故障时，报警等标志位清零
		LEDCnt=0;
		LEDTimeMs=0;
	}
	if((stru_Faults.R!=0)&&(ErrorLedstate==0))				//有故障时，报警等标志位为零，识别报警错位
	{
		ErrorLedstate = 1;
		if(stru_Faults.B.TempOverError == 1)							//NTC故障
		{
			if(TempOverErrorstate) LEDCnt = 2;							//NTC开路
			else LEDCnt = 3;																//NTC短路
		}
		if(stru_Faults.B.NTCError == 1)
		{
			LEDCnt = 4;																			//NTC在未达到设定温度前，连续检测超过5分钟，NTC温度未到达设定温度
		}
		if(stru_Faults.B.ZeroError == 1)
		{
			LEDCnt = 5;																			//当过零信号翻转周期不在50hz和60hz的频率范围内
		}
	}
	else if(LEDCnt)
	{
		LEDTimeMs++;
		if(LEDTimeMs<=200){ LEDO_ON(); }
		else { LEDALL_OFF(); }
		if(LEDTimeMs>=400) 
		{
			LEDTimeMs=0;
			LEDCnt--;
		}
	}
	
}


/*******************************************************************************
 函数名称：    void SpecialGPIOInit(void)
 功能描述：    RST/SWDIO/SWCLK 等特殊PIN脚复用成通用IO初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/01/28     V1.0           LLYY              创建
 *******************************************************************************/
void SpecialGPIOInit(void)
{
	  static u8 udelayGPIOcntdown=0;
	  static u8 IOstate=0;
	  static u8 u8SpecialIOinit=1;
	
    if(u8SpecialIOinit==1 && struFOC_CurrLoop.nBusVoltage>=2000)
		{
		  u8SpecialIOinit=0;
			GPIO_InitTypeDef GPIO_InitStruct;
			GPIO_StructInit(&GPIO_InitStruct);
					
			/* 写保护开启 */	
			SYS_WR_PROTECT = 0x7a83;    
			
      /* change SWCKL AND SWDIO TO GPIO */
      SYS_IO_CFG &= (~BIT6);

			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStruct.GPIO_Pin =  key2_port_pin ;
			GPIO_Init(key2_port, &GPIO_InitStruct);
			GPIO_PinAFConfig(key1_port, GPIO_PinSource_9, AF0_GPIO);	
			
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStruct.GPIO_Pin =  key1_port_pin ;
			GPIO_Init(key1_port, &GPIO_InitStruct);
       	
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStruct.GPIO_Pin =  key3_port_pin ;
			GPIO_Init(key3_port, &GPIO_InitStruct);
			GPIO_PinAFConfig(key1_port, GPIO_PinSource_8, AF0_GPIO);	
    }
		
    
		if(struFOC_CurrLoop.nBusVoltage<550)
		{
			udelayGPIOcntdown++;
		  if((udelayGPIOcntdown>50)&&(IOstate==0))
     	{
				IOstate =1;	 
				GPIO_InitTypeDef GPIO_InitStruct;
				GPIO_StructInit(&GPIO_InitStruct);
				
				SYS_WR_PROTECT = 0x7a83;
			
				/* Change  GPIO TO SWCKL AND SWDIO */								
				SYS_IO_CFG |= (BIT6);//
				
				/* P1.9 */
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
				GPIO_Init(GPIO1, &GPIO_InitStruct);		  							
        
				/* P1.8 */
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_ANA;
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
				GPIO_Init(GPIO1, &GPIO_InitStruct);			
			}	
       			
		}

}
s16 uDCfil=3500;
s16 t_VdcSpdCoef;
s32 s32uDCfil=56000;
void GetVdcSpeed(void)
{

				s32uDCfil+=(struFOC_CurrLoop.nVoltageCircleLim*16L-s32uDCfil)>>10;
				uDCfil = s32uDCfil>>4;
 
					if(uDCfil>=3850)  //电压饱满的时候 2挡
					{
						t_VdcSpdCoef = 1024;
						SPEED_on2=1;
					}
					else if(uDCfil>=(3850-800)) //1挡电压
					{
		       t_VdcSpdCoef = 1024-((s32)(3850-uDCfil)*(1024-VDC_SPEED_REDUCTION_COEF)/800);
					SPEED_on1=1;
					}
					else
					{
						t_VdcSpdCoef = VDC_SPEED_REDUCTION_COEF;	
						SPEED_on1=0;
						SPEED_on1=0;
					}
			
			powerfreqcmd[0] = (u32)t_VdcSpdCoef*App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_01))/1024;
			powerfreqcmd[1] = (u32)t_VdcSpdCoef*App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_02))/1024;
			
			
			
      powerfreqcmd[2] = (u32)t_VdcSpdCoef*App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_03))/1024;
			powerfreqcmd[3] = (u32)t_VdcSpdCoef*App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_04))/1024;
		//	testspeed = (s32)t_VdcSpdCoef*App2CoreFreqTrans(User2AppFreqTrans(Gear_Speed_03))/1024;
}

#ifdef MemoryMode
void MemoryRestore(void)
{
	 // Memorymessag.cmd_exe =(remotor.add[2]&0x000ff00)>>8;
	  TempGear_memory =(remotor_memory&0x0000000f);

		if(TempGear_memory>=3)
		{
				TempGear = 0;
		}
		else
		{
			TempGear = TempGear_memory;
		}
}

void vLoadForFlashing(void)
{
				if((TempGear_memory!=TempGear)&&(TempGear<=2)&&(hairmode==0))
				{			
						TempGear_memory=TempGear;
						Memorymsg =  TempGear_memory;
						Memorymessag_eraseflg =1;		//擦除标志位					
				}
}
#endif 
#if 1//def MemoryMode  lgh
void EraseWriteFlash(void)
{
//		if((Memorymessag_eraseflg==1)&&(Sys_State!=RUN))
	if((Memorymessag_eraseflg==1)&&(struFOC_CtrProc.bMC_RunFlg==0))
	{
			Memorymessag_eraseflg=0;
		 __disable_irq();
		EraseSector(Rmt_NVM_Sector_StartAddr, NVR_TYPE, 0x9A0D361F);
	  /* 遥控码个数*每个码字节数 */
		ProgramPage(Rmt_NVM_Sector_StartAddr, sizeof(Memorymsg), (u8 *)&Memorymsg, NVR_TYPE,0x9AFDA40C);
//		 Nvr_UserRoomErase(200);
//		Nvr_UserRoomWrite(200,Memorymsg);
		 __enable_irq();			
	} 
}
#endif 





