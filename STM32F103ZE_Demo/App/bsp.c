/**
  ********************************  STM32F10x  *********************************
  * @�ļ���     �� bsp.c
  * @����       �� strongerHuang
  * @��汾     �� V3.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��10��18��
  * @ժҪ       �� BSP�弶֧�ְ�Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2016-10-18 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "bsp.h"


/************************************************
�������� �� RCC_Configuration
��    �� �� ʱ������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void RCC_Configuration(void)
{
  /* ʹ��APB2ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB  | 
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD  | 
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF  | 
                         RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO , ENABLE);

#if 0
  /* ʹ��APB1ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* ʹ��AHBʱ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
#endif
}

/************************************************
�������� �� GPIO_Basic_Configuration
��    �� �� �������������������
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void GPIO_Basic_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin =  PIN_LED;                            //����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                  //Ƶ��(50M)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                   //�������(����ʽ���)
  GPIO_Init(PORT_LED, &GPIO_InitStructure);

#if 0
  /* ʱ����� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_MCOConfig(RCC_MCO_SYSCLK);
#endif
}

/************************************************
�������� �� BSP_Initializes
��    �� �� �ײ��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void BSP_Initializes(void)
{
  RCC_Configuration();                                               //ʱ������
  GPIO_Basic_Configuration();                                        //IO����
}


/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
