///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                         CCSHELPER.C                               ////
////                                                                   ////
//// Helper functions and definitions for using CCS's example programs ////
////                                                                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
//// RELEASE HISTORY:                                                  ////
////                                                                   ////
//// November 20th, 2006 -                                             ////
////    Added support for EX_ST_UDP.C example                          ////
////    Added DNS                                                      ////
////    SMTP Example uses DNS to resolve IP                            ////
////                                                                   ////
////    May 26, 2004: Fixed a bug in read_ext_eeprom_string() to       ////
////                  prevent infinite loops when EEPROM is all 0xFF.  ////
////                                                                   ////
////    May 24, 2004: Settings saved to external EEPROM                ////
////                                                                   ////
////    Jan 09, 2004: Initial Public Release                           ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2004 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////

#ifndef STACK_USE_CCS_PICNET
  #define STACK_USE_CCS_PICNET  FALSE
#endif

#ifndef STACK_USE_CCS_PICENS
  #define STACK_USE_CCS_PICENS  FALSE
#endif

#if (STACK_USE_CCS_PICNET+STACK_USE_CCS_PICENS+STACK_USE_CCS_PICEEC+STACK_USE_CCS_EWL3V+STACK_USE_CCS_EWL5V)==0
   #error You must define one of the prototype boards
#endif

#if STACK_USE_CCS_PICNET
   #define ANALOG_PORT_CONFIG    ANALOG_AN0_TO_AN1
   #define ADC_CHAN_0   0
   #define ADC_CHAN_1   1
   #define USER_BUTTON1 PIN_B0
   #define USER_BUTTON2 PIN_B1
   #define BUTTON_PRESSED(p)  (!input(p))
   #define USER_LED1    PIN_B2
   #define USER_LED2    PIN_B4
#elif STACK_USE_CCS_PICENS
   #define ANALOG_PORT_CONFIG    AN0
   #define ADC_CHAN_0   0
   #define USER_BUTTON1 PIN_A4
   #define BUTTON_PRESSED(p)  (!input(p))
   #define USER_LED1    PIN_A5
   #define USER_LED2    PIN_B4
   #define USER_LED3    PIN_B5
#elif STACK_USE_CCS_PICEEC
   #define ANALOG_PORT_CONFIG    AN0_TO_AN2
   #define ADC_CHAN_0   2
   #define USER_BUTTON1 PIN_A4
   #define BUTTON_PRESSED(p)  (!input(p))
   #define USER_LED1    PIN_B3
   #define USER_LED2    PIN_B4
   #define USER_LED3    PIN_B5
#elif STACK_USE_CCS_EWL3V
   #if !STACK_USE_PICDEM_LCD
      #define ANALOG_PORT_CONFIG    AN0_TO_AN7
      #define ADC_CHAN_0   6
      #define ADC_CHAN_1   7
      #define USER_LED1 DIGITAL3
      #define USER_LED2 DIGITAL4
   #else
      #define ANALOG_PORT_CONFIG    NO_ANALOGS
   #endif
   #define BUTTON_PRESSED(p)  (input(p))
#elif STACK_USE_CCS_EWL5V
   #if !STACK_USE_PICDEM_LCD
      #define ANALOG_PORT_CONFIG    AN0_TO_AN1
      #define ADC_CHAN_0   0
      #define ADC_CHAN_1   1
      #define USER_LED1 DIGITAL3
      #define USER_LED2 DIGITAL4
   #else
      #define ANALOG_PORT_CONFIG    NO_ANALOGS
   #endif
   #define BUTTON_PRESSED(p)  (input(p))
#endif

#if (STACK_USE_CCS_EWL3V || STACK_USE_CCS_EWL5V) && CCS_EMAIL_EXAMPLE
   #undef ANALOG_PORT_CONFIG
   #define ANALOG_PORT_CONFIG    NO_ANALOGS
   #define USER_BUTTON1 DIGITAL1
#endif

#if STACK_USE_CCS_EWL5V
   #define DIGITAL1   PIN_A0   
   #define DIGITAL2   PIN_A1
   #define DIGITAL3   PIN_A2
   #define DIGITAL4   PIN_A3
   #define DIGITAL5   PIN_A5
   #define DIGITAL6   PIN_B0
   #define DIGITAL7   PIN_B1
   #define DIGITAL8   PIN_C6
   #define DIGITAL9   PIN_C7
   #define DIGITAL10  PIN_B6
   #define DIGITAL11  PIN_B7
#elif STACK_USE_CCS_EWL3V
   #define DIGITAL1   PIN_F1
   #define DIGITAL2   PIN_F2
   #define DIGITAL3   PIN_F3
   #define DIGITAL4   PIN_F4
   #define DIGITAL5   PIN_F5
   #define DIGITAL6   PIN_F6
   #define DIGITAL7   PIN_A3
   #define DIGITAL8   PIN_C6
   #define DIGITAL9   PIN_C7
   #define DIGITAL10  PIN_B6
   #define DIGITAL11  PIN_B7
   #define DIGITAL12  PIN_B0
   #define DIGITAL13  PIN_B1
   #define DIGITAL14  PIN_B2
   #define DIGITAL15  PIN_B3
   #define DIGITAL16  PIN_B4
   #define DIGITAL17  PIN_B5
#endif


#ifndef STACK_USE_PICDEM_LCD
   #define STACK_USE_PICDEM_LCD TRUE
#endif

#ifndef STACK_USE_SERIAL
   #define STACK_USE_SERIAL TRUE
#endif


#ifndef STACK_USE_EEPROM
   #define STACK_USE_EEPROM   TRUE
#endif

#if STACK_USE_SERIAL
 #use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7, STREAM=USER)
#endif

#if STACK_USE_PICDEM_LCD
   #if STACK_USE_CCS_PICNET
      #include "tcpip/dlcd.c"
   #elif STACK_USE_CCS_PICENS
      #include "tcpip/mlcd.c"
   #elif STACK_USE_CCS_PICEEC
      #include "tcpip/elcd.c"
   #elif STACK_USE_CCS_EWL
      #include "tcpip/alcd.c"
   #else
      #error Can't use LCD without specifying which hardware. Or write your own LCD driver.
   #endif
#endif

#ifndef OUTPUT_DRIVE_MACRO
 #if defined(__PCH__)
   #define OUTPUT_DRIVE_MACRO(x) bit_clear(*(x/8+18),x%8)
 #else
   #define OUTPUT_DRIVE_MACRO(x) bit_clear(*(x/8+0x80),x%8)
 #endif
#endif

#ifndef OUTPUT_FLOAT_MACRO
 #if defined(__PCH__)
   #define OUTPUT_FLOAT_MACRO(x) bit_set(*(x/8+18),x%8)
 #else
   #define OUTPUT_FLOAT_MACRO(x) bit_set(*(x/8+0x80),x%8)
 #endif
#endif

#if STACK_USE_CCS_PICNET
 #ifndef EEPROM_SDA
    #define EEPROM_SDA  PIN_C4
    #define EEPROM_SCL  PIN_C3
    #include "24256.c"   //included with compiler
 #endif
#elif STACK_USE_CCS_PICENS
 #ifndef EEPROM_SELECT
    #define EEPROM_SELECT PIN_B3
    #define EEPROM_DI     PIN_C5
    #define EEPROM_DO     PIN_C4
    #define EEPROM_CLK    PIN_C3
    #define EEPROM_USE_SPI    ENC_MAC_USE_SPI
    #include "AT25256.C"
 #endif    
#elif STACK_USE_CCS_PICEEC
 #ifndef EEPROM_SELECT
    #define EEPROM_SELECT PIN_C1  //o
    #define EEPROM_DI     PIN_C5  //o
    #define EEPROM_DO     PIN_C4  //i
    #define EEPROM_CLK    PIN_C3  //o
    #define EEPROM_USE_SPI   TRUE
    #include "AT25256.C"
 #endif
#elif STACK_USE_CCS_EWL5V
 #ifndef FLASH_SELECT
    #define FLASH_SELECT PIN_C1
    #define FLASH_CLOCK  PIN_C2
    #define FLASH_DI     PIN_C0
    #define FLASH_DO     PIN_B4
    #define FLASH_BUFFER_SIZE    264     //bytes per page on the flash memory
    #define FLASH_BUFFER_COUNT   4096   //page count
    #include "at45db041.c"  
 #endif
 #if STACK_USE_TEMP
    #define DAL_SCL PIN_B6
    #define DAL_SDA PIN_B7
    #include "ds1631.c"   //ds1631 temperature sensor on the d'ment kit
 #endif
#elif STACK_USE_CCS_EWL3V
 #ifndef FLASH_SELECT
    #define FLASH_SELECT PIN_C2
    #define FLASH_CLOCK  PIN_C3
    #define FLASH_DI     PIN_C5
    #define FLASH_DO     PIN_C4
    #define FLASH_BUFFER_SIZE    264     //bytes per page
    #define FLASH_BUFFER_COUNT   4096   //page count
    #include "at45db041.c"
 #endif
 #if STACK_USE_TEMP
    #define DAL_SCL PIN_B6
    #define DAL_SDA PIN_B7
    #include "ds1631.c"   //ds1631 temperature sensor on the d'ment kit
 #endif
#endif




//if using PPP
#define EE_ISP_PHONENUMBER 0      //size=64
#define EE_ISP_USERNAME    64      //size=64
#define EE_ISP_PASSWORD    128      //size=64
//if using ETHERNET
#define EE_NIC_DHCP        192   //size=1
#define EE_NIC_GATEWAY     193   //size=4
#define EE_NIC_IP          197   //size=4
#define EE_NIC_NETMASK     201   //size=4
#define EE_NIC_MAC         205   //size=6
#define EE_DNS             211   //size=4
//if using CCS E-Mail Example
#define EE_SMTP_PORT       215   //size=2   [TCP Port]
#define EE_SMTP_HOSTNAME   217   //size=64  [E-mail SMTP server hostname]
#define EE_SMTP_TO         281   //size=64  [E-mail To address]
#define EE_SMTP_FROM       345   //size=64  [E-mail From address]
#define EE_SMTP_SUBJECT    409   //size=64  [E-mail Subject]
#define EE_SMTP_BODY       473   //size=64  [E-mail Body]
//if using CCS UDP Example
#define EE_UDP_DEST_IP     537   //size=4   [destination IP address for UDP example]
#define EE_UDP_DEST_PORT   541   //size=2   [destination port for UDP example]
#define EE_UDP_SRC_PORT    543   //size=2    [source port for UDP example]

#define EE_MAGIC           545
#define EE_LAST            546
#define EE_MAX             0x7FFF

#define MPFS_START_POSITION EE_LAST+2

//global variables holding PPP information
//PPP stack requires these to be global
#if STACK_USE_PPP
char ppp_phonenumber[64];
char ppp_username[64];
char ppp_password[64];
#endif

#if STACK_USE_PPP && STACK_USE_SERIAL
//Displays modem AT command result to LCD and RS232 serial output
void display_modem_result(MODEM_RESP err) {
   char str[15];
   str[0]=0;

   switch (err) {
      case MODEM_OK:          sprintf(str,"OK");          break;
      case MODEM_CONNECTED:   sprintf(str,"CONNECTED");   break;
      case MODEM_BUSY:        sprintf(str,"BUSY");        break;
      case MODEM_NO_RESPONSE: sprintf(str,"NO RESPONSE"); break;
      case MODEM_NO_CARRIER:  sprintf(str,"NO CARRIER");  break;
      case MODEM_NO_DIALTONE: sprintf(str,"NO DIALTONE"); break;
      default:                sprintf(str,"ERR %U", err); break;
   }
 #if STACK_USE_PICDEM_LCD
   printf(lcd_putc,"\n                ");
   printf(lcd_putc,"\n%s",str);
   delay_ms(3000);
 #endif
 fprintf(USER,"\r\nMODEM RESP: %s",str);
}
#endif

//Display's current IP address on the LCD and/or RS232 serial output
void display_ip_lcd(void) {
#if STACK_USE_PICDEM_LCD
      printf(lcd_putc,"\n                    ");
       #if STACK_USE_DHCP
        #if STACK_USE_EEPROM
          if (MACIsLinked() && ((DHCPIsBound() && read_ext_eeprom(EE_NIC_DHCP))||(!read_ext_eeprom(EE_NIC_DHCP))))
        #else
          if (MACIsLinked() && (DHCPIsBound()))
        #endif
           printf(lcd_putc,"\n%U.%U.%U.%U",MY_IP_BYTE1,MY_IP_BYTE2,MY_IP_BYTE3,MY_IP_BYTE4);
          else if (MACIsLinked())
             printf(lcd_putc,"\nDHCP NOT BOUND");
          else
            printf(lcd_putc,"\nNO ETHERNET LINK");

       #elif STACK_USE_PPP
         if (ppp_is_connected()) {
            printf(lcd_putc,"\n%U.%U.%U.%U",MY_IP_BYTE1,MY_IP_BYTE2,MY_IP_BYTE3,MY_IP_BYTE4);
         }
         else {
            printf(lcd_putc,"\nNOT CONNECTED");
         }
       #else
        if (MACIsLinked()) {
           printf(lcd_putc,"\n%U.%U.%U.%U",MY_IP_BYTE1,MY_IP_BYTE2,MY_IP_BYTE3,MY_IP_BYTE4);
        }
        else {
           printf(lcd_putc,"\nNO ETHERNET LINK");
        }
       #endif
#endif
}

//a simple routine to make a PPP connection
#if STACK_USE_PPP
void picdem_ppp_connect(void) {
   MODEM_RESP ec;
   int8 retries=5;

   while (!ppp_is_connected() && retries--) {
     #if STACK_USE_PICDEM_LCD
      printf(lcd_putc,"\nDialing ISP     ");
     #endif
     fprintf(USER,"\r\n\nDialing ISP");

      ec=ppp_connect(ppp_username, ppp_password, ppp_phonenumber);
      display_modem_result(ec);

      if (connected_baudrate) {
        #if STACK_USE_PICDEM_LCD
         printf(lcd_putc,"\fConnect %LUbps    ", connected_baudrate);
         printf(lcd_putc,"\nNegotiating PPP ");
        #endif
         fprintf(USER,"\r\nConnected %LU\r\nNegotiating PPP...", connected_baudrate);

         while (connected_baudrate && !MY_IP.Val) {
            restart_wdt();
            ppp_handle();    //keep calling the ppp task until we get assigned an IP address
            //BUG: if it gets stuck, it should hang-up and redial.
            //     (Many ISPs will do this for you though)
         }
         if (MY_IP.Val) {
            display_ip_lcd();     //we got a connection, show the IP address on the LCD screen
            fprintf(USER,"\r\nConnected to ISP, IP Address is %U.%U.%U.%U\r\n",MY_IP.v[0],MY_IP.v[1],MY_IP.v[2],MY_IP.v[3]);
         }
      }
   }
}
#endif

#if STACK_USE_EEPROM

//null terminated
void write_ext_eeprom_string(int16 address, char *str) {
   while(*str) {
      write_ext_eeprom(address,*str);
      address++;
      str++;
   }
   write_ext_eeprom(address,0);
}

void write_ext_eeprom16(int16 address, int16 data)
{
   write_ext_eeprom(address++, make8(data,0));
   write_ext_eeprom(address, make8(data,1));
}

int16 read_ext_eeprom16(int16 address)
{
   union
   {
      int8 b[2];
      int16 val;
   } result;

   result.b[0]=read_ext_eeprom(address++);
   result.b[1]=read_ext_eeprom(address);

   return(result.val);
}

void read_ext_eeprom_string(int16 address, char *str, int8 max) {
   char c;
   do {
      c=read_ext_eeprom(address++);
      *str=c;
      str++;
   } while ((c)&&(max--));
   *str=0;
}

void read_ext_eeprom_ip(int16 address, IP_ADDR *ip) {
   IP_ADDR temp;
   temp.v[0]=read_ext_eeprom(address++);
   temp.v[1]=read_ext_eeprom(address++);
   temp.v[2]=read_ext_eeprom(address++);
   temp.v[3]=read_ext_eeprom(address);
   ip->Val=temp.Val;
}

void write_ext_eeprom_ip(int16 address, IP_ADDR *ip) {
   IP_ADDR temp;
   temp.Val=ip->Val;
   write_ext_eeprom(address++,temp.v[0]);
   write_ext_eeprom(address++,temp.v[1]);
   write_ext_eeprom(address++,temp.v[2]);
   write_ext_eeprom(address,temp.v[3]);
}

//clears the EEPROM where ISP settings are saved to prevent others from getting your ISP configuration
void clear_ee(void) {
   int16 i;
  #if STACK_USE_PICDEM_LCD
   printf(lcd_putc,"\fResetting EEPROM");
  #endif
  #if STACK_USE_SERIAL
   fprintf(USER,"\r\n\n\nResetting EEPROM...");
  #endif
   for (i=0;i<MPFS_RESERVE_BLOCK;i++) {
      write_ext_eeprom(i,0);
   }
   write_ext_eeprom(EE_NIC_DHCP, 1);

   write_ext_eeprom(EE_NIC_MAC + 0, 0x00);
   write_ext_eeprom(EE_NIC_MAC + 1, 0x03);
   write_ext_eeprom(EE_NIC_MAC + 2, 0x04);
   write_ext_eeprom(EE_NIC_MAC + 3, 0x05);
   write_ext_eeprom(EE_NIC_MAC + 4, 0x06);
   write_ext_eeprom(EE_NIC_MAC + 5, 0x07);

   write_ext_eeprom16(EE_SMTP_PORT, 25);

   write_ext_eeprom16(EE_UDP_DEST_PORT, 5000);
   write_ext_eeprom16(EE_UDP_SRC_PORT, 5000);

   write_ext_eeprom(EE_MAGIC, 0x55);

  #if STACK_USE_SERIAL
   fprintf(USER,"\r\nEEPROM Cleared. Resetting.\r\n");
  #endif

  #if STACK_USE_PICDEM_LCD
   printf(lcd_putc,"\fEEPROM Cleared");
   delay_ms(5000);
  #endif

   reset_cpu();
}

void init_eeprom_defaults(void)
{
   if (read_ext_eeprom(EE_MAGIC) != 0x55)
      clear_ee();
}
#endif

#ifdef CCS_EMAIL_EXAMPLE
int16 SMTP_PORT;
char SMTP_HOST_NAME[64];
char SMTP_TO_ADDR[64];     //To address of your e-mail
char SMTP_FROM_ADDR[64];       //From address of your e-mail
char SMTP_SUBJECT[64];                 //Subject of your e-mail
char SMTP_BODY[64];      //Body of your e-mail

void init_smtp_settings(void) {
 read_ext_eeprom_string(EE_SMTP_HOSTNAME,SMTP_HOST_NAME,64);
 SMTP_PORT=read_ext_eeprom16(EE_SMTP_PORT);
 read_ext_eeprom_string(EE_SMTP_TO,SMTP_TO_ADDR,64);
 read_ext_eeprom_string(EE_SMTP_FROM,SMTP_FROM_ADDR,64);
 read_ext_eeprom_string(EE_SMTP_SUBJECT,SMTP_SUBJECT,64);
 read_ext_eeprom_string(EE_SMTP_BODY,SMTP_BODY,64);
}
#endif

//Initializes hardware, stack, default IP address and MAC address.
void init(void) {
   setup_wdt(WDT_OFF);
   set_tris_a(0xFF);
   set_tris_b(0xFF);
   set_tris_c(0xFF);
#if !STACK_USE_CCS_EWL5V
   set_tris_d(0xFF);
   set_tris_e(0xFF);
 #if STACK_USE_CCS_PICNET
   set_tris_f(0xFF);
 #endif
#endif

   #if !STACK_USE_CCS_EWL5V
   setup_comparator(NC_NC_NC_NC);
   #endif

   setup_adc_ports(ANALOG_PORT_CONFIG);
 
   setup_adc(ADC_CLOCK_INTERNAL);
 #if STACK_USE_CCS_PICEEC||STACK_USE_CCS_EWL3V
   bit_clear(*0xFC2,7); //temporary fix to a CCS bug
 #endif
 
 #if defined(ADC_CHAN_0)
   set_adc_channel(ADC_CHAN_0);
 #endif

   OUTPUT_DRIVE_MACRO(PIN_C6);
   //OUTPUT_FLOAT_MACRO(PIN_C7);

 #if defined(USER_LED1)
   OUTPUT_DRIVE_MACRO(USER_LED1);
   output_high(USER_LED1);
 #endif

 #if defined(USER_LED2)
   OUTPUT_DRIVE_MACRO(USER_LED2);
   output_high(USER_LED2);
 #endif

  #if defined(USER_LED3)
   OUTPUT_DRIVE_MACRO(USER_LED3);
   output_high(USER_LED3);
  #endif

  #if defined(USER_BUTTON1)
   OUTPUT_FLOAT_MACRO(USER_BUTTON1);
  #endif

  #if defined(USER_BUTTON2)
   OUTPUT_FLOAT_MACRO(USER_BUTTON2);
  #endif

 #if defined(EEPROM_SELECT)
  OUTPUT_DRIVE_MACRO(EEPROM_SELECT);
 #endif

 #if defined(EEPROM_DI)
  OUTPUT_DRIVE_MACRO(EEPROM_DI);
 #endif

 #if defined(EEPROM_DO)
  OUTPUT_FLOAT_MACRO(EEPROM_DO);
 #endif

 #if defined(EEPROM_CLK)
  OUTPUT_DRIVE_MACRO(EEPROM_CLK);
 #endif

 #if defined(MMC_SELECT)
  OUTPUT_DRIVE_MACRO(MMC_SELECT);
 #endif
 
 #if defined(FLASH_SELECT)
  OUTPUT_DRIVE_MACRO(FLASH_SELECT);
 #endif
 
 #if defined(FLASH_CLOCK)
  OUTPUT_DRIVE_MACRO(FLASH_CLOCK);
 #endif
 
 #if defined(FLASH_DI)
  OUTPUT_DRIVE_MACRO(FLASH_DI);
 #endif
 
 #if defined(FLASH_DO)
  OUTPUT_FLOAT_MACRO(FLASH_DO);
 #endif
 
 #if defined(DAL_SCL)
  OUTPUT_DRIVE_MACRO(DAL_SCL);
  output_high(DAL_SCL);
 #endif
 
 #if defined(DAL_SDA)
  OUTPUT_DRIVE_MACRO(DAL_SDA);
  output_high(DAL_SCL);
 #endif
 
 #if defined(DIGITAL1)
  OUTPUT_FLOAT_MACRO(DIGITAL1);
 #endif
 #if defined(DIGITAL2)
  OUTPUT_FLOAT_MACRO(DIGITAL2);
 #endif
 #if defined(DIGITAL3)
  OUTPUT_DRIVE_MACRO(DIGITAL3);
 #endif
 #if defined(DIGITAL4)
  OUTPUT_DRIVE_MACRO(DIGITAL4);
 #endif
 #if defined(DIGITAL5)
  OUTPUT_DRIVE_MACRO(DIGITAL5);
 #endif
 #if defined(DIGITAL6)
  OUTPUT_DRIVE_MACRO(DIGITAL6);
 #endif
 #if defined(DIGITAL7)
  OUTPUT_DRIVE_MACRO(DIGITAL7);
 #endif
 #if defined(DIGITAL8)
  OUTPUT_DRIVE_MACRO(DIGITAL8);
 #endif
 #if defined(DIGITAL9)
  OUTPUT_FLOAT_MACRO(DIGITAL9);
 #endif
 #if defined(DIGITAL10)
  OUTPUT_DRIVE_MACRO(DIGITAL10);
 #endif
 #if defined(DIGITAL11)
  OUTPUT_DRIVE_MACRO(DIGITAL11);
 #endif
 #if defined(DIGITAL12)
  OUTPUT_DRIVE_MACRO(DIGITAL12);
 #endif
 #if defined(DIGITAL13)
  OUTPUT_DRIVE_MACRO(DIGITAL13);
 #endif
 #if defined(DIGITAL14)
  OUTPUT_DRIVE_MACRO(DIGITAL14);
 #endif
 #if defined(DIGITAL15)
  OUTPUT_DRIVE_MACRO(DIGITAL15);
 #endif
 #if defined(DIGITAL16)
  OUTPUT_DRIVE_MACRO(DIGITAL16);
 #endif
 #if defined(DIGITAL17)
  OUTPUT_DRIVE_MACRO(DIGITAL17);
 #endif
 
#if STACK_USE_PICDEM_LCD
   lcd_init();
#endif

#if STACK_USE_TEMP
   init_temp();
#endif
  #if STACK_USE_MCPENC
   //Normally StackInit() will call this, but since we are sharing the same
   //SPI pins for the ENC and EEPROM, we need to call it now so we can use
   //the EEPROM before we do a StackInit().
   ENCSPIInit();
  #endif
  
 #if STACK_USE_EEPROM
   init_ext_eeprom();
   init_eeprom_defaults();
   //
   // Load default configuration into RAM.
   //

 #if STACK_USE_PPP
 read_ext_eeprom_string(EE_ISP_PHONENUMBER,ppp_phonenumber,64);
 read_ext_eeprom_string(EE_ISP_USERNAME,ppp_username,64);
 read_ext_eeprom_string(EE_ISP_PASSWORD,ppp_password,64);
 #elif STACK_USE_MAC
   read_ext_eeprom_ip(EE_NIC_IP, &AppConfig.MyIPAddr);
   read_ext_eeprom_ip(EE_NIC_NETMASK, &AppConfig.MyMask);
   read_ext_eeprom_ip(EE_NIC_GATEWAY, &AppConfig.MyGateway);
  #if STACK_USE_DNS
   read_ext_eeprom_ip(EE_DNS, &AppConfig.PrimaryDNSServer);
  #endif

   AppConfig.MyMACAddr.v[0]    = read_ext_eeprom(EE_NIC_MAC + 0);
   AppConfig.MyMACAddr.v[1]    = read_ext_eeprom(EE_NIC_MAC + 1);
   AppConfig.MyMACAddr.v[2]    = read_ext_eeprom(EE_NIC_MAC + 2);
   AppConfig.MyMACAddr.v[3]    = read_ext_eeprom(EE_NIC_MAC + 3);
   AppConfig.MyMACAddr.v[4]    = read_ext_eeprom(EE_NIC_MAC + 4);
   AppConfig.MyMACAddr.v[5]    = read_ext_eeprom(EE_NIC_MAC + 5);

   #if STACK_USE_DHCP
   if (!read_ext_eeprom(EE_NIC_DHCP))
      DHCPDisable();
   #endif
 #endif
#else //no eeprom
   AppConfig.MyMACAddr.v[0] = 2;
   AppConfig.MyMACAddr.v[1] = 2;
   AppConfig.MyMACAddr.v[2] = 2;
   AppConfig.MyMACAddr.v[3] = 2;
   AppConfig.MyMACAddr.v[4] = 2;
   AppConfig.MyMACAddr.v[5] = 2;
#endif

 #if STACK_USE_ANNOUNCE
  #if STACK_USE_CCS_PICNET
   InitAnnounce("PICNET");
  #elif STACK_USE_CCS_PICENS
   InitAnnounce("PICENS");
  #elif STACK_USE_CCS_PICEEC
   InitAnnounce("PICEEC");
  #elif STACK_USE_CCS_EWL
   InitAnnounce("EZ WEB LYNX");
  #endif
 #endif

 #if STACK_USE_MPFS
   MPFSInit();
#endif

#if STACK_USE_FAT
   fat_init();
#endif
 
   StackInit();

#ifdef CCS_EMAIL_EXAMPLE
   init_smtp_settings();
#endif
}

int1 set_port_bit(int8 *ptr, int16 fullPin, int1 new)
{
   int port, pin;
   int1 old;

   fullPin -=  (int16)PIN_A0;
   port = fullPin / 8;
   pin = fullPin % 8;

   ptr += port;

   port = *ptr;
   old = bit_test(port, pin);
   if (new)
      bit_set(port, pin);
   else
      bit_clear(port, pin);

   *ptr = port;

   return(old);
}

int1 get_port_bit(int8 *ptr, int16 fullPin)
{
   int port, pin;

   fullPin -=  (int16)PIN_A0;
   port = fullPin / 8;
   pin = fullPin % 8;

   ptr += port;

   port = *ptr;

   return(bit_test(port, pin));
}

#if defined(__PCH__)
 #define set_tris_variable(fullPin, new) set_port_bit(0xF92, fullPin, new)
 #define set_lat_variable(fullPin, new) set_port_bit(0xF89, fullPin, new)
 #define input_variable(fullPin) get_port_bit(0xF80, fullPin)
#else
 #define set_tris_variable(fullPin, new) set_port_bit(0x85, fullPin, new)
 #define set_lat_variable(fullPin, new) set_port_bit(0x05, fullPin, new)
 #define input_variable(fullPin) get_port_bit(0x05, fullPin)
#endif

#define output_float_variable(x) set_tris_variable(x,1)
#define output_drive_variable(x) set_tris_variable(x,0)

#define output_low_variable(x) set_lat_variable(x,0)
#define output_high_variable(x) set_lat_variable(x,1)

void get_pin_string(int16 fullPin, char *str)
{
   int port,pin;
   fullPin -=  (int16)PIN_A0;
   port = fullPin / 8;
   pin = fullPin % 8;
   sprintf(str, "PIN_");
   port += 'A';
   pin += '0';
   str[4]=port;
   str[5]=pin;
   str[6]=0;
}

int1 hardware_io_test_pin(int16 pin1, int16 pin2)
{
   int fail=0;
   char str[8];
   int1 oldTRIS1, oldTRIS2, oldLAT1, oldLAT2;
   oldLAT1=output_low_variable(pin1);
   oldLAT2=output_low_variable(pin2);
   oldTRIS1=output_drive_variable(pin1);
   oldTRIS2=output_float_variable(pin2);
   delay_us(100);
   if (input_variable(pin2))
      fail |= 1;

   output_high_variable(pin1);
   delay_us(100);
   if (!input_variable(pin2))
      fail |= 2;

   output_low_variable(pin2);
   output_float_variable(pin1);
   output_drive_variable(pin2);
   delay_us(100);
   if (input_variable(pin1))
      fail |= 4;

   output_high_variable(pin2);
   delay_us(100);
   if (!input_variable(pin1))
      fail |= 8;

   set_lat_variable(pin1, oldLAT1);
   set_lat_variable(pin2, oldLAT2);
   set_tris_variable(pin1, oldTRIS1);
   set_tris_variable(pin2, oldTRIS2);

 #if STACK_USE_SERIAL
   if (fail)
   {
      get_pin_string(pin1, str);
      fprintf(USER,"%s <-> ", str);
      get_pin_string(pin2, str);
      fprintf(USER,"%s ", str);
      if (fail)
         fprintf(USER,"FAIL [%X]", fail);
      else
         fprintf(USER,"OK");
      fprintf(USER,"\r\n");
   }
 #endif

   return(fail != 0);
}

#if STACK_USE_SERIAL
#if STACK_USE_CCS_PICENS
void hardware_test(void)
{
   int1 fail_nic=0,fail_ee=0;
   int1 fail_pins=0;

   fprintf(USER,"\r\n\n\nENC28J60 Test: ");
   SPISelectEthernet();
   BankSel(MAADR1);
   WriteReg(MAADR1 + 0, 0x15);
   WriteReg(MAADR1 + 1, 0x26);
   WriteReg(MAADR1 + 2, 0x37);
   if (ReadMACReg(MAADR1 + 1).Val != 0x26)
      fail_nic = TRUE;
   SPIUnselectEthernet();
   if (fail_nic)
      fprintf(USER,"FAIL");
   else
      fprintf(USER,"PASS");

   write_ext_eeprom(5000,0x55);
   write_ext_eeprom(5001,0x66);
   write_ext_eeprom(5002,0x77);
   fprintf(USER,"\r\nAT25256 Test: ");
   if (read_ext_eeprom(5001)==0x66)
      fprintf(USER,"PASS");
   else
   {
      fprintf(USER,"FAIL !!!");
      fail_ee=TRUE;
   }

   if (fail_nic && fail_ee)
      fprintf(USER,"\r\nBoth ENC28J60 and AT25256 fail!!!");

   fprintf(USER,"\r\n\nBlinking LEDs. Press A4 when LEDs are verified working.\r\n");
   output_high(USER_LED1);
   output_high(USER_LED2);
   output_high(USER_LED3);
   while(input(PIN_A4))
   {
      output_toggle(USER_LED1);
      output_toggle(USER_LED2);
      output_toggle(USER_LED3);
      delay_ms(250);
   }

   fprintf(USER, "\r\nTurn the POT completely to the right.");
   set_adc_channel(ADC_CHAN_0);
   delay_ms(1);
   while (read_adc() < 0xF8) { }
   fprintf(USER, "\r\nTurn the POT completely to the left.");
   while (read_adc() > 0x08) { }
   fprintf(USER, "\r\nPOT Test: PASS\r\n");

   setup_adc_ports(NO_ANALOGS);
   setup_spi(SPI_SS_DISABLED);

   fprintf(USER, "\r\nInsert test header now.  Press T when ready.");
   while(toupper(fgetc(USER))!='T') { }

   fprintf(USER, "\r\nTesting I/O header: \r\n");
   fail_pins |= hardware_io_test_pin(PIN_B7, PIN_B6);
   fail_pins |= hardware_io_test_pin(PIN_B5, PIN_B4);
   fail_pins |= hardware_io_test_pin(PIN_B3, PIN_B2);
   fail_pins |= hardware_io_test_pin(PIN_B1, PIN_B0);
   fail_pins |= hardware_io_test_pin(PIN_D7, PIN_D6);
   fail_pins |= hardware_io_test_pin(PIN_D5, PIN_D4);
   fail_pins |= hardware_io_test_pin(PIN_D3, PIN_D2);
   fail_pins |= hardware_io_test_pin(PIN_D1, PIN_D0);
   fail_pins |= hardware_io_test_pin(PIN_C5, PIN_C4);
   fail_pins |= hardware_io_test_pin(PIN_C3, PIN_C2);
   fail_pins |= hardware_io_test_pin(PIN_C1, PIN_C0);
   fail_pins |= hardware_io_test_pin(PIN_A5, PIN_A4);
   fail_pins |= hardware_io_test_pin(PIN_A3, PIN_A2);
   fail_pins |= hardware_io_test_pin(PIN_A1, PIN_E2);
   fail_pins |= hardware_io_test_pin(PIN_E1, PIN_E0);
   if (fail_pins)
      fprintf(USER, "\r\nI/O header FAIL !!!");
   else
      fprintf(USER, "PASS");

   fprintf(USER, "\r\n\nRemove test header.  Press T when ready.");
   while(toupper(fgetc(USER))!='T') { }

   fprintf(USER,"\r\n\nRESETTING BOARD\r\n\n");
   reset_cpu();
}
#elif STACK_USE_CCS_PICNET
void hardware_test(void)
{
   char modemStr[]="AT";

   fprintf(USER, "\r\n\n");

#if STACK_USE_MAC
   fprintf(USER, "\r\nNIC RTL8019AS (U603) TEST: ");
   NICPut(CMDR, 0x61); // CMDR = ; Select Page 1
   NICPut(PAR0, 0x15);  //PAR0 = 0x01
   NICPut(PAR0+1, 0x26);
   NICPut(PAR0+2, 0x37);
   NICPut(PAR0+3, 0x48);
   NICPut(PAR0+4, 0x59);
   NICPut(PAR0+5, 0x6A);
   if (NICGet(0x01+3) == 0x48)
      fprintf(USER,"PASS");
   else
      fprintf(USER,"FAIL");
#endif

#if STACK_USE_PPP
   fprintf(USER,"\r\nMODEM (U1 & U7) TEST: ");
   if (modem_at_command(modemStr, 2000) == MODEM_OK)
      fprintf(USER,"PASS");
   else
      fprintf(USER,"FAIL");
#endif

   fprintf(USER,"\r\n24LC256 (U103) TEST: ");
   write_ext_eeprom(5000,0x55);
   write_ext_eeprom(5001,0x66);
   write_ext_eeprom(5002,0x77);
   if (read_ext_eeprom(5001)==0x66)
      fprintf(USER,"PASS");
   else
      fprintf(USER,"FAIL");


   fprintf(USER,"\r\nBLINKING LEDS UNTIL BUTTON B0 IS PRESSED");
   output_high(USER_LED1);
   output_high(USER_LED2);
   while(input(PIN_B0))
   {
      output_toggle(USER_LED1);
      output_toggle(USER_LED2);
      delay_ms(250);
   }

   fprintf(USER,"\r\nBLINKING LEDS UNTIL BUTTON B1 IS PRESSED");
   output_high(USER_LED1);
   output_high(USER_LED2);
   while(input(PIN_B1))
   {
      output_toggle(USER_LED1);
      output_toggle(USER_LED2);
      delay_ms(250);
   }


   fprintf(USER,"\r\n\nRESETTING BOARD\r\n\n");
   reset_cpu();
}
#elif STACK_USE_CCS_PICEEC   //PICEEC
void hardware_test(void)
{
   int8 i;
   int1 fail_ee=0;
   int1 fail_pins=0;

   write_ext_eeprom(5000,0x55);
   write_ext_eeprom(5001,0x66);
   write_ext_eeprom(5002,0x77);
   fprintf(USER,"\r\n\n\nAT25256 (U7) TEST: ");
   if (read_ext_eeprom(5001)==0x66)
      fprintf(USER,"PASS");
   else
   {
      fprintf(USER,"FAIL");
      fail_ee=TRUE;
   }

   set_adc_channel(ADC_CHAN_0);
   fprintf(USER, "\r\nTURN POT ALL THE WAY TO THE LEFT.");
   while(read_adc() > 0x08);
   fprintf(USER, "\r\nTURN POT ALL THE WAY TO THE RIGHT.");
   while(read_adc() < 0xF8);

   fprintf(USER,"\r\nBLINKING LEDS UNTIL A4 IS PRESSED");
   output_high(USER_LED1);
   output_high(USER_LED2);
   output_high(USER_LED3);
   while(input(PIN_A4))
   {
      output_toggle(USER_LED1);
      output_toggle(USER_LED2);
      output_toggle(USER_LED3);
      delay_ms(250);
   }
   while(!input(PIN_A4));
   delay_ms(250);

   fprintf(USER, "\r\nTESTING I/O HEADER (J4):\r\n");
   fail_pins |= hardware_io_test_pin(PIN_D1, PIN_D0);
   fail_pins |= hardware_io_test_pin(PIN_G4, PIN_D2);
   fail_pins |= hardware_io_test_pin(PIN_E1, PIN_E0);
   fail_pins |= hardware_io_test_pin(PIN_E3, PIN_E2);
   fail_pins |= hardware_io_test_pin(PIN_E5, PIN_E4);
   fail_pins |= hardware_io_test_pin(PIN_B1, PIN_B0);
   fail_pins |= hardware_io_test_pin(PIN_B3, PIN_B2);
   fail_pins |= hardware_io_test_pin(PIN_B5, PIN_B4);
   fail_pins |= hardware_io_test_pin(PIN_A5, PIN_A4);
   //fail_pins |= hardware_io_test_pin(PIN_A3, PIN_C0);
   if (fail_pins)
      fprintf(USER, "\r\nI/O HEADER (J4): FAIL!!!");
   else
      fprintf(USER, "PASS");

   if (fail_ee || fail_pins)
      fprintf(USER,"\r\n\n!!!! BOARD DOES NOT PASS !!!!");
   else
      fprintf(USER,"\r\n\n++++ BOARD PASS ++++");

   fprintf(USER,"\r\n\nRESETTING BOARD\r\n\n");
   delay_ms(15);
   reset_cpu();
}
#else
void hardware_test(void)
{
   fprintf(USER,"\r\n\nNO HARDWARE TEST!\r\n\nRESETTING BOARD\r\n\n");
   delay_ms(15);
   reset_cpu();
}
#endif
#endif
