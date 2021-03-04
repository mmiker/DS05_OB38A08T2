#ifndef __MMI_FS_C__
#define __MMI_FS_C__

#include "mmi_fs.h"
#include "mmi_sys.h"
#include "eeprom.h"
#include "string.h"
//#include "stdio.h"

#include "mmi_fps.h"
#include "mmi_ms.h"
#include "dq_otp.h"

mmi_fs_setting g_dq_fs_init_set;

#define MMI_DQ_FS_PWD_MAX_NUM 3
mmi_fs_pwd 		g_dq_fs_pwd[MMI_DQ_FS_PWD_MAX_NUM];

#ifdef __LOCK_FP_SUPPORT__
#define			MMI_DQ_FS_FP_MAX_NUM    	2
mmi_fs_fp		g_dq_fs_fp[MMI_DQ_FS_FP_MAX_NUM];
#endif

#ifdef __LOCK_RFID_CARD_SUPPORT__
#define			MMI_DQ_FS_RFID_MAX_NUM  		10
mmi_fs_rfid		g_dq_fs_rfid[MMI_DQ_FS_RFID_MAX_NUM];
#endif

#define EEPROM_SET_SATRT_ADDR	0
#define EEPROM_PW_SATRT_ADDR	24
#define EEPROM_FP_SATRT_ADDR	48
#define EEPROM_RF_SATRT_ADDR	72

static void mmi_dq_fds_read(mid_fds_file_id file,  uint8_t* r_data ,uint16_t r_size)
{
	uint16_t i;
#if 0
	switch(file)
	{
		case MID_FDS_FILE_SET:
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = Read_EEPROM(i+EEPROM_SET_SATRT_ADDR);
			}
			break;
		case MID_FDS_FILE_PWD:
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = Read_EEPROM(i+EEPROM_PW_SATRT_ADDR);
			}
			break;
#ifdef __LOCK_FP_SUPPORT__
		case MID_FDS_FILE_FP:
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = Read_EEPROM(i+EEPROM_FP_SATRT_ADDR);
			}
			break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		case MID_FDS_FILE_RF:
			for(i = 0; i < r_size; i++)
			{
				r_data[i] = Read_EEPROM(i+EEPROM_RF_SATRT_ADDR);
			}
			break;
#endif
		default:
			break;
	}
#else
	for(i = 0; i < r_size; i++)
	{
		r_data[i] = Read_EEPROM(i+24*file);
	}
#endif
}

static RET_VAL mmi_dq_fds_write(mid_fds_file_id file, uint8_t* w_data ,uint16_t w_size)
{
	uint16_t i;
#if 0
	switch(file)
	{
		case MID_FDS_FILE_SET:
			for(i = 0; i < w_size; i++)
			{
				Write_EEPROM(i+EEPROM_SET_SATRT_ADDR,w_data[i]);
			}
			break;
		case MID_FDS_FILE_PWD:
			for(i = 0; i < w_size; i++)
			{
				Write_EEPROM(i+EEPROM_PW_SATRT_ADDR,w_data[i]);
			}
			break;
#ifdef __LOCK_FP_SUPPORT__
		case MID_FDS_FILE_FP:
			for(i = 0; i < w_size; i++)
			{
				Write_EEPROM(i+EEPROM_FP_SATRT_ADDR,w_data[i]);
			}
			break;
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		case MID_FDS_FILE_RF:
			for(i = 0; i < w_size; i++)
			{
				Write_EEPROM(i+EEPROM_RF_SATRT_ADDR,w_data[i]);
			}
			break;
#endif
		default:
			return RET_FAIL;
	}
	
#else
	for(i = 0; i < w_size; i++)
	{
		Write_EEPROM(i+24*file,w_data[i]);
	}
#endif
	return RET_SUCESS;
}



/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_init(void)
{
	mmi_dq_fds_read(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	if(FDS_INIT_LOCK_SUC == g_dq_fs_init_set.init_flag || FDS_INIT_APP_SUC == g_dq_fs_init_set.init_flag)
	{
		unsigned char i = 0;
		mmi_dq_fds_read(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
#ifdef __LOCK_FP_SUPPORT__
		mmi_dq_fds_read(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		mmi_dq_fds_read(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
#endif
		if(g_dq_fs_init_set.admin_status > 0)
		{
			for(;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
			{
				if(g_dq_fs_pwd[i].flag == FDS_USE_TYPE_ADMIN)
					break;
			}
			if(i>=MMI_DQ_FS_PWD_MAX_NUM)
			{
				g_dq_fs_init_set.admin_status = 0;
				mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
			}
		}
	}
	else
	{
		//printf("mmi_dq_fs_init init error");
		memset(g_dq_fs_pwd,0xFF,sizeof(g_dq_fs_pwd));
		g_dq_fs_pwd[0].flag = FDS_USE_TYPE_ADMIN;
		g_dq_fs_pwd[0].key_pwd[0] = 0x12;
		g_dq_fs_pwd[0].key_pwd[1] = 0x34;
		g_dq_fs_pwd[0].key_pwd[2] = 0x56;

		g_dq_fs_pwd[0].flag = FDS_USE_TYPE_USER;
		g_dq_fs_pwd[2].key_pwd[0] = 0x12;
		g_dq_fs_pwd[2].key_pwd[1] = 0x34;
		g_dq_fs_pwd[2].key_pwd[2] = 0x56;
		mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
		
#ifdef __LOCK_FP_SUPPORT__
		memset(g_dq_fs_fp,0xFF,sizeof(g_dq_fs_fp));
		mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);

		mmi_dq_fp_empty();
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
		memset(g_dq_fs_rfid,0xFF,sizeof(g_dq_fs_rfid));
		mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
#endif
		g_dq_fs_init_set.init_flag = FDS_INIT_LOCK_SUC;
		//g_dq_fs_init_set.open_pro_sound = 1;
		//g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
		g_dq_fs_init_set.admin_status = 0;
		g_dq_fs_init_set.factory_flag = 0;
		g_dq_fs_init_set.wifi_flag = 0;
		g_dq_fs_init_set.alarm_flag = 0;
		g_dq_fs_init_set.low_power_times = 0;
		g_dq_fs_init_set.language_flag = 0;
		//g_dq_fs_init_set.business_flag = 0;
		//for(i=0;i<8;i++)
		//	g_dq_fs_init_set.check_data[i] = 0xFF; 
		//mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
		mmi_dq_fs_clr_set();
	}
}

/**
  * @brief  手动初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_clr_set(void)
{
	unsigned char i = 0;
	g_dq_fs_init_set.open_pro_sound = 1;
	g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
	g_dq_fs_init_set.alarm_flag = 0;
	g_dq_fs_init_set.business_flag = 0;
	for(i=0;i<8;i++)
		g_dq_fs_init_set.check_data[i] = 0xFF; 
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/**
  * @brief  复位初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_reset(void)
{
	memset(g_dq_fs_pwd, 0xFF, sizeof(g_dq_fs_pwd));
	mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd, sizeof(mmi_fs_pwd) * MMI_DQ_FS_PWD_MAX_NUM);
#ifdef __LOCK_FP_SUPPORT__
	memset(g_dq_fs_fp, 0xFF, sizeof(g_dq_fs_fp));
	mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp) * MMI_DQ_FS_FP_MAX_NUM);

	mmi_dq_fp_empty();
#endif
#ifdef __LOCK_RFID_CARD_SUPPORT__
	memset(g_dq_fs_rfid, 0xFF, sizeof(g_dq_fs_rfid));
	mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid) * MMI_DQ_FS_RFID_MAX_NUM);
#endif
	g_dq_fs_init_set.init_flag = FDS_INIT_LOCK_SUC;
	//g_dq_fs_init_set.open_pro_sound = 1;
	//g_dq_fs_init_set.open_mode = SYS_OPEN_MODE_SIN;
	g_dq_fs_init_set.admin_status = 0;
	g_dq_fs_init_set.wifi_flag = 0;
	//g_dq_fs_init_set.business_flag = 0;
	//for(i=0;i<8;i++)
	//	g_dq_fs_init_set.check_data[i] = 0xFF; 
	return mmi_dq_fs_clr_set();//mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_pwd_string_to_byte(unsigned char *input_pwd,unsigned char pwd_len,unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char bit_l = 0;
	unsigned char bit_h = 0;

	for(i=0;i<pwd_len;i++)
	{
		bit_l = *(input_pwd+i)&0x0F;
		i++;
		if(i < pwd_len)
			bit_h = *(input_pwd+i)&0x0F;
		else
			bit_h = 0xF;
		*output_pwd++ = bit_l<<4|bit_h;
	}
	return;
}
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_pwd_byte_to_string(unsigned char *input_pwd,unsigned char *output_pwd)
{
	unsigned char i = 0;
	unsigned char pwd = 0;
	unsigned char len = 0;
	for(i=0;i<4;i++)
	{
		pwd = *(input_pwd+i);
		if(pwd == 0xFF)
			break;
		else 
		{
			*output_pwd++ = (pwd&0xF0)>>4;
			len++;
		}
		if((pwd&0x0F) == 0x0F)
			break;
		else
		{
			*output_pwd++ = pwd&0x0F;
			len++;
		}
	}
	return len;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd(unsigned char *input_pwd,unsigned char len,fds_use_type type)
{
	unsigned char i = 0;
	unsigned char k = 0;
	unsigned char password[4];
	unsigned char ret_val = 0xFF;
	
	memset(password,0xFF,sizeof(password));
	mmi_dq_fs_pwd_string_to_byte(input_pwd,len,password);

	for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
	{
		if(g_dq_fs_pwd[i].flag != FDS_USE_TYPE_INVALID)
		{
			for(k=0;k<4;k++)
			{
				if(password[k] != g_dq_fs_pwd[i].key_pwd[k])
					break;
			}
			if(k == 4)
			{
				break;
			}
		}
	}
	if(i<MMI_DQ_FS_PWD_MAX_NUM)
	{
		if((g_dq_fs_pwd[i].flag == type)||(type == FDS_USE_TYPE_ALL))
			ret_val = i;
		else
			ret_val = 0xFF;
	}
	else
		ret_val = 0xFF;
	
	return ret_val;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd_for_open(unsigned char *input_pwd,unsigned char len)
{
	unsigned char i = 0,n = 0;
	unsigned char k,j;
	unsigned char password[8];
	unsigned char passlen = 0;
	unsigned char ret_val = 0xFF;
	
	for(i=0;i<MMI_DQ_FS_PWD_MAX_NUM;i++)
	{
		if(g_dq_fs_pwd[i].flag == FDS_USE_TYPE_INVALID)
			continue;
		if(len !=6 && (g_dq_fs_pwd[i].key_pwd[0]==0x12&&g_dq_fs_pwd[i].key_pwd[1]==0x34
			&&g_dq_fs_pwd[i].key_pwd[2]==0x56&&g_dq_fs_pwd[i].key_pwd[3]==0xff))
			continue;
		memset(password,0xFF,sizeof(password));
		passlen = mmi_dq_fs_pwd_byte_to_string(g_dq_fs_pwd[i].key_pwd,password);
		for(k = 0;k+passlen <= len; k++)
		{
			for(j=0;j<passlen;i++)
			{
				if(password[j] != input_pwd[k+j])
					break;
			}
			if(j==passlen)
				break;
		}
		if(j == passlen)
			break;
	}
	
	if(i<MMI_DQ_FS_PWD_MAX_NUM)
	{
		return 1;
	}
	else
	{
		unsigned char adminword[8];
		unsigned char checkCode_out[8];
		bool pass = false;
		memset(adminword,0xFF,sizeof(adminword));
		passlen = mmi_dq_fs_pwd_byte_to_string(g_dq_fs_pwd[0].key_pwd,adminword);
		for(i=0;i<8;i++)
		{
			if(adminword[i]==0xFF)
				adminword[i] = 0;
			else
				adminword[i] += '0';

			if(input_pwd[i]==0xFF)
				password[i] = 0;
			else
				password[i] = input_pwd + '0';
		}
		pass = dq_check_otp((char *)password,(char *)adminword,g_dq_fs_init_set.check_data,checkCode_out);
		if(pass == true)
		{
			memcpy(g_dq_fs_init_set.check_data,checkCode_out,8);
			mmi_dq_fds_write(MID_FDS_FILE_SET,(unsigned char *)&g_dq_fs_init_set,sizeof(mmi_fs_setting));
			return 1;
		}
	}
	return 0;
}


/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pwd(unsigned char *pwd,unsigned char pwd_size,fds_use_type type)
{
	unsigned char i = 0xFF;
	unsigned char password[4];

	if(type == FDS_USE_TYPE_ADMIN)
		i = 0;
	else if (type == FDS_USE_TYPE_110)
		i = 1;
	else if(type == FDS_USE_TYPE_USER)
		i = 2;
	
	if(i<MMI_DQ_FS_PWD_MAX_NUM)
	{
		memset(password,0xFF,sizeof(password));
		//g_dq_fs_pwd[i].index = i;
		mmi_dq_fs_pwd_string_to_byte(pwd,pwd_size,password);
		memcpy((char *)g_dq_fs_pwd[i].key_pwd,(const char *)password,4);
		g_dq_fs_pwd[i].flag = type;
		return	mmi_dq_fds_write(MID_FDS_FILE_PWD, (unsigned char *)g_dq_fs_pwd,sizeof(mmi_fs_pwd)*MMI_DQ_FS_PWD_MAX_NUM);
		
	}
	return RET_FAIL;
}

#if defined (__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_fp_unuse_index(void)
{
	unsigned char i = 2;
	
	for(;i<MMI_DQ_FS_FP_MAX_NUM;i++)
	{
		if(g_dq_fs_fp[i].fp_index == 0xFF)
			break;
	}
	if(i>=MMI_DQ_FS_FP_MAX_NUM)
		return 0xFF;
	return i;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_check_fp(unsigned char fp_index, fds_use_type type)
{
	if((fp_index < MMI_DQ_FS_FP_MAX_NUM) && (g_dq_fs_fp[fp_index].fp_index == fp_index) && ((g_dq_fs_fp[fp_index].flag == type)||(type == FDS_USE_TYPE_ALL)))
		return RET_SUCESS;
	else
		return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_fp(unsigned char fs_index,fds_use_type type)
{
	g_dq_fs_fp[fs_index].fp_index = fs_index;
	g_dq_fs_fp[fs_index].flag = type;
	return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_fp(unsigned char fp_index,fds_use_type type)
{
	if(mmi_dq_fs_check_fp(fp_index,type) == RET_SUCESS)
	{
		g_dq_fs_fp[fp_index].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_fp[fp_index].fp_index = 0xFF;
		return mmi_dq_fds_write(MID_FDS_FILE_FP, (unsigned char *)g_dq_fs_fp, sizeof(mmi_fs_fp)*MMI_DQ_FS_FP_MAX_NUM);
	}
	return RET_FAIL;
}
#endif


#ifdef __LOCK_RFID_CARD_SUPPORT__

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_rfid_unuse_index(void)
{
	unsigned char i = 0;

	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		if(g_dq_fs_rfid[i].index == 0xFF)
			break;
	}

	if(i>=MMI_DQ_FS_RFID_MAX_NUM)
		return 0xFF;
	return i;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_rfid(unsigned char *sec_data, fds_use_type type)
{
	unsigned char i = 0,j = 0;
	
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		for(j=0;j<RFID_SEC_DATA_LEN;j++)
		{
			if(g_dq_fs_rfid[i].sec_data[j] != sec_data[j])
				break;
		}
		if(j == RFID_SEC_DATA_LEN)
			break;
	}
	if(i<MMI_DQ_FS_RFID_MAX_NUM&&((g_dq_fs_rfid[i].flag == type)||(type == FDS_USE_TYPE_ALL)))
	{
		return i;
	}
	else
	{
		return 0xFF;
	}
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_rfid(unsigned char *sec_data, fds_use_type type)
{
	unsigned char i = 0,j = 0;
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		if(g_dq_fs_rfid[i].index == 0xFF)
			break;
	}
	if(i < MMI_DQ_FS_RFID_MAX_NUM)
	{
		g_dq_fs_rfid[i].index = i;
		g_dq_fs_rfid[i].flag = type;
		for(j=0;j<RFID_SEC_DATA_LEN;j++)
		{
			g_dq_fs_rfid[i].sec_data[j] = sec_data[j];
		}
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
	}
	return RET_FAIL;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_rfid(unsigned char rfid_index)
{
	if(rfid_index < MMI_DQ_FS_RFID_MAX_NUM && g_dq_fs_rfid[rfid_index].index == rfid_index)
	{
		g_dq_fs_rfid[rfid_index].index = 0xFF;
		g_dq_fs_rfid[rfid_index].flag = FDS_USE_TYPE_INVALID;
		memset(g_dq_fs_rfid[rfid_index].sec_data,0xFF,sizeof(g_dq_fs_rfid[rfid_index].sec_data));
		return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
	}
	return RET_FAIL;
}


/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_clr_rfid(void)
{
	unsigned char i = 0;
	
	for(i=0;i<MMI_DQ_FS_RFID_MAX_NUM;i++)
	{
		g_dq_fs_rfid[i].flag = FDS_USE_TYPE_INVALID;
		g_dq_fs_rfid[i].index = 0xFF;
		memset(g_dq_fs_rfid[i].sec_data,0xFF,sizeof(g_dq_fs_rfid[i].sec_data));
	}
	return mmi_dq_fds_write(MID_FDS_FILE_RF, (unsigned char *)g_dq_fs_rfid, sizeof(mmi_fs_rfid)*MMI_DQ_FS_RFID_MAX_NUM);
}

#endif

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_open_mode(sys_open_mode mode)
{
	if(g_dq_fs_init_set.open_mode == mode)
		return RET_SUCESS;

	g_dq_fs_init_set.open_mode = mode;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
	
}
/*
parameter: 
	none
return :
	none
*/
sys_open_mode mmi_dq_fs_get_open_mode(void)
{
	return g_dq_fs_init_set.open_mode;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pro_sound(unsigned char flag)
{
	if(g_dq_fs_init_set.open_pro_sound == flag)
		return RET_SUCESS;
	
	g_dq_fs_init_set.open_pro_sound = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));

}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pro_sound_state(void)
{
	return g_dq_fs_init_set.open_pro_sound;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_init_flag(void)
{
	return g_dq_fs_init_set.init_flag;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_init_flag(unsigned char flag)
{
	g_dq_fs_init_set.init_flag = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_factory_flag(unsigned char flag)
{
	g_dq_fs_init_set.factory_flag= flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_factory_flag(void)
{
	return g_dq_fs_init_set.factory_flag;
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_admin_status(void)
{
	return g_dq_fs_init_set.admin_status;
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_admin_status(unsigned char status)
{
	g_dq_fs_init_set.admin_status = status;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_wifi_setting(unsigned char flag)
{
	g_dq_fs_init_set.wifi_flag = flag;
	return mmi_dq_fds_write(MID_FDS_FILE_SET, (unsigned char *)&g_dq_fs_init_set, sizeof(mmi_fs_setting));
}

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_wifi_setting(void)
{
	return g_dq_fs_init_set.wifi_flag;
}



























#endif
