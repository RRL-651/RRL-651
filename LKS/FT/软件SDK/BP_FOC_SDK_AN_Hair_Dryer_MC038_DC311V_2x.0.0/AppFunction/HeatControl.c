/*******************************************************************************
 * ��Ȩ���� (C)2022, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� HeatControl.c
 * �ļ���ʶ��
 * ����ժҪ�� KeyScan
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� Robin Chen
 * ������ڣ� 2022��12��13��
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
 * Description:  ����˿����
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
 /*****************************************************************************
 * Function:     void HeaterControl(void)
 * Description:  ����˿����
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
 u8 FRS_ON=0;
u8 ControlOFF;
 void HeaterControl(void)
{
	static u16 AcDownCD1ms;
   static	u8 AccCrossZeroCnt=0;
   FRSControl.ThrowWaveMode = ThrowHalfWave;  //����ģʽĬ�϶�*�� �벨��ThrowHalfWave  ȫ����ThrowFullWave
	 
	 /* ����˿����������1.״̬������RUN  2.���ʵ��ת�ٴﵽһ���Ƚϴ��ֵ  3.ϵͳû�з����κδ���  4.������Ƶ�ʼ�����  5.����˿��ʱ��������*/
	 if((struFOC_CtrProc.eSysState == RUN)&&(struMotorSpeed.wSpeedEst > 15000)&&(stru_Faults.R == 0)&&(FRSControl.ACFrequencyDetectFinishFlag == 1)&&(FRSControl.TurnOnDelayCnt>=HEATER_DELAY_ON_TIME))  //�жϷ���˿��������
//	 if((struFOC_CtrProc.eSysState == RUN)&&(struMotorSpeed.wSpeedEst > 15000)&&(stru_Faults.R == 0)&&(FRSControl.ACFrequencyDetectFinishFlag == 1))  //�жϷ���˿��������

	 {
	     FRSControl.TurnOnOffFlag = 1;  //����˿��������
	 }
	 else
	 {
	     FRSControl.TurnOnOffFlag = 0;  //����˿�����ر�
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
	if(!FRSControl.CrossZeroPosedge) //�����
	{
		if(++FRSControl.ACFrequencyDetectCnt > 6 )    //
		{
				FRSControl.CrossZeroPosedge = 1;
				FRSControl.ACFrequencyDetectCnt = 0;
				FRSControl.CrossZeroPosedgeFlag ++;			
		}
	}
	if(FRSControl.CrossZeroPosedgeFlag>=2) //�����
	{
		FRSControl.CrossZeroPosedgeFlag=0;

	/*	  
		  if(FRSControl.ACFrequencyDetectFinishFlag == 0)  //������Ƶ�ʼ���־
			{
				  if((FRSControl.CrossZeroCnt > 1)&&(FRSControl.CrossZeroCnt < 5 )) //CrossZeroCnt>0 �����ϵ�����
					{
							if((FRSControl.ACFrequencyDetectCnt > FRSControl.AC50HzFrequencyDetectCntMin) && (FRSControl.ACFrequencyDetectCnt < FRSControl.AC50HzFrequencyDetectCntMax))  //�ز�22K 50Hz10ms��220��  60Hz8.33ms��183.3��
							{
								 FRSControl.ACFrequency = AC50Hz;  //������Ƶ��50Hz
								 FRSControl.ACFrequencyDetectFinishFlag = 1;   //������Ƶ�ʼ�����
							}
							else if((FRSControl.ACFrequencyDetectCnt > FRSControl.AC60HzFrequencyDetectCntMin) && (FRSControl.ACFrequencyDetectCnt < FRSControl.AC60HzFrequencyDetectCntMax))  //�ز�22K 50Hz10ms��220��  60Hz8.33ms��183.3��
							{
								 FRSControl.ACFrequency = AC60Hz;  //������Ƶ��60Hz
								 FRSControl.ACFrequencyDetectFinishFlag = 1;   //������Ƶ�ʼ�����
							}
							else
              {
								  FRSControl.ACFrequencyDetectFinishFlag = 0;   //������Ƶ�ʼ��ʧ��
									FRSControl.CrossZeroErrorFlag = 1;    //���������
							}
				  }
					else if(FRSControl.CrossZeroCnt >= 5)   //�ϵ�󾭹�5�ι����źŶ�û�м���������Ƶ��
					{
//						  FRSControl.ACFrequency = AC50Hz;   //Ĭ�Ͻ�����Ƶ��50Hz
//						  FRSControl.ACFrequencyDetectFinishFlag = 1;
						
						  FRSControl.ACDetectErrorFlag = 1;//������Ƶ�ʼ�����
					}
		  }
	*/		
	    FRSControl.ACFrequency = AC50Hz;  //������Ƶ��60Hz
		  FRSControl.ACFrequencyDetectFinishFlag = 1;   //������Ƶ�ʼ�����
      FRSControl.CrossZeroErrorFlag= 0;       //���������ָ�
		 	FRSControl.ACFrequencyDetectCnt = 0;    //������Ƶ�ʼ���������
			FRSControl.CrossZeroCnt ++;    //�����������

			
			if(FRSControl.ThrowWaveMode == ThrowHalfWave)   //�벨����ģʽ
			{
					if(FRSControl.CrossZeroCnt > 49)
					{
						 FRSControl.CrossZeroCnt = 0;
					}
					FRSControl.ThrowWaveTabIndex= HotTab[(FRSControl.ThrowWaveCnt*50)+(FRSControl.CrossZeroCnt)];  //����˿��ͨ״̬���
		  }
			else   //ȫ������ģʽ
			{
			   	if(FRSControl.CrossZeroCnt > 99)
					{
						 FRSControl.CrossZeroCnt = 0;
					}
					FRSControl.ThrowWaveTabIndex= HotTab[(FRSControl.ThrowWaveCnt*50)+(FRSControl.CrossZeroCnt>>1)];  //����˿��ͨ״̬���
			}	
				 if(FRSControl.TurnOnOffFlag == 1)    //�жϷ���˿�Ƿ������������
	 {
			// if((FRSControl.CrossZeroStateLast == 0)&&(FRSControl.CrossZeroState == 1))  //����������
			 {
				   FRSControl.ThrowWaveFlag = 1;   //���������ź���������������־
			 }

			 if(FRSControl.ThrowWaveFlag == 1) 
			 {
					 FRSControl.ThrowWaveDelayCnt ++;  //������ʱ����
					 
				   if(FRSControl.ACFrequency == AC50Hz)
					 {
							 if(FRSControl.ThrowWaveDelayCnt >= FRSControl.AC50HzThrowWaveDelayCnt)  //������ʱ  ��ʱд0
							 {
									 FRSControl.ThrowWaveDelayCnt = 0;
									 if(FRSControl.ThrowWaveTabIndex == 1)    //��������Ҫ���ɿع�
									 {
											 HEATER_CONTROL_ON();        //����˿��
											 FRSControl.ThrowWaveFlag = 0;
										   FRS_ON = 1;
										   FRSControl.activecnt =20;
									 }
									 else
									 {
											 HEATER_CONTROL_OFF();       //����˿��
											 FRSControl.ThrowWaveFlag = 0;
//										   FRS_ON = 0;
									 }
							 }
				   }
					 else if(FRSControl.ACFrequency == AC60Hz)
					 {
							 if(FRSControl.ThrowWaveDelayCnt >= FRSControl.AC50HzThrowWaveDelayCnt)  //������ʱ  //�ز�22K 60Hz8.333ms��183.3��
							 {
									 FRSControl.ThrowWaveDelayCnt = 0;
									 if(FRSControl.ThrowWaveTabIndex == 1)    //��������Ҫ���ɿع�
									 {
											 HEATER_CONTROL_ON();        //����˿��
											 FRSControl.ThrowWaveFlag = 0;
									 }
									 else
									{
											 HEATER_CONTROL_OFF();       //����˿��
											 FRSControl.ThrowWaveFlag = 0;
									 }
							 }
					 }
					 else
					 {
							 HEATER_CONTROL_OFF();           //����˿��
							 FRSControl.ThrowWaveDelayCnt = 0;
							 FRSControl.ThrowWaveFlag = 0;
					 }
			 }
	 }
	 else
	 {
			 HEATER_CONTROL_OFF();           //����˿��
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
			AcDownCD1ms = 500;		//�������ֵ �����ϵ�CD�� ��λ1ms
		}
		if(AcDownCD1ms)AcDownCD1ms--;
			FRSControl.CrossDownAcStateLast=FRSControl.CrossDownAcState;
			
		FRSControl.CrossZeroState = ZERO_SCR();    //��ȡ�����źŵ�ƽ
		
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
			 FRSControl.CrossZeroPosedge = 0;  //���������ź������ر�־
			 FRSControl.CrossZeroMsCnt=FRSControl.CrossZeroVoltageCnt1;
			FRSControl.CrossZeroVoltageCnt1=0;
		}
		if((FRSControl.CrossZeroStateLast == 1) && (FRSControl.CrossZeroState == 0))
		{
//		   FRSControl.ACFrequencyDetectCnt = 0;
//			 FRSControl.CrossZeroPosedge = 0;  //���������ź������ر�־
		}
		FRSControl.CrossZeroStateLast = FRSControl.CrossZeroState;
	 
}


/*****************************************************************************
 * Function:     void HeaterTemperature_Control(void)
 * Description:  ����˿�¶ȿ���
 * Parameter:    no
 * Return:       no
 *****************************************************************************/
u8 xxxx = 0;
s16 testtemp=32000;
void HeaterTemperature_Control(void)
{
	if(hairmode<=1)																	//����ģʽ
	{
		if(iTargetGear==0)
		{
			if(TempGear ==1)																	//80��
			{
				FRSControl.TargetTemperature =19000;
				
				FRSControl.ThrowWaveBase = 16;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 14;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =18;         //��������ֵ
				//FRSControl.ThrowWaveCnt =10;	
			}
			else if(TempGear==2)															//95��
			{
				FRSControl.TargetTemperature =14000;
				FRSControl.ThrowWaveBase = 20;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 18;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =23;         //��������ֵ		
			}
			else
			{
				FRSControl.TargetTemperature =0;
				FRSControl.ThrowWaveBase = 0;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 0;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =0;         //��������ֵ							
			}
		}
		else	if(iTargetGear==1)
		{
			if(TempGear ==1)																	//80��
			{
				FRSControl.TargetTemperature =18000;
				
				FRSControl.ThrowWaveBase = 18;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 16;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =20;         //��������ֵ
				//FRSControl.ThrowWaveCnt =10;	
			}
			else if(TempGear==2)															//95��
			{
				FRSControl.TargetTemperature =14000;
				FRSControl.ThrowWaveBase = 25;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 22;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =27;         //��������ֵ		
			}
			else
			{
				FRSControl.TargetTemperature =0;
				FRSControl.ThrowWaveBase = 0;            //�궨�õĶ�������ֵ 
				FRSControl.ThrowWaveLimitMin = 0;        //��������ֵ
				FRSControl.ThrowWaveLimitMax =0;         //��������ֵ							
			}
		}
	}
	else if(hairmode==2)														//��ͯģʽ			45��
	{
			FRSControl.TargetTemperature =27000;			
			FRSControl.ThrowWaveBase = 5;            //�궨�õĶ�������ֵ 
			FRSControl.ThrowWaveLimitMin = 3;        //��������ֵ
			FRSControl.ThrowWaveLimitMax =7;         //��������ֵ
			//FRSControl.ThrowWaveCnt =10;	
	}
	else if(hairmode==3)														//�ٸ�ģʽ			95��
	{
			FRSControl.TargetTemperature =14000;			
			FRSControl.ThrowWaveBase = 25;            //�궨�õĶ�������ֵ 
			FRSControl.ThrowWaveLimitMin = 22;        //��������ֵ
			FRSControl.ThrowWaveLimitMax =27;         //��������ֵ
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
