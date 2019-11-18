


#define ON 1
#define OFF 0

/*
struct
{
  byte Ammonia;
  byte  Hyidrogen;
  byte  Ethanol;
  byte  Humidity;
  byte  PM25;    //5
  unsigned int  CarbonMonoxide;
  unsigned int  Propane;
  unsigned int  IsoButane;
  unsigned int Methane;
  unsigned int CO2;
  unsigned int  eCO2;
  unsigned int  VOC; //14
  float Formaldehyd;
  float  NitrogenDioxide;
  float Temperature; //12   //31
}Values;
*/



struct
{
  byte Ammonia;
  byte  Hyidrogen;
  byte  Ethanol;
  byte  Humidity;
  byte  PM25;    //
  unsigned short  CarbonMonoxide;
  unsigned short  Propane;
  unsigned short  IsoButane;
  unsigned short Methane;
  unsigned short CO2;
  unsigned short  eCO2;
  unsigned short  VOC; //17
  float Formaldehyd;//19
  float  NitrogenDioxide;//23
  float Temperature; // 27
}Values;


//Check routine taken from
//http://web.mit.edu/6.115/www/miscfiles/amulet/amulet-help/xmodem.htm
int calcrc(char *ptr, int count)
{
    int  crc;
    char i;
    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}

