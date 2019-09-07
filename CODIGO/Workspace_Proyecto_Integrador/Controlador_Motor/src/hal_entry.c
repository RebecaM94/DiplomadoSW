#include "hal_data.h"

#define LOW 1
#define HIGH 0

uint16_t u16ADC_Data, FilteredData;

void hal_entry(void)
{
    /* ADC configuration*/
    g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    /* PWM configuration*/
    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->start(g_timer1.p_ctrl);

    while(1)
    {
        /* Read ADC value*/
        g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &u16ADC_Data);
        FilteredData = (u16ADC_Data * 100)/255;

        /* Change PWM dutyCycle*/
        g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
        g_timer1.p_api->start(g_timer1.p_ctrl);
        g_timer1.p_api->dutyCycleSet(g_timer1.p_ctrl, FilteredData, TIMER_PWM_UNIT_PERCENT, 1);

    }
}