/*	Making Devices 2022
	https://makingdevices.com
	Rubén García Segovia
	RHT Device
*/
#define I2C_IO_V5

#include <p18f14k50.h>
#include <delays.h>
#include <i2c.h>

 // setup config bits 
 #pragma config PCLKEN=OFF
 #pragma config FOSC = IRC
 #pragma config BOREN = OFF 
 #pragma config WDTEN = OFF 
 #pragma config LVP = OFF  

/** Default I2C address for the HTU21D. */
#define HTU31D_DEFAULT_I2CADDR (0x40)

/** Read temperature and humidity. */
#define HTU31D_READTEMPHUM (0x00)

/** Start a conversion! */
#define HTU31D_CONVERSION (0x40)

/** Read serial number command. */
#define HTU31D_READSERIAL (0x0A)

/** Enable heater */
#define HTU31D_HEATERON (0x04)

/** Disable heater */
#define HTU31D_HEATEROFF (0x02)

/** Reset command. */
#define HTU31D_RESET (0x1E)

char digit = 0;
char const vector[] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01100111,0b01111001}; //Numbers 8-segment codification
char number[] = {0,0,0,0}; //Number Storage
char buzz = 0; //Buzzer counter
char data[] = {0,0,0,0,0,0}; //Dato
int temp = 0;
int reset = 0; //Reset event counter
int deep_sleep = 0; //Deep Sleep counter
int buzz_reset = 0;  //Enable-disable buzz event counter
char buzz_en = 1; //Buzzer enable
int sleep_time = 10350; //Time before deep sleep
int buzzer_time = 10; //Time for the buzzer sound
int event_timer = 500; //The time we need to mantain pressed the botons to execute reset/sound events.
void InitOSC(void); 
void _low_isr (void);
void _high_isr (void);
void Interrupts_enable (void);

#pragma code low_vector=0x18 //Low interrupt priority starts at 0x18
void low_interrupt(void)
{
_asm goto _low_isr _endasm
}

#pragma code high_vector=0x08 //High interrupt priority starts at 0x08
void high_interrupt(void)
{
_asm goto _high_isr _endasm
}
#pragma code


#pragma interrupt _low_isr

void _low_isr (void){

}

#pragma interrupt _high_isr
void _high_isr (void)   //High priority interrupt.
{
char i=0; 


if(INTCONbits.TMR0IF) //Timer0 interrupt
	{


//We set the timer0 again
TMR0H = 0xFE;
TMR0L = 0xC7;

	if(buzz > 0) {  //If the buzzer was activated
		buzz++; //increase buzz time
	} 
	if(buzz > buzzer_time) { //If the buzzer has been activated long enough
		buzz = 0;	//we stop the buzzer
		PORTA = 0;
	} 
	LATC = 0; //Turn off the display before changing the number AND RESET
	LATA = 0;
	switch(digit){  //Print the numbers over the display
		case 3:		//we light the correct display
			LATB = 0b10001111; 
			digit = 0;
			break;
		case 0:
			LATB = 0b00001111;
			LATA = 0b00100000; 
			digit = 1;
			break;
		case 1:
			LATB = 0b00001111; 
			LATA = 0b00010000; 
			digit = 2;
			break;
		case 2:
			LATB = 0b00101111; 
			digit = 3;
			break;
		default:
			break;
	}
	LATC = vector[number[digit]];  //we write the correct number depending on the display.
	INTCONbits.TMR0IF = 0; // reset overflow bit (for timer0).
	}	

 if(INTCONbits.RABIF) //if we are pressing a button...
      { 
	  	deep_sleep = 0; //We restart the deep sleep counter
		OSCCONbits.IDLEN = 1; //Set idle mode. 

		  if(PORTAbits.RA0 == 0){ //
		  	 LATA = 0b00110010;
		  }
			
      	INTCONbits.RABIF = 0;	//Clear RAB Interrupt Flag 
      }

	deep_sleep++;  //We increase time before sleep

	if (deep_sleep > sleep_time){ //If the time for sleep has come
		OSCCONbits.IDLEN = 0; //Prepare the microchip for deep sleep.
		LATB = 0b00001111; //turn off the display
	}
}


/* ****************** MAIN ****************** */
char init = 0;
void main(void)
{
    TRISBbits.TRISB4 = 1;     // SDIO -> RB4      
    TRISBbits.TRISB6 = 1;     // SCLK -> RB6

	Delay10TCYx(120);
	if(init == 0){
		InitOSC();     //Internal OSC 16MHz 
		Delay10TCYx(1000);
		OpenI2C(MASTER_FIRMW, SLEW_OFF);   //I2C Communication
		SSPADD = 0x77; 

		IdleI2C();                         // Wait until the bus is idle
		StartI2C();                        // Send START condition
		WriteI2C(0b10000000);  // Send address with R/W cleared for write
		IdleI2C();
		WriteI2C(0xF3);       // Conversion command      
		IdleI2C();              
		RestartI2C();
		WriteI2C(0b10000001);  // Send address with R/W set for read
		data[0] = ReadI2C();               // Read first byte of data
		AckI2C(); 
		data[1] = ReadI2C();
		AckI2C(); 
		data[2] = ReadI2C();
		NotAckI2C();                       // Send NACK
		StopI2C();                        
/*
		temp = temp + data[0]<<6;
		temp = temp&&data[1]>>2;
		temp = temp/65535.0;
		temp = temp*175.72;
		temp = temp - 46.85;
*/
		if(data[0]&0b00000001 == 1) {
			number[0] = 1;
		}	
		if(data[0]&0b00000010 == 1) {
			number[1] = 1;
		}	
		if(data[0]&0b00000100 == 1) {
			number[2] = 1;
		}	
		if(data[0]&0b00001000 == 1) {
			number[3] = 1;
		}		

    	Interrupts_enable(); //Enable RA0 & RA1 interrupts
		TRISB =0; //Set port B as output
		TRISC =0; //Set port C as output
		init = 1; //We only run this loop once.
		OSCCONbits.IDLEN = 1; //We activate idle mode.
	}
	Sleep(); //Sleep either idle or deep mode!  
}

 void InitOSC(void) 
 {    
      OSCCON  = 0b10010110;   //Internal 250KHz    
 } 

 void Interrupts_enable(void) 
 {    
	TRISA = 0b11001111; //A port as input
	PORTA = 0;
    //INTCON2bits.RABPU = 0; // Enable Pull-UP on port A-B
    INTCON2bits.RABIP = 1; // Change on port = High priority
	IOCA  = 0b00000011;        //Enable Interrupt on Change for Pin 4 of Port A 
    //INTCONbits.RABIE = 1;      //Enable RA and RB Port Change Interrupt 

T0CONbits.T08BIT = 0;	//5ms at 250Khz timer 0 interrupt
T0CONbits.T0CS = 0;
T0CONbits.PSA = 1;
TMR0H = 0xFE;
TMR0L = 0xC7;
T0CONbits.TMR0ON = 1;

	RCONbits.IPEN       = 1;    //Enable Interrupt Priorities
    INTCONbits.GIEL     = 1;    //Enable Low Priority Interrupt
    INTCONbits.GIEH     = 1;    //Enable high priority interrupts        
    INTCONbits.TMR0IE   = 1;    //Enable Timer0 Interrupt
	INTCONbits.T0IE     = 1;   
    INTCON2bits.TMR0IP  = 1;    //TMR0 set to low Priority Interrupt
    INTCONbits.TMR0IF = 0;  // T0 int flag bit cleared before starting
    T0CONbits.TMR0ON = 1;   // timer0 START
	INTCONbits.GIE = 1; 		   //Enable all unmasked interrupts   
 } 
 
 