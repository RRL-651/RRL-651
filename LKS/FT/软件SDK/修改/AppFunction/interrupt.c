/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： interrupt.c
 * 文件标识：
 * 内容摘要： 中断服务程序文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet
 * 完成日期： 2020年8月5日
 *
 * 修改记录1：
 * 修改日期：2020年8月5日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet
 * 修改内容：创建
 *
 *******************************************************************************/
#include "hardware_config.h"
#include "global_variable.h"
#include "fault_detection.h"
#include "segger_rtt.h"
#include "PowerCalculation.h"
#include "HeatControl.h"

//HEAT_CONTROL FRSControl;
extern  s16 Mag_nCurr;
void HeaterControl(void);

#if (RTT_FUNCTION == FUNCTION_ON)
struct
{
    s16 data0;
    s32 data1;
    s16 data2;
    s16 data3;
} Rttstru;
#endif

#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT) || (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)\
||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
/*******************************************************************************
 函数名称：    void ADC_IRQHandler(void)
 功能描述：    ADC0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
 u8 test425=0;
 s16 test989=0;
void ADC_IRQHandler(void)
{
    ADC_IF |= BIT1 | BIT0;

    #if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)
    Hall_ElecAnglePWM_Process(&struHallProcess); /* HALL角度处理 */
    #endif

    FOC_Model(&struFOC_CtrProc);              /* FOC电流内环 */

    struFOC_CtrProc.nSys_TimerPWM++;          /* PWM时基计数器 */

    struTaskScheduler.bPWM_UpdateFlg = 1;     /* PWM更新标志 */

    struFOC_CurrLoop.nBusVoltage = GET_BUS_VOL_ADC_RESULT; /* 母线电压采样 */
	
	  DcVoltPerUnitCalcInt(struFOC_CurrLoop.nBusVoltage); 

   // if(struFOC_CtrProc.eSysState == RUN)
    {
//        FaultCurrentCheck(&struFOC_CurrLoop.mStatCurrUVW, &struFaultCurrentTime);  //过流检测
//        CurrentAmplitudeCalc(&struFOC_CurrLoop.mStatCurrUVW, &struCurrentAmplitude, &struImaxCurrent);
			 //FaultCurrentCheck(Mag_nCurr,stru_FaultValue.nOverCurrent); 
			if(ABS(struFOC_CurrLoop.mStatCurrDQ.nAxisQ) >= stru_FaultValue.nOverCurrent)
			{
			            PWMOutputs(MCPWM0, DISABLE);
            stru_Faults.B.SoftCurretError = 1;
			}
    }
		
//    FGScan(struFluxOB_Param.wElectAngle >> 16);

    #if(RTT_FUNCTION == FUNCTION_ON)
    {
        Rttstru.data0 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseU);   //开环角度
        Rttstru.data1 = (struMotorSpeed.wSpeedEst);    //估算角度
        //        Rttstru.data2 = (struFOC_CtrProc.eSysState);       //实际角度

        SEGGER_RTT_Write(1, &Rttstru, 6);
    }
    #endif
//		test989=GET_AC_ZERO_CHEAK_CHANNEL;
//		if(FRSControl.ACFrequencyDetectCnt < 300 )    //载波22K 50Hz 220=10ms  60Hz 183.3=8.33ms
//		{
//				FRSControl.ACFrequencyDetectCnt ++;
//			//GPIO_ResetBits(GPIO0,GPIO_Pin_5);
//		}
//		else
//		{
//				FRSControl.ACFrequencyDetectCnt = 300; //载波22K  300=13.636ms
//			
//			  FRSControl.CrossZeroPosedgeFlag = 0;  //没发生过零信号上升沿标志 //拨动开关断开电源
//	  //	GPIO_SetBits(GPIO0,GPIO_Pin_5);
////			  struFOC_CtrProc.bMC_RunFlg = 0;
//		}
////     if(test425==0)
////		 {
////		 GPIO_ResetBits(GPIO0,GPIO_Pin_5);
////		 }
////		 else
////		 {
////		  GPIO_SetBits(GPIO0,GPIO_Pin_5);
////		 }
//		
//		FRSControl.CrossZeroState = ZERO_SCR();    //读取过零信号电平
//		
		//if((FRSControl.CrossZeroStateLast == 0) && (FRSControl.CrossZeroState == 1))
//		{
//		   FRSControl.ACFrequencyDetectCnt = 0;
//			 FRSControl.CrossZeroPosedgeFlag = 1;  //发生过零信号上升沿标志
//		}
//		
//		FRSControl.CrossZeroStateLast = FRSControl.CrossZeroState;
}
#endif

#if(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
/*******************************************************************************
 函数名称：    void MCPWM_IRQHandler(void)
 功能描述：    MCPWM中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_IRQHandler(void)
{
    MCPWM_IF0 = BIT1 | BIT0;

    struTaskScheduler.bPWM_UpdateFlg = 1;     /* PWM更新标志 */

    struFOC_CurrLoop.nBusVoltage = GET_BUS_VOL_ADC_RESULT; /* 母线电压采样 */

    FOC_Model(&struFOC_CtrProc);              /* FOC电流内环 */


    if(struFOC_CtrProc.eSysState == RUN)
    {
        //        FaultCurrentCheck(&struFOC_CurrLoop.mStatCurrUVW);  //过流检测
        //    PowerCalc(&struFOC_CurrLoop.mStatCurrDQ, &struFOC_CurrLoop.mStatVoltDQ, &struPower);
        //    struCurrentAmplitude.bTheta = (struFluxOB_Param.wElectAngle >> 16);
        CurrentAmplitudeCalc(&struFOC_CurrLoop.mStatCurrUVW, &struCurrentAmplitude, &struImaxCurrent);
    }

    #if(RTT_FUNCTION == FUNCTION_ON)
    {
        Rttstru.data0 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseU);   //开环角度
        Rttstru.data1 = (struFOC_CurrLoop.mStatCurrUVW.nPhaseV);    //估算角度
        Rttstru.data2 = (struFluxOB_Param.wElectAngle >> 16);       //实际角度
        Rttstru.data3 = (struFluxOB_Param.wElectAngle >> 16);       //实际角度

        SEGGER_RTT_Write(1, &Rttstru, 8);
    }
    #endif
}
#else
/*******************************************************************************
 函数名称：    void MCPWM_IRQHandler(void)
 功能描述：    MCPWM中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_IRQHandler(void)
{
    if((MCPWM_EIF & BIT4) || (MCPWM_EIF & BIT5))
    {
        PWMOutputs(MCPWM0, DISABLE);
        MCPWM_EIF = BIT4 | BIT5;
        stru_Faults.B.HardCurretError = 1;// 硬件过流标志位置1
    }
}
/*******************************************************************************
 函数名称：    void MCPWM_IRQHandler(void)
 功能描述：    MCPWM中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM1_IRQHandler(void)
{
}
#endif

/*******************************************************************************
 函数名称：    void HALL_IRQHandler(void)
 功能描述：    HALL中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void HALL_IRQHandler(void)
{
    #if (ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR)
    HALL_IRQProcess(HALL, &struHallProcess);
    #endif

}


/*******************************************************************************
 函数名称：    void TIMER0_IRQHandler(void)
 功能描述：    TIMER0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER0_IRQHandler(void)
{
    PWMScan();
}

/*******************************************************************************
 函数名称：    void TIMER1_IRQHandler(void)
 功能描述：    TIMER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void TIMER1_IRQHandler(void)
{
    /* 时基500us */
    UTIMER1_IF |= TIM_IRQ_IF_ZC;

    struTaskScheduler.bTimeCnt1ms++;
    struTaskScheduler.nTimeCnt10ms ++;
		struTaskScheduler.nTimeCnt100ms ++;
    struTaskScheduler.nTimeCnt500ms++;
}

/*******************************************************************************
 函数名称：    void ENCODER0_IRQHandler(void)
 功能描述：    ENCODER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ENCODER0_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void ENCODER0_IRQHandler(void)
 功能描述：    ENCODER1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ENCODER1_IRQHandler(void)
{

}


/*******************************************************************************
 函数名称：    void CMP_IRQHandler(void)
 功能描述：    比较器中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void CMP_IRQHandler(void)
{
    CMP_IF = BIT0 | BIT1;

    if(CMP_IF & (BIT1))
    {
        volatile u8 t_bi, t_bcnt;

        t_bcnt = 0;
        for(t_bi = 0; t_bi < 5; t_bi++)
        {
            if(CMP_DATA & BIT1) /* BIT0 CMP0 OUT Flag| BIT1 CMP1 OUT Flag */
            {
                t_bcnt ++;
            }
        }

        if(t_bcnt >= 1)
        {
            PWMOutputs(MCPWM0, DISABLE);
            MCPWM_EIF = BIT4 | BIT5;
            stru_Faults.B.HardCurretError = 1;// 硬件过流标志位置1
        }
    }
}



/*******************************************************************************
 函数名称：    void UART_IRQHandler(void)
 功能描述：    UART0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void UART1_IRQHandler(void)
 功能描述：    UART1中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void UART1_IRQHandler(void)
{


}

/*******************************************************************************
 函数名称：    void SysTick_Handler(void)
 功能描述：    系统滴答定时中断
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SysTick_Handler(void)
{

}

/*******************************************************************************
 函数名称：    void SleepTimer_IRQHandler(void)
 功能描述：    休眠唤醒中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SleepTimer_IRQHandler(void)
{
    while(1);
}

/*******************************************************************************
 函数名称：    void GPIO_IRQHandler(void)
 功能描述：    GPIO中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void GPIO_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void I2C0_IRQHandler(void)
 功能描述：    I2C0中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void I2C_IRQHandler(void)
{

}

/*******************************************************************************
 函数名称：    void SPI_IRQHandler(void)
 功能描述：    SPI中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SPI_IRQHandler(void)
{

}
/*******************************************************************************
 函数名称：    void DMA_IRQHandler(void)
 功能描述：    DMA中断处理函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void DMA_IRQHandler(void)
{

}
void WAKE_IRQHandler(void)
{

}
void SW_IRQHandler(void)
{
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */


