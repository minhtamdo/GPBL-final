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
int i=0;

void small_right_down(void){
 analogWrite(analogOutPin1, 50);
 analogWrite(analogOutPin2, 90);
}
void right_down(void){
 analogWrite(analogOutPin1, 0);
 analogWrite(analogOutPin2, 90);
}
void small_left_down(void){
 analogWrite(analogOutPin1, 90);
 analogWrite(analogOutPin2, 50);
}
void left_down(void){
 analogWrite(analogOutPin1, 90);
 analogWrite(analogOutPin2, 0);
}
void straight(void){
 analogWrite(analogOutPin1, 90);
 analogWrite(analogOutPin2, 90);
}
const int trig = 11;     // chân trig của HC-SR04
const int echo = 12;  
int t=0;
// the setup function runs once when you press reset or power the board
void setup() {
 // initialize digital pin 13 as an output.
  Serial.begin(9600);
   pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(LEDPin0, OUTPUT);
 pinMode(LEDPin1, OUTPUT);
 pinMode(LEDPin2, OUTPUT);
}
void SLow()
{
   analogWrite(analogOutPin1, 50);
 analogWrite(analogOutPin2, 50);
}
void Stop()
{
   analogWrite(analogOutPin1, 0);
 analogWrite(analogOutPin2, 0);
}
int mapp=0;
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
 
  /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
   
                
                  if(RB0==1 && RB1==0 && RB2==1)      
                                 mapp=0;//đường đen 
                  if(RB0==0 && RB1==1 && RB2==0)    
                     mapp=1;
                      if(t%200==0) { unsigned long duration; // biến đo thời gian
    int distance;  
                        digitalWrite(trig,0);   // tắt chân trig
                          delayMicroseconds(2);
                          digitalWrite(trig,1);   // phát xung từ chân trig
                          delayMicroseconds(5);   // xung có độ dài 5 microSeconds
                          digitalWrite(trig,0); 
                          duration = pulseIn(echo,HIGH);  
                          // Tính khoảng cách đến vật.
                          distance = int(duration/2/29.412);
   
                                Serial.print("mapp=");
                                Serial.println(mapp);
                                      Serial.print(distance);
                                      Serial.println("cm");
                                      delay(200);
                                            if(distance<=30){
      SLow();
      delay(100);
      Stop();
      while(distance<=30)
      {     digitalWrite(trig,0);   // tắt chân trig
                          delayMicroseconds(2);
                          digitalWrite(trig,1);   // phát xung từ chân trig
                          delayMicroseconds(5);   // xung có độ dài 5 microSeconds
                          digitalWrite(trig,0);
                          duration = pulseIn(echo,HIGH);  
                          // Tính khoảng cách đến vật.
                          distance = int(duration/2/29.412);
                                              delay(30);
                                              Serial.print("Do u know my father???");

      }
                                            }

    }
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
              
              t++;
              
      
}