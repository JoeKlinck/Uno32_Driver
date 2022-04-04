/*
This code runs on the Arduino UNO32 board
It uses Timer 1 to alternately blink
LED 4 and LED 5
 */
#include <p32xxxx.h>
#include <stdio.h>
#include <plib.h>
#pragma config FPLLIDIV = DIV_12 // PLL Input Divider (12x Divider)
#pragma config FPLLMUL = MUL_24 // PLL Multiplier (24x Multiplier)
#pragma config FPLLODIV = DIV_256 // System PLL Output Clock Divider (PLL Divide by 256)
#pragma config FNOSC = FRC // Oscillator Selection Bits (Fast RC Osc (FRC))
#pragma config FSOSCEN = OFF // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1 // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSECME // Clock Switching and Monitor Selection (Clock Switch Enable, FSCM Enabled)
#pragma config WDTPS = PS1048576 // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config ICESEL = ICS_PGx2 // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config PWP = OFF // Program Flash Write Protect (Disable)
#pragma config BWP = OFF // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF // Code Protect (Protection Disabled)
#define SYS_FREQ (80000000L)
#define GetSystemClock()  SYS_FREQ
#define GetInstructionClock() (GetSystemClock()/1)
#define GetPeripheralClock() (GetSystemClock()/1)
#define LED4 LATGbits.LATG6
#define LED5 LATFbits.LATF0
void Timer1_Init(void);
enum{led_off, led_on};
unsigned char led_flag,a,b,c,d,e;
unsigned int i,ii;
enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun};
enum week day;
typedef unsigned int Uint_32;
typedef unsigned short Ushort_16;
Uint_32 t;
Ushort_16 r;
int main(void)
{
    OSCCON=0x0000;
    AD1PCFG=0xFFFF;
    TRISB=0x0000;
    TRISC=0x0000;
    TRISD=0x0000;
    TRISE=0x0000;
    TRISF=0x0000;
    TRISG=0x0000;
    PORTB=0x0000;
    PORTC=0x0000;
    PORTD=0x0000;
    PORTE=0x0000;
    PORTF=0x0000;
    PORTG=0x0000;
    DDPCONbits.JTAGEN=0;
    INTEnableSystemMultiVectoredInt();
    led_flag=0;
    t=5;
    r=8;
    while(1)
    {
        day = Wed;
        day = Fri;
        day = Sat;
        day = Sun;
        i=day;
    }
    Timer1_Init();
    while(1);
}
void __ISR(_TIMER_1_VECTOR, IPL6AUTO) Timer1Handler(void)
{
    led_flag=(led_flag==0)?1:0;
    LED4=led_flag;
    LED5=led_flag^1;
    TMR1=0;
    IFS0bits.T1IF=0;
}
void Timer1_Init(void)
{
    IPC1bits.T1IP=6;
    T1CON=0X8070;
    IFS0bits.T1IF=0;
    IEC0bits.T1IE=1;
    PR1=4500;//4000
    TMR1=0;
}