//---------------------------------------NRF905 ���ݽ����˿�------------------------------------------------
// TXEN = PB.1
// TRX_CE = PA.7
// MISO = PA.3
// MOSI = PA.2														 	
// SCK = PA.1
// CSN = PA.0
// PWR = PB.2
// AM = PA.5
// DR = PA.4;
// CD = PA.6;
//----------------------------------------------------------------------------------------------------------
#define NRF905_BYTE_BIT0	0x01
#define NRF905_BYTE_BIT1	0x02
#define NRF905_BYTE_BIT2	0x04
#define NRF905_BYTE_BIT3	0x08
#define NRF905_BYTE_BIT4	0x10
#define NRF905_BYTE_BIT5	0x20
#define NRF905_BYTE_BIT6	0x40
#define NRF905_BYTE_BIT7	0x80
//----------------------------------------------------------------------------------------------------------
unsigned char NRF905_DATA_BUF;
#define NRF905_DATA7	((NRF905_DATA_BUF&NRF905_BYTE_BIT7) != 0)
#define NRF905_DATA0    ((NRF905_DATA_BUF&NRF905_BYTE_BIT0) != 0)
//-------------------------------------------nrf905����ָ��-------------------------------------------------
#define NRF905_WC		0x00
#define NRF905_RC		0x10
#define NRF905_WTP		0x20
#define NRF905_RTP		0x21
#define NRF905_WTA		0x22
#define NRF905_RTA		0x23
#define NRF905_RRP		0x24
//------------------------------------------------NRF905�Ĵ�������------------------------------------------
unsigned char NRF905_RFConf[11]={
  0x00,                             //��������
  0x4c,                             //CH_NO,����Ƶ����430MHZ
  0x0c,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
  0x44,                             //��ַ������ã�Ϊ4�ֽ�
  0x04,0x04,                        //���շ�����Ч���ݳ���Ϊ32�ֽ�
  0x11,0x22,0x33,0x44,              //���յ�ַ
  0x58                              //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
};
unsigned char NRF905_TxAddress[4]={0x11,0x22,0x33,0x44};
unsigned char NRF905_data[4]={0x00,0x00,0x00,0x00};
//------------------------------------------------��ʱ-------------------------------------------------------
static void NRF905_Delay(unsigned char n)
{
	unsigned int i;
	while(n--)
	for(i=0;i<80;i++);
}
//-------------------------------------------------SPIд����--------------------------------------------------
void NRF905_SpiWrite(unsigned char send)
{
	unsigned char i;
	NRF905_DATA_BUF=send;
	for (i=0;i<8;i++)
	{
		if (NRF905_DATA7)	
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		}
		else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		}
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		NRF905_DATA_BUF=NRF905_DATA_BUF<<1;
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
	}
}
//---------------------------------------------------SPI������-----------------------------------------------------
unsigned char NRF905_SpiRead(void)
{
	unsigned char j;
	for (j=0;j<8;j++)
	{
    NRF905_DATA_BUF=NRF905_DATA_BUF<<1;
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))	
		{
			NRF905_DATA_BUF|=NRF905_BYTE_BIT0;
		}
		else
		{
			NRF905_DATA_BUF&=~NRF905_BYTE_BIT0;
		}
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
	 }
	 return NRF905_DATA_BUF;
}
//------------------------------------------------------��ʼ��nRF905-------------------------------------------
void NRF905_Init(void)
{
	unsigned char i;
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET);						
	GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_SET);					
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);					
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);	
	NRF905_Delay(1);
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);									
	for (i=0;i<11;i++)	
	{
	  NRF905_SpiWrite(NRF905_RFConf[i]);
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
}
//-----------------------------------------------------�������ݴ��----------------------------------------------
void NRF905_Tx(unsigned char Buf0,unsigned char Buf1,unsigned char Buf2,unsigned char Buf3)
{
	unsigned char i;
	unsigned char NRF905_TxBuf[4]={0x08,0x08,0x08,0x08};
	NRF905_TxBuf[0]=Buf0;
	NRF905_TxBuf[1]=Buf1;
	NRF905_TxBuf[2]=Buf2;
	NRF905_TxBuf[3]=Buf3;
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
	NRF905_Delay(1); 
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
	NRF905_SpiWrite(NRF905_WTP);
	for (i=0;i<4;i++)
	{
		NRF905_SpiWrite(NRF905_TxBuf[i]);		
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	NRF905_Delay(1);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);						
	NRF905_SpiWrite(NRF905_WTA);				
	for (i=0;i<4;i++)			
	{
		NRF905_SpiWrite(NRF905_TxAddress[i]);
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);						
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);					
	NRF905_Delay(1);					
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);					
}
//----------------------------------------------------��NRF905��������-------------------------------------------------
void NRF905_Rx(void)						
{
	unsigned char i;
	NRF905_Delay(1);
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);
	NRF905_Delay(100);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET);
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);						
	NRF905_Delay(1);
	NRF905_SpiWrite(NRF905_RRP);
	for (i = 0 ;i < 4 ;i++)
	{ 
		NRF905_data[i]=NRF905_SpiRead();		    
	}
	GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
	NRF905_Delay(10);
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET);							
}
