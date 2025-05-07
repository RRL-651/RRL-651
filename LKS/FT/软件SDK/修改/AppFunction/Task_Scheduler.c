/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： Time_Process.c
 * 文件标识：
 * 内容摘要： 定时相关函数
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Howlet Li
 * 完成日期： 2020年8月16日
 *
 * 修改记录1：
 * 修改日期：2020年8月16日
 * 版 本 号：V 1.0
 * 修 改 人：Howlet Li
 * 修改内容：创建
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "basic.h"
#include "Global_Variable.h"
#include "math.h"
#include "Time_Process.h"
#include "hardware_config.h"
#include "fault_detection.h"
#include "PowerCalculation.h"
#include "USER_APP.h"
#include "HeatControl.h"
void Sys_State_Machine(void);
void StartUpProcess(void);

/*******************************************************************************
 函数名称：    void Task_Scheduler(void)
 功能描述：    按时间片任务调度函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void Task_Scheduler(void)
{
    volatile u32 t_data;

    if (struTaskScheduler.bTimeCnt1ms >= TASK_SCHEDU_1MS)
    {
        /* 1毫秒事件，任务调度 */

        struTaskScheduler.bTimeCnt1ms = 0;

        SetTime_CountDown();  /* 倒计数函数计时处理 */

        FaultCheck();
				USER_APP_vTick1ms();
			  GetVdcSpeed();  //0-1-2档转速
        if(stru_Faults.R != 0)   //出现故障则进入FAULT状态
        {
            struFOC_CtrProc.eSysState = FAULT;
        }

//        PWMDutyScan();
//        PWMSpeedScan();
				
//		    if(struFOC_CtrProc.bMC_RunFlg == 0)
//				{
//					  if(GPIO_ReadInputDataBit(GPIO1, GPIO_Pin_6) != 1)
//						{
//							 struFOC_CtrProc.bMC_RunFlg = 1;
//						}
//			  }
//				else
//				{
//						if(GPIO_ReadInputDataBit(GPIO1, GPIO_Pin_4) != 1)
//						{
//							 struFOC_CtrProc.bMC_RunFlg = 0;
//						}
//				}

        
        Sys_State_Machine(); /* 电机0状态机调度 */

        DcVoltPerUnitCalc(struFOC_CurrLoop.nBusVoltage);  /* 直流母线电压标幺化处理 */
        
//        PowerCalc(&struFOC_CurrLoop.mStatCurrDQ, &struFOC_CurrLoop.mStatVoltDQ, &struPower);

    }

    if (struTaskScheduler.nTimeCnt10ms >= TASK_SCHEDU_10MS)
    {
        /* 10毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt10ms = 0;
        #if ((ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) || (ROTOR_SENSOR_TYPE == ROTOR_HALL2SENSORLESS))
        Hall_learn_Process();   /* Hall自学习算法 */
        #endif
    }
    if (struTaskScheduler.nTimeCnt100ms >= TASK_SCHEDU_100MS)
    {
        /* 100毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt100ms = 0;
			
			#if (TEMP_CONSTANT_FUNCTION == FUNCTION_ON)
			  if(FRSControl.TurnOnOffFlag == 1)   //发热丝正常工作
				{
			     HeaterTemperature_Control();  //发热丝温度控制
				}
			#endif
    }
		
		
		
    if (struTaskScheduler.nTimeCnt500ms >= TASK_SCHEDU_500MS)
    {
        /* 500毫秒事件，任务调度 */
        struTaskScheduler.nTimeCnt500ms = 0;
			#ifdef  MemoryMode //lgh
					vLoadForFlashing();
		  #endif
    }

    if(struTaskScheduler.bPWM_UpdateFlg)
    {
        /* 每个PWM周期更新一次 */
        struTaskScheduler.bPWM_UpdateFlg = 0;

        #if ((ROTOR_SENSOR_TYPE == ROTOR_HALL_SENSOR) || (ROTOR_SENSOR_TYPE == ROTOR_HALL2SENSORLESS))
        Verify_Hall_State(HALL, &struHallProcess);  /* hall 冗余检测 */
        #endif

    }

}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    软件延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;

    for(t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __nop();
    }
}


/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */



