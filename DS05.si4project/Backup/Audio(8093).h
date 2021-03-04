#ifndef __AUDIO_H__
#define __AUDIO_H__

typedef enum 
{
//---------------------------------------------------
	AUD_BASE_ID_PRO_AUDIO = 1,//������

	AUD_BASE_ID_INPUT_68_PWD = 2,//������6-8λ����
	AUD_BASE_ID_PWD_68_LEN = 3, //����ӦΪ6-8λ
	AUD_BASE_ID_PWD_INPUT_AGAIN = 4,//���ٴ���������
	AUD_BASE_ID_SUCCESS = 5,//�����ɹ�
	AUD_BASE_ID_NOT_SAME = 6,//�������벻һ��
	AUD_BASE_ID_CONTINUE = 7,//�����밴#
	AUD_BASE_ID_FAIL = 8,//����ʧ��
	AUD_BASE_ID_INPUT_OLD_PWD = 9,//�����������
	AUD_BASE_ID_PWD_NOT_EXIST = 10,//���벻����
	AUD_BASE_ID_INPUT_NEW_PWD = 11,//������������
	AUD_BASE_ID_PWD_SAME = 12,//�¾�����һ��
	AUD_BASE_ID_INPUT_DEL_PWD = 13,//������Ҫɾ��������
	AUD_BASE_ID_NUM_NOT_EXIST = 14,//��Ų�����
	AUD_BASE_ID_INPUT_CONFIRM = 15,//ȷ���밴#
	AUD_BASE_ID_PRESS_FP = 16,//�밴��ָ
	AUD_BASE_ID_PRESS_FP_AGAIN = 17,//���ٰ�һ��
	AUD_BASE_ID_FP_SAME = 18,//�¾�ָ��һ��
	AUD_BASE_ID_PRESS_OLD_FP = 19,//�밴�ɵ�ָ��
	AUD_BASE_ID_PRESS_NEW_FP = 20,//�밴�µ�ָ��
	AUD_BASE_ID_INPUT_DEL_FP = 21,//������Ҫɾ����ָ��
	AUD_BASE_ID_FP_NOT_EXIST = 22,//ָ�Ʋ�����
	AUD_BASE_ID_PRESS_RFCARD = 23,//��ˢ��
	AUD_BASE_ID_PRESS_RFCARD_AGAIN = 24,//����ˢһ��
	AUD_BASE_ID_RFCARD_EXIST = 25,//RF���Ѵ���
	AUD_BASE_ID_PRESS_OLD_RFCARD = 26,//��ˢ�ɿ�
	AUD_BASE_ID_PRESS_NEW_RFCARD = 27,//��ˢ�¿�
	AUD_BASE_ID_RFCARD_SAME = 28,//�¾�RF��һ��
	AUD_BASE_ID_INPUT_DEL_RFCARD = 29,//������Ҫɾ����RF��
	AUD_BASE_ID_RFCARD_NOT_EXIST = 30,//RF��������
	AUD_BASE_ID_PWD_EXIST = 31,//�����Ѵ���
	AUD_BASE_ID_INPUT_ADMIN_PWD = 32,//���������Ա����
	AUD_BASE_ID_SET_SUCESS = 33,//���óɹ�
	AUD_BASE_ID_SET_FAIL = 34,//����ʧ��
	AUD_BASE_ID_INPUT_END = 35,//��#������
	AUD_BASE_ID_RETRY = 36,//������
	AUD_BASE_ID_INPUT_BACK = 37,//���ذ�*
	AUD_BASE_ID_CONTACT_ADMIN = 38,//����ϵ����Ա
	AUD_BASE_ID_REINPUT = 39,//����������
	AUD_BASE_ID_ADD_ADMIN_PWD_FIRST = 40,//Ϊ������ʹ�ð�ȫ��������ӹ���Ա����
	AUD_BASE_ID_DOOR_OPEN = 41,//�ѿ���
	AUD_BASE_ID_DOOR_CLOSE = 42,//�ѹ���
	AUD_BASE_ID_PWD_WRONG = 43,//�������
	AUD_BASE_ID_FP_WRONG = 44,//ָ�ƴ���
	AUD_BASE_ID_RFCARD_WRONG = 45,//RF������
	AUD_BASE_ID_RONG_TIMES_EXCEED = 46,//��������ѳ����ƣ����Ժ�����
	AUD_BASE_ID_LOW_BATTERY = 47,//������

	AUD_BASE_ID_SYS_PASSWORD = 48,//����
	AUD_BASE_ID_SYS_FP = 49,//ָ��
	AUD_BASE_ID_SYS_RFCARD = 50,//RF��
	AUD_BASE_ID_SYS_ADMIN = 51,//����Ա
	AUD_BASE_ID_SYS_SETTING = 52,//����
	AUD_BASE_ID_SYS_RESTORE = 53,//�ָ���������
	AUD_BASE_ID_SYS_ADD_PWD = 54,//�������
	AUD_BASE_ID_SYS_CHG_PWD = 55,//�޸�����
	AUD_BASE_ID_SYS_DEL_PWD = 56,//ɾ������
	AUD_BASE_ID_SYS_CLR_PWD = 57,//ɾ����������
	AUD_BASE_ID_SYS_ADD_FP = 58,//���ָ��
	AUD_BASE_ID_SYS_CHG_FP = 59,//�޸�ָ��
	AUD_BASE_ID_SYS_DEL_FP = 60,//ɾ��ָ��
	AUD_BASE_ID_SYS_CLR_FP = 61,//ɾ������ָ��
	AUD_BASE_ID_SYS_ADD_RFCARD = 62,//���RF��
	AUD_BASE_ID_SYS_CHG_RFCARD = 63,//�޸�RF��
	AUD_BASE_ID_SYS_DEL_RFCARD = 64,//ɾ��RF��
	AUD_BASE_ID_SYS_CLR_RFCARD = 65,//ɾ������RF��
	AUD_BASE_ID_SYS_CHG_ADMIN_PWD = 66,//�޸Ĺ���Ա����
	AUD_BASE_ID_SYS_CHG_ADMIN_FP = 67,//�޸Ĺ���Աָ��
	AUD_BASE_ID_SYS_NO1_ADMIN_FP = 68,//1�Ź���Աָ��
	AUD_BASE_ID_SYS_NO2_ADMIN_FP = 69,//2�Ź���Աָ��
	AUD_BASE_ID_SYS_PRO_AUDIO = 70,//��ʾ��
	AUD_BASE_ID_SYS_CLOSE_PRO_AUDIO = 71,//�ر�
	AUD_BASE_ID_SYS_OPEN_PRO_AUDIO = 72,//����
	AUD_BASE_ID_SYS_OPEN_MODE = 73,//���ŷ�ʽ
	AUD_BASE_ID_SYS_SIN_OPEN_MODE = 74,//�����ŷ�ʽ
	AUD_BASE_ID_SYS_DBL_OPEN_MODE = 75,//˫���ŷ�ʽ
	AUD_BASE_ID_SYS_RESTORE_SUCCESS = 76,//��ʼ���ɹ�
	AUD_BASE_ID_APP_SYN = 77,//��ʹ��appͬ��
	AUD_BASE_ID_FM_KEY_INPUT = 78,//��������а���
	AUD_BASE_ID_FM_RESTORE = 79,//�밴��λ��
	AUD_BASE_ID_SYS_NUM_0 = 80,//0
	AUD_BASE_ID_SYS_NUM_1 = 81,//1
	AUD_BASE_ID_SYS_NUM_2 = 82,//2
	AUD_BASE_ID_SYS_NUM_3 = 83,//3
	AUD_BASE_ID_SYS_NUM_4 = 84,//4
	AUD_BASE_ID_SYS_NUM_5 = 85,//5
	AUD_BASE_ID_SYS_NUM_6 = 86,//6
	AUD_BASE_ID_SYS_NUM_7 = 87,//7
	AUD_BASE_ID_SYS_NUM_8 = 88,//8
	AUD_BASE_ID_SYS_NUM_9 = 89,//9
	AUD_BASE_ID_SYS_NUM_S = 90,//*
	AUD_BASE_ID_SYS_NUM_H = 91,//#
	AUD_BASE_ID_MEM_FULL = 92,//����ʧ�ܣ����ڴ���ռ�����

	AUD_BASE_ID_MAX,

}AUD_PLAY_ID;


void Audio_Init(void);

void Audio_Play(AUD_PLAY_ID aud_id);

void Audio_Stop(void);

#endif
