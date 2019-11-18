








  //     int led = D0; //D14

const int greenled =  6;      // the number of the LED pin  PA20_TCC0-W6
const int yellowled =  7;      // the number of the LED pin  PA21_TCC0-W7

byte Task=0;
unsigned int CRC_Error = 0;
bool EnableLoop = 0;

bool LoopProcess1 = 0;
bool LoopProcess2 = 0;
bool LoopProcess3 = 0;

byte Temp;
byte ReqArray[6] =  {'5','5','5','5','5','5'};
byte ReceiveArray[64];
byte ReceiveCounter = 0;
byte ArraySize =0;
unsigned short CRC_Calculate = 0;
unsigned short CRC_Received = 0;
//byte Indexer = 0;

/*
char ssid[] = "Yagci"; //  your network SSID (name)
char pass[] = "berkmert";    // your network password (use for WPA, or use as key for WEP)
*/
///*
char ssid[] = "OpenAir_24G"; //  your network SSID (name)
char pass[] = "CloseAir";    // your network password (use for WPA, or use as key for WEP)
//*/
long rssi;
int status = WL_IDLE_STATUS;
byte ControlM2XCounter= 0;


unsigned int counter = 0;
unsigned int IntCounter = 0;
uint32_t sampleRate = 1000; //sample rate of the sine wave in Hertz, how many times per second the TC5_Handler() function gets called per second basically

//#define LED_PIN 13 //just for an example
bool state = 0; //just for an example


void tcStartCounter(void);
void tcConfigure(int);


void TimerSetup(void){
	  // put your setup code here, to run once:
	//  pinMode(LED_PIN,OUTPUT); //this configures the LED pin, you can remove this it's just example code
	  tcConfigure(sampleRate); //configure the timer to run at <sampleRate>Hertz
      tcStartCounter(); //starts the timer
}

/*
 *  TIMER SPECIFIC FUNCTIONS FOLLOW
 *  you shouldn't change these unless you know what you're doing
 */



//Function that is used to check if TC5 is done syncing
//returns true when it is done syncing
bool tcIsSyncing()
{
  return TC5->COUNT16.STATUS.reg & TC_STATUS_SYNCBUSY;
}

//This function enables TC5 and waits for it to be ready
void tcStartCounter()
{
  TC5->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE; //set the CTRLA register
  while (tcIsSyncing()); //wait until snyc'd
}

//Reset TC5
void tcReset()
{
  TC5->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  while (tcIsSyncing());
  while (TC5->COUNT16.CTRLA.bit.SWRST);
}

//disable TC5
void tcDisable()
{
  TC5->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (tcIsSyncing());
}

//Configures the TC to generate output events at the sample frequency.
//Configures the TC in Frequency Generation mode, with an event output once
//each time the audio sample frequency period expires.
 void tcConfigure(int sampleRate)
{
 // Enable GCLK for TCC2 and TC5 (timer counter input clock)
 GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5)) ;
 while (GCLK->STATUS.bit.SYNCBUSY);

 tcReset(); //reset TC5

 // Set Timer counter Mode to 16 bits
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
 // Set TC5 mode as match frequency
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
 //set prescaler and enable TC5
 TC5->COUNT16.CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_ENABLE;
 //set TC5 timer counter based off of the system clock and the user defined sample rate or waveform
 TC5->COUNT16.CC[0].reg = (uint16_t) (SystemCoreClock / sampleRate - 1);
 while (tcIsSyncing());

 // Configure interrupt request
 NVIC_DisableIRQ(TC5_IRQn);
 NVIC_ClearPendingIRQ(TC5_IRQn);
 NVIC_SetPriority(TC5_IRQn, 0);
 NVIC_EnableIRQ(TC5_IRQn);

 // Enable the TC5 interrupt request
 TC5->COUNT16.INTENSET.bit.MC0 = 1;
 while (tcIsSyncing()); //wait until TC5 is done syncing
}







/*
const char *streamNames[] = { "temperature", "humidity" };
int counts[] = { 2, 1 };
const char *ats[] = { "2013-09-09T19:15:00Z",
                      "2013-09-09T19:15:10Z",
                      "2013-09-09T19:15:20Z"};
double values[] = { 10.0, 20.0, 7.5 };
*/

/*
void (*stream_value_read_callback)(const char* at,
                                           m2x_value value,
                                           int index,
                                           void* context,
                                           int type)


//void (*stream_value_read_callback)(const char* at, const char* value, int index, void* context, int type)

{
  Serial.print("Found a data point, index:");
  Serial.println(index);
  Serial.print("Type:");
  Serial.println(type);
  Serial.print("At:");
  Serial.println(at);
  Serial.print("Value:");
  //Serial.println(value.value_string);
    Serial.println(value);
}
*/


void PrintValues(){
     for (int i= 0; i<64; i++){
        Serial.print(ReceiveArray[i]);Serial.print('.');
     }


    Serial.println();
    Serial.print("Temperature ");Serial.println(Values.Temperature);
    Serial.print("Humidity ");Serial.println(Values.Humidity);
    Serial.print("CO2 ");Serial.println(Values.CO2);
    Serial.print("eCO2 ");Serial.println(Values.eCO2);
    Serial.print("VOC ");Serial.println(Values.VOC);
    Serial.print("PM25 ");Serial.println(Values.PM25);
    Serial.print("Formaldehyd ");Serial.println(Values.Formaldehyd);

    Serial.print("Ammonia ");Serial.println(Values.Ammonia);
    Serial.print("Hyidrogen ");Serial.println(Values.Hyidrogen);
    Serial.print("Ethanol ");Serial.println(Values.Ethanol);
    Serial.print("CarbonMonoxide ");Serial.println(Values.CarbonMonoxide);
    Serial.print("Propane ");Serial.println(Values.Propane);
    Serial.print("IsoButane ");Serial.println(Values.IsoButane);
    Serial.print("Methane ");Serial.println(Values.Methane);
    Serial.print("NitrogenDioxide ");Serial.println(Values.NitrogenDioxide);

  //    Serial.println(" ");
 /*
      float Buff = FloatSerialConvert(&ReceiveArray[0]);
      Serial.print(Buff);

      Serial.println(" ");
*/

}

void GetValues(byte Indexer){
    //byte Indexer = 5;
    Values.Ammonia = ReceiveArray[Indexer];
    Values.Hyidrogen= ReceiveArray[++Indexer];
    Values.Ethanol= ReceiveArray[++Indexer];
    Values.Humidity= ReceiveArray[++Indexer];
    Values.PM25= ReceiveArray[++Indexer];

   // short *SlTemp;

 //   SlTemp = (short*) &ReceiveArray[5];
 //   Values.CarbonMonoxide = *SlTemp;

    Values.CarbonMonoxide = ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.Propane  =       ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.IsoButane  =     ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.Methane   =     ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.CO2    =        ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.eCO2  =         ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;
    Values.VOC   =         ReceiveArray[++Indexer] + ReceiveArray[++Indexer]*256 ;


/*
     byte *p;
     p = (byte*)&Values;
      for (int j=0; j<sizeof(Values); j++){
        *p = ReceiveArray[j];
   //     Serial.print(*p);Serial.print('.');
        p++;
      }
      */
    float *FlTemp;
    FlTemp = (float*) &ReceiveArray[++Indexer];
    Values.Formaldehyd = *FlTemp;

    FlTemp = (float*) &ReceiveArray[Indexer += 4];
    Values.NitrogenDioxide = *FlTemp;

    FlTemp = (float*) &ReceiveArray[Indexer += 4];
    Values.Temperature = *FlTemp;
     //Serial2.write((byte*)&Values, sizeof(Values));



}

	String	String_Temperature = String(Values.Temperature); // float
	String	String_Humidity    = String(Values.Humidity);
	String	String_Pressure    = "1001";
	String	String_PM25		   = String(Values.PM25);
	String	String_TVOC		   = String(Values.VOC);
	String	String_CO2e		   = String(Values.eCO2);
	String	String_Ammonia		= String(Values.Ammonia);
	String	String_Hydrogen	=    String(Values.Hyidrogen);
	String	String_Ethanol		= String(Values.Ethanol);
	String	String_CO2			= String(Values.CO2);
	String	String_Methane		= String(Values.Methane);
	String	String_IsoButane	= String(Values.IsoButane);
	String	String_Propane		= String(Values.Propane);
	String	String_CarbonMonoxide	= String(Values.CarbonMonoxide);
	String	String_Formaldehyd	= String(Values.Formaldehyd);
	String	String_NitrogenDioxide	= String(Values.NitrogenDioxide);
	String WifiSignal ="-45";
	String WifiSSID ="";
	String String_ID = "5699";
  //  String String_Control	="";

void UpdateM2XStream(void ){

	     			String_Temperature = String(Values.Temperature); // float
		 			String_Humidity    = String(Values.Humidity);
		 			String_Pressure    = "1001";
		 			String_PM25		   = String(Values.PM25);
		 			String_TVOC		   = String(Values.VOC);
		 			String_CO2e		   = String(Values.eCO2);
		 			String_Ammonia		= String(Values.Ammonia);
		 			String_Hydrogen	=    String(Values.Hyidrogen);
		 			String_Ethanol		= String(Values.Ethanol);
		 			String_CO2			= String(Values.CO2);
		 			String_Methane		= String(Values.Methane);
		 			String_IsoButane	= String(Values.IsoButane);
		 			String_Propane		= String(Values.Propane);
		 String_CarbonMonoxide	= String(Values.CarbonMonoxide);
		String_Formaldehyd	= String(Values.Formaldehyd);
		String_NitrogenDioxide	= String(Values.NitrogenDioxide);


}


  /*
     byte *p;
     p = (byte*)&Values;
      for (int j=0; j<sizeof(Values); j++){
        *p = ReceiveArray[j];
        p++;
      }
*/




/*
 *
 *
     uint16_t crc=0; // starting value as you like, must be the same before each calculation
  for (int i=0;i<strlen(ReceiveArray);i++) // for each character in the string
  {
    crc= _crc16_update (crc, str[i]); // update the crc value
  }
*/









void M2X_SendStream(void){

   const char *streamNames[] = {
                   "Temperature",
                   "Humidity",
                   "Pressure",
                   "PM25",
                   "VOC",
                   "eCO2",
                   "Ammonia",
                   "Hydrogen",
                   "Ethanol",
                   "CO2",
                   "Methane",
                   "IsoButane",
                   "Propane",
                   "CarbonMonoxide",
                   "Formaldehyd",
                   "NitrogenDioxide",
                   "WIFI",
                   "ID",
                   "WIFI_SSID",
                   "Control"

                };
  String M2Xvalues[] = {
		String_Temperature,
		String_Humidity,
		String_Pressure,
		String_PM25,
		String_TVOC,
		String_CO2e,
		String_Ammonia,
		String_Hydrogen,
		String_Ethanol,
		String_CO2,
		String_Methane,
		String_IsoButane,
		String_Propane,
		String_CarbonMonoxide,
		String_Formaldehyd,
		String_NitrogenDioxide,
            WifiSignal,
            String_ID,
            WifiSSID,
            String(ControlM2XCounter)
            //Device[USERID]
            };
    Serial.println("M2x starting expexted 202: ");
    int response = m2xClient.postDeviceUpdate(deviceId, 20, streamNames, M2Xvalues, NULL);

//	response = -1;

  Serial.print("M2x client response code: ");
  Serial.println(response);

//  if (response == -1) while(1) ; // rarely stucks here
}






/*



String String_Temperature ="23";
String String_Humidity    ="24";
String String_Pressure    = "1001";
String String_Light = "333";
String String_PM25 = "12";
String String_TVOC = "345";
String String_Noise  = "29";
String WifiSignal ="12";
String String_ID = "4006";

void M2X_SendStream(void){
   const char *streamNames[] = {
                    "VOC",
                   "Pressure",
                   "PM25",
                   "Temperature",
                   "Humidity",
                   "Light",
                   "Noise",
                   "WIFI",
                   "ID"
                };
  String M2Xvalues[] = {
            String_TVOC,
            String_Pressure,
            String_PM25,
            String_Temperature,
            String_Humidity,
            String_Light,
            String_Noise,
            WifiSignal,
            String_ID
            //Device[USERID]
            };
    Serial.println("M2x starting expexted 202: ");
    int response = m2xClient.postDeviceUpdate(deviceId, 9, streamNames, M2Xvalues, NULL);



  Serial.print("M2x client response code: ");
  Serial.println(response);

  if (response == -1) while(1) ;
}



*/

void M2X_ReceiveStream(void){
    Serial.println("M2x starting expexted 200: ");
    char strName2[] = "Pressure"; // Stream you want to receive values
    int response2 = m2xClient.listStreamValues(deviceId, strName2, on_data_point_found, NULL);
    Serial.print("M2x client response code: ");
    Serial.println(response2);
    if (response2 == -1) while(1) ;
  }

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.print(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("   IP Address:");
  Serial.print(ip);

  // print the received signal strength:
  rssi = WiFi.RSSI();
  Serial.print("    RSSI:");
  Serial.print(rssi);
  Serial.println(" dBm");

	WifiSignal =   String(rssi);
    WifiSSID = String(WiFi.SSID());
}

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

