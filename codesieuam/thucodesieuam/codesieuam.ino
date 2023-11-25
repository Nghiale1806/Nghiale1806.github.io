#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "Phu Hai"
#define WIFI_PASSWORD "11021988"
String GOOGLE_SCRIPT_ID ="AKfycbxDt6-v33vY5t7xq1yG807WcKNUZNqB1prDT-S5pBX0l_IzWXWlF4kW4do9GAOH4jBu";

#define FIREBASE_HOST "tieuluantn-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "2OWhlZqrdDkxS4vqKzr4FIFl4sI6Y7XulNPWbPWL"
FirebaseData fbdb;

const int trig1 = 4;  
const int echo1 = 2;

const int trig2 = 25;  
const int echo2 = 27;
int led;
int relay = 19;
unsigned long thoigian1;
unsigned long thoigian2; 

int kccb1bandau;
int kccb2bandau;
//int khoangcach;
int khoangcach1;
int khoangcach2;          
//int gioihan = 25;
//int luotvao;
//int luotra;

int songuoitrongphong;
String hangdoi = "";
String den;
int timeoutcounter=0;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT); 
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
//connect wifi........................................
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status()  != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
//connect firebase Database...........................
Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Firebase.setReadTimeout(fbdb, 1000*60);
Firebase.setwriteSizeLimit(fbdb, "tiny");

  songuoitrongphong=0;
  
  delay(500);
  dokhoangcach1();
  kccb1bandau=khoangcach1;
  dokhoangcach2();
  kccb2bandau=khoangcach2;
  Serial.print(kccb1bandau);Serial.print("   ");
  Serial.println(kccb2bandau);
  den="";
}

void loop() {
  // put your main code here, to run repeatedly:
  khoangcach1 = 0;
  khoangcach2 = 0;
  dokhoangcach1();
  dokhoangcach2();
  //delay(500);
  if(songuoitrongphong==0){digitalWrite(relay,LOW);den="Tat";}
  else {digitalWrite(relay,HIGH);den="Sang";}
  if(khoangcach1<30 && hangdoi.charAt(0)!='1')
  {
    hangdoi+="1";
  }
  else if(khoangcach2<30 && hangdoi.charAt(0)!='2')
  {
    hangdoi+="2";
  }
  if(hangdoi.equals("12"))
  {
    songuoitrongphong++;
    Serial.print("Hang doi: ");
    Serial.println(hangdoi);
    hangdoi="";
    delay(550);
  }
 else if(hangdoi.equals("21") && songuoitrongphong>0)
 {
    songuoitrongphong--;
    Serial.print("Hang doi: ");
    Serial.println(hangdoi);
    hangdoi="";
    delay(550);
 }
 if(songuoitrongphong<=0){
  digitalWrite(12,LOW);
  led =0;}
      else {
      digitalWrite(12,HIGH);
      led=1;
 
  }
 // Reset hàng đợi nếu giá trị hàng đợi sai (11 hoặc 22) hoặc hết thời gian chờ
  if(hangdoi.length()>2 || hangdoi.equals("11") || hangdoi.equals("22") ||timeoutcounter>200)
  {
      hangdoi="";
  }
  if(hangdoi.length()==1)
  {timeoutcounter++;}
  else {timeoutcounter=0;}

  Serial.print("  Hang doi: ");
  Serial.print(hangdoi);
  Serial.print(" CB1: ");
  Serial.print(khoangcach1);
  Serial.print(" CB2: ");
  Serial.println(khoangcach2);
  Serial.print("So nguoi: ");
  Serial.print(songuoitrongphong);
hienthichuoi(0,0,"So Nguoi: ");
  hienthiso(11,0,songuoitrongphong);
  hienthichuoi(0,1,"Den Dang: ");
  hienthichuoi(11,1,den);
  //Serial.println(songuoitrongphong);
}
void dokhoangcach1()
{

  digitalWrite(trig1, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig1, LOW); 


  // Đo độ rộng xung HIGH ở chân echo.
  thoigian1 = pulseIn(echo1, HIGH);

  khoangcach1 = thoigian1 / 2 / 29.412;

}
void dokhoangcach2()
{

  digitalWrite(trig2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trig2, LOW); 


  // Đo độ rộng xung HIGH ở chân echo.
  thoigian2 = pulseIn(echo2, HIGH);

  khoangcach2 = thoigian2 / 2 / 29.412;

}

void hienthichuoi(int cot, int dong, String chuoi)
{
  lcd.setCursor(cot,dong);
  for(int j=0;j<chuoi.length();j++)
    {
      lcd.print(chuoi[j]);
    } 
    if(chuoi.length()==3){lcd.setCursor(cot+3,dong);lcd.print(" ");}
}
void hienthiso(int cot, int dong, int so)
{
  String chuoi=String(so);
  lcd.setCursor(cot-(chuoi.length()-1),dong);
  for(int j=0;j<chuoi.length();j++)
    {
      lcd.print(chuoi[j]);
    } 
  if(chuoi.length()==2){lcd.setCursor(cot-2,dong);lcd.print(" ");}
  if(chuoi.length()==1){lcd.setCursor(cot-2,dong);lcd.print(" ");lcd.setCursor(cot-1,dong);lcd.print(" ");}
  
  Firebase.setInt(fbdb, "/Room1/Songuoi", songuoitrongphong );
  Firebase.setInt(fbdb, "/Room1/trangthaiden", led);
}
