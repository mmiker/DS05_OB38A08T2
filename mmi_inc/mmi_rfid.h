#ifndef __MMI_RFID_H__
#define __MMI_RFID_H__

#include "mmi_feature.h"
#ifdef __LOCK_RFID_CARD_SUPPORT__
#include "mmi_com.h"

#define RFID_SEC_DATA_LEN 12
/*
parameter: 
	none
return :
	none
*/
void mmi_dq_rfid_init(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_check(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_work(void);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_gen_char(unsigned char index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_match(void);
/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_temp(unsigned char* index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_search_by_id(unsigned char id, unsigned char* index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_delete(unsigned char index);

/*
parameter: 
	none
return :
	none
*/
RET_VAL mmi_dq_rfid_store(unsigned char id);
#endif
#endif //__MMI_RFID_H__

