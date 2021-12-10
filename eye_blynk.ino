//#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial gsm(2, 3);//rx,tx gsm module pins
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
String exString;
unsigned char sdata=0,rx[40],r;
int la,lo,latt,lonn,gps_chk='0';
float lath,latl,lonh,lonl,lat,lon;
int vib=A5,buz=13,ct,alc=A1,acc=A2;
void setup() 
{
  Serial.begin(9600);

  gsm.begin(9600);   // Setting the baud rate of GSM Module  
  pinMode(A0,INPUT);pinMode(alc,INPUT);pinMode(acc,INPUT);
  pinMode(13,OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("ACC DETECTION & ");
  lcd.setCursor(0,1);
  lcd.print("DRIVER ALERT SYS");
  delay(500);
  //RecieveMessage();
}

void loop() 
{
  Serial.println(digitalRead(acc));
  Serial.println(digitalRead(alc));
  if(digitalRead(A0)==0)
  {
    lcd.setCursor(0,0);
    lcd.print("DRIVER IN SLEEP ");
    lcd.setCursor(0,1);
    lcd.print("PERSON IN DANGER");
    Serial.println("Accedent occured--------");
    digitalWrite(buz,HIGH);
    //gps_sms(2);
    delay(200);
    digitalWrite(buz,LOW);ct++;
    delay(1000);
    if(ct==15)
    {
     ct=0; digitalWrite(buz,HIGH);
     gps_sms(1);
     digitalWrite(buz,HIGH);
    }
  }
  else
  {
    ct=0;
  }
  if(digitalRead(acc)==0)
  {
    lcd.setCursor(0,0);
    lcd.print("ACCEDENT DETECT ");
    lcd.setCursor(0,1);
    lcd.print("SMS SENDING.....");
    digitalWrite(buz,HIGH);
    gps_sms(2);
    digitalWrite(buz,LOW);
  }
  if(digitalRead(alc)==0)
  {
    lcd.setCursor(0,0);
    lcd.print("ALCOHOL DETECT  ");
    lcd.setCursor(0,1);
    lcd.print("SMS SENDING.....");
    digitalWrite(buz,HIGH);
    gps_sms(3);
    digitalWrite(buz,LOW);
  }
}        

/*void SendMessage(unsigned int m)
{
  lcd.setCursor(0,0);lcd.print("SENDING SMS... ");
  lcd.setCursor(0,1);lcd.print("                ");
  if(m=='1')
  {
    gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.println("AT+CMGS=\"9493635165\"\r"); // Replace x with mobile number
  delay(1000);
  gsm.print("VEHICLE THEFTED AT:");
  gsm.print("http://maps.google.com/maps?q=");
  gsm.print(lat,6);gsm.print(", ");gsm.println(lon,6);
  delay(100);
   gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  chk='2';
  }
  else if(m=='2')
  {
    Serial.println("nnnnnnnnnnnnnnnnnn");
    gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.println("AT+CMGS=\"7659070083\"\r"); // Replace x with mobile number
  delay(1000);
  gsm.print("ACCIDENT OCCURED AT:");
  gsm.print("http://maps.google.com/maps?q=");
  gsm.print(lat,6);gsm.print(", ");gsm.println(lon,6);
  delay(100);
   gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  chk='2';
  }
  else if(m=='3')
  {k=0;
    gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  gsm.print("AT+CMGS=\""); // Replace x with mobile number
  gsm.print(exString.substring(12,22));
  gsm.println("\"\r"); // Replace x with mobile number
  gsm.print("AT+CMGS=\""); // Replace x with mobile number
  gsm.print(exString.substring(12,22));
  gsm.println("\"\r"); // Replace x with mobile number
  delay(1000);
  gsm.print("PRESENT LOCATION:");
  gsm.print("http://maps.google.com/maps?q=");
  gsm.print(lat,6);gsm.print(", ");gsm.println(lon,6);
  delay(100);
   gsm.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  chk='2';
  }
}*/
 /*void RecieveMessage()
{
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  gsm.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
}*/
unsigned char rxd (void)
{                    
  while (gsm.available()==0);
  return(gsm.read());
  //return (sdata);
}
void gps_sms(int ll)
{
    gps_chk='0';
    while(gps_chk='0')
    {
      //Serial.println("kkkkkkkkkkkkkk");
    if(rxd()=='$')
    {
      if(rxd()=='G')
      {
        if(rxd()=='P')
        {
          //Serial.println("k");
          if(rxd()=='G')
          {
            if(rxd()=='G')
            {
              if(rxd()=='A')
              {
                gps_chk='1';
                for(r=0;r<36;r++)
                {
                  rx[r] = rxd();
                }
                for(r=12;r<36;r++)
                {
                  Serial.write(rx[r]);//rx[r] = rxd();
                }
                Serial.println();
                la=(rx[11]&0x0f)*10+(rx[12]&0x0f);
                lath=(rx[13]&0x0f)*10+(rx[14]&0x0f);
                //lath=(rx[13]&0x0f)*10+(rx[14]&0x0f);
                latl=(rx[16]&0x0f)*1000+(rx[17]&0x0f)*100+(rx[19]&0x0f)*10+(rx[20]&0x0f);
                lo=(rx[25]&0x0f)*10+(rx[26]&0x0f);
                lonh=(rx[27]&0x0f)*10+(rx[28]&0x0f);
                lonl=(rx[30]&0x0f)*1000+(rx[31]&0x0f)*100+(rx[32]&0x0f)*10+(rx[33]&0x0f);
                //-----------------lat------------------------
                lath=lath/60;
                latl=(latl/60)/10000;
                lat=lath+latl;
                latt=lat*10000;
                //------------------lon------------------------
                lonh=lonh/60;
                lonl=(lonl/60)/10000;
                lon=lonh+lonl;
                lonn=lon*10000;
                if(ll==1)
                {
                  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
                  delay(1000);  // Delay of 1000 milli seconds or 1 second
                  gsm.println("AT+CMGS=\"8008758515\"\r"); // Replace x with mobile number
                  delay(1000);
                  gsm.print("DRIVER IN SLEEPING:");
                  gsm.print("http://maps.google.com/maps?q=");
                  gsm.print(la);gsm.print('.');gsm.print(latt);gsm.print(",");//Serial.println(latl);
                  gsm.print(lo);gsm.print('.');gsm.println(lonn);//16.496390, 80.654752
                  Serial.print("http://maps.google.com/maps?q=");
                  Serial.print(la);Serial.print('.');Serial.print(latt);Serial.print(",");//Serial.println(latl);
                  Serial.print(lo);Serial.print('.');Serial.println(lonn);//16.496390, 80.654752
                  delay(100);
                  gsm.println((char)26);// ASCII code of CTRL+Z
                  delay(1000);
                  gps_chk='1';
                  break;
                }
                else if(ll==2)
                {
                  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
                  delay(2000);  // Delay of 1000 milli seconds or 1 second
                  Serial.println("AT+CMGS=\"9391910785\"\r"); // Replace x with mobile number
                  gsm.println("AT+CMGS=\"8008758515\"\r"); // Replace x with mobile number
                  delay(2000);
                  gsm.print("ACCIDENT DETECTED AT:");
                  gsm.print("http://maps.google.com/maps?q=");
                  Serial.print("http://maps.google.com/maps?q=");
                  gsm.print(la);gsm.print('.');gsm.print(latt);gsm.print(",");//Serial.println(latl);
                  Serial.print(la);Serial.print('.');Serial.print(latt);Serial.print(",");//Serial.println(latl);
                  gsm.print(lo);gsm.print('.');gsm.println(lonn);//16.496390, 80.654752
                  Serial.print(lo);Serial.print('.');Serial.println(lonn);//16.496390, 80.654752
                  delay(1000);
                  gsm.println((char)26);// ASCII code of CTRL+Z
                  delay(2000);
                  gps_chk='1';
                  break;
                }
                else if(ll==3)
                {
                  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
                  delay(2000);  // Delay of 1000 milli seconds or 1 second
                  Serial.println("AT+CMGS=\"9391910785\"\r"); // Replace x with mobile number
                  gsm.println("AT+CMGS=\"8008758515\"\r"); // Replace x with mobile number
                  delay(2000);
                  gsm.print("ALCOHOL DETECTED AT:");
                  gsm.print("http://maps.google.com/maps?q=");
                  Serial.print("http://maps.google.com/maps?q=");
                  gsm.print(la);gsm.print('.');gsm.print(latt);gsm.print(",");//Serial.println(latl);
                  Serial.print(la);Serial.print('.');Serial.print(latt);Serial.print(",");//Serial.println(latl);
                  gsm.print(lo);gsm.print('.');gsm.println(lonn);//16.496390, 80.654752
                  Serial.print(lo);Serial.print('.');Serial.println(lonn);//16.496390, 80.654752
                  delay(1000);
                  gsm.println((char)26);// ASCII code of CTRL+Z
                  delay(2000);
                  gps_chk='1';
                  break;
                }
                
              }  
            }  
          }  
        }  
      }
    }
    gps_chk='1';
  }
}

