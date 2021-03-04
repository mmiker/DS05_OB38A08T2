#ifndef __MMI_FPC_C__
#define __MMI_FPC_C__

// #include "string.h"
#include "mmi_fps.h"
#include "mmi_feature.h"
#include "dqiot_fp_sy.h"
#include "OB38A08T2.h"
#include "Timer.h"
#include "Audio.h"
// #include "dqiot_drv.h"

#define FP_INT P0_3

#ifdef __LOCK_FP_SUPPORT__
unsigned char FP_oldStatus = 0;
/*
parameter: 
	current status machine
return :
	none
*/
//void mmi_dq_fp_set_fp_uart_handle_cb(fp_uart_handle_callback cb)
//{

//}

/*
parameter: 
	current status machine
return :
	none
*/
//void mmi_dq_fps_set_irq_handle_cb(fp_irq_handle_callback cb)
//{
//	cb = NULL;
//}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_fp_mode(void)
{
	return 1;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_image(void)
{
	unsigned char retval = 0;

	retval = PS_GetImage();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_gen_char(unsigned char id)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

	retval = PS_GenChar(real_buf_id); //生成特征
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_match(void)
{
	unsigned char retval = 0;

	retval = PS_Match();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_reg_module(void)
{
	unsigned char retval = 0;

	retval = PS_RegModel();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_store_char(unsigned char id, unsigned short index)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (id == 3)
		real_buf_id = CHAR_BUFFER4;

	retval = PS_StoreChar(real_buf_id, index); //储存模板
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_delete(unsigned short index)
{
	unsigned char retval = 0;

	retval = PS_DeletChar(index, 1);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_empty(void)
{
	unsigned char retval = 0;

	retval = PS_Empty();
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_get_valid_templete(unsigned short *count)
{
	unsigned char retval = 0;

	retval = PS_ValidTempleteNum(count);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
unsigned char mmi_dq_fp_high_speed_search(unsigned char Buf_id, unsigned short *index)
{
	unsigned char retval = 0;
	unsigned char real_buf_id;

	if (Buf_id == 0)
		real_buf_id = CHAR_BUFFER1;
	else if (Buf_id == 1)
		real_buf_id = CHAR_BUFFER2;
	else if (Buf_id == 2)
		real_buf_id = CHAR_BUFFER3;
	else if (Buf_id == 3)
		real_buf_id = CHAR_BUFFER4;
	retval = PS_HighSpeedSearch(real_buf_id, 0, 300, index);
	return retval;
}

/*
parameter: 
	current status machine
return :
	none
*/
void mmi_dq_fp_light(FP_COLOR_E light_id)
{
	FP_Light(light_id); //点灯
}

/*
parameter: 
	current status machine
return :
	none
*/
FP_COLOR_E mmi_dq_fp_get_light(void)
{
	FP_COLOR_E retval = 0;
	retval = FP_Get_Light();
	return retval;
}

/**
  * @brief  触摸判断
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char mmi_dq_fp_work(void)
{
	if (FP_INT == 0)
	{
		if (FP_oldStatus == 0)
		{
			FP_oldStatus = 1;
			return 1;
		}
	}
	else
		FP_oldStatus = 0;
	return 0;
}

unsigned char mmi_dq_fp_get_pin(void)
{
	// return gpio_bit_get(GPIOF, GPIO_PIN_6);
	return FP_INT;
}

/**
  * @brief  录指纹
  * @param  ID 记录指纹个数
  * @return none
  * @note   none
  * @see    none
  */
void Add_FR(u16 ID)
{
	u8 i = 0, ensure, processnum = 0;
	u16 index = 0; //模板号

	while (1)
	{
		switch (processnum)
		{
		case 0:
			Audio_Play(AUD_ID_PRESS_FP); //请按手指
			processnum = 1;				 //跳到第二步
		case 1:
			i++;
			ensure = PS_GetImage();
			if (ensure == 0x00)
			{
				ensure = PS_GenChar(CHAR_BUFFER1); //生成特征
				if (ensure == 0x00)
				{
					ensure = PS_HighSpeedSearch(CHAR_BUFFER1, 0, 300, &index);
					if (ensure == 0x00)
					{
						FP_Light(FP_RED);
						Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹已存在，请换个手指
					}
					else
					{
						// "Fingerprint correct" //指纹正确
						FP_Light(FP_GREEN);
						i = 0;
						processnum = 2; //跳到第二步
					}
				}
				else
				{
					FP_Light(FP_RED);
					Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				}
			}
			else
				; // is error
			break;

		case 2:
			Audio_Play(AUD_ID_PRESS_FP_AGAIN); //请再按一次
			processnum = 3;					   //跳到第二步

		case 3:
			i++;

			ensure = PS_GetImage();
			if (ensure == 0x00)
			{
				ensure = PS_GenChar(CHAR_BUFFER2); //生成特征
				if (ensure == 0x00)
				{
					ensure = PS_HighSpeedSearch(CHAR_BUFFER2, 0, 300, &index);
					if (ensure == 0x00)
					{
						FP_Light(FP_RED);
						Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹已存在，请换个手指
					}
					else
					{
						// "Fingerprint correct" //指纹正确
						i = 0;
						processnum = 4; //跳到第三步
					}
				}
				else
				{
					FP_Light(FP_RED);
					Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				}
			}
			else
				; // is error
			break;

		case 4:
			// "Compare twice fingerprint" //对比两次指纹
			ensure = PS_Match();
			if (ensure == 0x00 || ensure == 0xff)
			{
				// "Twice fingerprint are same" //两次指纹是一样的
				processnum = 5; //跳到第四步
			}
			else
			{
				FP_Light(FP_RED);
				Audio_Play(AUD_ID_OPRATION_FAIL);	 //两次输入的指纹不一致
				Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				i = 0;
				processnum = 0; //跳回第一步
			}
			// TIMER1_Delay(1000);
			break;

		case 5:
			// "Generate fingerprint template" //产生一个指纹模板
			ensure = PS_RegModel();
			if (ensure == 0x00)
			{
				// "Generate fingerprint success" //生成指纹模板成功
				processnum = 6; //跳到第五步
			}
			else
			{
				FP_Light(FP_RED);
				Audio_Play(AUD_ID_ADD_FAIL);		 //添加失败，请重试
				Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				processnum = 0;
				// is error
			}
			// TIMER1_Delay(1000);
			break;

		case 6:
			if (ID > 50)
			{
				// is error
				FP_Light(FP_RED);
				Audio_Play(AUD_ID_FP_FULL);			 //指纹已满，请联系管理员
				Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				return;
			}

			ensure = PS_StoreChar(CHAR_BUFFER2, ID); //储存模板
			if (ensure == 0x00)
			{
				FP_Light(FP_GREEN);
				Audio_Play(AUD_ID_ADD_FP_SUCESS); //指纹添加成功
				ID++;							  //成功id++，失败不变
				return;
			}
			else
			{
				FP_Light(FP_RED);
				Audio_Play(AUD_ID_ADD_FAIL);		 //添加失败，请联系管理员
				Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
				processnum = 0;
				// is error
			}
			break;
		}
		TIMER1_Delay(300);
		if (i == 5) //超过5次没有按手指则退出
		{
			FP_Light(FP_NONE_COLOR);
			TIMER1_Delay(300);
			FP_Light(FP_RED);
			// is quit
			return;
		}
	}
}

/**
  * @brief  删指纹
  * @param  TouchNum
  * 0: 清空
  * 1: 删除单个指纹
  * @return 确认码
  * @note   none
  * @see    none
  */
void Del_FR(u16 TouchNum)
{
	u8 i = 0, ensure, processnum = 0;
	u16 index = 0; //模板号

	if (TouchNum == 0)
	{
		ensure = PS_Empty(); //清空指纹库
		if (ensure == 0)
			Audio_Play(AUD_ID_DEL_FP_SUCESS);
		else
			Audio_Play(AUD_ID_DEL_FAIL_RETRY);
		return;
	}

	if (TouchNum == 1)
	{
		while (1)
		{
			switch (processnum)
			{

			case 0:
				Audio_Play(AUD_ID_PRESS_FP); //请输入要删除的指纹
				processnum = 1;				 //跳到第二步

			case 1:
				i++;
				ensure = PS_GetImage();
				if (ensure == 0x00)
				{
					ensure = PS_GenChar(CHAR_BUFFER1); //生成特征
					if (ensure == 0x00)
					{
						ensure = PS_HighSpeedSearch(CHAR_BUFFER1, 0, 300, &index);
						if (ensure == 0x00)
						{
							// "Fingerprint correct" //指纹正确
							FP_Light(FP_GREEN);
							i = 0;
							processnum = 2; //跳到第二步
						}
						else
						{
							FP_Light(FP_RED);
							Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹不存在，请重新输入
						}
					}
					else
					{
						FP_Light(FP_RED);
						Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
					}
				}
				else
					; // is error
				break;

			case 2:
				Audio_Play(AUD_ID_PRESS_FP_AGAIN); //请输入要删除的指纹
				processnum = 3;					   //跳到第二步

			case 3:
				i++;
				ensure = PS_GetImage();
				if (ensure == 0x00)
				{
					ensure = PS_GenChar(CHAR_BUFFER2); //生成特征
					if (ensure == 0x00)
					{
						ensure = PS_HighSpeedSearch(CHAR_BUFFER2, 0, 300, &index);
						if (ensure == 0x00)
						{
							// "Fingerprint correct" //指纹正确
							i = 0;
							processnum = 4; //跳到第三步
						}
						else
						{
							FP_Light(FP_RED);
							Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹不存在，请重新输入
						}
					}
					else
					{
						FP_Light(FP_RED);
						Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
					}
				}
				else
					; // is error
				break;

			case 4:
				ensure = PS_DeletChar(index, 1); //删除单个指纹
				if (ensure == 0x00)
				{
					FP_Light(FP_GREEN);
					Audio_Play(AUD_ID_DEL_FP_SUCESS);
					return;
				}
				else
				{
					FP_Light(FP_RED);
					Audio_Play(AUD_ID_DEL_FAIL_RETRY);
				}
			}
			TIMER1_Delay(800);
			if (i == 5) //超过5次没有按手指则退出
			{
				FP_Light(FP_NONE_COLOR);
				TIMER1_Delay(300);
				FP_Light(FP_RED);
				TIMER1_Delay(300);
				// is quit
				return;
			}
		}
	}
}

/**
  * @brief  刷指纹
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
void press_FR(void)
{
	u8 ensure;
	u16 index = 0;
	char *str;
	ensure = PS_GetImage();
	if (ensure == 0x00) //获取图像成功
	{
		ensure = PS_GenChar(CHAR_BUFFER1);
		if (ensure == 0x00) //生成特征成功
		{
			ensure = PS_HighSpeedSearch(CHAR_BUFFER1, 0, 300, &index);
			if (ensure == 0x00) //搜索成功
			{
				Audio_Play(AUD_ID_DOOR_OPEN);
				Audio_Play(AUD_ID_DOOR_CLOSE);
			}
			else
				Audio_Play(AUD_ID_CHECK_FAIL_RETRY);
		}
		else
		{
			FP_Light(FP_RED);
			Audio_Play(AUD_ID_CHECK_FAIL_RETRY); //指纹错误，请重试
		}
	}

	return;
}

#endif //__LOCK_FP_SUPPORT__

#endif //__MMI_FPC_C__
