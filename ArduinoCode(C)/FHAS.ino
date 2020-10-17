#include <dht.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

 
#define SS_PIN 53
#define RST_PIN 6
MFRC522 mfrc522(SS_PIN, RST_PIN); 

#define R1Servo 5
#define R2Servo 4
#define R3Servo 2
#define R4Servo 3

#define R1Lgt 24
#define R2Lgt 23
#define R3Lgt 22
#define R5Lgt 26
#define R4Lgt1 25
#define R4LgtV2 28

#define Buzz 12
#define LgtS A2
#define Temp A4
#define GasS A3
#define Rain A9

#define R1PIR A1
#define R2PIR A0
#define R3PIR A5
#define R4PIR A15
#define R5PIR A6

#define R1Tch A8
#define R2Tch A10
#define R3Tch A12

bool R1L=false;
bool R2L=false;
bool R3L=false;
bool R4L=false;
bool R5L=false;

bool R1S=false;
bool R2S=false;
bool R3S=false;
bool R4S=false;

void Inp(int n) { pinMode(n,INPUT); }
void Outp(int n) { pinMode(n,OUTPUT); }

bool TchSns=false;

Servo R1Ser,R2Ser,R3Ser,R4Ser;

void setup() {
  Outp(R1Servo);
  Outp(R2Servo);
  Outp(R3Servo);
  Outp(R4Servo);
  Outp(R1Lgt);
  Outp(R2Lgt);
  Outp(R3Lgt);
  Outp(R4Lgt1);
  Outp(R5Lgt);
  Outp(Buzz);
  Outp(R4LgtV2);
  Inp(GasS);
  Inp(LgtS);
  Inp(Temp);
  Inp(R1PIR);
  Inp(Rain);
  Inp(R4PIR);
  Inp(R2PIR);
  Inp(R3PIR);
  Inp(R1Tch);
  Inp(R2Tch);
  Inp(R3Tch);
  Inp(LgtS);

  R1Ser.attach(R1Servo);
  R2Ser.attach(R2Servo);
  R3Ser.attach(R3Servo);
  R4Ser.attach(R4Servo);

  Serial.begin(9600);
  Serial.println("Initiating\nEnter Password");

  SPI.begin();
  mfrc522.PCD_Init(); 

    CloseDoor('1');
  CloseDoor('2');
  CloseDoor('3');
  CloseDoor('4');
}

String MainPassword="Password";

void OpenDoor(char n){
  switch(n){
    case '1':R1Ser.write(90);R1S=true;break;

    case '2':R2Ser.write(90);R2S=true;break;

    case '3':R3Ser.write(0);R3S=true;break;

    case '4':R4Ser.write(90);R4S=true;break;
  }


  
}

void CloseDoor(char r){
  switch(r){
    case '1':R1Ser.write(0);R1S=false;break;

    case '2':R2Ser.write(0);R2S=false;break;

    case '3':R3Ser.write(90);R3S=false;break;

    case '4':R4Ser.write(0);R4S=false;break;
  }
}

void LgtOn(char n){
  switch(n){
    case '1':digitalWrite(R1Lgt,1);R1L=true;break;

    case '2':digitalWrite(R2Lgt,1);R2L=true;break;

    case '3':digitalWrite(R3Lgt,1);R3L=true;break;

    case '4':digitalWrite(R4Lgt1,1);digitalWrite(R4LgtV2,1);R4L=true;break;
    
    case '5':digitalWrite(R5Lgt,1);R5L=true;break;
  }


  
}

void LgtOff(char r){
  switch(r){
    case '1':digitalWrite(R1Lgt,0);R1L=false;break;

    case '2':digitalWrite(R2Lgt,0);R2L=false;break;

    case '3':digitalWrite(R3Lgt,0);R3L=false;break;

    case '4':digitalWrite(R4Lgt1,0);digitalWrite(R4LgtV2,0);R4L=false;break;

    case '5':digitalWrite(R5Lgt,0);R5L=false;break;
  }
}

bool forceopendoors=false;
bool Night=false;
bool Authorized=false;
bool R1Human=false;
bool R2Human=false;
bool R3Human=false;
bool R4Human=false;
bool R5Human=false;

void AutoDL()
{
  if(analogRead(R1PIR)>600&&!R1Human){
    if(Night){
    LgtOn('1');}
    if(!forceopendoors){OpenDoor('2');}
    
    R1Human=true;
  }
  if(analogRead(R1PIR)<600&&R1Human){
    //delay(100);
    if(analogRead(R1PIR)<600){
      R1Human=false;
      if(!forceopendoors){
      CloseDoor('2');}
      if(Night){
      LgtOff('1');}
      bool TouchSR1Lgt=false;
      bool TouchSR1Door=false;

    }
  }


if(analogRead(R5PIR)>600&&!R5Human){
  if(Night){
    LgtOn('5');}
    if(!forceopendoors){
    OpenDoor('3');
    OpenDoor('4');}
    R5Human=true;
  }
  if(analogRead(R5PIR)<600&&R5Human){
    //delay(100);
    if(analogRead(R1PIR)<600){
      R5Human=false;
      if(!forceopendoors){
      CloseDoor('3');
      CloseDoor('4');}
      if(Night){
      LgtOff('5');}

    }
  }
  
    if(analogRead(R2PIR)>600&&!R2Human){
      if(Night){
    LgtOn('2');}
    R2Human=true;
  }
  if(analogRead(R2PIR)<600&&R2Human){
    //delay(100);
    if(analogRead(R2PIR)<600){
      R2Human=false;
      if(Night){
      LgtOff('2');}
      bool TouchSR2Lgt=false;
      bool TouchSR2Door=false;

    }
    }
  if(analogRead(R3PIR)>600&&!R3Human){
    if(Night){
    LgtOn('3');}
    R3Human=true;
  }
  if(analogRead(R3PIR)<600&&R3Human){
    //delay(100);
    if(analogRead(R3PIR)<600){
      R3Human=false;
      if(Night){
      LgtOff('3');}
      bool TouchSR3Lgt=false;
      bool TouchSR3Door=false;

    }
      if(analogRead(R4PIR)>600&&!R4Human){
        if(Night){
    LgtOn('4');}
    R4Human=true;
  }
  if(analogRead(R4PIR)<600&&R4Human){
    //delay(100);
    if(analogRead(R4PIR)<600){
      R4Human=false;
      if(Night){
      LgtOff('4');}

    }
  }
}
}

bool touched1;
bool touched2;
bool touched3;

void TouchS(){
    if(analogRead(R1Tch)>500&&touched1&&TchSns)
    {
      if(R1S){CloseDoor('1');R1S=false;}
      else{OpenDoor('1');R1S=true;}    
      touched1=false;
       delay(2000);
    }
    else if(touched1 &&TchSns)
    {
      if(R1L){LgtOff('1'); }
      else{LgtOn('1');}
      touched1=false;
       delay(2000);
    }
    if(analogRead(R1Tch)>500&&TchSns){
    touched1=true;
    delay(1000);}


    if(analogRead(R2Tch)>500&&touched2&&TchSns)
    {
      if(R2S){CloseDoor('2');R2S=false;}
      else{OpenDoor('2');R2S=true;}    
      touched2=false;
       delay(2000);
    }
    else if(touched2&&TchSns)
    {
      if(R2L){LgtOff('2'); }
      else{LgtOn('2');}
      touched2=false;
       delay(2000);
    }
      if(analogRead(R2Tch)>500&&TchSns){
    touched2=true;
    delay(1000);}


    if(analogRead(R3Tch)>500&&touched3&&TchSns)
    {
      if(R3S){CloseDoor('3');R3S=false;}
      else{OpenDoor('3');R3S=true;}    
      touched3=false;
       delay(2000);
    }
    else if(touched3&&TchSns)
    {
      if(R3L){LgtOff('3'); }
      else{LgtOn('3');R3L=true;}
      touched3=false;
       delay(2000);
    }
      if(analogRead(R3Tch)>500&&TchSns){
    touched3=true;
    delay(1000);}
       
  
}

bool autoMode=true;

void Unlocked(char a)
{
  Unlocked_Safety_Sensors();
  if(autoMode){AutoDL();} 
  if(TchSns){
      TouchS();
  }
  if(a=='3'){
    autoMode=false;
  }
  if(a=='4'){
    autoMode=true;
  }
  CheckRFID();
  if(a=='1'){
    TchSns=false;
  }
  doorfunc(a);
  lightfunc(a);
}

void ShutDown(){
  LgtOff('1');
  CloseDoor('1');

  LgtOff('2');
  CloseDoor('2');

  LgtOff('3');
  CloseDoor('3');

  LgtOff('4');
  CloseDoor('4'); 

   LgtOff('5');
}

void Locked(String a)
{
  Locked_Safety_Sensors();
  CheckRFID();
  if(a==MainPassword&&!Authorized)
  {
    Authorized=true;
    Serial.println("Authorized\n");

    OpenDoor('1');
    if(Night){
    LgtOn('1');}
  }
  else if(a!=""&&a!=MainPassword&&!Authorized)
  {
    Serial.println("Access Deined\n");
  }  
}

void CheckRFID()
{
  
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "65 6C E1 52") //change here the UID of the card/cards that you want to give access
  {
    if(!Authorized){
    Authorized=true;Serial.println("Authorized"); delay(1000);OpenDoor('1');delay(1000);if(Night){LgtOn('1');}}
    else{Authorized=false;Serial.println("Locked");ShutDown();}
  }
 
 else   {
  if(!Authorized){
    Serial.println("Access denied");
    delay(3000);}
  }
} 

bool GasLeak=false;

void Locked_Safety_Sensors(){
  
  if(analogRead(GasS)>300){
    GasLeak=true;
    Serial.println("Gas Leak");
    for(int m=0;m<10;m++){
    for(int i=0;i<5000;i++){
  tone(Buzz,i,50);
}}GasLeak=false;
  }
}

float Temperature;
float Humidity;

dht DHT;
void temp(){
  int chk = DHT.read11(Temp);
  Temperature=DHT.temperature;
  Humidity=DHT.humidity;
}

void lightfunc(char a){
  if(a=='i'){
    LgtOn('1');
  }
  if(a=='k'){
    LgtOn('2');
  }if(a=='m'){
    LgtOn('3');
  }if(a=='o'){
    LgtOn('4');
  }
  if(a=='r'){
    LgtOn('5');
  }
  

    if(a=='j'){
    LgtOff('1');
  }
  if(a=='l'){
    LgtOff('2');
  }if(a=='n'){
    LgtOff('3');
  }if(a=='p'){
    LgtOff('4');
  }
  if(a=='t'){
    LgtOff('5');
  }
}

void doorfunc(char a){
  if(a=='a'){
    OpenDoor('1');
  }
  if(a=='c'){
    OpenDoor('2');
  }if(a=='e'){
    OpenDoor('3');
  }if(a=='g'){
    OpenDoor('4');
  }

    if(a=='b'){
    CloseDoor('1');
  }
  if(a=='d'){
    CloseDoor('2');
  }if(a=='f'){
    CloseDoor('3');
  }if(a=='h'){
    CloseDoor('4');
  }}
String RainAvailable="Nope";

void RecieverProtocol(){
  Serial.println(String(R1Human)+":"+String(R1L)+":"+String(R1S)+";"+String(R2Human)+":"+String(R2L)+":"+String(R2S)+";"+String(R3Human)+":"+String(R3L)+":"+String(R3S)+";"+String(R4Human)+":"+String(R4L)+":"+String(R4S)+";"+String(R5Human)+":"+String(R5L)+";"+String(autoMode)+";"+String(Night)+";"+String(GasLeak)+";"+String(Temperature)+":"+String(Humidity)+";"+String(RainAvailable));  
}

void Unlocked_Safety_Sensors(){
  if(analogRead(Rain)<300&&RainAvailable!="Yup"){
    RainAvailable="Yup";
    digitalWrite(Buzz,1);
    RecieverProtocol();
    delay(500);
    digitalWrite(Buzz,0);
    RainAvailable="Nope";
    
  } 
  
  if(analogRead(GasS)>400){
    GasLeak=true;
    Serial.println("Gas Leak");
    for(int m=0;m<10;m++){
    for(int i=0;i<5000;i++){
  tone(Buzz,i,50);
  }}}
  GasLeak=false;
}

void Sleep(){
  char s;
  ShutDown();
  while(true){
    s=Serial.read();
    if(s=='2'){
      RecieverProtocol();
    }
    if(s=='*'){
      break;    }
  }

  
}

  
char s;
char q;
void loop() 
{
  
  temp();
  if(analogRead(LgtS)<10){
  Night=true;

  }
  else{
    Night=false;
        LgtOff('1');
    LgtOff('2');
    LgtOff('3');
    LgtOff('4');
    LgtOff('5');
  }
  s=Serial.read();
  if(s=='$'){
    Sleep();
  }
  if(s=='^'){
    forceopendoors=true;
    OpenDoor('1');
    OpenDoor('2');
    OpenDoor('3');
    OpenDoor('4');
  }
  if(s=='%'){
    forceopendoors=false;
  }
  if(s=='?'){
    if(Authorized){
      Serial.println("Authorized");
    }
    else{
      Serial.println("Denied");
    }
  }
  if(s=='2'){
    RecieverProtocol();
  }
  if(s=='q')q='q';
  if(s=='1'){
    TchSns=false;   
  }
  if(s=='&'){
    TchSns=true;
  }
  if(q=='q' or !Authorized){
    String a=Serial.readString();
    if(!Authorized)
    {
      Locked(a);
    }
    else{
      if(a==MainPassword){
        Serial.println("Locked");
        Authorized=false;
        ShutDown();
      }
    }
  }
  if(Authorized)
  {
    Unlocked(s);
  }
  
}
