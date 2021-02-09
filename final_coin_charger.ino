#include <Keypad.h>

#include<LiquidCrystal.h>

//#include<EEPROM.h>

const int rs =7 , en =6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal liquid_crystal_display(rs, en, d4, d5, d6, d7);

char password[4];

char initial_password[4];
char new_password[4];

int i=0;

char key_pressed=0;

const byte rows = 4; 

const byte columns = 4; 

char hexaKeys[rows][columns] = {

{'1','2','3'},

{'4','5','6'},

{'7','8','9'},

{'*','0','#'}

};

byte row_pins[rows] = {40,42,44,46};

byte column_pins[columns] = {48,50,52};   

Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

//defining pins
int red_led=28;

int green_led=29;

int ir_sensor1=31;

int ir_sensor2=32;

int motor1=34;

int motor2=33;

int buzzer=30;

int slot_charge_pin=35;

int only_charge_pin=36;
 
int password_button=8;

int warn=0;

int button=0;

int timer;

void setup()

{

  Serial.begin(9600);
  
  liquid_crystal_display.begin(16,2);
  
  pinMode(red_led, OUTPUT);
        
  pinMode(green_led, OUTPUT);
  
  pinMode(motor1, OUTPUT);
  
  pinMode(motor2, OUTPUT);
  
  pinMode(ir_sensor1, INPUT);// 1 rupee sensor 
   
  pinMode(ir_sensor2, INPUT); // 5 rupee sensor
  
  pinMode(buzzer, OUTPUT);
  
  pinMode(password_button,INPUT);
  
  pinMode(buzzer, OUTPUT);
  
  pinMode(slot_charge_pin, OUTPUT);
  
  pinMode(only_charge_pin, OUTPUT);

  liquid_crystal_display.print("Hello Welcome to ");

  liquid_crystal_display.setCursor(0,1);

  liquid_crystal_display.print("Charging Boot ");

  delay(4000);
 
  
}


void loop() {
 int k=0;
 int v=0;
 button=0;
 info();
 delay(500);
 keys();
 delay(500);
 
 while(k<1){
  
  //Serial.println("inside while");
  //int val1=digitalRead(ir_sensor1);
  //Serial.println(val1);
  delay(500);
  
  char key=keypad_key.getKey();
  
  if(key=='2')
   { 
     liquid_crystal_display.clear();
     liquid_crystal_display.setCursor(0,0);
     liquid_crystal_display.print("Insert Rs1 Coin");
     delay(7000);
     int val1=digitalRead(ir_sensor1);
     Serial.println(val1);
     delay(500);
      
     if(val1==1)
     {
      
     digitalWrite(only_charge_pin,HIGH); 
     digitalWrite(green_led ,HIGH);   
     liquid_crystal_display.clear();
     liquid_crystal_display.setCursor(0,0);
     liquid_crystal_display.print("Time remaining");
     delay(1000); 
     //liquid_crystal_display.setCursor(1,1);
     for(int timer=60;timer>0;--timer){
      Serial.println(timer);
      delay(1000);
     liquid_crystal_display.setCursor(1,1);
     liquid_crystal_display.print(timer);
     liquid_crystal_display.setCursor(4,1);
     liquid_crystal_display.print("seconds");
     }
     delay(500); 
     digitalWrite(only_charge_pin,LOW);
     delay(2000); 
     k++;
    }    
   }
   
   if(key=='1'){
    
    Serial.print("key pressed");
    liquid_crystal_display.clear();
    liquid_crystal_display.setCursor(0,0);
    liquid_crystal_display.print("Insert Rs5 Coin");
    delay(8000);
    Serial.println("check");
     int val2=digitalRead(ir_sensor2);
     Serial.print(val2);
     delay(500);
     
    if(val2==1)
    {
     delay(500);
     Serial.print("ir2 activated");
     warn=1;
     liquid_crystal_display.clear();
     liquid_crystal_display.setCursor(2,0);
     liquid_crystal_display.print("Slot Opening");
     digitalWrite(motor1,HIGH);
     digitalWrite(motor2,LOW);
     delay(12000);
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,LOW);
     delay(2000);
     initialpassword();
     liquid_crystal_display.clear();
     liquid_crystal_display.setCursor(2,0);
     liquid_crystal_display.print("Slot Closing");
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,HIGH);
     delay(12000);
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,LOW);
     delay(1000);
     digitalWrite(slot_charge_pin,HIGH);
     liquid_crystal_display.clear();
     liquid_crystal_display.setCursor(0,0);
     liquid_crystal_display.print("Time remaining");
     delay(1000); 
     for(int timer=60;timer>0;--timer){
     Serial.print(timer);
     digitalWrite(green_led,HIGH);
     delay(100);
     liquid_crystal_display.setCursor(1,1);
     liquid_crystal_display.print(timer);
     liquid_crystal_display.setCursor(4,1);
     liquid_crystal_display.print("seconds");
     int button=digitalRead(password_button);
     delay(500);
     
     if(button==0)
      {
      Serial.println("button not  pressed");
      delay(700);
      
      }
     else{
      Serial.println("button pressed");
      delay(700);
      change();
      button=LOW;
      delay(500);
      timer=0;
      delay(500);
     }
     }
     digitalWrite(slot_charge_pin,LOW);
     digitalWrite(green_led,LOW); 
     delay(1000);
     change();
     delay(1000); 
     k++;
    }
   }
 }
   delay(100);


} //loop ends
  


void change()
{

  int j=0;
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Enter Password");
  liquid_crystal_display.setCursor(0,1);
  while(j<4)
  {
    char key=keypad_key.getKey();
    if(key)
    {
      new_password[j++]=key;
      liquid_crystal_display.print("*");
    }
   key=0;

  }

  delay(500);



  
  if((strncmp(new_password, initial_password, 4)))

  {
    
    liquid_crystal_display.clear();
    liquid_crystal_display.print("Wrong Password");
    liquid_crystal_display.setCursor(0,1);
    liquid_crystal_display.print("Try Again");
    delay(1000);
    digitalWrite(red_led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(3000);
    digitalWrite(red_led,LOW);
    digitalWrite(buzzer,LOW);
    button=0;
    delay(1000);
    timer=0;
    info();
    
}
else{
    
    liquid_crystal_display.clear();
    liquid_crystal_display.print("Access Granted");
    digitalWrite(green_led,HIGH);
    delay(2000);
    liquid_crystal_display.setCursor(0,1);
    liquid_crystal_display.clear();
    liquid_crystal_display.print("Slot Opening");
     digitalWrite(motor1,HIGH);
     digitalWrite(motor2,LOW);
     delay(13000);
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,LOW);
     delay(6000);
     liquid_crystal_display.clear();
     liquid_crystal_display.print("Slot Closing");
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,HIGH);
     delay(14000);
     digitalWrite(motor1,LOW);
     digitalWrite(motor2,LOW);
     delay(1000);
     digitalWrite(green_led,LOW);
     key_pressed=0;
     digitalWrite(password_button,LOW);
     delay(1000);
     timer=0;
     info();
}

}

void initialpassword(){
 int j=0;
 liquid_crystal_display.clear();
 liquid_crystal_display.print("Set 4 digit pin");
 liquid_crystal_display.setCursor(0,1); 
  while(j<4)
  {
   char key=keypad_key.getKey();
    if(key)
    {
      initial_password[j++]=key;
      liquid_crystal_display.print("*");
}
key=0;
}
delay(500);
  liquid_crystal_display.clear();
  liquid_crystal_display.setCursor(0,0);
  liquid_crystal_display.print("PIN set success");
  digitalWrite(green_led,HIGH);
  delay(2000);
  digitalWrite(green_led,LOW);
  delay(2000);
}


void info(){
  
  liquid_crystal_display.setCursor(0,1);
  liquid_crystal_display.clear();
  liquid_crystal_display.print("1 To Open Slot ");
  liquid_crystal_display.setCursor(0,1);
  //liquid_crystal_display.print(" ");
  delay(1000);
  liquid_crystal_display.print("2 To Only Charge ");
  delay(1000);
  
  }

void keys(){
      int button=digitalRead(password_button);
      delay(500);
      if(button==0)
      {
      Serial.println("button not  pressed");
      delay(700);
      
      }
     else{
      Serial.println("button pressed");
      delay(700);
      change();
      delay(500);
      button=0;
      delay(500);
      
     }
      }  
