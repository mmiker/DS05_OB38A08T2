
//#if defined (__PREIPHERAL_FP_SY_SUPPORT__)
//#include "string.h"
#include "dqiot_fp_sy.h"
// #include "dqiot_drv.h"
#include "OB38A08T2.h"
#include "fps.h"
#include "UART0.h"
#include "Timer.h"

//unsigned long fp_pin_irq_mask;

//fp_irq_handle_callback fp_callback_handle;
//fp_uart_handle_callback fp_uart_handle = 0;
//unsigned char fp_Mode = 0;
//static unsigned char fp_temp_mode = 0;

static unsigned char uart_rec_buff[20];

//static FP_TYPE fp_flag = FP_NONE;
static FP_COLOR_E Light_Color = FP_NONE_COLOR;
//static unsigned char ps_start_flag = 0;

extern unsigned char UART0_RXBUF[];
extern unsigned char UART0_RXLEN;

//unsigned short  ReceiveInfo( unsigned char *rec_data);
//void AS608_log(void);

//void fp_set_irq_handle(fp_irq_handle_callback cb)
//{
//	fp_callback_handle = cb;
//}

//void fp_set_uart_handle(fp_uart_handle_callback cb)
//{
//	fp_uart_handle = cb;
//}

///FP_TYPE fp_get_type(void)
//{
//	return fp_flag;

//}

//--------------------------------------------------------------------------------

//static unsigned char uart_len=0;
//static unsigned short uart_maxlen = 0;
//static unsigned char uart_buff[25]={0};

//static void UART_Callback(unsigned char send_data)
//{
//	send_data = 0;
//}

//unsigned char fp_GetModeState(void)
//{
//	return fp_Mode;
//}

//void fp_SetModeState(unsigned char s)
//{
//	fp_Mode = s;

//	if(s == 0)
//		Light_Color = FP_NONE_COLOR;
//}

//static void PS_UART_Callback(unsigned char send_data)
//{
//	if(send_data == 0x55 )
//	{
//		ps_start_flag = 1;
//	}
//}

//void FP_PowerOn(void)
//{

//}

/**
  * @brief  AS608_USART串口向指纹模块传递数据
  * @param  data;传输的数据
  */
void AS608_SendData(unsigned char send_data)
{
	UART0_TX(send_data);
}

/**
  * @brief  AS608_USART串口向指纹模块命令包头格式 
  * @param  无
  */
unsigned char AS608_PackHead(void)
{
	/*包头 SendHead*/
	AS608_SendData(0xEF);
	AS608_SendData(0x01);

	/*指纹模块地址 SendAddr*/
	AS608_SendData(AS608_Addr >> 24);
	AS608_SendData(AS608_Addr >> 16);
	AS608_SendData(AS608_Addr >> 8);
	AS608_SendData(AS608_Addr);

	return 0;
}

/**
  * @brief  发送包标识
  * @param  flag:包标标志
  * @retval 无
  */
void SendFlag(unsigned char flag)
{
	AS608_SendData(flag);
}

/**
  * @brief  发送包长度
  * @param  length:包长度
  * @retval 无
  */
void SendLength(unsigned short length)
{
	AS608_SendData(length >> 8);
	AS608_SendData(length);
}

/**
  * @brief  发送指令码
  * @param  cmd;指令码
  * @retval 无
  */
void Sendcmd(unsigned char cmd)
{
	AS608_SendData(cmd);
}

/**
  * @brief  发送校验和
  * @param  check:检查位
  * @retval 无
  */
void SendCheck(unsigned short check)
{
	AS608_SendData(check >> 8);
	AS608_SendData(check);
}

/**
  * @brief  判断中断接收的数组有没有应答包
  * @param  
  * waittime为等待中断接收数据的时间(单位1ms)
  * length为包长度
  * @return 数据包确认码
  * @note   1 failed
  * @see    none
  */
static u8 JudgeStr(u16 waittime, u8 length)
{
	// u8 getdata;
	u8 i = 0, j = 0;

	while (--waittime)
	{
		// delay_ms(1);
		TIMER1_Delay(1);

		/* 接收到一次数据 */
		if (UART0_RXLEN >= 9 + length)
		{
			/* 寻找0xEF位置 */
			for (i = 0; i < UART0_RXLEN; i++)
			{
				if (UART0_RXBUF[i] == 0xEF && UART0_RXBUF[i + 1] == 0x01)
					break;
			}

			/* 判断是否为应答包 */
			if (UART0_RXBUF[i] == 0xEF && UART0_RXBUF[i + 1] == 0x01 && UART0_RXBUF[i + 6] == 0x07 && ((UART0_RXBUF[i + 7] << 8) + UART0_RXBUF[i + 8]) == length)
			{
				for (i; i < UART0_RXLEN; i++)
				{
					uart_rec_buff[j] = UART0_RXBUF[i];
					j++;
				}
				// getdata = uart_rec_buff[9]; //确认码

				/* 清空缓存 */
				UART0_RXLEN = 0;

				return uart_rec_buff[9]; //确认码
			}
		}
	}

	return 1;
}

unsigned char PS_GetEcho(void)
{
	AS608_PackHead();
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x53); /*生成特征指令*/
	SendCheck(0x57);

	return JudgeStr(1000, 0x03);
}

//录入图像 PS_GetImage
//功能:探测手指，探测到后录入指纹图像存于ImageBuffer。
//模块返回确认字
unsigned char PS_GetImage(void)
{
	/* 清空缓存 */
	UART0_RXLEN = 0;

	//delay_ms(300);
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); /*命令包标识*/
	SendLength(0x03);
	Sendcmd(0x01); /*录指纹指令*/
	SendCheck(0x01 + 0x03 + 0x01);

	// nrf_delay_ms(50); /*等待指纹识别模块处理数据*/

	return JudgeStr(1000, 0x03);
}

//生成特征 PS_GenChar
//功能:将ImageBuffer中的原始图像生成指纹特征文件存于CharBuffer1或CharBuffer2
//参数:BufferID --> charBuffer1:0x01	charBuffer1:0x02
//模块返回确认字
unsigned char PS_GenChar(unsigned char BufferID)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x04);
	Sendcmd(0x02); /*生成特征指令*/
	AS608_SendData(BufferID);
	SendCheck(0x01 + 0x04 + 0x02 + BufferID);
	//	mmi_dq_log_wakeup_count();

	return JudgeStr(1000, 0x03);
}

//精确比对两枚指纹特征 PS_Match
//功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
//模块返回确认字
unsigned char PS_Match(void)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x03); /*精确比对指令*/
	SendCheck(0x01 + 0x03 + 0x03);

	return JudgeStr(1000, 0x05);
}

//合并特征（生成模板）PS_RegModel
//功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
//说明:  模块返回确认字
unsigned char PS_RegModel(void)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x03);
	Sendcmd(0x05); /*合并特征指令*/
	SendCheck(0x01 + 0x03 + 0x05);

	return JudgeStr(1000, 0x03);
}

//储存模板 PS_StoreChar
//功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
//参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
//       PageID（指纹库位置号）
//说明:  模块返回确认字
unsigned char PS_StoreChar(unsigned char BufferID, unsigned short PageID)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x06);
	Sendcmd(0x06); /*存储模板指令*/
	AS608_SendData(BufferID);
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	SendCheck(0x01 + 0x06 + 0x06 + BufferID + (PageID >> 8) + (unsigned char)PageID);

	return JudgeStr(1000, 0x03);;
}

//删除模板 PS_DeletChar
//功能:  删除flash数据库中指定ID号开始的N个指纹模板
//参数:  PageID(指纹库模板号)，N删除的模板个数。
//说明:  模块返回确认字
unsigned char PS_DeletChar(unsigned short PageID, unsigned short N)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x07);
	Sendcmd(0x0C); /*删除指定指纹模板指令*/
	AS608_SendData(PageID >> 8);
	AS608_SendData(PageID);
	AS608_SendData(N >> 8);
	AS608_SendData(N);
	SendCheck(0x01 + 0x07 + 0x0C + (PageID >> 8) + (unsigned char)PageID + (N >> 8) + (unsigned char)N);

	//AS608_DELAY_MS(400);

	return JudgeStr(1000, 0x03);
}

//高速搜索PS_HighSpeedSearch
//功能：以 CharBuffer1或CharBuffer2中的特征文件高速搜索整个或部分指纹库。
//		  若搜索到，则返回页码,该指令对于的确存在于指纹库中 ，且登录时质量
//		  很好的指纹，会很快给出搜索结果。
//参数:  BufferID， StartPage(起始页)，PageNum（页数）
//说明:  模块返回确认字+页码（相配指纹模板）
unsigned char PS_HighSpeedSearch(unsigned char BufferID, unsigned short StartPage, unsigned short PageNum, unsigned short *p)
{
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01);
	SendLength(0x08);
	Sendcmd(0x1b); /*高速搜索指纹库指令*/
	AS608_SendData(BufferID);
	AS608_SendData(StartPage >> 8);
	AS608_SendData(StartPage);
	AS608_SendData(PageNum >> 8);
	AS608_SendData(PageNum);
	SendCheck(0x01 + 0x08 + 0x1b + BufferID + (StartPage >> 8) + (unsigned char)StartPage + (PageNum >> 8) + (unsigned char)PageNum);

	// ensure = ReturnFlag(&rc);
	ensure = JudgeStr(1000, 0x07);

	*p = (uart_rec_buff[10] << 8) + uart_rec_buff[11]; //模板号

	return ensure;
}

//清空指纹库 PS_Empty
//功能:  删除flash数据库中所有指纹模板
//参数:  无
//说明:  模块返回确认字
unsigned char PS_Empty(void)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x0D);
	SendCheck(0x01 + 0x03 + 0x0D);

	return JudgeStr(1000, 0x03);
}

//读有效模板个数 PS_ValidTempleteNum
//功能：读有效模板个数
//参数: 无
//说明: 模块返回确认字+有效模板个数ValidN
unsigned char PS_ValidTempleteNum(unsigned short *ValidN)
{
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x1d);
	SendCheck(0x01 + 0x03 + 0x1d);

	// ensure = ReturnFlag(&p);
	ensure = JudgeStr(1000, 0x05);

	*ValidN = (uart_rec_buff[10] << 8) + uart_rec_buff[11];

	return ensure;
}

//自动注册模板 PS_AutoEnRoll
//功能：采集一次指纹注册模板，在指纹库中搜索空位并存储，返回存储ID
//参数: 无
//说明: 模块返回确认字+页码（相配指纹模板）
unsigned char PS_AutoEnRoll(unsigned short id, unsigned char num, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x08);
	Sendcmd(0x31);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(num);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
	SendCheck(0x01 + 0x08 + 0x31 + (id >> 8) + (id & 0xFF) + num + (param >> 8) + (param & 0xFF));

	return 0;
}

//自动验证指纹 PS_AutoIdentify
//功能：
//1.自动采集指纹，在指纹库中搜索目标模板并返回搜索结果。
//2.如果目标模板同当前采集的指纹比对得分大于最高阀值，并且目标模板为不完整特征则以采集的特征更新目标模板的空白区域。
//参数: 无
//说明: 模块返回确认字+页码（相配指纹模板）
unsigned char PS_AutoIdentify(unsigned short id, unsigned char level, unsigned short param)
{
	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x08);
	Sendcmd(0x32);
	AS608_SendData(level);
	AS608_SendData(id >> 8);
	AS608_SendData(id & 0xFF);
	AS608_SendData(param >> 8);
	AS608_SendData(param & 0xFF);
	SendCheck(0x01 + 0x08 + 0x32 + (id >> 8) + (id & 0xFF) + level + (param >> 8) + (param & 0xFF));

	return 0;
}

//与AS608握手 PS_HandShake
//参数: PS_Addr地址指针
//说明: 模块返新地址（正确地址） 返回确认码
unsigned char PS_HandShake(unsigned long *PS_Addr)
{
	*PS_Addr = 0;

	if (AS608_PackHead() == 1)
		return 0xFF;

	SendFlag(0x01);
	SendLength(0x07);
	Sendcmd(0x13);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	AS608_SendData(0x00);
	SendCheck(0x1B);

	return 0;
}

unsigned char PS_Reset(void)
{
	return 0;
}

unsigned char PS_Sleep(void)
{
	unsigned char ensure;

	if (AS608_PackHead() == 1)
		return 0xFF;
	SendFlag(0x01); //命令包标识
	SendLength(0x03);
	Sendcmd(0x60);
	SendCheck(0x01 + 0x03 + 0x60);
	return ensure;
}

void FP_Light(FP_COLOR_E light_id)
{
	//	if(fp_flag == FP_LT5X)
	//	{
	//#ifdef __FP_LT5X_LIGHT_SUPPORT__
	unsigned short temp;

	// unsigned char sure = 0; //,p=0;
	if (light_id == Light_Color)
		return;

	if (AS608_PackHead() == 1)
		return;
	SendFlag(0x01);
	SendLength(0x07);
	Sendcmd(0x41);
	switch (light_id)
	{
	case FP_BLUE:
		AS608_SendData(0x01);
		AS608_SendData(0x01);
		AS608_SendData(0x00);
		AS608_SendData(0x50);
		temp = 0x01 + 0x07 + 0x41 + 0x02 + 0x50;
		break;
	case FP_GREEN:
		AS608_SendData(0x01);
		AS608_SendData(0x02);
		AS608_SendData(0x02);
		AS608_SendData(0);
		temp = 0x01 + 0x07 + 0x41 + 0x05 + 0;
		break;
	case FP_RED:
		AS608_SendData(0x01);
		AS608_SendData(0x04);
		AS608_SendData(0x04);
		AS608_SendData(0);
		temp = 0x01 + 0x07 + 0x41 + 0x09 + 0;
		break;
	case FP_NONE_COLOR:
		AS608_SendData(0x04);
		AS608_SendData(0x00);
		AS608_SendData(0x00);
		AS608_SendData(0xC8);
		temp = 0x01 + 0x07 + 0x41 + 0x04 + 0xC8;
		break;
	}
	SendCheck(temp);

	//sure=ReturnFlag(&p);
	// sure = JudgeStr(1000, 0x03);
	//#endif
	Light_Color = light_id;

	//	}
}

FP_COLOR_E FP_Get_Light(void)
{
	return Light_Color;
}
