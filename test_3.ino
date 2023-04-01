/*
 1A B0 AE 80
 09 9B DA 7C
 9A 57 DD 34
 AA 7F 52 2F
 4A 08 20 30
 B9 1F 23 CB
 */


#include <SPI.h>
#include <MFRC522.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
#define CLK_PIN   7 // or any other digital pin
#define DIN_PIN   6 // or any other digital pin
#define CS_PIN    5 // or any other digital pin
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

MD_Parola P = MD_Parola(HARDWARE_TYPE, DIN_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_MAX72XX M = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

typedef struct{
  String id;
  String pname;
  int price;
  
}shop;
    const shop arr[] = {
    {" 1A B0 AE 80","chips",10},
    {" 09 9B DA 7C","oil",100},
    {" 9A 57 DD 34","rice",50},
    {" AA 7F 52 2F","ghee",250},
    {" 4A 08 20 30","soap",30},
    {" B9 1F 23 CB","salt",130}
  };
   const String key[] = {" 1A B0 AE 80"," 09 9B DA 7C"," 9A 57 DD 34"," AA 7F 52 2F"," 4A 08 20 30"," B9 1F 23 CB"};
     int sum=0;
  String msg = "                                                   Generating Bill :- ";
  int no_of_item=3;
  int no=0;


void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
    P.begin();
    P.setInvert(false);
  // P.setSpeed(0);
  // P.setFont(-5);
  P.displayText("Welcome", PA_CENTER, 50, 3, PA_PRINT, PA_NO_EFFECT);
  // delay(1000);
  // P.displayText("Scanning", PA_CENTER, 50, 3, PA_PRINT, PA_NO_EFFECT);
  // no=0;
  // // P.displayText
  // no_of_item = 3;

}
void loop() 
{

 P.displayAnimate();

  // if(Serial.parseInt()==1)
  // {
  //   // start billing
  //   msg = "";
  //   sum = 0;
  //   P.print("");
  //   P.displayText("Scan...", PA_CENTER,20,0,PA_PRINT, PA_NO_EFFECT);
  //   // P.displayAnimate();
  //         // delay(1000);
  // }



  // Look for new cards
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
  // Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  // Serial.print("Message : ");
  content.toUpperCase();
  // String str = "";
  for(int i=0;i<6;i++)
  {
        if(content.equals(key[i]))
        {
          no=no+1;
          sum+= arr[i].price;
          String strno = String(no);
          msg += strno +") "+ arr[i].pname+ " - Price"+arr[i].price + " Rs            ";
          String str ="                "+ strno +") "+ arr[i].pname+ " - "+arr[i].price + " Rs";
          // P.print("");

          // int i=0;
          // while(i<10000)
          // {
          P.displayText(str.c_str(), PA_LEFT, 50, 0, PA_SCROLL_LEFT);
          Serial.println(str);
          P.displayAnimate();
          //  no++;
          // delay(3000);
          // P.print("");
          // str = "Bill - "+s

          }

    }
 Serial.println(no);

      if(no_of_item==no)
  {

    msg+= "bill:"+String(sum);

    P.displayText(msg.c_str(), PA_LEFT, 0, 0, PA_SCROLL_LEFT);
 Serial.println(msg+""+sum);
    

  }
      
 P.displayAnimate();
//  Serial.println(msg);
//  Serial.println(sum);


  // if()

delay(1000);
 
 
} 
