#ifndef __MMI_FS_H__
#define __MMI_FS_H__

#include "mmi_sys.h"
#include "mmi_rfid.h"
#include "mmi_com.h"


typedef enum
{
	MID_FDS_FILE_SET = 0x00,
	MID_FDS_FILE_PWD = 0x01,
	MID_FDS_FILE_FP = 0x02,
	MID_FDS_FILE_RF = 0x03,
	MID_FDS_FILE_INVALID_ID = 0xFF
}mid_fds_file_id;

typedef enum
{
	FDS_USE_TYPE_ADMIN = 0x00,
	FDS_USE_TYPE_USER = 0x01,
	FDS_USE_TYPE_110 = 0x02,
	FDS_USE_TYPE_ALL = 0x03,
	FDS_USE_TYPE_INVALID = 0xFF
}fds_use_type;

typedef enum
{
	FDS_INIT_LOCK_SUC = 0x01,
	FDS_INIT_APP_SUC = 0x02,
	//FDS_INIT_LOCK_RESTART = 0x03,
	FDS_INIT_INVALID = 0xFF
}fds_init_type;

typedef struct opt_file_block_id
{
	unsigned char		file_id;
	unsigned char	 	block_handle_index;
}opt_file_block_id;

typedef struct mmi_fs_setting
{
	unsigned char init_flag;
	unsigned char open_pro_sound;
	sys_open_mode open_mode;
	unsigned char admin_status;
	unsigned char factory_flag;
	unsigned char wifi_flag;
	unsigned char alarm_flag;
	unsigned char language_flag;
	unsigned char low_power_times;
	unsigned char business_flag;
	unsigned char check_data[8];
}mmi_fs_setting;

typedef struct mmi_fs_pwd
{
	//unsigned char 	index;
	unsigned char 	key_pwd[4];
	fds_use_type 	flag;//0 for admin;1 for user
}mmi_fs_pwd;

typedef struct mmi_fs_fp
{
	//fds_use_type  flag;//0 for admin;1 for user
	unsigned char fp_index;
}mmi_fs_fp;

#ifdef __LOCK_RFID_CARD_SUPPORT__
typedef struct mmi_fs_rfid
{
	unsigned char	index;
	fds_use_type  	flag;//0 for admin;1 for user
	unsigned char 	sec_data[RFID_SEC_DATA_LEN];
}mmi_fs_rfid;
#endif





/*
parameter: 
	none
return :
	none
*/
void mmi_dq_fs_init(void);

/**
  * @brief  手动初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_clr_set(void);

/**
  * @brief  复位初始化
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
RET_VAL mmi_dq_fs_reset(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pwd_unuse_index(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd(unsigned char *input_pwd,unsigned char len,fds_use_type type);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_input_pwd_for_open(unsigned char *input_pwd,unsigned char len);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pwd(unsigned char *pwd,unsigned char size,fds_use_type type);

#if defined (__LOCK_FP_SUPPORT__)
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_fp_unuse_index(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_check_fp(unsigned char fp_index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_fp(unsigned char fs_index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_fp(unsigned char fp_index);
#endif


#ifdef __LOCK_RFID_CARD_SUPPORT__
/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_rfid_unuse_index(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_check_rfid(unsigned char *sec_data, fds_use_type type);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_rfid(unsigned char *sec_data, fds_use_type type);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_del_rfid(unsigned char rfid_index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_clr_rfid(void);
#endif

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_open_mode(sys_open_mode mode);

/*
parameter: 
	none
return :
	none
*/
sys_open_mode mmi_dq_fs_get_open_mode(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_pro_sound(unsigned char flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_pro_sound(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_factory_flag(unsigned char flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_factory_flag(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_wifi_setting(unsigned char flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_wifi_setting(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_alarm_flag(unsigned char flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_alarm_flag(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_fs_set_business_flag(unsigned char flag);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_fs_get_business_flag(void);

#endif
