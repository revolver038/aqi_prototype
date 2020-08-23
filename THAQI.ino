/*
Author: Tural Alizada, 23.08.2020
SDS011 + DHT11 + SSH1306 Oled display + Arduino UNO

Qeydler:
SSD1306 nin yaddasi az olduguna gore string variabledan istifade etmek meslehet deyl
display.print("Hello World") evezine display.print(F("Hello World)) seklinde yazilmasi ssd1306 ucun size elave bytelar qazandiracaq
Sensor olcumlerini loopda qoyacaqsinizsa delay(1000), delay(3000) ve s. den istifade edin mutleq. 

AQI neticesi ucun istifade edilen cedvel: https://www3.epa.gov/airnow/aqi-technical-assistance-document-sept2018.pdf

Send me an email if you have difficulty to set up
alizade.tural@yahoo.com
*/

//Lazimi librarylerin include edilmesi
#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SDS011.h>

dht DHT;
//Rutubet sensorunun UNO-daki pini
#define DHT11_PIN 7
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//ENG: Replace TX and RX if any issues occur
//AZE: TX ve RX yerleri ferqlidir. Bele ki TX UNOda Digital: 0 pinine ve RX ise Digital: 1 pinine yerlesdirilir
//Eger islemese TX ve RX in yerini deyisdirin
int rxPin = 0;
int txPin = 1;
int ldrPin = A0;
int ldrStatus = 0;

//SDS011 sensoru ucun PM variablelarin tanidilmasi
float p10, p25;
int error;
SDS011 my_sds;

// OLED SSD1306:
#define OLED_RESET    -1 // Reset pin # (eger -1 de islemese 4 - le deyisdirin ele yoxlayin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int a = 0;
//Rutubet sensoru ucun variablelar
int dt = 0;
int dh = 0;

int px25 = 0;
int px10 = 0;
void setup() {
  Serial.begin(9600);


  //AZE: DIQQET SDS1306 oled ekrani ucun "0x3C" olaraq deyisdirilib burada, 
  //ferqli ekranlar ucun ferqlidir bu kod.Eger islemese 0x3D yazaraq yoxlayin
  //ENG: Below we used 0x3C but it isn't same for all oled displays. Try 0x3D if any issue occurs for display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  //Kontrast ve parlaqligin deyisdirilmesi
  display.ssd1306_command(SSD1306_SETPRECHARGE);
  display.ssd1306_command(4);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(4);

  display.clearDisplay();
  display.drawPixel(10, 10, SSD1306_WHITE);
  display.display();
  delay(1000);

  //SDS011 setupda aktivlesdirilmesi
  my_sds.begin(0, 1);

  //display ON and OFF etmek ucun
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  // delay(3000);
  //display.ssd1306_command(SSD1306_DISPLAYON);

}

void loop() {
  if (a == 0) {
    tempverut();   
    a = 1;
    delay(100);
  } else {
    pmvalues();
    a = 0;
    delay(100);
  }
}


// SDS011 sensorundan pm2.5 ve pm10-nun oxunmasi ve ekranda print edilmesi
void pmvalues(void) {
  error = my_sds.read(&p25, &p10);
  display.clearDisplay();
  display.fillRect(0, 0, 77, 11, SSD1306_WHITE);
  display.setTextSize(1);            
  display.setTextColor(SSD1306_BLACK); // SSD1306_BLACK);       
  display.setCursor(3, 2);           
  display.print(F("PM DEYERLERI\n"));
  display.setTextColor(SSD1306_WHITE);
  display.print(F("-------------\n"));
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(F("PM2.5 : "));
  display.setTextSize(2);          
  display.setTextColor(SSD1306_WHITE);
  display.print(F(" "));
  if (! error) {
    display.print(p25); 
  } else {
    display.print(F("Xeta"));
  }
  display.print(F("\n"));
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(F("PM10 : "));
  display.setTextSize(2);
  display.print(F(" "));
  if (! error) {
    display.print(p10); 
  } else {
    display.print(F("Xeta"));
  }
  display.print(F("\n"));
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (p25 <= 12) {
    px25 = 1;
  } else if (p25 <= 35.4) {
    px25 = 2;
  } else if (p25 <= 55.4) {
    px25 = 3;
  } else if (p25 <= 150.4) {
    px25 = 4;
  } else if (p25 <= 250.4) {
    px25 = 5;
  } else if (p25 <= 500.4) {
    px25 = 6;
  } else {
    px25 = 7;
  }

  if (p10 <= 54) {
    px10 = 1;
  } else if (p10 <= 154) {
    px10 = 2;
  } else if (p10 <= 254) {
    px10 = 3;
  } else if (p10 <= 354) {
    px10 = 4;
  } else if (p10 <= 424) {
    px10 = 5;
  } else if (p10 <= 604) {
    px10 = 6;
  } else {
    px10 = 7;
  }

  if (px25 >= px10) {
    if (px25 == 1) {
      display.print(F("AQI : YAXSI"));
    } else if (px25 == 2) {
      display.print(F("AQI : NORMAL"));
    } else if (px25 == 3) {
      display.print(F("AQI : QENAET BEXS"));
    } else if (px25 == 4) {
      display.print(F("AQI : ASAGI"));
    } else if (px25 == 5) {
      display.print(F("AQI : COX ASAGI"));
    } else if (px25 == 6) {
      display.print(F("AQI : TEHLUKELI"));
    }
  }  else if (px10 > px25) {
    if (px10 == 2) {
      display.print(F("AQI : NORMAL"));
    } else if (px10 == 3) {
      display.print(F("AQI : QENAET BEXS"));
    } else if (px10 == 4) {
      display.print(F("AQI : ASAGI"));
    } else if (px10 == 5) {
      display.print(F("AQI : COX ASAGI"));
    } else if (px10 == 6) {
      display.print(F("AQI : TEHLUKELI"));
    }
  }

  display.display();
  delay(3000);
}

// DT11 sensorundan temp ve rutubet deyerlerinin oxunmasi ve ekranda print edilmesi
void tempverut(void) {
  int chk = DHT.read11(DHT11_PIN);
  dt = DHT.temperature;
  dh = DHT.humidity;
  display.clearDisplay();
  display.fillRect(0, 0, 95, 11, SSD1306_WHITE);
  display.setTextSize(1); 
  display.setTextColor(SSD1306_BLACK); 
  display.setCursor(3, 2);           // Yaziya 3 piksel sagdan ve 2 piksel soldan baslanilmasi
  display.print(F("TEMP VE RUTUBET\n"));
  display.setTextColor(SSD1306_WHITE);
  display.print(F("----------------\n"));
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(F("TEMP (C) : "));
  display.setTextSize(2);           
  display.setTextColor(SSD1306_WHITE);
  display.print(F(" "));
  display.print(dt);
  display.print(F("\n"));
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(F("RUTB (%) : "));
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.print(F(" "));
  display.print(dh);
  display.print(F("\n"));
  display.setTextSize(1);
  display.print(F("-> NORMAL")); 
  display.display();
  delay(3000);
  //display.ssd1306_command(SSD1306_DISPLAYOFF);
  //delay(3000);
  //display.ssd1306_command(SSD1306_DISPLAYON);
}
