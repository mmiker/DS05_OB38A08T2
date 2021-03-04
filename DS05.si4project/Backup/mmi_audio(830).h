#ifndef __MMI_AUDIO_H__
#define __MMI_AUDIO_H__

#include "string.h"
#include "mmi_feature.h"

#define __AUD_PLAY_BY_ARR__

typedef enum 
{
//---------------------------------------------------
	AUD_ID_PRO_AUDIO				=1,
	AUD_ID_PRO_AUDIO2			=2,
	AUD_ID_PRO_AUDIO_SUC			=3,

	AUD_ID_ADD_FP					=4, 
	AUD_ID_ADD_FAIL 				= 5,///¼��ʧ��
	AUD_ID_ADD_SUCCESS 			= 6,//¼��ɹ�
	AUD_ID_PRESS_FP 				= 7,//�밴��ָ
	AUD_ID_PRESS_FP_AGAIN 		= 8,//���ٰ���ָ
	
	AUD_ID_DOOR_OPEN 				= 9,//��֤ͨ��
	AUD_ID_DOOR_CLOSE 			= 10,//�����ֹ���
	
	AUD_ID_FP_FULL 				= 11,//ָ���û�����
	AUD_ID_TIMEOUT				=12,//������ʱ
	AUD_ID_SET_ALARM_SUCESS		=13,//�񶯾����ѿ���
	AUD_ID_FP_EXIST 				= 14,//��ָ���Ѵ���
	AUD_ID_SYS_SIN_OPEN_MODE = 15,//����֤ģʽ
	AUD_ID_SYS_DBL_OPEN_MODE = 16,//˫��֤ģʽ
	AUD_ID_INPUT_PWD				= 17,//���������룬��#������
	AUD_ID_CHECK_FAIL_RETRY					=18,//��֤ʧ�ܣ�����������
	//AUD_ID_CHECK_SUCCESS				=19,

	AUD_ID_LOW_BATTERY 			= 19,//��ѹ�ͣ��뻻���

	AUD_ID_RETRY				=20,//����������

	AUD_ID_INPUT_FAIL_RETRY		=21,//�����������������
	AUD_ID_INPUT_ADMIN_PWD 		= 22,//���������Ա���룬����#��ȷ��

	AUD_ID_SYSTEM 				= 23,//ϵͳ����
	AUD_ID_INPUT_NEW_PWD 		= 24,//������������
	AUD_ID_PWD_INPUT_AGAIN 			= 25,//���ٴ�����

	AUD_ID_SET_SUCCESS			=26,//���óɹ�
	AUD_ID_DEL_FAIL					= 27,//ɾ��ʧ��
	AUD_ID_DEL_SUCCESS 			= 28,//ɾ���ɹ�
	AUD_ID_SYS_OPEN_MODE 		=29,//����ģʽ�밴1����ȫģʽ�밴2 
	
	AUD_ID_CLOSE_PRO_AUDIO_SUCESS 	= 30,//����ģʽ�ѹر�
	AUD_ID_OPEN_PRO_AUDIO_SUCESS 	= 31,//����ģʽ�ѿ���

	AUD_ID_OPRATION_FAIL				=32,//����ʧ��
	AUD_ID_OPRATION_SUCCESS			=33,//�����ɹ�

	AUD_ID_RESTORE_SUCESS 			= 34,//��ʼ���ɹ�
	
	AUD_ID_XIANGTI_SELECT=35,//1�������밴1��2�������밴2  

	//AUD_ID_YOU_ARE_WELCOME 			= 36,//娆㈣繋浣跨敤鐐硅叮鐗╄仈鏅鸿兘閿?

	AUD_ID_LANGUAGE_SELECT			= 36,//璁剧疆璇█
	
	AUD_ID_WIFI_CONNECT_OK			= 36,//�����ɹ�

	AUD_ID_WIFI_CONNECTING			= 37,//������

	AUD_ID_SET_FAILED		= 38,//����ʧ��

	AUD_PWD_EXIST       = 39,//�������Ѵ���
	
	AUD_ADD_FP_FIRST			=	40,//�������ָ��

	AUD_ID_SYSTEM_XIEPO			=	44,//ϵͳ����в��

	AUD_ID_OUT_OPEN 		=	45,//��������ģʽ
	
	AUD_ID_OUT_CLOSED 		=	46,//�رճ���ģʽ


	AUD_NEXT_LANGUAGE			=	47,

//---------------------------------------------------
	
	AUD_ID_INPUT_68_PWD				= AUD_ID_INPUT_PWD,//������6-8λ���룬��#������
	AUD_ID_PWD_68_LEN 				= AUD_ID_INPUT_FAIL_RETRY,//����ӦΪ6-8λ������������
	//AUD_ID_ADD_PWD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��������ӳɹ�
	AUD_ID_PWD_NOT_SAME 			= AUD_ID_INPUT_FAIL_RETRY,//������������벻һ��
	//AUD_ID_PWD_NOT_SAME_RETRY		= AUD_ID_INPUT_FAIL_RETRY,//������������벻һ��,����������
	//AUD_ID_CONTINUE_ADD_PWD 		= 9+AUD_BASE_ID_MAX,//��������밴#�������밴*
	//AUD_ID_PWD_FULL 				= AUD_BASE_ID_MEM_FULL,//��������������ϵ����Ա
	AUD_ID_INPUT_OLD_PWD 			= AUD_ID_INPUT_PWD,//����������룬��#������
	AUD_ID_PWD_NOT_EXIST 			= AUD_ID_CHECK_FAIL_RETRY,//���벻���ڣ�����������
	//AUD_ID_INPUT_NEW_PWD 			= 21+AUD_BASE_ID_MAX,//�����������룬��#������
	AUD_ID_INPUT_NEW_PWD_AGAIN 		= AUD_ID_PWD_INPUT_AGAIN,//�������������룬��#������
	AUD_ID_CHG_PWD_SUCESS 			= AUD_ID_SET_SUCCESS,//�������޸ĳɹ�
	AUD_ID_CHG_FAIL 				= AUD_ID_OPRATION_FAIL,//�޸�ʧ�ܣ�����ϵ����Ա
	AUD_ID_PWD_OLD_NEW_NOT_SAME 	= AUD_ID_OPRATION_FAIL,//�¾����벻��һ��
	//AUD_ID_INPUT_DEL_NUM 			= 27+AUD_BASE_ID_MAX,//������Ҫɾ���ı�Ż����룬��#������
	AUD_ID_NUM_NOT_EXIST 			= AUD_ID_CHECK_FAIL_RETRY,//��Ų����ڣ�����������
	//AUD_ID_DEL_PWD_CONFIRM 			= 33+AUD_BASE_ID_MAX,//�����밴#��ȷ��ɾ����ȡ���밴*��
	//AUD_ID_INPUT_DEL_PWD_AGAIN 		= AUD_BASE_ID_PWD_INPUT_AGAIN,//���ٴ�����Ҫɾ��������
	//AUD_ID_DEL_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//������ɾ���ɹ�
	//AUD_ID_DEL_FAIL					= 12+AUD_BASE_ID_MAX,//ɾ��ʧ�ܣ�����ϵ����Ա
	//AUD_ID_DEL_CONFIRM 				= 9+AUD_BASE_ID_MAX,//����ɾ���밴#�������밴*
	//AUD_ID_CLR_PWD_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��#��ȷ��ɾ���������룬ȡ���밴*��
	//AUD_ID_CLR_PWD_SUCESS 			= AUD_BASE_ID_SUCCESS,//ɾ����������ɹ�
	//AUD_ID_CLR_PWD_FAIL 			= AUD_BASE_ID_FAIL,//ɾ����������ʧ��
	AUD_ID_ADD_FP_SUCESS 			= AUD_ID_ADD_SUCCESS,//��ָ����ӳɹ�
	AUD_ID_ADD_FAIL_RETRY 			= AUD_ID_ADD_FAIL,//���ʧ�ܣ�������
	AUD_ID_FP_TWICE_NOT_SAME		= AUD_ID_OPRATION_FAIL,//���������ָ�Ʋ�һ��
	AUD_ID_FP_FULL 					= AUD_BASE_ID_MEM_FULL,//ָ������������ϵ����Ա
	AUD_ID_PRESS_OLD_FP 			= AUD_BASE_ID_PRESS_OLD_FP,//�밴�ɵ�ָ��
	AUD_ID_PRESS_NEW_FP 			= AUD_BASE_ID_PRESS_NEW_FP,//�밴�µ�ָ��
	AUD_ID_PRESS_NEW_FP_AGAIN 		= AUD_BASE_ID_PRESS_FP_AGAIN,//���ٰ�һ����ָ��
	AUD_ID_CHG_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//��ָ���޸ĳɹ�
	AUD_ID_FP_NOT_SAME 				= AUD_BASE_ID_FP_SAME,//�¾�ָ�Ʋ���һ��	
	AUD_ID_INPUT_DEL_FP_NUM 		= AUD_BASE_ID_INPUT_DEL_FP,//������Ҫɾ���ı�Ż�ָ�ƣ���#������
	AUD_ID_CHG_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//�޸�ʧ�ܣ�������
	AUD_ID_CHG_CONTINUE_CONFIRM 	= 9+AUD_BASE_ID_MAX,//�����޸��밴#�������밴*
	//0x27
	AUD_ID_FP_NOT_EXIST 			= 39+AUD_BASE_ID_MAX,//ָ�Ʋ����ڣ�����������
	AUD_ID_DEL_FP_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��ָ�ư�#ȷ��ɾ����ȡ���밴*
	AUD_ID_PRESS_DEL_FP_AGAIN 		= AUD_BASE_ID_PRESS_FP_AGAIN,//���ٰ�һ��Ҫɾ����ָ��
	AUD_ID_DEL_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//��ָ��ɾ���ɹ�
	AUD_ID_DEL_FAIL_RETRY 			= 36+AUD_BASE_ID_MAX,//ɾ��ʧ�ܣ�������
	AUD_ID_CLR_FP_CONFIRM 			= 33+AUD_BASE_ID_MAX,//��#ȷ��ɾ������ָ�ƣ�ȡ���밴*
	AUD_ID_CLR_FP_SUCESS 			= AUD_BASE_ID_SUCCESS,//ɾ������ָ�Ƴɹ�
	AUD_ID_CLR_FP_FAIL 				= AUD_BASE_ID_FAIL,//ɾ������ָ��ʧ��
	AUD_ID_PRESS_RFCARD 			= AUD_BASE_ID_PRESS_RFCARD,//��ˢ��
	AUD_ID_PRESS_RFCARD_AGAIN		= AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ��
	AUD_ID_ADD_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF����ӳɹ�
	AUD_ID_RFCARD_EXIST 			= AUD_BASE_ID_RFCARD_EXIST,//RF���Ѵ��ڣ��뻻�ſ�
	AUD_ID_RFCARD_FULL 				= AUD_BASE_ID_MEM_FULL,//RF������������ϵ����Ա
	AUD_ID_PRESS_OLD_RFCARD 		= AUD_BASE_ID_PRESS_OLD_RFCARD,//��ˢ�ɿ�
	AUD_ID_PRESS_NEW_RFCARD 		= AUD_BASE_ID_PRESS_NEW_RFCARD,//��ˢ�¿�
	AUD_ID_PRESS_NEW_RFCARD_AGAIN = AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ���¿�
	AUD_ID_CHG_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF���޸ĳɹ�
	AUD_ID_RFCARD_NOT_SAME 			= AUD_BASE_ID_RFCARD_SAME,//�¾�RF������һ��
	AUD_ID_INPUT_DEL_RFCARD_NUM = AUD_BASE_ID_INPUT_DEL_RFCARD,//������Ҫɾ���ı�Ż�RF������#������
	AUD_ID_RFCARD_NOT_EXIST 		= 42+AUD_BASE_ID_MAX,//RF�������ڣ�����������
	AUD_ID_DEL_RFCARD_CONFIRM 		= 33+AUD_BASE_ID_MAX,//��RF����#ȷ��ɾ����ȡ���밴*
	AUD_ID_PRESS_DEL_RFCARD_AGAIN = AUD_BASE_ID_PRESS_RFCARD_AGAIN,//����ˢһ��Ҫɾ����RF��
	AUD_ID_DEL_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//��RF��ɾ���ɹ�
	AUD_ID_CLR_RFCARD_CONFIRM 		= 33+AUD_BASE_ID_MAX,//��#ȷ��ɾ������RF����ȡ���밴*
	AUD_ID_CLR_RFCARD_SUCESS 		= AUD_BASE_ID_SUCCESS,//ɾ������RF���ɹ�
	AUD_ID_CLR_RFCARD_FAIL 			= AUD_BASE_ID_FAIL,//ɾ������RF��ʧ��
	AUD_ID_INPUT_ADMIN_PWD 			= 45+AUD_BASE_ID_MAX,//���������Ա���룬��#������
	AUD_ID_INPUT_NEW_ADMIN_PWD = 0+AUD_BASE_ID_MAX,//�������¹���Ա���룬��#������
	//
	AUD_ID_INPUT_NEW_ADMIN_PWD_AGAIN 			= 6+AUD_BASE_ID_MAX,//���ٴ������¹���Ա���룬��#������
	AUD_ID_CHG_ADMIN_PWD_SUCESS					= AUD_BASE_ID_SUCCESS,//����Ա�����޸ĳɹ�
	AUD_ID_PWD_EXIST 							= 48+AUD_BASE_ID_MAX,//�����Ѵ��ڣ�����������
	AUD_ID_NEW_ADMIN_FP 						= AUD_BASE_ID_PRESS_FP,//�밴�µĹ���Աָ��
	AUD_ID_ADD_NO1_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//1�Ź���ָ����ӳɹ�
	AUD_ID_ADD_NO2_ADMIN_FP_SUCESS 				= AUD_BASE_ID_SUCCESS,//2�Ź���ָ����ӳɹ�
	AUD_ID_CLOSE_PRO_AUDIO_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//�ر���ʾ���ɹ�
	AUD_ID_CLOSE_PRO_AUDIO_FAIL 				= AUD_BASE_ID_SET_FAIL,//�ر���ʾ��ʧ��
	AUD_ID_OPEN_PRO_AUDIO_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//������ʾ���ɹ�
	AUD_ID_OPEN_PRO_AUDIO_FAIL 					= AUD_BASE_ID_SET_FAIL,//������ʾ��ʧ��
	AUD_ID_SIN_OPEN_MODE_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//�����ŷ�ʽ���óɹ�
	AUD_ID_SIN_OPEN_MODE_FAIL 					= AUD_BASE_ID_SET_FAIL,//�����ŷ�ʽ����ʧ��
	AUD_ID_DBL_OPEN_MODE_SUCESS 				= AUD_BASE_ID_SET_SUCESS,//˫���ŷ�ʽ���óɹ�
	AUD_ID_DBL_OPEN_MODE_FAIL 					= AUD_BASE_ID_SET_FAIL,//˫���ŷ�ʽ����ʧ��
	AUD_ID_RESTORE_SUCESS 						= AUD_BASE_ID_SYS_RESTORE_SUCCESS,//�ָ��������óɹ�
	AUD_ID_RESTORE_FAIL 						= AUD_BASE_ID_SET_FAIL,//�ָ���������ʧ��
	AUD_ID_ADD_ADMIN_PWD_FIRST 					= 51+AUD_BASE_ID_MAX,//Ϊ������ʹ�ð�ȫ��������ӹ���Ա���룬��#������
	AUD_ID_INPUT_ADMIN_PWD_INIT_AGAIN 			= 6+AUD_BASE_ID_MAX,//���ٴ��������Ա���룬��#������
	AUD_ID_ADD_ADMIN_PWD_INIT_SUCESS 			= AUD_BASE_ID_SUCCESS,//����Ա������ӳɹ�
	AUD_ID_DOOR_OPEN 							= AUD_BASE_ID_DOOR_OPEN,//�ѿ���
	AUD_ID_DOOR_CLOSE 							= AUD_BASE_ID_DOOR_CLOSE,//�ѹ���
	AUD_ID_PWD_WRONG_TRY 						= 54+AUD_BASE_ID_MAX,//�������,������
	AUD_ID_FP_WRONG_TRY 						= 57+AUD_BASE_ID_MAX,//ָ�ƴ���������
	AUD_ID_RFCARD_WRONG_TRY 					= 60+AUD_BASE_ID_MAX,//RF������������
	AUD_ID_RONG_TIMES_EXCEED 					= AUD_BASE_ID_RONG_TIMES_EXCEED,//��������ѳ����ƣ���**���Ӻ�����
	AUD_ID_LOW_BATTERY 							= AUD_BASE_ID_LOW_BATTERY,//�����ͣ��뼰ʱ�������
	//AUD_ID_YOU_ARE_WELCOME 						= AUD_BASE_ID_YOU_ARE_WELCOME,//��ӭʹ�õ�Ȥ����������
	AUD_ID_RESTORE_LOCK_CONTINUE_CONFIRM		=33+AUD_BASE_ID_MAX,//��#�ָ��������ã�ȡ���밴*
	AUD_ID_APP_SYN = AUD_BASE_ID_APP_SYN,//��ʹ��appͬ��
	AUD_ID_APP_ADD_SUC = AUD_BASE_ID_SET_SUCESS,//app��ӳɹ�
	AUD_ID_APP_ADD_FAIL = AUD_BASE_ID_SET_FAIL,//app���ʧ��
	AUD_ID_SYSTEM = 132+AUD_BASE_ID_MAX,//ϵͳ
	AUD_ID_SYSTEM2 = 93+AUD_BASE_ID_MAX,//ϵͳ2
	AUD_ID_SYS_PASSWORD = 101+AUD_BASE_ID_MAX,//����
	AUD_ID_SYS_FP = 109+AUD_BASE_ID_MAX,//ָ��
	AUD_ID_SYS_RFCARD = 117+AUD_BASE_ID_MAX,//RF��
	AUD_ID_SYS_ADMIN = 63+AUD_BASE_ID_MAX,//����Ա
	AUD_ID_SYS_ADMIN2 = 128+AUD_BASE_ID_MAX,//����Ա
	AUD_ID_SYS_SETTING = 69+AUD_BASE_ID_MAX,//����
	AUD_ID_SYS_CHG_ADMIN_PWD = AUD_BASE_ID_SYS_CHG_ADMIN_PWD,//�޸Ĺ���Ա����
	AUD_ID_SYS_CHG_ADMIN_FP = 75+AUD_BASE_ID_MAX,//�޸Ĺ���Աָ��
	AUD_ID_SYS_PRO_AUDIO = 81+AUD_BASE_ID_MAX,//��ʾ��
	AUD_ID_SYS_OPEN_MODE = 87+AUD_BASE_ID_MAX,//���ŷ�ʽ
	AUD_ID_SYS_DBL_OPEN_MODE = AUD_BASE_ID_SYS_DBL_OPEN_MODE,//˫���ŷ�ʽ
	AUD_ID_FM_KEY_INPUT = AUD_BASE_ID_FM_KEY_INPUT,//��������а���
	AUD_ID_FM_MOTO = 33+AUD_BASE_ID_MAX,
	AUD_ID_FM_RESET = AUD_BASE_ID_FM_RESTORE,//�밴��λ��
	AUD_ID_FM_TEST_PASS = AUD_BASE_ID_SUCCESS,//���Գɹ�
	AUD_ID_FM_TEST_FAIL = AUD_BASE_ID_FAIL,//����ʧ��
	AUD_ID_SET_SUCESS = AUD_BASE_ID_SET_SUCESS,
	AUD_ID_INPUT_MAX = AUD_BASE_ID_INPUT_END,//��#������

	AUD_ID_SYS_NUM_0 = AUD_BASE_ID_SYS_NUM_0,//0
	AUD_ID_SYS_NUM_1 = AUD_BASE_ID_SYS_NUM_1,//1
	AUD_ID_SYS_NUM_2 = AUD_BASE_ID_SYS_NUM_2,//2
	AUD_ID_SYS_NUM_3 = AUD_BASE_ID_SYS_NUM_3,//3
	AUD_ID_SYS_NUM_4 = AUD_BASE_ID_SYS_NUM_4,//4
	AUD_ID_SYS_NUM_5 = AUD_BASE_ID_SYS_NUM_5,//5
	AUD_ID_SYS_NUM_6 = AUD_BASE_ID_SYS_NUM_6,//6
	AUD_ID_SYS_NUM_7 = AUD_BASE_ID_SYS_NUM_7,//7
	AUD_ID_SYS_NUM_8 = AUD_BASE_ID_SYS_NUM_8,//8
	AUD_ID_SYS_NUM_9 = AUD_BASE_ID_SYS_NUM_9,//9
	AUD_ID_SYS_NUM_S = AUD_BASE_ID_SYS_NUM_S,//*
	AUD_ID_SYS_NUM_H = AUD_BASE_ID_SYS_NUM_H,//#

	AUD_ID_MAX_COUNT,
	AUD_ID_INVALID_INDEX = 0xFF,
}AUD_PLAY_ID;

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_init(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_audio_id(unsigned char text_id);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_stop(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_with_id(unsigned char aud_id);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_tone(void);

/*
parameter: 
	none
return :
	none
*/
void mmi_dq_aud_play_key_num(unsigned char key_val);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_state(void);

/*
parameter: 
	none
return :
	none
*/
unsigned char mmi_dq_aud_get_end_flag(void);

#endif //__MMI_AUDIO_H__

