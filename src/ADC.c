#include "OB38A08T2.h"
#include "ADC.h"
#include "Timer.h"

unsigned int n_data = 0x0000;
bit ADCfinish = 0;

void ADC_Start(unsigned char n_ADC_CH)
{
    ADCC2 = n_ADC_CH; //Set a new channel 使能ADC取样
    ADCC2 |= 0x80;    //ADC start conversion
}

void ADC_Init(void)
{
    ADCC1 = d_ADCnEN0;                 //Set ADC channel
    ADCCS = d_ADCnEN1 | d_ADC_CLK_Sel; //Set ADC channel & Select ADC clock
    IEADC = 1;                         //Enable ADC interrupt.
    EA = 1;
}

unsigned int ADC_Read12() //12-bit ADC
{
    unsigned int n_ADCD12 = 0x0000;
    n_ADCD12 = (ADCDH << 4) | ADCDL; //12-bit ADC
    return n_ADCD12;
}

void ADCInterrupt(void) interrupt d_ADC_Vector // ADC Interrupt Vector Address 0053h => interrupt 10
{
    n_data = ADC_Read12(); //Read ADC
    ADCfinish = 1;
}

unsigned int ADC(void)
{
    if (d_ADCnEN0 & 0x40)
    {
        ADC_Start(d_ADC_CH6_IN);
        while (!ADCfinish)
            ;
        ADCfinish = 0;
    }
    return n_data;
}

/**
  * @brief  get adc data
  * @param  adc_channel_addr:ADC channel
  * @return none
  * @note   none
  * @see    none
  */
uint16_t get_adc_data(uint8_t adc_channel_addr)
{
    uint16_t adc_data;
    adc_data = ADC();
    return adc_data;
}

/**
  * @brief  获取adc数据的平均值
  * @param  
  * adc_channel_addr ADC channel;
  * times 时间ms
  * @return none
  * @note   none
  * @see    none
  */
static uint16_t Get_Adc_Average(uint8_t adc_channel_addr, uint8_t times)
{
    uint32_t temp_val = 0;
    uint8_t t;
    for (t = 0; t < times; t++)
    {
        temp_val += get_adc_data(adc_channel_addr);
        TIMER1_Delay(5);
    }
    return temp_val / times;
}

/**
  * @brief  电压计算
  * @param  none
  * @return none
  * @note   none
  * @see    none
  */
unsigned char adc_VolT(void)
{
    unsigned int adcx;
    float temp;

    // ADC_ENABLE();
    TIMER1_Delay(5);
    adcx = Get_Adc_Average(d_ADCnEN0, 10); //获取10ms平均值
    // ADC_DISABLE();

    temp = (float)adcx * (3.3 / 4096); //计算电压

    if (temp < 2.22) //4.8v=2.22
        return 2;
    else if (temp < 2.3525) //<5v=2.3525
        return 1;           //mmi_dq_aud_play_with_id(AUD_BASE_ID_LOW_BATTERY);

    return 0;
}
