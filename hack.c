#include "mbed.h"

AnalogIn analog_value(A0);
Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut led_D1( PA_5 );  // LED D1
DigitalOut led_D2( PA_6 );  // LED D2
DigitalOut led_D3( PA_7 );  // LED D3
//DigitalOut led_D4( PB_6 );  // LED D4

int main() {
    float meas;
    led_D1 = false;
    led_D2 = false;
    led_D3 = false;
    pc.printf("\nAnalogIn example \n\r");

    while(1) {
        meas = analog_value.read(); // Converts and read the analog, input value (value from 0.0 to 1.0)
        meas = meas * 3300; // Change the value to be in the 0 to 3300 range
        pc.printf("measure = %.0f mV \n\r", meas);
        if (meas > 250)
            led_D1 = !true; 
        else
            led_D1 = !false;
        if (meas > 700){
            led_D1 = !false;
            led_D2 = !true;
            }
        else
            led_D2 = !false;
        if (meas > 1000){
            led_D1 = !false;
            led_D2 = !false;
            led_D3 = !true;
            }
        else
            led_D3 = !false;
        if (meas > 1500){
            led_D1 = !true;
            led_D2 = !true;
            led_D3 = !true;
        }
        wait_ms(0.8); // 200 ms
    }
}



