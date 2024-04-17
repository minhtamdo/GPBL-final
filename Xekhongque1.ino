

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
const int analogInPin0 = A0; // Analog input pin that the potentiometer is attached to
const int analogInPin1 = A1; // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A2; // Analog input pin that the potentiometer is attached to
const int LEDPin0 = 6; // Analog output pin that the LED is attached to
const int LEDPin1 = 7; // Analog output pin that the LED is attached to
const int LEDPin2 = 8; // Analog output pin that the LED is attached to
int RIGHT_DOWN=1;
int LEFT_DOWN=2;
int STRAIGHT=0;
int last_time=0; 
int sensorValue0 = 0; // value read from the pot
int sensorValue1 = 0; // value read from the pot
int sensorValue2 = 0; // value read from the pot
int outputValue0 = 0; // value output to the PWM (analog out)
int outputValue1 = 0; // value output to the PWM (analog out)
int outputValue2 = 0; // value output to the PWM (analog out)
int RB0 = 0; // value output to the PWM (analog out)
int RB1 = 0; // value output to the PWM (analog out)
int RB2 = 0; // value output to the PWM (analog out)
const int analogOutPin2 = 9; // Analog output pin that the LED is attached to
const int analogOutPin1 = 10; // Analog output pin that the LED is attached to
int outputValue = 0; // value output to the PWM (analog out)
int mapp=0;

void small_right_down(void){
 analogWrite(analogOutPin1, 30);
 analogWrite(analogOutPin2, 80);
}
void right_down(void){
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("RIGHT!");
         lcd.setCursor(3, 1);
        lcd.print((mapp==0)?"Blackline":"Whiteline"); 
 analogWrite(analogOutPin1, 10);
 analogWrite(analogOutPin2, 80);
}
void small_left_down(void){
 analogWrite(analogOutPin1, 80);
 analogWrite(analogOutPin2, 30);
}
void left_down(void){
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("LEFT");
     lcd.setCursor(3, 1);
        lcd.print((mapp==0)?"Blackline":"Whiteline"); 
 analogWrite(analogOutPin1, 80);
 analogWrite(analogOutPin2, 10);
}
void straight(void){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("STRAIGHT");
     lcd.setCursor(3, 1);
        lcd.print((mapp==0)?"Blackline":"Whiteline"); 
 analogWrite(analogOutPin1, 80);
 analogWrite(analogOutPin2, 80);
}

// the setup function runs once when you press reset or power the board
void setup() {
 // initialize digital pin 13 as an output.
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(LEDPin0, OUTPUT);
 pinMode(LEDPin1, OUTPUT);
 pinMode(LEDPin2, OUTPUT);
 lcd.init();         // initialize the lcd
  lcd.backlight();
    lcd.setCursor(4, 0);
  lcd.print("Vietnam!");
  lcd.setCursor(5, 1);
  lcd.print("Japan!");
  delay(500);
}
void loop() {
 sensorValue0 = analogRead(analogInPin0);
 sensorValue1 = analogRead(analogInPin1);
 sensorValue2 = analogRead(analogInPin2);
 if(sensorValue0>150){
 outputValue0 = 1;
 }
 else{
 outputValue0 = 0;
}
if(sensorValue1>150){
 outputValue1 = 1;
 }
 else{
 outputValue1 = 0;
}
if(sensorValue2>150){
 outputValue2 = 1;
 }
 else{
 outputValue2 = 0;
}
 if(outputValue0==0){
 digitalWrite(LEDPin0,LOW);
 }
 else{
 digitalWrite(LEDPin0,HIGH);
 }
 if(outputValue1==0){
 digitalWrite(LEDPin1,LOW);
 }
 else{
 digitalWrite(LEDPin1,HIGH);
 }
 if(outputValue2==0){
 digitalWrite(LEDPin2,LOW);
 }
 else{
 digitalWrite(LEDPin2,HIGH);
 }
 delay(2);
 //sensor monitor 
 RB0=outputValue2;
 RB1=outputValue1;
 RB2=outputValue0;
 //last_time=STRAIGHT;
 // led_sens();
   
                
                  if(RB0==1 && RB1==0 && RB2==1)      
                                mapp=0;//đường đen
                          
                                
                  if(RB0==0 && RB1==1 && RB2==0)    
                    mapp=1;
                    
                     
                if(mapp==0)
                {
                                
                if(RB0==1 && RB1==1 && RB2==1 && last_time==LEFT_DOWN){
                left_down(); /*"White White White" and "LEFT_DOWN last time"*/
                last_time=LEFT_DOWN; /* turn left */
                }
                else if(RB0==1 && RB1==1 && RB2==1 && last_time==RIGHT_DOWN){
                right_down(); /*"White White White" and "RIGHT_DOWN last time"*/
                last_time=RIGHT_DOWN; /* turn right */
                }
                else if(RB0==0 && RB1==0 && RB2==1){ /* Black Black White */
                small_left_down(); /* turn left a little */
                last_time=LEFT_DOWN;
                }
                else if(RB0==0 && RB1==1 && RB2==1){ /* Black White White */
                left_down(); /* turn left */
                last_time=LEFT_DOWN;
                }
                else if(RB0==1 && RB1==0 && RB2==0){ /* White Black Black */
                small_right_down(); /* turn right a little */
                last_time=RIGHT_DOWN;
                }
                else if(RB0==1 && RB1==1 && RB2==0){ /* White White Black */
                right_down(); /* turn right */
                last_time=RIGHT_DOWN;
                }
                if (RB0==1 && RB1==0 && RB2==1) 
                straight(); /* go to straight */
                //last_time=STRAIGHT;
                }
                if(mapp==1)
                {
            
                  if(RB0==0 && RB1==0 && RB2==0 && last_time==LEFT_DOWN){
                left_down(); /*"Black Black Black" and "LEFT_DOWN last time"*/
                last_time=LEFT_DOWN; /* turn left */
                }
                else if(RB0==0 && RB1==0 && RB2==0 && last_time==RIGHT_DOWN){
                right_down(); /*"Black Black Black" and "RIGHT_DOWN last time"*/
                last_time=RIGHT_DOWN; /* turn right */
                }
                else if(RB0==1 && RB1==1 && RB2==0){ /* White White Black */
                small_left_down(); /* turn left a little */
                last_time=LEFT_DOWN;
                }
                else if(RB0==1 && RB1==0 && RB2==0){ /* White Black Black */
                left_down(); /* turn left */
                last_time=LEFT_DOWN;
                }
                else if(RB0==0 && RB1==1 && RB2==1){ /* Black White White */
                small_right_down(); /* turn right a little */
                last_time=RIGHT_DOWN;
                }
                else if(RB0==0 && RB1==0 && RB2==1){ /* Black Black White */
                right_down(); /* turn right */
                last_time=RIGHT_DOWN;
                }
                else{ /* The other case */
                straight(); /* go to straight */
                //last_time=STRAIGHT;
                }

                }               
              
              
              
      
}