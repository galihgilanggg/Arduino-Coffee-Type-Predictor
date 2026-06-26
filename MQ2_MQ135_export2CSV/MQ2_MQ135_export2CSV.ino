// Include the library
#include "MQ-Sensor-SOLDERED.h"


#define RatioMQ2CleanAir (9.83) // RS / R0 = 9.83 ppm
#define RatioMQ135CleanAir 3.6 // RS / R0 = 3.6 ppm

// Create library object for this specific sensor.
MQ2 mq2(A1);
MQ2 mq135(A2);

unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 5000;  // interval at which to blink (milliseconds)

void setup()
{
    // Init the serial port communication at 115200 bauds. It's used to print out measured data.
    Serial.begin(115200);

    // Set math model to calculate the PPM concentration and the value of constants
    mq2.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq2.setA(574.25);
    mq2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
    /*
      Exponential regression:
      Gas    | a      | b
      H2     | 987.99 | -2.162
      LPG    | 574.25 | -2.222
      CO     | 36974  | -3.109
      Alcohol| 3616.1 | -2.675
      Propane| 658.71 | -2.168
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/

    mq2.begin(); // If you have easyC version of this sensor
                 // you should add here I2C address of sensor
                 // which is 0x30 by default and can be changed
                 // by onboard switches labeled with ADDR

    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq2.setRL(10);
    */
    /*****************************  MQ CAlibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
    // and now is on clean air (Calibration conditions), and it will setup R0 value.
    // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
    // This routine not need to execute to every restart, you can load your R0 if you know the value
    // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
    //Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        mq2.update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += mq2.calibrate(RatioMQ2CleanAir);
        //Serial.print(".");
    }
    mq2.setR0(calcR0 / 10);
    //Serial.println("  done!.");

    if (isinf(calcR0))
    {
        //Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your "
                       //"wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        //Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please "
                       //"check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/

    mq2.serialDebug(false);

    // Set math model to calculate the PPM concentration and the value of constants
    mq135.setRegressionMethod(1); //_PPM =  a*ratio^b
    mq135.setA(605.18);
    mq135.setB(-3.937); // Configurate the ecuation values to get NH4 concentration

    /*
      Exponential regression:
    GAS      | a      | b
    CO       | 605.18 | -3.937
    Alcohol  | 77.255 | -3.18
    CO2      | 110.47 | -2.862
    Tolueno  | 44.947 | -3.445
    NH4      | 102.2  | -2.473
    Acetona  | 34.668 | -3.369
    */

    /*****************************  MQ Init ********************************************/
    // Remarks: Configure the pin of arduino as input.
    /************************************************************************************/
    mq135.begin(); // If you have easyC version of this sensor
                   // you should add here I2C address of sensor
                   // which is 0x30 by default and can be changed
                   // by onboard switches labeled with ADDR
    /*
      //If the RL value is different from 10K please assign your RL value with the following method:
      mq135.setRL(10);
    */
    /*****************************  MQ CAlibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
    // and now is on clean air (Calibration conditions), and it will setup R0 value.
    // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
    // This routine not need to execute to every restart, you can load your R0 if you know the value
    // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
    //Serial.print("Calibrating please wait.");
    float mq135calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        mq135.update(); // Update data, the arduino will be read the voltage on the analog pin
        mq135calcR0 += mq135.calibrate(RatioMQ135CleanAir);
        Serial.print(".");
    }
    mq135.setR0(mq135calcR0 / 10);
    //Serial.println("  done!.");

    if (isinf(mq135calcR0))
    {
        //Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your "
                       //"wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        //Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please "
                       //"check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/
    mq135.serialDebug(false);

}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    mq2.update();      // Update data, the arduino will be read the voltage on the analog pin
    mq2.readSensor();  // Sensor will read PPM concentration using the model and a and b values setted before or in the

    mq135.update();     // Update data, the arduino will be read the voltage on the analog pin
    mq135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the

    mq2.export2CSV();
    Serial.print(",");
    mq135.export2CSV();
    Serial.print("\n");
  }
}
