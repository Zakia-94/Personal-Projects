#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //Initialise the LCD with the arduino. LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(8,9,4,5,6,7);
const int LED_green = 11;
const int LED_red = 10;
String content= "";

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(LED_green, OUTPUT);
  pinMode(LED_red, OUTPUT); 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Start scanning...");
  Serial.print("Start scanning... \n");
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
   //Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
 }
  //Show UID of your tag on serial monitor
  lcd.setCursor(0,0);
  lcd.print("UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     lcd.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card that you want to give access(ex: tag approved --> C6 7E C7 F7/Access denied --> BD 31 15 2B)
  {
    lcd.setCursor(0,1);
    lcd.print("tag approved");
    Serial.print("tag approved");
    digitalWrite(LED_green, HIGH);
    delay(3000);
  }
 else {
    lcd.setCursor(0,1);
    lcd.print(" Access denied");
    Serial.print(" Access denied");
    digitalWrite(LED_red, HIGH);
    delay(3000);
  }
} 
