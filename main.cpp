#include <Arduino.h>
#include <M5Stack.h>
#include <M5StackUpdater.h>
#include <Free_Fonts.h>  // From M5Stack/docs/examples/Advanced/Display/All_Free_Fonts_Demo
#include <Usb.h>
#include <PaSoRi.h>

PaSoRi pasori;

int readSFC()
{
  byte b[16];
  char toLCD[32];
  int ret = -1;
  for (int i = 0; i < 1; i++)
  { // 直近の記録のみ
    int rcode = pasori.read_without_encryption02(0x090f, i, b);
    if (rcode)
    {
      Serial.print("rcode = ");
      Serial.println(rcode, HEX);
      break;
    }
    Serial.print(i, DEC);
    Serial.print(": ");
    Serial.print(b[11] * 256 + b[10]);
    Serial.print(" YEN  ");

    M5.Lcd.fillScreen(TFT_GREEN);
    M5.Lcd.setTextDatum(MC_DATUM);
    // Set text colour to orange with black background
    M5.Lcd.setTextColor(TFT_BLACK, TFT_GREEN);
    sprintf(toLCD, "%d YEN", b[11] * 256 + b[10]);
    M5.Lcd.setFreeFont(FF32);                // Select the font
    M5.Lcd.drawString(toLCD, 160, 60, GFXFF); // Print the string name of the font

    if (i == 0)
      ret = (unsigned int)b[11] * 256 + b[10];

    // date
    Serial.print(2000 + ((b[4] >> 1) & 0x7f), DEC);
    Serial.print(".");
    Serial.print(((b[4] & 0x01) << 3) | ((b[5] >> 5) & 0x07), DEC);
    Serial.print(".");
    Serial.print(b[5] & 0x1F, DEC);

    // from/to
    Serial.print(" from:");
    Serial.print(b[6], HEX);
    Serial.print("-");
    Serial.print(b[7], HEX);
    Serial.print(" to:");
    Serial.print(b[8], HEX);
    Serial.print("-");
    Serial.print(b[9], HEX);

    Serial.println("");
  }
  return ret;
}

void setup() {
  M5.begin();
  if (digitalRead(BUTTON_A_PIN) == 0)
  {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
  Serial.begin(115200);
  Serial.println("Start");
  delay(5);                    // ★5ms遅らす
  byte rcode = pasori.begin(); // initialize PaSoRi
  if (rcode != 0)
  {
    Serial.print("PaSoRi initialization failed! : rcode = ");
    Serial.println(rcode, HEX);
    while (1)
      ; // stop
  }
  M5.Lcd.fillScreen(GREEN);
}

void loop() {
  byte rcode, i;
  pasori.task(); // call this at every loop
  static short syscode = POLLING_SUICA;

  rcode = pasori.poll(syscode);
  if (rcode)
  {
    M5.Lcd.fillScreen(TFT_BLUE);
    delay(100);
  }
  else
  {
    // Polling successful
    Serial.println("FeliCa detected. IDm=");
    for (i = 0; i < 8; i++)
    {
      Serial.print(pasori.getIDm()[i], HEX);
      Serial.print(" ");
    }
    Serial.print("  PMm=");
    for (i = 0; i < 8; i++)
    {
      Serial.print(pasori.getPMm()[i], HEX);
      Serial.println(" ");
    }
    Serial.println("");

    // Read SFC (Suica etc.)
    Serial.println("<< SFC >>");
    readSFC();
    delay(5000);
  }
}

