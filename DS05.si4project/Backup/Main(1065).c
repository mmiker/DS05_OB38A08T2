#include "mmi_feature.h"
#include "dqiot_drv.h"
#include "mmi_ms.h"
#include "mmi_fs.h"
#include "mmi_fps.h"
#include "mmi_sys.h"
#include "mmi_audio.h"
#include "mmi_bsp.h"
#include "mmi_fm.h"

void WDT_ISR(void) interrupt d_WDT_Vector
{
    ((void(code*)(void))0x200B)();      //WDT ISR Function
}

void main(void)
{
	mmi_dq_bsp_init();
    mmi_dq_led_init();
    mmi_dq_key_init();
	mmi_dq_aud_init();
#ifdef	__LOCK_FP_SUPPORT__
	mmi_dq_fp_init();
#endif
	mmi_dq_sys_init();

    //LVC=0x40;    // For Power down mode
	if(0 == mmi_dq_sys_check_vbat())
	{
		mmi_dq_ms_set_sys_state(SYS_STATUS_IDLE);
	}

    while(1)
    {

		if(SYS_STATUS_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
		{
			PCON |= 0x02;			
			mmi_sleep_task_proc();
		}
		else
		{
			mmi_task_proc();
		}
		
		mmi_dq_ms_sys_msg_handle();

		if(SYS_STATUS_WAIT_FOR_ENTER_SLEEP == mmi_dq_ms_get_sys_state())
			mmi_wait_sleep_task_proc();

    }
}
