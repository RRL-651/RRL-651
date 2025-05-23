/*******************************************************************************
 * 版权所有 (C)2016, LINKO Semiconduct
 *
 * 文件名称： FOC.Drive.c
 * 文件标识：
 * 内容摘要： 电机矢量控制电流内环及关键控制算法
 * 其它说明： 无
 * 当前版本： V 2.0
 * 作    者： WhenCai Zhao Howlet Li
 * 完成日期： 2020年9月10日
 *
 * 修改记录1：
 *    修改日期：2020年9月10日
 *    版 本 号：V2.0
 *    修 改 人：Howlet Li
 *    修改内容：格式整理
 *
 *******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "FOC_Drive.h"
#include "global_variable.h"
#include "hardware_config.h"
#include "mc_math.h"
#include "MC_Parameter.h"


#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_1SHUNT)
/*******************************************************************************
 函数名称：    stru_CurrPhaseUVW SVPWM_1ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
 功能描述：    单电阻采样算法根据SVPWM调制扇区，得到U, V相电流
 输入参数：    stru_FOC_CurrLoopDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
stru_CurrPhaseUVW SVPWM_1ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
{

    stru_Array_Def mADC_Result;
    stru_CurrPhaseUVW Local_Stator_Currents;
    s32 wAux;
    s16 hCurrA, hCurrB, hCurrC;

    u8 bCurrASamp = 0, bCurrBSamp = 0;

    GET_ADC_DATA(mADC_Result);
    switch (this->bSampCur1)
    {
        case SAMP_IA:

            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrA = sat(wAux, S16_MIN, S16_MAX);

            bCurrASamp = 1;
            break;
        case SAMP_IB:
            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrB = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;
        case SAMP_IC:
            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

            break;

        case SAMP_NIA:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrA = sat(wAux, S16_MIN, S16_MAX);

            bCurrASamp = 1;
            break;

        case SAMP_NIB:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrB = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;

        case SAMP_NIC:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

        case SAMP_OLDA:
            hCurrA = this->mStatCurrUVW.nPhaseU;
            bCurrASamp = 1;
            break;

        case SAMP_OLDB:
            hCurrB = this->mStatCurrUVW.nPhaseV;
            bCurrBSamp = 1;
            break;

        case SAMP_OLDC:
            hCurrC = this->mStatCurrUVW.nPhaseW;

            break;


        default:

            break;
    }

    GET_ADC1_DATA(mADC_Result);
    // Second sampling point
    switch (this->bSampCur2)
    {
        case SAMP_IA:
            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrA = sat(wAux, S16_MIN, S16_MAX);
            bCurrASamp = 1;
            break;
        case SAMP_IB:
            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrB = sat(wAux, S16_MIN, S16_MAX);
            bCurrBSamp = 1;
            break;
        case SAMP_IC:
            wAux = mADC_Result.nData0 - (s32)(this->nBusShuntOffset);
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

            break;
        case SAMP_NIA:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrA = sat(wAux, S16_MIN, S16_MAX);

            bCurrASamp = 1;
            break;

        case SAMP_NIB:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrB = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;

        case SAMP_NIC:
            wAux = (s32)(this->nBusShuntOffset) - mADC_Result.nData0;
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

            break;
        case SAMP_OLDA:
            hCurrA = this->mStatCurrUVW.nPhaseU;
            bCurrASamp = 1;
            break;

        case SAMP_OLDB:
            hCurrB = this->mStatCurrUVW.nPhaseU;
            bCurrBSamp = 1;
            break;

        case SAMP_OLDC:
            hCurrC = this->mStatCurrUVW.nPhaseU;
            break;

        default:

            break;
    }

    if (bCurrASamp == 0)
    {
        /* 饱和处理 */
        wAux = -hCurrB - hCurrC;
        hCurrA = sat(wAux, S16_MIN, S16_MAX);
    }
    if (bCurrBSamp == 0)
    {
        wAux = -hCurrA - hCurrC;
        hCurrB = sat(wAux, S16_MIN, S16_MAX);
    }


    Local_Stator_Currents.nPhaseU = hCurrA;
    Local_Stator_Currents.nPhaseV = hCurrB;

    return (Local_Stator_Currents);
}

/*******************************************************************************
 函数名称：    void ADC_NormalModeCFG(void)
 功能描述：    ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ADC_NormalModeCFG(void)
{

    ADC_CHN0 = ADC_1SHUNT_CURR_CH | (ADC_1SHUNT_CURR_CH << 4) | (ADC_1SHUNT_CURR_CH << 8) | (ADC_1SHUNT_CURR_CH << 12);
    ADC_CHN1 = ADC_BUS_VOL_CHANNEL | (ADC_TEMP_CHANNEL << 4);

}

void ADC_NormalModeCFG1(void)
{
 
    //ADC_CHN0 = ADC_1SHUNT_CURR_CH | (ADC_1SHUNT_CURR_CH << 4) | (ADC_BUS_VOL_CHANNEL << 8) | (ADC_1SHUNT_CURR_CH << 12);
    ADC_CHN0 = BEMF_CH_A | (ADC_BUS_VOL_CHANNEL << 4) | (BEMF_CH_B << 8) | (BEMF_CH_C << 12);
    ADC_CHN1 = ADC_BUS_VOL_CHANNEL | (ADC_BUS_CURR_CHANNEL << 4);
  
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = struFOC_CurrLoop.mVoltUVW_NegPWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

}

#endif

#if (CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_2SHUNT)
/*******************************************************************************
 函数名称：    stru_CurrPhaseUVW SVPWM_2ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
 功能描述：    根据SVPWM调制扇区，得到U, V相电流
 输入参数：    stru_FOC_CurrLoopDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
stru_CurrPhaseUVW SVPWM_2ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
{
    stru_Array_Def mADC_Result;
    stru_CurrPhaseUVW Local_Stator_Currents;
    s32 wAux;
    s16 hCurrA = 0, hCurrB = 0, hCurrC = 0;

    u8 bCurrASamp = 0, bCurrBSamp = 0;
    GET_ADC0_DATA(mADC_Result);
    hCurrA = (s32)(this->nPhaseAOffset) - mADC_Result.nData0;
    /* First sampling point */
    //    switch (this->bSampCur1)
    //    {
    //    case SAMP_IA:

    //        wAux = (s32)(this->nPhaseAOffset) - mADC_Result.nData0;
    //        //hCurrA = sat(wAux, S16_MIN, S16_MAX);

    //        //bCurrASamp = 1;
    //        break;

    //    case SAMP_IB:

    //        wAux = (s32)(this->nPhaseBOffset) - mADC_Result.nData0;
    //        hCurrB = sat(wAux, S16_MIN, S16_MAX);

    //        bCurrBSamp = 1;
    //        break;

    //    case SAMP_IC:

    //        wAux = (s32)(this->nPhaseCOffset) - mADC_Result.nData0;
    //        hCurrC = sat(wAux, S16_MIN, S16_MAX);

    //        bCurrBSamp = 1;
    //        break;
    //    case SAMP_NIA:
    //        hCurrA = this->mStatCurrUVW.nPhaseU;
    //        bCurrASamp = 1;

    //        break;
    //    case SAMP_NIB:
    //        hCurrB = this->mStatCurrUVW.nPhaseV;
    //        bCurrBSamp = 1;

    //        break;
    //    case SAMP_NIC:
    //        hCurrC = 0 - this->mStatCurrUVW.nPhaseU - this->mStatCurrUVW.nPhaseV;

    //        break;
    //    default:
    //        wAux = 0;
    //        break;
    //    }

    GET_ADC1_DATA(mADC_Result);
    hCurrB = (s32)(this->nPhaseBOffset) - mADC_Result.nData0;
    /* Second sampling point */
    //    switch (this->bSampCur2)
    //    {
    //    case SAMP_IA:
    //        wAux = (s32)(this->nPhaseAOffset) - mADC_Result.nData0;
    //        hCurrA = sat(wAux, S16_MIN, S16_MAX);

    //        bCurrASamp = 1;
    //        break;

    //    case SAMP_IB:

    //        wAux = (s32)(this->nPhaseBOffset) - mADC_Result.nData0;
    //        //hCurrB = sat(wAux, S16_MIN, S16_MAX);

    //       // bCurrBSamp = 1;
    //        break;

    //    case SAMP_IC:

    //        wAux = (s32)(this->nPhaseCOffset) - mADC_Result.nData0;
    //        hCurrC = sat(wAux, S16_MIN, S16_MAX);

    //        break;
    //    case SAMP_NIA:
    //        hCurrA = this->mStatCurrUVW.nPhaseU;
    //        bCurrASamp = 1;

    //        break;
    //    case SAMP_NIB:
    //        hCurrB = this->mStatCurrUVW.nPhaseV;
    //        bCurrBSamp = 1;

    //        break;
    //    case SAMP_NIC:
    //        hCurrC = 0 - this->mStatCurrUVW.nPhaseU - this->mStatCurrUVW.nPhaseV;

    //        break;
    //    default:
    //        wAux = 0;
    //        break;
    //    }
    //    if (bCurrASamp == 0)
    //    {   /* 饱和处理 hd */
    //        wAux = -hCurrB - hCurrC;
    //        hCurrA = sat(wAux, S16_MIN, S16_MAX);
    //    }
    //    if (bCurrBSamp == 0)
    //    {
    //        wAux = -hCurrA - hCurrC;
    //        hCurrB = sat(wAux, S16_MIN, S16_MAX);
    //    }

    #if (CHIP_PART_NUMBER == LKS32MC057D_V0)
    Local_Stator_Currents.nPhaseU = -hCurrA;
    #else
    Local_Stator_Currents.nPhaseU = hCurrA;
    #endif
    Local_Stator_Currents.nPhaseV = hCurrB;

    return (Local_Stator_Currents);
}

/*******************************************************************************
 函数名称：    void ADC_NormalModeCFG(void)
 功能描述：    ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if	(PowerUP_Motor_Start_Dir == CW)
void ADC_NormalModeCFG(void)
{
    ADC_CHN0 = ADC_CURRETN_A_CHANNEL | (ADC_CURRETN_B_CHANNEL << 4) | (ADC_BUS_VOL_CHANNEL << 8) | (AC_ZERO_CHEAK_CHANNEL << 12);
    ADC_CHN1 = NTC_CHEAK_CHANNEL | (ADC_1SHUNT_CURR_CH << 4);
}
#elif (PowerUP_Motor_Start_Dir == CCW)
void ADC_NormalModeCFG(void)
{
    ADC_CHN0 = ADC_CURRETN_B_CHANNEL | (ADC_CURRETN_A_CHANNEL << 4) | (ADC_BUS_VOL_CHANNEL << 8) | (AC_ZERO_CHEAK_CHANNEL << 12);
    ADC_CHN1 = NTC_CHEAK_CHANNEL | (ADC_1SHUNT_CURR_CH << 4);
}
#endif
void ADC_NormalModeCFG1(void)
{
    ADC_CHN0 = BEMF_CH_A | (BEMF_CH_B << 4) | (ADC_BUS_VOL_CHANNEL << 8) | (BEMF_CH_C << 12);    //BEMF_CH_B
    ADC_CHN1 = ADC_BUS_VOL_CHANNEL | (ADC_BUS_VOL_CHANNEL << 4);
  
}

/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
#if	(PowerUP_Motor_Start_Dir == CW)
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

}
#elif (PowerUP_Motor_Start_Dir == CCW)
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

}
#endif
#endif


#if ((CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_3SHUNT)||(CURRENT_SAMPLE_TYPE == CURRENT_SAMPLE_MOSFET))
/*******************************************************************************
 函数名称：    stru_CurrPhaseUVW SVPWM_3ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
 功能描述：    根据SVPWM调制扇区，得到U, V相电流
 输入参数：    stru_FOC_CurrLoopDef *this  结构体指针
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
stru_CurrPhaseUVW SVPWM_3ShuntGetPhaseCurrent(stru_FOC_CurrLoopDef *this)
{
    stru_Array_Def mADC_Result;
    stru_CurrPhaseUVW Local_Stator_Currents;
    s32 wAux;
    s16 hCurrA = 0, hCurrB = 0, hCurrC = 0;

    u8 bCurrASamp = 0, bCurrBSamp = 0;
    GET_ADC_DATA(mADC_Result);
    /* First sampling point */
    switch (this->bSampCur1)
    {
        case SAMP_IA:

            wAux = (s32)(this->nPhaseAOffset) - mADC_Result.nData0;
            hCurrA = sat(wAux, S16_MIN, S16_MAX);

            bCurrASamp = 1;
            break;

        case SAMP_IB:

            wAux = (s32)(this->nPhaseBOffset) - mADC_Result.nData0;
            hCurrB = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;

        case SAMP_IC:

            wAux = (s32)(this->nPhaseCOffset) - mADC_Result.nData0;
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;
        case SAMP_NIA:
            hCurrA = this->mStatCurrUVW.nPhaseU;
            bCurrASamp = 1;

            break;
        case SAMP_NIB:
            hCurrB = this->mStatCurrUVW.nPhaseV;
            bCurrBSamp = 1;

            break;
        case SAMP_NIC:
            hCurrC = 0 - this->mStatCurrUVW.nPhaseU - this->mStatCurrUVW.nPhaseV;

            break;
        default:
            wAux = 0;
            break;
    }

    GET_ADC1_DATA(mADC_Result);
    /* Second sampling point */
    switch (this->bSampCur2)
    {
        case SAMP_IA:
            wAux = (s32)(this->nPhaseAOffset) - mADC_Result.nData0;
            hCurrA = sat(wAux, S16_MIN, S16_MAX);

            bCurrASamp = 1;
            break;

        case SAMP_IB:

            wAux = (s32)(this->nPhaseBOffset) - mADC_Result.nData0;
            hCurrB = sat(wAux, S16_MIN, S16_MAX);

            bCurrBSamp = 1;
            break;

        case SAMP_IC:

            wAux = (s32)(this->nPhaseCOffset) - mADC_Result.nData0;
            hCurrC = sat(wAux, S16_MIN, S16_MAX);

            break;
        case SAMP_NIA:
            hCurrA = this->mStatCurrUVW.nPhaseU;
            bCurrASamp = 1;

            break;
        case SAMP_NIB:
            hCurrB = this->mStatCurrUVW.nPhaseV;
            bCurrBSamp = 1;

            break;
        case SAMP_NIC:
            hCurrC = 0 - this->mStatCurrUVW.nPhaseU - this->mStatCurrUVW.nPhaseV;

            break;
        default:
            wAux = 0;
            break;
    }
    if (bCurrASamp == 0)
    {
        /* 饱和处理 hd */
        wAux = -hCurrB - hCurrC;
        hCurrA = sat(wAux, S16_MIN, S16_MAX);
    }
    if (bCurrBSamp == 0)
    {
        wAux = -hCurrA - hCurrC;
        hCurrB = sat(wAux, S16_MIN, S16_MAX);
    }

    Local_Stator_Currents.nPhaseU = hCurrA;
    Local_Stator_Currents.nPhaseV = hCurrB;

    return (Local_Stator_Currents);
}

/*******************************************************************************
 函数名称：    void ADC_NormalModeCFG(void)
 功能描述：    ADC正常工作模式通道配置
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void ADC_NormalModeCFG(void)
{
    ADC_CHN0 = ADC_CURRETN_A_CHANNEL | (ADC_CURRETN_B_CHANNEL << 4) | (ADC_CURRETN_A_CHANNEL << 8) | (ADC_CURRETN_B_CHANNEL << 12);
    ADC_CHN1 = ADC_BUS_VOL_CHANNEL | (ADC_BUS_VOL_CHANNEL << 4);

    struFOC_CurrLoop.ADC_A_B_CurrentSamp = ADC_CURRETN_A_CHANNEL | (ADC_CURRETN_B_CHANNEL << 4) | (ADC_CURRETN_A_CHANNEL << 8) | (ADC_CURRETN_B_CHANNEL << 12);
    struFOC_CurrLoop.ADC_A_C_CurrentSamp = ADC_CURRETN_A_CHANNEL | (ADC_CURRETN_C_CHANNEL << 4) | (ADC_CURRETN_A_CHANNEL << 8) | (ADC_CURRETN_C_CHANNEL << 12);
    struFOC_CurrLoop.ADC_B_C_CurrentSamp = ADC_CURRETN_B_CHANNEL | (ADC_CURRETN_C_CHANNEL << 4) | (ADC_CURRETN_B_CHANNEL << 8) | (ADC_CURRETN_C_CHANNEL << 12);
}


/*******************************************************************************
 函数名称：    void MCPWM0_RegUpdate(void)
 功能描述：    加载MCPWM模块占空比值，加载MCPWM模块ADC触发点寄存器值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2020/8/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void MCPWM0_RegUpdate(void)
{
    MCPWM_TH00 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;
    MCPWM_TH01 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseU;

    MCPWM_TH10 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;
    MCPWM_TH11 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseV;

    MCPWM_TH20 = -struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;
    MCPWM_TH21 = struFOC_CurrLoop.mVoltUVW_PWM.nPhaseW;

}

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* ------------------------------END OF FILE------------------------------------ */

