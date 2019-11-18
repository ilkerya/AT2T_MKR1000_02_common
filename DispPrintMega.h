




//DISPLAY CONSTANTS
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    13
#define OLED_RESET 12



#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

/*
 * In Adafruit_SSD1306.h
 * 1. uncomment #define SSD1306_128_64
2. comment #define SSD1306_128_32
3. comment #define SSD1306_96_16
In the example ssd1306_128x64_i2c
4. add #define SSD1306_LCDHEIGHT 64
 *
 */

#define SSD1306_LCDHEIGHT 64

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//Adafruit_SSD1306 display(OLED_RESET);
//DISPLAY INITIALIZER
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void displayValues(void)
{
  display.clearDisplay();

  display.setTextSize(1);

        display.setCursor(0, 1);
    //display.print("->");

      display.print("Meth:");display.print((unsigned int)Values.Methane); //5/5
     //   display.setCursor(0, 12);
        display.print(" CO:");display.println((unsigned int)Values.CarbonMonoxide);

   //       display.setCursor(1, 1);
      display.print("Prop:");display.print((unsigned int)Values.Propane);
    //  display.setCursor(1, 12);
        display.print(" NO2:");display.println(Values.NitrogenDioxide);

      display.print("IsBt:");display.print((unsigned int)Values.IsoButane);
        display.print(" Ethn:");display.println((unsigned int)Values.Ethanol);

      display.print("Hyd:");display.print((unsigned int)Values.Hyidrogen);
        display.print(" Ammn:");display.println((unsigned int)Values.Ammonia);

      display.print("FormAld:");display.print(Values.Formaldehyd);
      display.print(" CO2:");display.println(Values.CO2);

      display.print("VOC:");display.print((unsigned int)Values.VOC);
        display.print(" eCO2:");display.println((unsigned int)Values.eCO2);

      //display.print("Temp:");
      display.print(Values.Temperature);
      display.print("C   ");
      //display.print("C  Hum:");
      display.print(Values.Humidity);display.println("% ");

      display.print("Tmr:");display.print(Timeout);
   //   display.print("  I:");display.print(IntTimer);




/*
    display.print("PM 2.5: "); display.print("DD"); display.println(" ug/m3");
    display.print("PM 10: "); display.print("DD"); display.println(" ug/m3");
    display.print("CO2: "); display.print("DD"); display.println(" ppm");
    display.print("TVOC: "); display.print("DD"); display.println(" ppb");
    display.print("HCHO: "); display.print("DD"); display.println(" ppm");
*/
  /*
  display.print("Device Id: "); display.println(deviceId);

  if((taskCounter == 61 || (taskCounter >= 0 && taskCounter <= 29)) && !responseRecived)
  display.println("Sending sample...");

  else if(responseRecived && dataPosted && taskCounter <= 35 && startUpFlag)
  display.println("Sample received!");

  else if(startUpFlag && ((!responseRecived && taskCounter <= 32) || (responseRecived && !dataPosted)))
  display.println("Delivery failed!");

  else
  {
    display.print("Next sample in: "); display.print(61 - taskCounter - 1); display.println(" s");
  }
  */
  display.display();
}


void DisplayInit(void){
	  //-- DISPLAY INIT --//

	  display.begin(SSD1306_SWITCHCAPVCC);
	  display.clearDisplay();

	  display.setTextSize(3);
	  display.setTextColor(WHITE);
	  display.setCursor(0, 0);
	  display.println();
	  display.println("OpenAir");
  		display.display();


}

