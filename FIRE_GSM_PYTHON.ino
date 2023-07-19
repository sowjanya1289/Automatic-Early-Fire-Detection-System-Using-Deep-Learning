#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int BUZZ = A3; //Connect BUZZ  To Pin #7 ////////buzzer
int RLED = A0; //Connect LED  To Pin #A0 ///////led
int GLED = A1; //Connect LED  To Pin #A1 ///////led
int relay = A2; //Connect relay To Pin #6 ///////relay


char data = 0;

void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(BUZZ, OUTPUT); 
pinMode(RLED, OUTPUT); 
pinMode(GLED, OUTPUT);
pinMode(relay, OUTPUT); 

digitalWrite(BUZZ,LOW);
digitalWrite(GLED,LOW);
digitalWrite(relay,LOW);
digitalWrite(RLED,LOW);

lcd.clear();
lcd.setCursor(0,0);lcd.print("Fire Detection");
lcd.setCursor(0,1);lcd.print("and Alerting");
delay(5000);lcd.clear();
lcd.setCursor(0,0);lcd.print("System Using");
lcd.setCursor(0,1);lcd.print("Arduino- GSM");
delay(5000);lcd.clear();
digitalWrite(GLED,LOW);delay(100);
digitalWrite(BUZZ,LOW);delay(100);
digitalWrite(GLED,HIGH);
lcd.setCursor(0,0);
lcd.print("  NO FIRE    ");
lcd.setCursor(0,1);
lcd.print("  ALAERT     ");
digitalWrite(BUZZ,LOW);delay(100);
digitalWrite(RLED,LOW);delay(100);
digitalWrite(GLED,HIGH);delay(100);
digitalWrite(relay,LOW);delay(100);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
st:

if (Serial.available() > 0) 
{
data = Serial.read();
///////////////////////////////////
if(data == 'S')
{
lcd.setCursor(0,0);
lcd.print("  NO FIRE    ");
lcd.setCursor(0,1);
lcd.print("  ALAERT     ");
digitalWrite(BUZZ,LOW);delay(100);
digitalWrite(RLED,LOW);delay(100);
digitalWrite(GLED,HIGH);delay(100);
digitalWrite(relay,LOW);delay(100);
}

if(data == 'F')
{
lcd.setCursor(0,0);
lcd.print("     Fire  ");
lcd.setCursor(0,1);
lcd.print("  Detected  ");
digitalWrite(BUZZ,HIGH);delay(100);
digitalWrite(RLED,HIGH);delay(100);
digitalWrite(GLED,LOW);delay(100);
digitalWrite(relay,HIGH);delay(100);
lcd.clear();lcd.print("Sending SMS ");
delay(500);
Send();
delay(500);
digitalWrite(BUZZ,LOW);digitalWrite(RLED,LOW);
digitalWrite(relay,LOW);delay(100);
lcd.clear();lcd.print("CALLING------1 ");
Serial.print("ATD+91");
Serial.print("7095906007");
Serial.print(";\r\n");delay(12000);
Serial.println("ATH");
delay(2000);
lcd.setCursor(0,0);
lcd.print("  NO FIRE    ");
lcd.setCursor(0,1);
lcd.print("  ALAERT     ");
digitalWrite(BUZZ,LOW);delay(100);
digitalWrite(RLED,LOW);delay(100);
digitalWrite(GLED,HIGH);delay(100);
digitalWrite(relay,LOW);delay(100);
goto st;
}

}
}


void init_sms1()
{Serial.println("AT+CMGF=1");delay(400);Serial.println("AT+CMGS=\"7095906007\""); delay(400);}

void Send_sms()
{
Serial.println("Fire Detected");delay(500);
Serial.println("Plz Rescue ");delay(500);
Serial.println("https://www.google.com/maps/place/17.3572096,78.5580032");delay(500);
Serial.write(26);delay(3000);lcd.clear();
lcd.print("Message Sent ");
delay(1000); lcd.clear();
Serial.print("AT\r\n");delay(500);
Serial.print("AT\r\n");delay(500);
Serial.println("AT+CMGF=1");delay(200);
lcd.clear();
}

void Send()
{ 
init_sms1();delay(1000);lcd.clear();lcd.print("Sending SMS  ");Send_sms();
}
