


MICS_VZ_89TE VOCSensor;
Weather Si072_Sensor;

 byte SendArray[64];
 byte ReceiveArray[6];
 byte ReceiveCounter = 0;
 bool EnableDataSend = 0;


struct
{
  bool Task1;
  bool Task2;
  bool Task3;
  bool Task4;
  bool Task5;
  bool Task6;
  bool Task7;
  bool Task8;
  bool Task9;
}Loop;

char StrAmm[]         = "Ammonia(NH3): ";
char StrCO[]          = "Carbon Mon(CO): ";
char StrNO2[]         = "Nit.Dioxide(NO2): ";
char StrPropane[]     = "Propane(C3H8): ";
char StrIsoButane[]   = "IsoButane(C4H10): ";
char StrMethane[]     = "Methane(CH4): ";
char StrHydrogane[]   = "Hydrogen(H2): ";
char StrEthanol[]     = "Ethanol(C2H5OH): ";
char StrCO2[]         = "CarbonDioxide(CO2): ";
char StrFormaldehy[]  = "Formald.(HCHO): ";

#define MAX_AMMONIA 200
#define MIN_AMMONIA 1

#define MAX_CO 1000
#define MIN_CO 1

#define MAX_NO2 10
#define MIN_NO2 0.05

#define MAX_PROPANE 15000
#define MIN_PROPANE 3000

#define MAX_ISOBUTANE 15000
#define MIN_ISOBUTANE 3000

#define MAX_METHANE 15000
#define MIN_METHANE 3000

#define MAX_HYDROGEN 250
#define MIN_HYDROGEN 1

#define MAX_ETHANOL 250
#define MIN_ETHANOL 10

#define MAX_FORMALDEHYDE 5
#define MIN_FORMALDEHYDE 0

#define MAX_CO2 3000
#define MIN_CO2 200

byte readCO2_S8SenseAir[] = {0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25};  //Command packet to read Co2 (see app note)
byte response_S8SenseAir[] = {0,0,0,0,0,0,0};  //create an array to store the response


void sendRequest(byte packet[]) {
      Serial1.begin(9600);
      delay(10);
    while(!Serial1.available())  //keep sending request until we start to get a response
    {
      Serial1.write(readCO2_S8SenseAir,7);
      delay(50);
  }
    int timeout=0;  //set a timeoute counter
    while(Serial1.available() < 7 ) //Wait to get a 7 byte response
    {
      timeout++;
      if(timeout > 10)    //if it takes to long there was probably an error
        {
          while(Serial1.available())  //flush whatever we have
            Serial1.read();

            break;                        //exit and try again
        }
        delay(50);
    }

    for (int i=0; i < 7; i++)
    {
      response_S8SenseAir[i] = Serial1.read();
    }
}
/*
unsigned int getValue_S8SenseAir(byte packet[])
{

   unsigned int val = packet[3]*256 + packet[4];                //Combine high byte and low byte with this formula to get value
  return val;

}
*/
unsigned int readCO2SenseAir(void) {
  sendRequest(readCO2_S8SenseAir);
 // Values.CO2 = getValue_S8SenseAir(response_S8SenseAir);

  return (response_S8SenseAir[3]*256 + response_S8SenseAir[4]);                //Combine high byte and low byte with this formula to get value

}
float analogReadPPM()
{
   float analogVoltage = analogRead(SensorAnalogPin) / 1024.0 * VREF;
   float ppm = 3.125 * analogVoltage - 1.25;  //linear relationship(0.4V for 0 ppm and 2V for 5ppm)
   if(ppm<0)  ppm=0;
   else if(ppm>5)  ppm = 5;
   return ppm;
}

void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
    //dafruit Industries
    //  https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexerbreakout
    Wire.write(1 << i);
    Wire.endTransmission();
    delay(20);
}

void GasSensorMeasure(){
      tcaselect(CHANNEL_GAS);
      gas.begin(0x04);//the default I2C address of the slave is 0x04

  Values.Ammonia =  gas.measure_NH3();
  if( Values.Ammonia > MAX_AMMONIA ) Values.Ammonia = MAX_AMMONIA;
  if( Values.Ammonia < MIN_AMMONIA ) Values.Ammonia = MIN_AMMONIA;

  Values.CarbonMonoxide = gas.measure_CO();
  if( Values.CarbonMonoxide > MAX_CO ) Values.CarbonMonoxide = MAX_CO;
  if( Values.CarbonMonoxide < MIN_CO ) Values.CarbonMonoxide = MIN_CO;

  Values.NitrogenDioxide = gas.measure_NO2();
    if( Values.NitrogenDioxide > MAX_NO2 ) Values.NitrogenDioxide = MAX_NO2;
    if( Values.NitrogenDioxide < MIN_NO2 ) Values.NitrogenDioxide = MIN_NO2;

  Values.Propane = gas.measure_C3H8();
    if( Values.Propane > MAX_PROPANE ) Values.Propane = MAX_PROPANE;
    if( Values.Propane < MIN_PROPANE ) Values.Propane = MIN_PROPANE;

  Values.IsoButane = gas.measure_C4H10();
    if( Values.IsoButane > MAX_ISOBUTANE ) Values.IsoButane = MAX_ISOBUTANE;
    if( Values.IsoButane < MIN_ISOBUTANE ) Values.IsoButane = MIN_ISOBUTANE;

 // delay(100);

  Values.Methane = gas.measure_CH4();
     if( Values.Methane > MAX_METHANE ) Values.Methane = MAX_METHANE;
    if( Values.Methane < MIN_METHANE ) Values.Methane = MIN_METHANE;

  Values.Hyidrogen = gas.measure_H2();
     if( Values.Hyidrogen > MAX_HYDROGEN ) Values.Hyidrogen = MAX_HYDROGEN;
    if( Values.Hyidrogen < MIN_HYDROGEN ) Values.Hyidrogen = MIN_HYDROGEN;

  Values.Ethanol = gas.measure_C2H5OH();
       if( Values.Ethanol > MAX_ETHANOL ) Values.Ethanol = MAX_ETHANOL;
    if( Values.Ethanol < MIN_ETHANOL ) Values.Ethanol = MIN_ETHANOL;

  Values.Formaldehyd = analogReadPPM();
    if( Values.Formaldehyd > MAX_FORMALDEHYDE ) Values.Formaldehyd = MAX_FORMALDEHYDE;
    if( Values.Formaldehyd < MIN_FORMALDEHYDE ) Values.Formaldehyd = MIN_FORMALDEHYDE;

  Values.CO2 = readCO2SenseAir();
    if( Values.CO2 > MAX_CO2 ) Values.CO2 = MAX_CO2;
    if( Values.CO2 < MIN_CO2 ) Values.CO2 = MIN_CO2;
}
void PrintVal(float Val, char *p, unsigned int Max, unsigned int Min){
  long percent;
  Serial.print(p);
   if(Val > 0){
      Serial.print(Val);
      Serial.print(" ppm");

      if(Val < Min ) Val = Min;
      if(Val > Max ) Val = Max;
      percent = (long)(Val - Min) * 100;
      percent /= (Max - Min);
    //  Serial.print(Val);
    //  Serial.print(" ppm");

      Serial.print("  // Range: ");
      Serial.print(Min);
      Serial.print("-");
      Serial.print(Max);
      Serial.print(" ppm");
      Serial.print("   %");
      Serial.print(percent);
      Serial.println();
    }
    else Serial.println("invalid");
}

 void GasSensorPrint(){
      PrintVal(Values.Ammonia,&StrAmm[0], MAX_AMMONIA, MIN_AMMONIA);
      PrintVal(Values.CarbonMonoxide,&StrCO[0], MAX_CO, MIN_CO);
      PrintVal(Values.NitrogenDioxide,&StrNO2[0],MAX_NO2 ,MIN_NO2 );
      PrintVal(Values.Propane,&StrPropane[0],MAX_PROPANE ,MIN_PROPANE );
      PrintVal(Values.IsoButane,&StrIsoButane[0],MAX_ISOBUTANE ,MIN_ISOBUTANE );
      PrintVal(Values.Methane,&StrMethane[0], MAX_METHANE, MIN_METHANE);
      PrintVal(Values.Hyidrogen,&StrHydrogane[0], MAX_HYDROGEN, MIN_HYDROGEN);
      PrintVal(Values.Ethanol, &StrEthanol[0],MAX_ETHANOL, MIN_ETHANOL);
      PrintVal(Values.Formaldehyd, &StrFormaldehy[0],MAX_FORMALDEHYDE, MIN_FORMALDEHYDE);
      PrintVal(Values.CO2, &StrCO2[0],MAX_CO2, MIN_CO2);
}

void TempSensorMeasure(){
    tcaselect(CHANNEL_TEMP);
     Values.Humidity = (unsigned int)Si072_Sensor.getRH();
      delay(10);
     Values.Temperature = Si072_Sensor.readTemp();
    if (Values.Temperature < -35){
      //Serial.println("Error");
      delay(100);
      Si072_Sensor.begin();
    }
}


void TempSensorPrint(){
    Serial.print("Temp:");
    Serial.print(Values.Temperature);
    Serial.print("C  ");

    Serial.print("Humidity:");
    Serial.print(Values.Humidity);
    Serial.println("%");

    if (Values.Temperature < -35){
      Serial.println("Error");
      //delay(100);
      //Si072_Sensor.begin();
      //delay(100);
    }
}
float StatusVOC;
void VOCSensorMeasure(){
      tcaselect(CHANNEL_VOC);
      VOCSensor.begin();
      VOCSensor.getVersion();
      VOCSensor.readSensor();
      Values.eCO2 = VOCSensor.getCO2();
      Values.VOC = VOCSensor.getVOC();
      StatusVOC = VOCSensor.getStatus();
}

void VOCSensorPrint(){
      Serial.print("VOC:");
      Serial.print(Values.VOC);
      Serial.print("    eCO2:");
      Serial.println(Values.eCO2);
      Serial.print("Status:");
     // float Status = VOCSensor.getStatus();
      Serial.println(StatusVOC);

      if(Preheat == false)Serial.println("Not Calibrated!");
      if(Preheat == true)Serial.println("Calibrated!");

     Serial.print("PreHeatTimer: ");
     Serial.print((PreheatTimer*25)/10);
     Serial.print("Sec      RawTimer:");
     Serial.println(PreheatTimer);
     Serial.print("Timer:");Serial.print(Timeout);

}



void ShowRawDAta(){
    float R0_NH3, R0_CO, R0_NO2;
    float Rs_NH3, Rs_CO, Rs_NO2;
    float ratio_NH3, ratio_CO, ratio_NO2;

    R0_NH3 = gas.getR0(0);
    R0_CO  = gas.getR0(1);
    R0_NO2 = gas.getR0(2);

    Rs_NH3 = gas.getRs(0);
    Rs_CO  = gas.getRs(1);
    Rs_NO2 = gas.getRs(2);

    ratio_NH3 = Rs_NH3/R0_NH3;
    ratio_CO  = Rs_CO/R0_CO;
    ratio_NO2 = Rs_NH3/R0_NO2;

    Serial.println("R0:");
    Serial.print(R0_NH3);
    Serial.print('\t');
    Serial.print(R0_CO);
    Serial.print('\t');
    Serial.println(R0_NO2);

    Serial.println("Rs:");
    Serial.print(Rs_NH3);
    Serial.print('\t');
    Serial.print(Rs_CO);
    Serial.print('\t');
    Serial.println(Rs_NO2);

    Serial.println("ratio:");
    Serial.print(ratio_NH3);
    Serial.print('\t');
    Serial.print(ratio_CO);
    Serial.print('\t');
    Serial.println(ratio_NO2);
}


