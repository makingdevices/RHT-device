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
char const vector[] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01100111,0b001000000,0b01111001}; //Numbers 8-segment codification
char const letters[] = {0b01011110,0b01110100};
char const batmess[] = {0b01111000,0b01111000,0b01110111,0b01111100};
char number[] = {0,0,0,0}; //Number Storage
char dot = 5;
char buzz = 0; //Buzzer counter
char data[] = {0,0,0,0,0,0}; //Dato
float temperature = 0;
float humidity = 0;
float rhcompensation = 0;
int temp = 0;
int reset = 0; //Reset event counter
int deep_sleep = 0; //Deep Sleep counter
int buzz_reset = 0;  //Enable-disable buzz event counter
char buzz_en = 1; //Buzzer enable
int sleep_time = 2000; //Time before deep sleep
int time_letters = 500; //time for type of measurement message
int batt_time = 300; //Time for battery message
int event_timer = 500; //The time we need to mantain pressed the botons to execute reset/sound events.
int bouncing_timer_var = 25; //The time we need to wait between two button actions
int bouncing_time = 0;
char state = 0;  // 0 = temperature, 1 = humidity
char command = 0;
char battery = 0;

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
		if((battery>0) && (deep_sleep < batt_time)){
			LATC = batmess[digit];
		} else {
			if(digit>0){
				if(digit==dot)LATC = vector[number[digit]] + 0b10000000;
				else LATC = vector[number[digit]];  //we write the correct number depending on the display.
			} else {
				if(deep_sleep<time_letters)LATC = letters[state];
				else{
					if(digit==dot)LATC = vector[number[digit]] + 0b10000000;
					else LATC = vector[number[digit]];  //we write the correct number depending on the display.
				}
			}
		}
	}	
	INTCONbits.TMR0IF = 0; // reset overflow bit (for timer0).

 bouncing_time++;
 if(INTCONbits.RABIF) //if we are pressing a button...
      { 
		OSCCONbits.IDLEN = 1; //Set idle mode. 

		if(PORTAbits.RA0 == 0 && deep_sleep <= sleep_time && bouncing_time >= bouncing_timer_var){ //
			bouncing_time = 0;
			if(state==0)state = 1;
			else state = 0;
		}	

		deep_sleep = 0; //We restart the deep sleep counter
      	INTCONbits.RABIF = 0;	//Clear RAB Interrupt Flag 
      }

	deep_sleep++;  //We increase time before sleep
	if (deep_sleep >= sleep_time){ //If the time for sleep has come
		LATA = 0; //turn off the display
		LATB = 0;
		LATC = 0;
		OSCCONbits.IDLEN = 0; //Prepare the microchip for deep sleep.
	}
}

/*****************Float to display*************************/
// Mode == 1 Temperature // Mode == 2 Humidity

void floattodisplay(char mode)
{
	int i,j;
	if (mode == 1){
		if((temperature<100 && temperature>=0)||(temperature>-10 && temperature<0)){
			i = (int)((float)temperature*100);
			dot = 2;
		}
		else{
			i = (int)((float)temperature*10);
			dot = 1;
		}
		if(temperature<0)i = -i;
		number[0] = i % 10;
		i /= 10;
		number[1] = i % 10;
		i /= 10;
		number[2] = i % 10;
		i /= 10;
		if(temperature<0){
			number[3] = 10;
		} else number[3] = i % 10;
	} else {
		if((humidity>10)){
			i = (int)((float)humidity*100);
			dot = 2;
		}
		else{
			i = (int)((float)humidity*10);
			dot = 1;
		}
		number[0] = i % 10;
		i /= 10;
		number[1] = i % 10;
		i /= 10;
		number[2] = i % 10;
		i /= 10;
		number[3] = i % 10;
	}
	for(j==0;j<4;j++){
		if(number[j]>10 || number[j]<0)number[j] = 11;
	}
}
/* ****************** Obtain data from I2C ****************** */

void getdata(char reading){
		if(reading==1) command = 0xF3;
		if(reading==2) command = 0xF5;
		StartI2C();                        // Send START condition
		WriteI2C(0b10000000);  // Send address with R/W cleared for write 0x40
		WriteI2C(command);       // Conversion command NO HOLD          
		Delay10TCYx(200);
		StartI2C();   
		WriteI2C(0b10000001);  // Send address with R/W set for read 0x41
		data[0] = ReadI2C();               // Read first byte of data
		AckI2C(); 
		data[1] = ReadI2C();
		AckI2C(); 
		data[2] = ReadI2C();
		NotAckI2C();                       // Send NACK
		StopI2C();
		if(reading==1){            
			temp = data[0];
			temp = temp<<8;
			temp = temp+data[1];
			temperature = temp;
			temperature = temperature/65536;
			temperature = temperature*175.72;
			temperature = temperature - 46.85;
		}
		if(reading==2){
			temp = data[0];
			temp = temp<<8;
			temp = temp+data[1];
			humidity = temp;
			humidity = humidity/65536;
			humidity = humidity*125.0;
			humidity = humidity - 6;
			rhcompensation = (-0.15)*(25.0-temperature);
			humidity = humidity + rhcompensation;
		} 
		temp = 0;
}

void batterylevel(void){
	StartI2C();  
	WriteI2C(0b10000000);  // Send address with R/W cleared for write 0x40
	WriteI2C(0xE7);  // READ REGISTER FOR BATTERY LEVEL   
	Delay10TCYx(100);
	StartI2C();
	WriteI2C(0b10000001);  // Send address with R/W cleared for write 0x41  
	battery = ReadI2C()&0b01000000;     // Read first byte of data
	NotAckI2C();                       // Send NACK
	StopI2C();
}

void resolutionhigh(void){
	StartI2C();  
	WriteI2C(0b10000000);  // Send address with R/W cleared for write 0x40
	WriteI2C(0xE7);  // READ REGISTER 
	Delay10TCYx(100);
	StartI2C();
	WriteI2C(0b10000001);  // Send address with R/W cleared for write 0x41  
	temperature = ReadI2C();               // Read first byte of data
	NotAckI2C();                       // Send NACK
	StartI2C();
	WriteI2C(0b10000000);  // Send address with R/W cleared for write 0x41  
	WriteI2C(0xE6);  // WRITE REGISTER 
	WriteI2C(0b00000010); //12 bits RH // 14 bits TEMP
	StopI2C();
}

/* ****************** MAIN ****************** */
char init = 0;
void main(void)
{
	ANSELHbits.ANS10 = 0;	  // Desactivate ANALOG pins

	if(init == 0){
		InitOSC();     //Internal OSC 16MHz 
		Delay10TCYx(1000);
    	Interrupts_enable(); //Enable RA0 & RA1 interrupts
		TRISB =0; //Set port B as output
		TRISC =0; //Set port C as output
		TRISBbits.TRISB4 = 1;     // SDIO -> RB4      
    	TRISBbits.TRISB6 = 1;     // SCLK -> RB6
		init = 1; //We only run this loop once.
		OSCCONbits.IDLEN = 1; //We activate idle mode.

		OpenI2C(MASTER_FIRMW, SLEW_OFF);   //I2C Communication
		SSPADD = 0x77; 
		resolutionhigh();
	}
	getdata(state+1);
	Delay10TCYx(200);
	batterylevel();
	floattodisplay(state+1);
	Sleep(); //Sleep either idle or deep mode!
	//Delay10TCYx(120);  
}

 void InitOSC(void) 
 {    
      OSCCON  = 0b10010110;   //Internal 250KHz    31KHz?? OSCCON  = 0b10010110;
 } 

 void Interrupts_enable(void) 
 {    
	TRISA = 0b11001111; //A port as input
	PORTA = 0;
    //INTCON2bits.RABPU = 0; // Enable Pull-UP on port A-B
    INTCON2bits.RABIP = 1; // Change on port = High priority
	IOCA  = 0b00000011;        //Enable Interrupt on Change for Pin 4 of Port A 
    INTCONbits.RABIE = 1;      //Enable RA and RB Port Change Interrupt 

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
 
 