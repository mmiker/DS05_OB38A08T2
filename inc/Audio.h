#ifndef __AUDIO_H__
#define __AUDIO_H__

typedef enum AUD_PLAY_ID
{
	AUD_ID_PRO_AUDIO = 1,
	AUD_ID_PRO_AUDIO2 = 2,
	AUD_ID_PRO_AUDIO_SUC = 3,

	AUD_ID_ADD_FP = 4,
	AUD_ID_ADD_FAIL = 5,	   ///录入失败
	AUD_ID_ADD_SUCCESS = 6,	   //录入成功
	AUD_ID_PRESS_FP = 7,	   //请按手指
	AUD_ID_PRESS_FP_AGAIN = 8, //请再按手指

	AUD_ID_DOOR_OPEN = 9,	//验证通过
	AUD_ID_DOOR_CLOSE = 10, //请随手关门

	AUD_ID_FP_FULL = 11,		   //指纹用户已满
	AUD_ID_TIMEOUT = 12,		   //操作超时
	AUD_ID_SET_ALARM_SUCESS = 13,  //振动警戒已开启
	AUD_ID_FP_EXIST = 14,		   //该指纹已存在
	AUD_ID_SYS_SIN_OPEN_MODE = 15, //单认证模式
	AUD_ID_SYS_DBL_OPEN_MODE = 16, //双认证模式
	AUD_ID_INPUT_PWD = 17,		   //请输入密码，按#键结束
	AUD_ID_CHECK_FAIL_RETRY = 18,  //验证失败，请重新输入

	AUD_ID_LOW_BATTERY = 19, //电压低，请换电池

	AUD_ID_RETRY = 20, //请重新输入

	AUD_ID_INPUT_FAIL_RETRY = 21, //输入错误，请重新输入
	AUD_ID_INPUT_ADMIN_PWD = 22,  //请输入管理员密码，并按#键确认

	AUD_ID_SYSTEM = 23,			 //系统设置
	AUD_ID_INPUT_NEW_PWD = 24,	 //请输入新密码
	AUD_ID_PWD_INPUT_AGAIN = 25, //请再次输入

	AUD_ID_SET_SUCCESS = 26,   //设置成功
	AUD_ID_DEL_FAIL = 27,	   //删除失败
	AUD_ID_DEL_SUCCESS = 28,   //删除成功
	AUD_ID_SYS_OPEN_MODE = 29, //常用模式请按1，安全模式请按2

	AUD_ID_CLOSE_PRO_AUDIO_SUCESS = 30, //静音模式已关闭
	AUD_ID_OPEN_PRO_AUDIO_SUCESS = 31,	//静音模式已开启

	AUD_ID_OPRATION_FAIL = 32,	  //操作失败
	AUD_ID_OPRATION_SUCCESS = 33, //操作成功

	AUD_ID_RESTORE_SUCESS = 34, //初始化成功

	AUD_ID_XIANGTI_SELECT = 35, //1号箱体请按1，2号箱体请按2

	AUD_ID_LANGUAGE_SELECT = 36, //鐠佸墽鐤嗙拠顓♀枅

	AUD_ID_WIFI_CONNECT_OK = 36, //配网成功

	AUD_ID_WIFI_CONNECTING = 37, //配网中

	AUD_ID_SET_FAILED = 38, //设置失败

	AUD_PWD_EXIST = 39, //该密码已存在

	AUD_ADD_FP_FIRST = 40, //请先添加指纹

	AUD_ID_SYSTEM_XIEPO = 44, //系统设置胁迫

	AUD_ID_OUT_OPEN = 45, //开启出差模式

	AUD_ID_OUT_CLOSED = 46, //关闭出差模式

	AUD_NEXT_LANGUAGE = 47,


	// #endif
	//-----------------------------------------------------------------------------------------------------------------------------------

	AUD_ID_INPUT_68_PWD = AUD_ID_INPUT_PWD,		 //请输??-8位密码，??键结??
	AUD_ID_PWD_68_LEN = AUD_ID_INPUT_FAIL_RETRY, //密码应为6-8位，请重新输??
	//AUD_ID_ADD_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//号密码添加成??
	AUD_ID_PWD_NOT_SAME = AUD_ID_INPUT_FAIL_RETRY, //两次输入的密码不一??

	AUD_ID_INPUT_OLD_PWD = AUD_ID_INPUT_PWD,			 //请输入旧密码，按#键结??
	AUD_ID_INPUT_NEW_PWD_AGAIN = AUD_ID_PWD_INPUT_AGAIN, //请再输入新密码，??键结??
	AUD_ID_PWD_NOT_EXIST = AUD_ID_CHECK_FAIL_RETRY,		 //密码不存在，请重新输??
	AUD_ID_CHG_PWD_SUCESS = AUD_ID_SET_SUCCESS,			 //号密码修改成??
	AUD_ID_CHG_FAIL = AUD_ID_OPRATION_FAIL,				 //修改失败，请联系管理??
	AUD_ID_PWD_OLD_NEW_NOT_SAME = AUD_ID_OPRATION_FAIL,	 //新旧密码不能一??

	AUD_ID_ADD_FP_SUCESS = AUD_ID_ADD_SUCCESS,		 //号指纹添加成??
	AUD_ID_ADD_FAIL_RETRY = AUD_ID_ADD_FAIL,		 //添加失败，请重试
	AUD_ID_FP_TWICE_NOT_SAME = AUD_ID_OPRATION_FAIL, //两次输入的指纹不一???
	AUD_ID_INPUT_DEL_FP_NUM = AUD_ID_PRESS_FP,		 //请输入要删除的编号或指纹，按#键结??
	//AUD_ID_CHG_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//修改失败，请重试
	//AUD_ID_CHG_CONTINUE_CONFIRM 	= 9+AUD_BASE_ID_MAX,//继续修改请按#，返回请??
	//0x27
	AUD_ID_FP_NOT_EXIST = AUD_ID_CHECK_FAIL_RETRY, //指纹不存在，请重新输??
	//AUD_ID_DEL_FP_CONFIRM 			= 33+AUD_BASE_ID_MAX,//号指纹按#确认删除，取消请??
	AUD_ID_PRESS_DEL_FP_AGAIN = AUD_ID_PRESS_FP_AGAIN, //请再按一次要删除的指??
	AUD_ID_DEL_FP_SUCESS = AUD_ID_DEL_SUCCESS,		   //号指纹删除成??
	AUD_ID_DEL_FAIL_RETRY = AUD_ID_DEL_FAIL,		   //删除失败，请重试

	AUD_ID_INPUT_NEW_ADMIN_PWD = AUD_ID_INPUT_NEW_PWD, //请输入新管理员密码，??键结??
	//
	AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN = AUD_ID_PWD_INPUT_AGAIN, //请再次输入新管理员密码，??键结??
	AUD_ID_CHG_ADMIN_PWD_SUCESS = AUD_ID_SET_SUCCESS,		   //管理员密码修改成??
	AUD_ID_PWD_EXIST = AUD_ID_OPRATION_FAIL,				   //密码已存在，请重新输??

	//AUD_ID_NEW_ADMIN_FP 						= AUD_BASE_ID_PRESS_FP,//请按新的管理员指??
	//AUD_ID_ADD_NO1_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//1号管理指纹添加成??
	//AUD_ID_ADD_NO2_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//2号管理指纹添加成??
	AUD_ID_CLOSE_PRO_AUDIO_FAIL = AUD_ID_OPRATION_FAIL, //关闭提示音失??
	AUD_ID_OPEN_PRO_AUDIO_FAIL = AUD_ID_OPRATION_FAIL,	//开启提示音失败

	AUD_ID_SIN_OPEN_MODE_SUCESS = AUD_ID_SYS_SIN_OPEN_MODE, //单开门方式设置成??
	AUD_ID_SIN_OPEN_MODE_FAIL = AUD_ID_OPRATION_FAIL,		//单开门方式设置失??
	AUD_ID_DBL_OPEN_MODE_SUCESS = AUD_ID_SYS_DBL_OPEN_MODE, //双开门方式设置成??
	AUD_ID_DBL_OPEN_MODE_FAIL = AUD_ID_OPRATION_FAIL,		//双开门方式设置失??
	AUD_ID_RESTORE_FAIL = AUD_ID_OPRATION_FAIL,				//恢复出厂设置失败
	//AUD_ID_ADD_ADMIN_PWD_FIRST 					= 51+AUD_BASE_ID_MAX,//为了您的使用安全，请先添加管理员密码，按#键结??
	//AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN 			= 6+AUD_BASE_ID_MAX,//请再次输入管理员密码，按#键结??
	//AUD_ID_ADD_ADMIN_PWD_INIT_SUCESS 			= AUD_BASE_ID_SUCCESS,//管理员密码添加成??
	AUD_ID_PWD_WRONG_TRY = AUD_ID_CHECK_FAIL_RETRY, //密码错误,请重??
	AUD_ID_FP_WRONG_TRY = AUD_ID_CHECK_FAIL_RETRY,	//指纹错误，请重试
	//AUD_ID_RFCARD_WRONG_TRY 					= 60+AUD_BASE_ID_MAX,//RF卡错误，请重??
	AUD_ID_RONG_TIMES_EXCEED = AUD_ID_OPRATION_FAIL, //错误次数已超限制，请**分钟后重??

#ifdef __LANGUAGE_SELECT__
	AUD_ID_LANGUAGE_SELECT_SUCESS = AUD_ID_SET_SUCCESS,
	AUD_ID_LANGUAGE_SELECT_FAIL = AUD_ID_OPRATION_FAIL,
#endif
	AUD_ID_WIFI_UNFINDE = AUD_ID_OPRATION_FAIL,

	AUD_ID_MAX_COUNT,
	AUD_ID_INVALID_INDEX = 0xFF,
} AUD_PLAY_ID;

void Audio_Init(void);

void Audio_Play(AUD_PLAY_ID aud_id);

void Audio_Stop(void);

#endif
