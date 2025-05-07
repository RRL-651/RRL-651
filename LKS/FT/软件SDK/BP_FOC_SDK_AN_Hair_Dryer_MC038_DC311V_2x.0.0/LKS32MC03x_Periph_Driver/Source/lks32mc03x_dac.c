/*******************************************************************************
 * ��Ȩ���� (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� lks32mc03x_dac.c
 * �ļ���ʶ��
 * ����ժҪ�� DAC������������
 * ����˵���� ��
 * ��ǰ�汾�� V 1.0
 * ��    �ߣ� Zhu Jie
 * ������ڣ� 2022��4��18��
 *
 *******************************************************************************/
#include "lks32mc03x_dac.h"
#include "string.h"
#include "lks32mc03x_nvr.h"
#include "global_variable.h"
DAC_CheckTypeDef Stru_DAC_CHECK;
/*******************************************************************************
 �������ƣ�    void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
 ����������    DAC�ṹ���ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/04/18     V1.0           Zhu Jie              ����
 *******************************************************************************/
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct)
{
    memset(DAC_InitStruct, 0, sizeof(DAC_InitTypeDef));
}
/*******************************************************************************
 �������ƣ�    void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
 ����������    DAC��ʼ��
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    03xDAC��AB�汾�����̿�ѡ Aֻ��3.0V��B�汾��3.0��4.8V
               ��ʼ������ʱֻ��Ҫѡ�����̼��ɣ���ΪоƬΪB�汾����4.8V������Ч��
               ��оƬΪA�汾����ֻ��ʹ��3.0V���̣�4.8V������Ч
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/04/18      V1.0          Zhu Jie           ����
 -----------------------------------------------------------------------------
 2022/10/27      V2.0          Zhu Jie           �޸�
 *******************************************************************************/
void DAC_Init(DAC_InitTypeDef* DAC_InitStruct)
{
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_DAC, ENABLE);  /* DAC ʱ��ʹ�� */
	
	  DAC_InitStruct->DAC_VERSION = REG32(0x40000004); /* ��ȡ03оƬ�汾�� 1 ΪA�汾��2ΪB�汾 */
	
	  SYS_WR_PROTECT = 0x7a83;  /* �����Ĵ���д���� */
	
	  SYS_AFE_REG1 |= (DAC_InitStruct->DACOUT_EN << 1);/* DAC�����IO��ʹ������ */
	  
	  SYS_WR_PROTECT = 0xffff;  /* �����Ĵ���д���� */
	
		if ((DAC_InitStruct->DAC_VERSION) == 1)/* ����DAC 3.0V����У��ֵ */
		{
			  Stru_DAC_CHECK.VersionAndDACGain = 1;
				Stru_DAC_CHECK.DAC_AMC = (Read_Trim(0x000001c0)&0xFFFF);
				Stru_DAC_CHECK.DAC_DC  = (Read_Trim(0x000001c4)&0xFFFF);
			  
		}
		else if (DAC_InitStruct->DAC_VERSION == 2)
		{
	      if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_3V0)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 2;
				    Stru_DAC_CHECK.DAC_AMC = (Read_Trim(0x000001c0)&0xFFFF);
				    Stru_DAC_CHECK.DAC_DC  = (Read_Trim(0x000001c4)&0xFFFF);
				}
				else if(DAC_InitStruct->DAC_GAIN == DAC_RANGE_4V8)
				{
					  Stru_DAC_CHECK.VersionAndDACGain = 3;
				    Stru_DAC_CHECK.DAC_AMC = ((Read_Trim(0x000001c0)&0xFFFF0000) >> 16);
				    Stru_DAC_CHECK.DAC_DC  = ((Read_Trim(0x000001c4)&0xFFFF0000) >> 16);
				}
		}
}

/*******************************************************************************
 �������ƣ�    void DAC_OutputValue(uint32_t DACValue)
 ����������    DAC�����������ֵ����
 �����ı�    ��
 ���������    ��
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    03xDAC���̷�AB�棬A��ֻ��3.0Vһ�����̣�B����3.0V��4.8V�������̿�ѡ 
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/04/18     V1.0           Zhu Jie              ����
 -----------------------------------------------------------------------------
 2022/10/27     V2.0           Zhu Jie              �޸�
 *******************************************************************************/
void DAC_OutputValue(uint32_t DACValue)
{
	  s16 temp1 = 0;
	
	  if(DACValue >=255) /* �޷� */
		{
		    DACValue = 255;
		}
		
		temp1 = (s16)(DACValue * Stru_DAC_CHECK.DAC_AMC >> 9 )+ (s16)Stru_DAC_CHECK.DAC_DC;
		
		if(temp1 < 0)
		{
		  temp1 = 0;
		}
		else if(temp1 > 255)
		{
		  temp1 = 255;
		}	
	  SYS_AFE_DAC = (u32)temp1;
}

/*******************************************************************************
 �������ƣ�    void DAC_OutputVoltage(uint32_t DACVoltage)
 ����������    DAC���ģ������ֵ����
 �����ı�    ��
 ���������    DACVoltageΪQ12��ʽ,��Χ0~4096��ӦDAC���0~3V
 ���������    ��
 �� �� ֵ��    ��
 ����˵����    03xDAC���̷�AB�棬A��ֻ��3.0Vһ�����̣�B����3.0V��4.8V�������̿�ѡ 
               ��05x��08x��ͬ��DAC��������Ҫ��Ϊ������ٸ�ֵ���Ĵ���SYS_AFE_DAC
               y = A * x + B����DAC�����ѹ = DAC_Gain * x + DAC_Offset;
               У��ֵ�ӵ�ַ��ֱ�Ӷ�ȡ �ֱ��Ӧ0x000001c4 �� 0x000001c0;
               ����Read_Trim();��nvr.o�С�
 �޸�����      �汾��          �޸���            �޸�����
 -----------------------------------------------------------------------------
 2022/04/18     V1.0           Zhu Jie              ����
 -----------------------------------------------------------------------------
 2022/10/28     V2.0           Zhu Jie              �Ż�
 *******************************************************************************/
void DAC_OutputVoltage(uint16_t DACVoltage)
{
	  s32 temp = 0;
	  u32 range = 0;
	  s16 temp1 = 0; 
    
	  if(Stru_DAC_CHECK.VersionAndDACGain <= 2)
		{
		    range = (uint16_t)((1.0/3.0)*BIT8); /* BIT8 ��ʾ2^8 DACΪ8λ */
		}
    else if(Stru_DAC_CHECK.VersionAndDACGain == 3)
		{
		    range = (uint16_t)((1.0/4.8)*BIT8); /* BIT8 ��ʾ2^8 DACΪ8λ */
		}
	  temp = (DACVoltage * range ) >> 12; 
	
	  if(temp >=255) /* �޷� */
		{
		    temp = 255;
		}
		
		temp1 = (s16)((temp * Stru_DAC_CHECK.DAC_AMC )>> 9) + (s16)Stru_DAC_CHECK.DAC_DC; ;
		
		if(temp1 < 0)
		{
		  temp1 = 0;
		}
		else if(temp1 > 255)
		{
		  temp1 = 255;
		}		
	  SYS_AFE_DAC = temp1;
	//	SYS_AFE_DAC=85;
	
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
