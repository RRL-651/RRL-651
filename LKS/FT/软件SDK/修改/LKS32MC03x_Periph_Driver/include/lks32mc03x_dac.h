/*******************************************************************************
 * ��Ȩ���� (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� lks32mc03x_dac.h
 * �ļ���ʶ��
 * ����ժҪ�� DAC������������ͷ�ļ�
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Zhujie
 * ������ڣ� 2022��4��18��
 *
 *******************************************************************************/

#ifndef _LKS32MC03x_DAC_H_
#define _LKS32MC03x_DAC_H_

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x.h"
#include "basic.h"
typedef struct
{	
	  uint8_t DACOUT_EN;          /* DAC�����IOʹ�ܣ�0����ʹ�ܣ�1��ʹ�ܡ� */
	  uint8_t DAC_VERSION;        /* 03оƬ�汾�ţ�1��ʾA�汾��2��ʾB�汾���������ã����� */
	  uint8_t DAC_GAIN;           /* DAC����ѡ��0��3.0V��1��4.8V��ע��03A�汾ֻ��3.0Vһ�����̣�B�汾��3.0V��4.8V���� */                   
}DAC_InitTypeDef;

typedef struct
{	
	  uint8_t VersionAndDACGain; /* оƬ�ͺź�DAC���� 1&2��Ӧ3.0V���� 3��Ӧ4.8V���� */
	  int16_t DAC_AMC;           /* DAC����У׼ֵ */
	  int16_t DAC_DC;            /* DACƫ��У׼ֵ */                   
}DAC_CheckTypeDef;

#define DAC_RANGE_3V0                  0                       /* DAC 3.0V���� */
#define DAC_RANGE_4V8                  1                       /* DAC 4.8V���� */

void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);/* DAC�ṹ���ʼ�� */
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct);      /* DAC��ʼ�� */
void DAC_OutputValue(uint32_t DACValue);             /* DAC�����ֵ����--������ */
void DAC_OutputVoltage(uint16_t DACVoltage);         /* DAC���ģ������ֵ����--ģ���� */

#endif

