#include <SoftwareSerial.h>
#include <SoftReset.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <SPI.h>
#include <SD.h>


int count = 0;
char header[5] ;
char latitude[10];
char longitude[10];
char velocity[10];
char Time[10];
char altitude[10];

String pressure="";
String bmp_altitude="";
String temp=""; 

int comma_count = 0;
int ccount = 0;
const int chipSelect = 53;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


void get_latitude(){
  
  if(comma_count == 2){
    ccount = 0;
    while(comma_count <3){
      if(Serial1.available()){
        char c2 = Serial1.read();
        if(c2 == ',') comma_count = comma_count + 1;
        else{
          latitude[ccount] = c2;
          ccount = ccount + 1 ;
         // slatitude = slatitude + String(c2); 
        }
      }
    }
    
   /*
      for(int i=0;i<10;i++){
    Serial.print(latitude[i]);
   
      }
    
    */
     
  }


}

void get_longitude(){
 
  
  if(comma_count == 4){
    ccount = 0;
    while(comma_count <5){
      if(Serial1.available()){
        char c2 = Serial1.read();
        if(c2 == ',') comma_count = comma_count + 1;
        else{
          longitude[ccount] = c2;
          ccount = ccount + 1 ;
         
        }
      }
    }
    
   /*
    Serial.print(" longitude func ");
    for(int i=0;i<10;i++){
      
      Serial.print(longitude[i]);
      
     }
     Serial.print("    ");
   */

  }

}

void get_altitude(){
  //saltitude = "";
  
  if(comma_count == 9){
    ccount = 0;
    while(comma_count <10){
      if(Serial1.available()){
        char c2 = Serial1.read();
        if(c2 == ',') comma_count = comma_count + 1;
        else{
          altitude[ccount] = c2;
          ccount = ccount + 1 ;
          //saltitude = saltitude + String(c2);
        }
      }
    }
   // Serial.print ("altitude  :");
   /*
   Serial.print(" altitude ");
    for(int i=0;i<10;i++){
        Serial.print(altitude[i]);
         }
        Serial.print("     ");
        */

 

    
  }

}


void get_velocity(){
  //svelocity = "";
  
  if(comma_count == 7){
    ccount = 0;
    while(comma_count <8){
      if(Serial1.available()){
        char c2 = Serial1.read();
        if(c2 == ',') comma_count = comma_count + 1;
        else{
          velocity[ccount] = c2;
          ccount = ccount + 1 ;
          //svelocity = svelocity + String(c2);
          
        }
      }
    }
    //Serial.print ("velocity  :");
    /*
    Serial.print(" velocity ");
    for(int i=0;i<10;i++){
        
        Serial.print(velocity[i]);
         }
         Serial.print("    ");
         */
 /*
      if (dataFile){
        dataFile.print(svelocity);
        dataFile.print(",");
        dataFile.close();
        
      }
*/
         
     get_bmpdata(); 
     
     
    
      
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      String slatitude= "";//String(latitude);
      
      String slongitude= "";// String(longitude);
      String saltitude="";// String(altitude);
      String svelocity="";//String(velocity);
      String stime= "";// String(Time);


      if (dataFile) {
        //slatitude = String(latitude[0]) + String(latitude[2]) + String(latitude[3]) + String(latitude[4]) + String(latitude[5]) ;

        for(int i =0;i<10;i++)
        {
          slatitude = slatitude + String(latitude[i]);
        }        
        dataFile.print(slatitude);
        dataFile.print(",");
        
        Serial.print("latitude  ");
        Serial.print(slatitude);
        
        Serial.print(" , ");              

        for(int i =0;i<10;i++)
        {
          slongitude = slongitude + String(longitude[i]);
        }

        dataFile.print(slongitude);
        dataFile.print(",");
        Serial.print("longitude  ");
        Serial.print(slongitude);
        //Serial.print(" ");
        //Serial.print(longitude);
        Serial.print(",  ");        

        for(int i =0;i<10;i++)
        {
          saltitude = saltitude + String(altitude[i]);
        }

        dataFile.print(saltitude);
        dataFile.print(",");
        Serial.print("altitude  ");
        Serial.print(saltitude);
        Serial.print(",  ");        

        for(int i =0;i<10;i++)
        {
          svelocity = svelocity + String(velocity[i]);
        }
  
        dataFile.print(svelocity);
        dataFile.print(",");
        Serial.print("velocity  ");
        Serial.print(svelocity);
        Serial.print(",  ");        

        for(int i =0;i<10;i++)
        {
          stime = stime + String(Time[i]);
        }

        dataFile.print(stime);
        dataFile.print(",");
        Serial.print("time  ");
        Serial.print(stime);
        Serial.print(",  ");        

        dataFile.print(pressure);
        dataFile.print(",");
        Serial.print("pressure  ");
        Serial.print(pressure);
        Serial.print(",  ");        

        dataFile.print(temp);
        dataFile.print(",");
        Serial.print("temp  ");
        Serial.print(temp);
        Serial.print(",  ");        

        dataFile.print(bmp_altitude);
        Serial.print("altitude  ");
        Serial.print(bmp_altitude);
        Serial.println(",  ");        
        dataFile.println(",");
        dataFile.close();
      
     }
        
    
  }
  

}

void get_time(){
  //stime = "";
  
  if(comma_count == 1){
    ccount = 0;
    while(comma_count <2){
      if(Serial1.available()){
        char c2 = Serial1.read();
        if(c2 == ',') comma_count = comma_count + 1;
        else{
          Time[ccount] = c2;
          ccount = ccount + 1 ;
         // stime =  stime + String(c2);
          
        }
      }
    }
   // Serial.print ("time  :");
   /*
    Serial.print(" time ");
    for(int i=0;i<10;i++){
        
        Serial.print(Time[i]);
        
         }
         Serial.print("   ");
    */     
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  }

}

void get_bmpdata(){
     
      //Bmp data :
      
      sensors_event_t event;
      bmp.getEvent(&event);
      if (event.pressure){
      //   Serial.print(" pressure ");
      //   Serial.print(event.pressure);
         pressure = event.pressure;
         //dataFile.println(String(event.pressure));
         //dataFile.println(",");
         float temperature;
         bmp.getTemperature(&temperature);
      //   Serial.print(" temperature ");
      //   Serial.print(temperature);
         temp = String(temperature);
         //dataFile.println(String(temperature));
         //dataFile.println(",");
         float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
      //   Serial.print(" altitude ");
      //   Serial.println(bmp.pressureToAltitude(seaLevelPressure,
//                                        event.pressure)); 
         bmp_altitude = String(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure));                                       
         //dataFile.println(String(bmp.pressureToAltitude(seaLevelPressure,
//                                       event.pressure)));
         //dataFile.println(","); 
         //dataFile.close();                             

      }  
}


void setup() {
 Serial1.begin(9600);
 Serial.begin(9600);
 
  if(!bmp.begin())
 {
   
   Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
   while(1);
 }

   if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  

 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    

    char c = Serial1.read();
    

    if(c=='$'){
      
      while(count <5){
        
        if(Serial1.available()>0){
          char c1 = Serial1.read();
          
          header[count] = c1;
          count = count + 1;

        }
      }
     /*
      for(int i=0;i<5;i++){
      Serial.print(header[i]);
      }
      Serial.print("    ");
    */
    
      count = 0;
      
      if (header[2] == 'G' && header[3]=='G' && header[4]=='A') {

        comma_count = 0;
     
        while(comma_count<9)   //number of iterations have been reduced to the max number of commas needed
        {
          if(Serial1.available())
          {
            char c2 = Serial1.read();
            if(c2 == ',') comma_count = comma_count + 1;
          
              get_latitude();
              get_longitude();
              get_altitude();

              delay(5);

              
          }
        }
        
       
      }                               //GGA check. 

      
      if (header[2] == 'R' && header[3]=='M' && header[4]=='C') {
       
      //Serial.print(" RMC detected ");
        comma_count = 0;

        while(comma_count<7)        //number of iterations have been reduced to the max number of commas needed 
        {
          if(Serial1.available())
          {
            char c2 = Serial1.read();
            if(c2 == ',') comma_count = comma_count + 1;
          
              get_time();
              get_velocity();
                                      

              
          }
        }
      }                               //RMC check. 


      
    }                                    // dollar check  
    
 
  
  }                                      //1st serial available check 
  
}                      //void loop
