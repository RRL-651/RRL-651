/*******************************************************************************
 * 版权所有 (C)2022, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： HeatControl.c
 * 文件标识：
 * 内容摘要： KeyScan
 * 其它说明： 无
 * 当前版本： V1.0
 * 作    者： Robin Chen
 * 完成日期： 2022年12月13日
 *
 *******************************************************************************/
#include "HeatControl.h"
#include "USER_APP.h"
const uint8_t HotTab[2500]={  
	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0, /* 0 */
	1,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0, /* 1 */
	1,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,1,0,0,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,1,	0,0,0,0,0,	0,0,0,0,0,	0,0,0,0,0, /* 2 */
	1,0,0,0,0,	0,0,0,0,0,	0,0,1,0,0,	0,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0,	0,0,1,0,0,	0,0,0,0,0,	0,0,0,0,0, /* 3 */
	1,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,0,0,0, /* 4 */

	1,0,0,0,0,	0,0,0,1,0,	0,0,0,0,0,	0,1,0,0,0,	0,0,0,0,0,	1,0,0,0,0,	0,1,0,0,0,	0,0,0,0,0,	0,1,0,0,0,	0,0,0,0,0, /* 5 */
	1,0,0,0,0,	0,0,1,0,0,	0,0,0,0,1,	0,0,0,0,0,	0,1,0,0,0,	0,0,0,1,0,	0,0,0,0,0,	1,0,0,0,0,	0,0,1,0,0,	0,0,0,0,0, /* 6 */
	1,0,0,0,0,	0,0,1,0,0,	0,0,0,1,0,	0,0,0,0,1,	0,0,0,0,0,	1,0,0,0,0,	0,0,1,0,0,	0,0,0,1,0,	0,0,0,0,1,	0,0,0,0,0, /* 7 */
	1,0,0,0,0,	0,1,0,0,0,	0,1,0,0,0,	0,0,1,0,0,	0,0,1,0,0,	0,0,0,1,0,	0,0,0,1,0,	0,0,0,0,1,	0,0,0,0,1,	0,0,0,0,0, /* 8 */	
	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0,	1,0,0,0,0, /* 9 */

	1,0,0,0,0,	1,0,0,0,1,	0,0,0,0,1,	0,0,0,1,0,	0,0,0,1,0,	0,0,1,0,0,	0,0,1,0,0,	0,1,0,0,0,	0,1,0,0,0,	1,0,0,0,0, /* 10 */
	1,0,0,0,0,	1,0,0,0,1,	0,0,0,1,0,	0,0,1,0,0,	0,1,0,0,0,	1,0,0,0,0,	1,0,0,0,1,	0,0,0,1,0,	0,0,1,0,0,	0,1,0,0,0, /* 11 */
	1,0,0,1,0,	0,0,1,0,0,	0,1,0,0,0,	1,0,0,0,1,	0,0,0,1,0,	0,1,0,0,0,	1,0,0,0,1,	0,0,0,1,0,	0,0,1,0,0,	0,1,0,0,0, /* 12 */
	1,0,0,0,1,	0,0,1,0,0,	0,1,0,0,1,	0,0,0,1,0,	0,1,0,0,0,	1,0,0,1,0,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0,	0,1,0,0,0, /* 13 */
	1,0,0,0,1,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0, /* 14 */
	
	1,0,0,0,1,	0,0,1,0,0,	1,0,0,1,0,	0,1,0,0,1,	0,0,1,0,0,	1,0,0,0,1,	0,0,1,0,0,	1,0,0,1,0,	0,1,0,0,1,	0,0,1,0,0, /* 15 */
	1,0,0,1,0,	0,1,0,0,1,	0,0,1,0,0,	1,0,0,1,0,	0,1,0,0,1,	0,0,1,0,0,	1,0,0,1,0,	0,1,0,0,1,	0,0,1,0,0,	1,0,0,1,0, /* 16 */
	1,0,1,0,0,	1,0,0,1,0,	0,1,0,1,0,	0,1,0,0,1,	0,0,1,0,0,	1,0,1,0,0,	1,0,0,1,0,	0,1,0,1,0,	0,1,0,0,1,	0,0,1,0,0, /* 17 */
	1,0,1,0,0,	1,0,0,1,0,	1,0,0,1,0,	0,1,0,1,0,	0,1,0,0,1,	0,1,0,0,1,	0,0,1,0,1,	0,0,1,0,0,	1,0,1,0,0,	1,0,0,1,0, /* 18 */
	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0,	1,0,1,0,0, /* 19 */	
	
	1,0,0,1,0,	1,0,1,0,0,	1,0,1,0,1,	0,0,1,0,1,	0,1,0,0,1,	0,1,0,1,0,	0,1,0,1,0,	1,0,0,1,0,	1,0,1,0,0,	1,0,1,0,0, /* 20 */
	1,0,0,1,0,	1,0,1,0,0,	1,0,1,0,1,	0,1,0,0,1,	0,1,0,1,0,	1,0,0,1,0,	1,0,1,0,0,	1,0,1,0,1,	0,1,0,0,1,	0,1,0,1,0, /* 21 */
	1,0,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,0,1,0,1,	0,1,0,1,0, /* 22 */
	1,0,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0, /* 23 */
	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0, /* 24 */
	
	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,0,1,0,	1,0,1,0,0, /* 25 */
	1,1,0,1,0,	1,0,1,0,1,	0,1,0,1,1,	0,1,0,1,0,	1,0,1,0,1,	0,1,1,0,1,	0,1,0,1,0,	1,0,1,0,1,	1,0,1,0,1,	0,1,0,1,0, /* 26 */
	1,1,0,1,0,	1,0,1,1,0,	1,0,1,0,1,	0,1,1,0,1,	0,1,0,1,0,	1,1,0,1,0,	1,0,1,1,0,	1,0,1,0,1,	0,1,1,0,1,	0,1,0,1,0, /* 27 */
	0,1,1,0,1,  0,1,0,1,1,  0,1,0,1,0,  1,1,0,1,0,  1,0,1,1,0,  1,0,1,0,1,  1,0,1,0,1,  0,1,1,0,1,  0,1,0,1,1,  0,1,0,1,1, /* 28 */
	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1,	0,1,0,1,1, /* 29 */
	
	0,1,0,1,1,  0,1,1,0,1,  0,1,1,0,1,  1,0,1,0,1,  1,0,1,1,0,  1,0,1,1,0,  1,1,0,1,0,  1,1,0,1,1,  0,1,0,1,1,  0,1,1,0,1, /* 30 */
	0,1,0,1,1,  0,1,1,0,1,  1,0,1,0,1,  1,0,1,1,0,  1,1,0,1,1,  0,1,0,1,1,  0,1,1,0,1,  1,0,1,0,1,  1,0,1,1,0,  1,1,0,1,1, /* 31 */
	0,1,1,0,1,  1,0,1,1,0,  1,1,0,1,1,  0,1,1,0,1,  1,0,1,1,0,  1,1,0,1,1,  0,1,1,0,1,  1,0,1,1,0,  1,1,0,1,1,  0,1,1,0,1, /* 32 */
	0,1,1,1,0,  1,1,0,1,1,  0,1,1,0,1,  1,0,1,1,0,  1,1,0,1,1,  0,1,1,1,0,  1,1,0,1,1,  0,1,1,0,1,  1,0,1,1,0,  1,1,0,1,1, /* 33 */
	0,1,1,1,0,  1,1,0,1,1,  0,1,1,1,0,  1,1,0,1,1,  0,1,1,1,0,  1,1,0,1,1,  0,1,1,1,0,  1,1,0,1,1,  0,1,1,1,0,  1,1,0,1,1, /* 34 */
	
	0,1,1,1,0,	1,1,0,1,1,	1,0,1,1,0,	1,1,1,0,1,	1,0,1,1,1,	0,1,1,0,1,	1,1,0,1,1,	0,1,1,1,0,	1,1,0,1,1,  1,0,1,1,1, /* 35 */
	0,1,1,0,1,  1,1,0,1,1,	1,0,1,1,1,  0,1,1,1,0,  1,1,1,0,1,  1,0,1,1,1,  0,1,1,1,0,  1,1,1,0,1,  1,1,0,1,1,  1,0,1,1,1, /* 36 */
	0,1,1,1,1,	0,1,1,1,0,	1,1,1,0,1,	1,1,0,1,1,	1,0,1,1,1,	0,1,1,1,1,	0,1,1,1,0,	1,1,1,0,1,	1,1,0,1,1,	1,0,1,1,1, /* 37 */
	0,1,1,1,1,	0,1,1,1,0,	1,1,1,1,0,	1,1,1,0,1,	1,1,1,0,1,	1,1,0,1,1,	1,1,0,1,1,	1,0,1,1,1,	1,0,1,1,1,	0,1,1,1,1, /* 38 */
	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1,	0,1,1,1,1, /* 39 */
	
	0,1,1,1,1,	1,0,1,1,1,	1,0,1,1,1,	1,1,0,1,1,	1,1,0,1,1,	1,1,1,0,1,	1,1,1,0,1,	1,1,1,1,0,	1,1,1,1,0,	1,1,1,1,1, /* 40 */
	0,1,1,1,1,	1,1,0,1,1,	1,1,1,0,1,	1,1,1,1,0,	1,1,1,1,1,	0,1,1,1,1,	1,1,0,1,1,	1,1,1,0,1,	1,1,1,1,0,	1,1,1,1,1, /* 41 */
	0,1,1,1,1,	1,1,0,1,1,	1,1,1,1,0,	1,1,1,1,1,	1,0,1,1,1,	1,1,1,0,1,	1,1,1,1,1,	0,1,1,1,1,	1,1,0,1,1,	1,1,1,1,1, /* 42 */
	0,1,1,1,1,	1,1,1,0,1,	1,1,1,1,1,	1,0,1,1,1,	1,1,1,1,1,	0,1,1,1,1,	1,0,1,1,1,	1,1,1,1,1,	1,0,1,1,1,	1,1,1,1,1, /* 43 */
	1,1,1,1,0,	1,1,1,1,1,	1,1,1,1,0,	1,1,1,1,1,	1,1,1,1,0,	1,1,1,1,1,	1,1,1,1,0,	1,1,1,1,1,	1,1,1,1,0,	1,1,1,1,1, /* 44 */
	
	1,0,1,1,1,	1,1,1,1,1,	1,1,1,0,1,	1,1,1,1,1,	1,1,1,1,1,	1,0,1,1,1,	1,1,1,1,1,	1,1,1,0,1,	1,1,1,1,1,	1,1,1,1,1, /* 45 */
	1,0,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,0,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	0,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1, /* 46 */
	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,0,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,0, /* 47 */
	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,0, /* 48 */
	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1,	1,1,1,1,1, /* 49 */
};


HEAT_CONTROL FRSControl;
void HeaterControl(void);
void HeaterTemperature_Control(void);

/*****************************************************************************
 * Function:     void HeaterControl(void)
 * Description:  发热丝控制
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
 /*****************************************************************************
 * Function:     void HeaterControl(void)
 * Description:  发热丝控制
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
 u8 FRS_ON=0;
u8 ControlOFF;
 void HeaterControl(void)
{
	static u16 AcDownCD1ms;
   static	u8 AccCrossZeroCnt=0;
   FRSControl.ThrowWaveMode = ThrowHalfWave;  //丢波模式默认丢*波 半波：ThrowHalfWave  全波：ThrowFullWave
	 
	 /* 发热丝工作条件：1.状态机处于RUN  2.电机实际转速达到一个比较大的值  3.系统没有发生任何错误  4.交流电频率检测完成  5.发热丝延时工作计数*/
	 if((struFOC_CtrProc.eSysState == RUN)&&(struMotorSpeed.wSpeedEst > 15000)&&(stru_Faults.R == 0)&&(FRSControl.ACFrequencyDetectFinishFlag == 1)&&(FRSControl.TurnOnDelayCnt>=HEATER_DELAY_ON_TIME))  //判断发热丝工作条件
//	 if((struFOC_CtrProc.eSysState == RUN)&&(struMotorSpeed.wSpeedEst > 15000)&&(stru_Faults.R == 0)&&(FRSControl.ACFrequencyDetectFinishFlag == 1))  //判断发热丝工作条件

	 {
	     FRSControl.TurnOnOffFlag = 1;  //发热丝正常工作
	 }
	 else
	 {
	     FRSControl.TurnOnOffFlag = 0;  //发热丝工作关闭
	 }
	
//	if(!FRSControl.CrossZeroPosedge)
//	{
//		if(++FRSControl.ACFrequencyDetectCnt > 1 )    //
//		{
//				FRSControl.CrossZeroPosedge = 1;
//				FRSControl.ACFrequencyDetectCnt = 0;
//				FRSControl.CrossZeroPosedgeFlag = 1;			
//		}
//	}
	if(!FRSControl.CrossZeroPosedge) //过零点
	{
		if(++FRSControl.ACFrequencyDetectCnt > 6 )    //
		{
				FRSControl.CrossZeroPosedge = 1;
				FRSControl.ACFrequencyDetectCnt = 0;
				FRSControl.CrossZeroPosedgeFlag ++;			
		}
	}
	if(FRSControl.CrossZeroPosedgeFlag>=2) //过零点
	{
		FRSControl.CrossZeroPosedgeFlag=0;

	/*	  
		  if(FRSControl.ACFrequencyDetectFinishFlag == 0)  //交流电频率检测标志
			{
				  if((FRSControl.CrossZeroCnt > 1)&&(FRSControl.CrossZeroCnt < 5 )) //CrossZeroCnt>0 避免上电误检测
					{
							if((FRSControl.ACFrequencyDetectCnt > FRSControl.AC50HzFrequencyDetectCntMin) && (FRSControl.ACFrequencyDetectCnt < FRSControl.AC50HzFrequencyDetectCntMax))  //载波22K 50Hz10ms（220）  60Hz8.33ms（183.3）
							{
								 FRSControl.ACFrequency = AC50Hz;  //交流电频率50Hz
								 FRSControl.ACFrequencyDetectFinishFlag = 1;   //交流电频率检测完成
							}
							else if((FRSControl.ACFrequencyDetectCnt > FRSControl.AC60HzFrequencyDetectCntMin) && (FRSControl.ACFrequencyDetectCnt < FRSControl.AC60HzFrequencyDetectCntMax))  //载波22K 50Hz10ms（220）  60Hz8.33ms（183.3）
							{
								 FRSControl.ACFrequency = AC60Hz;  //交流电频率60Hz
								 FRSControl.ACFrequencyDetectFinishFlag = 1;   //交流电频率检测完成
							}
							else
              {
								  FRSControl.ACFrequencyDetectFinishFlag = 0;   //交流电频率检测失败
									FRSControl.CrossZeroErrorFlag = 1;    //过零检测错误
							}
				  }
					else if(FRSControl.CrossZeroCnt >= 5)   //上电后经过5次过零信号都没有检测出交流电频率
					{
//						  FRSControl.ACFrequency = AC50Hz;   //默认交流电频率50Hz
//						  FRSControl.ACFrequencyDetectFinishFlag = 1;
						
						  FRSControl.ACDetectErrorFlag = 1;//交流电频率检测错误
					}
		  }
	*/		
	    FRSControl.ACFrequency = AC50Hz;  //交流电频率60Hz
		  FRSControl.ACFrequencyDetectFinishFlag = 1;   //交流电频率检测完成
      FRSControl.CrossZeroErrorFlag= 0;       //过零检测错误恢复
		 	FRSControl.ACFrequencyDetectCnt = 0;    //交流电频率检测计数清零
			FRSControl.CrossZeroCnt ++;    //过零次数计数

			
			if(FRSControl.ThrowWaveMode == ThrowHalfWave)   //半波丢波模式
			{
					if(FRSControl.CrossZeroCnt > 49)
					{
						 FRSControl.CrossZeroCnt = 0;
					}
					FRSControl.ThrowWaveTabIndex= HotTab[(FRSControl.ThrowWaveCnt*50)+(FRSControl.CrossZeroCnt)];  //发热丝开通状态查表
		  }
			else   //全波丢波模式
			{
			   	if(FRSControl.CrossZeroCnt > 99)
					{
						 FRSControl.CrossZeroCnt = 0;
					}
					FRSControl.ThrowWaveTabIndex= HotTab[(FRSControl.ThrowWaveCnt*50)+(FRSControl.CrossZeroCnt>>1)];  //发热丝开通状态查表
			}	
				 if(FRSControl.TurnOnOffFlag == 1)    //判断发热丝是否可以正常工作
	 {
			// if((FRSControl.CrossZeroStateLast == 0)&&(FRSControl.CrossZeroState == 1))  //发生上升沿
			 {
				   FRSControl.ThrowWaveFlag = 1;   //发生过零信号上升沿允许丢波标志
			 }

			 if(FRSControl.ThrowWaveFlag == 1) 
			 {
					 FRSControl.ThrowWaveDelayCnt ++;  //丢波延时计数
					 
				   if(FRSControl.ACFrequency == AC50Hz)
					 {
							 if(FRSControl.ThrowWaveDelayCnt >= FRSControl.AC50HzThrowWaveDelayCnt)  //丢波延时  延时写0
							 {
									 FRSControl.ThrowWaveDelayCnt = 0;
									 if(FRSControl.ThrowWaveTabIndex == 1)    //此周期需要开可控硅
									 {
											 HEATER_CONTROL_ON();        //发热丝开
											 FRSControl.ThrowWaveFlag = 0;
										   FRS_ON = 1;
										   FRSControl.activecnt =20;
									 }
									 else
									 {
											 HEATER_CONTROL_OFF();       //发热丝关
											 FRSControl.ThrowWaveFlag = 0;
//										   FRS_ON = 0;
									 }
							 }
				   }
					 else if(FRSControl.ACFrequency == AC60Hz)
					 {
							 if(FRSControl.ThrowWaveDelayCnt >= FRSControl.AC50HzThrowWaveDelayCnt)  //丢波延时  //载波22K 60Hz8.333ms（183.3）
							 {
									 FRSControl.ThrowWaveDelayCnt = 0;
									 if(FRSControl.ThrowWaveTabIndex == 1)    //此周期需要开可控硅
									 {
											 HEATER_CONTROL_ON();        //发热丝开
											 FRSControl.ThrowWaveFlag = 0;
									 }
									 else
									{
											 HEATER_CONTROL_OFF();       //发热丝关
											 FRSControl.ThrowWaveFlag = 0;
									 }
							 }
					 }
					 else
					 {
							 HEATER_CONTROL_OFF();           //发热丝关
							 FRSControl.ThrowWaveDelayCnt = 0;
							 FRSControl.ThrowWaveFlag = 0;
					 }
			 }
	 }
	 else
	 {
			 HEATER_CONTROL_OFF();           //发热丝关
		   FRSControl.ThrowWaveDelayCnt = 0;
			 FRSControl.ThrowWaveFlag = 0;
	 }
	}

	  if(FRS_ON)
		{
		 if(FRSControl.activecnt >=1)
		 {
		  FRSControl.activecnt--;
		 }
		  if(FRSControl.activecnt==0)
			{
			 HEATER_CONTROL_OFF();  
				FRS_ON = 0;
				
			}
		}
		if((FRSControl.CrossZeroVoltageCnt < 12)&&(FRSControl.CrossZeroVoltageCnt2 < 12))
		{
//			GPIO_SetBits(GPIO0,GPIO_Pin_5);
			if(AcDownCD1ms == 0)
			FRSControl.CrossDownAcState=0;
		}
		else
		{
//			GPIO_ResetBits(GPIO0,GPIO_Pin_5);
			FRSControl.CrossZeroVoltageCnt = 12;
//			FRSControl.CrossZeroVoltageCnt2 = 12;
			FRSControl.CrossDownAcState=1;
		}
		if((FRSControl.CrossDownAcStateLast == 1) && (FRSControl.CrossDownAcState == 0))
		{
			stru_Faults.R = 0;
			PWMOutputs(MCPWM0, ENABLE);
		 MCPWM_EIF = BIT4 | BIT5;
		}
		else 	if((FRSControl.CrossDownAcStateLast == 0) && (FRSControl.CrossDownAcState == 1))
		{
			AcDownCD1ms = 500;		//检测掉电幅值 重新上电CD。 单位1ms
		}
		if(AcDownCD1ms)AcDownCD1ms--;
			FRSControl.CrossDownAcStateLast=FRSControl.CrossDownAcState;
			
		FRSControl.CrossZeroState = ZERO_SCR();    //读取过零信号电平
		
//		if(FRSControl.CrossZeroVoltage>10000)
//		{
//			FRSControl.CrossZeroVoltageCnt++;
//		//	FRSControl.CrossZeroState = 0;			
//		}
//		else if(FRSControl.CrossZeroVoltage <4000)
//		{
//		//	FRSControl.CrossZeroState = 1;
//			FRSControl.CrossZeroVoltageCnt=0;
//		}
//		if(FRSControl.CrossZeroVoltage<4000)
//		{
//			FRSControl.CrossZeroState = 1;	
//		}
//		else if(FRSControl.CrossZeroVoltage > 10000)
//		{
//			FRSControl.CrossZeroState = 0;
//		}
		if(FRSControl.CrossZeroState)
		{
			FRSControl.CrossZeroVoltageCnt++;
			FRSControl.CrossZeroVoltageCnt2=0;
		//	FRSControl.CrossZeroState = 0;			
		}
		else if(FRSControl.CrossZeroState==0)
		{
		//	FRSControl.CrossZeroState = 1;
			FRSControl.CrossZeroVoltageCnt2++;
			FRSControl.CrossZeroVoltageCnt=0;
		}
		FRSControl.CrossZeroVoltageCnt1++;
		if((FRSControl.CrossZeroStateLast == 0) && (FRSControl.CrossZeroState == 1))
		{
//		   FRSControl.ACFrequencyDetectCnt = 0;
			 FRSControl.CrossZeroPosedge = 0;  //发生过零信号上升沿标志
			 FRSControl.CrossZeroMsCnt=FRSControl.CrossZeroVoltageCnt1;
			FRSControl.CrossZeroVoltageCnt1=0;
		}
		if((FRSControl.CrossZeroStateLast == 1) && (FRSControl.CrossZeroState == 0))
		{
//		   FRSControl.ACFrequencyDetectCnt = 0;
//			 FRSControl.CrossZeroPosedge = 0;  //发生过零信号上升沿标志
		}
		FRSControl.CrossZeroStateLast = FRSControl.CrossZeroState;
	 
}


/*****************************************************************************
 * Function:     void HeaterTemperature_Control(void)
 * Description:  发热丝温度控制
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
u8 xxxx = 0;
s16 testtemp=32000;
void HeaterTemperature_Control(void)
{
	if(hairmode<=1)																	//常风模式
	{
		if(iTargetGear==0)
		{
			if(TempGear ==1)																	//80°
			{
				FRSControl.TargetTemperature =19000;
				
				FRSControl.ThrowWaveBase = 16;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 14;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =18;         //丢波上限值
				//FRSControl.ThrowWaveCnt =10;	
			}
			else if(TempGear==2)															//95°
			{
				FRSControl.TargetTemperature =14000;
				FRSControl.ThrowWaveBase = 20;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 18;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =23;         //丢波上限值		
			}
			else
			{
				FRSControl.TargetTemperature =0;
				FRSControl.ThrowWaveBase = 0;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 0;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =0;         //丢波上限值							
			}
		}
		else	if(iTargetGear==1)
		{
			if(TempGear ==1)																	//80°
			{
				FRSControl.TargetTemperature =18000;
				
				FRSControl.ThrowWaveBase = 18;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 16;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =20;         //丢波上限值
				//FRSControl.ThrowWaveCnt =10;	
			}
			else if(TempGear==2)															//95°
			{
				FRSControl.TargetTemperature =14000;
				FRSControl.ThrowWaveBase = 25;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 22;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =27;         //丢波上限值		
			}
			else
			{
				FRSControl.TargetTemperature =0;
				FRSControl.ThrowWaveBase = 0;            //标定好的丢波基础值 
				FRSControl.ThrowWaveLimitMin = 0;        //丢波下限值
				FRSControl.ThrowWaveLimitMax =0;         //丢波上限值							
			}
		}
	}
	else if(hairmode==2)														//儿童模式			45°
	{
			FRSControl.TargetTemperature =27000;			
			FRSControl.ThrowWaveBase = 5;            //标定好的丢波基础值 
			FRSControl.ThrowWaveLimitMin = 3;        //丢波下限值
			FRSControl.ThrowWaveLimitMax =7;         //丢波上限值
			//FRSControl.ThrowWaveCnt =10;	
	}
	else if(hairmode==3)														//速干模式			95°
	{
			FRSControl.TargetTemperature =14000;			
			FRSControl.ThrowWaveBase = 25;            //标定好的丢波基础值 
			FRSControl.ThrowWaveLimitMin = 22;        //丢波下限值
			FRSControl.ThrowWaveLimitMax =27;         //丢波上限值
			//FRSControl.ThrowWaveCnt =10;	
	}
		FRSControl.HEATER_NTCTemperature = GET_NTC_CHEAK_CHANNEL;
	  if((FRSControl.ThrowWaveCnt > FRSControl.ThrowWaveLimitMax) || (FRSControl.ThrowWaveCnt < FRSControl.ThrowWaveLimitMin))
		{
		   FRSControl.ThrowWaveCnt = FRSControl.ThrowWaveBase;
		}
	
		if(FRSControl.HEATER_NTCTemperature > FRSControl.TargetTemperature)
		{   
			  if(FRSControl.ThrowWaveCnt < FRSControl.ThrowWaveLimitMax)
				{   
					  if(FRSControl.ThrowWaveCnt < 49)
						{
                FRSControl.ThrowWaveCnt ++;
						}
				}
		}
		else if (FRSControl.HEATER_NTCTemperature < FRSControl.TargetTemperature)
		{
			  if(FRSControl.ThrowWaveCnt > FRSControl.ThrowWaveLimitMin)
				{
						if(FRSControl.ThrowWaveCnt > 0)
						{
                FRSControl.ThrowWaveCnt --;
						}
				}
		}
}
