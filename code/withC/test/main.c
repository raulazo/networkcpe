#include "C:\Users\dorakengi\Desktop\HW\test\main.h"


void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
//Setup_Oscillator parameter not selected from Intr Oscillator Config tab

   // TODO: USER CODE!!
   while(1){
      output_high(PIN_D0);
      printf("Hi!!\r\n");
      delay_ms(250);
   }
}
