/*
 * File:   main.c
 * Author: Jose Victor Vanegas
 *
 * Created on 27 de abril de 2021, 10:12 AM
 */


#include <xc.h>
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#define _XTAL_FREQ 4000000




void main(void) {
    ANSEL = 3;
    TRISC = 0;
    TRISD = 0;
    //configuraciondes del adcon1
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG1 =0;
    ADCON1bits.VCFG0 =0;
            
    //configuraciones del adcon0
    ADCON0bits.ADCS = 0b01;
    ADCON0bits.CHS  = 0b0000;
    ADCON0bits.ADON = 1;
    ADCON0bits.GO   = 1;       
    
    //CONFIGURACION DEL CCP
    CCP2CONbits.CCP2M = 0b1100; //pwm
    CCP2CONbits.DC2B0 =  0;
    CCP2CONbits.DC2B1 =  0;
    CCP1CONbits.CCP1M = 0b1100; 
    CCP1CONbits.P1M = 0;
    CCP1CONbits.DC1B = 0;
    
    // timer 2
    T2CONbits.T2CKPS = 0b11; //prescaler de 16
    T2CONbits.TMR2ON = 1;
    PR2 = 249;
    
    
    
    while(1){
        if(ADCON0bits.GO == 0){
            
            
            switch(ADCON0bits.CHS){
                case 0:
                    CCPR1L = ADRESH/4 +64 ;
                   // __delay_ms(1);
                    ADCON0bits.CHS = 1;
                    ADCON0bits.GO = 1;
                    
                    break;
                case 1:
                    CCPR2L = ADRESH/4 + 64;
                    //__delay_ms(1);
                    ADCON0bits.CHS = 0;
                    ADCON0bits.GO = 1;
                    break;
            }
            
        }
        
    }
    
    
    return;
}