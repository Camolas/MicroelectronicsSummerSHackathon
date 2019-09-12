#include "mbed.h"
//#include "TextLCD.h"

#define voltage 3300;
#define ON 0;
#define OFF 1;

AnalogIn analog_light(A1);
AnalogIn analog_humid(A0);


Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut led_D1(PA_8);  // Vermelho PwnOut <- 0 e 255
DigitalOut led_D2(PA_9);  // Verde
DigitalOut led_D3(PC_7);  // Azul

DigitalOut sw_s1( PB_6 );   //relay

//TextLCD lcd(D8, D3, D7, D6, D5, D4, TextLCD::LCD8x2);

bool verificacao(float humid_sensor, float light_sensor);
void liga_rega(float humid_sensor);


int main()
{
    
    pc.printf("Hello World");
    float light_sensor, humid_sensor;
    int /*count=0, a=0,*/ disp=0;
    bool rega;

    sw_s1=OFF;
    led_D1 = !false;
    led_D2 = !false;
    led_D3 = !false;
    //  lcd.cls();

    while(1) {

        humid_sensor =1- analog_humid.read();
        light_sensor = analog_light.read();


        //se for noite e estiver entre 0.45 e 0.50 liga azul
        if(humid_sensor<0.5f) {  // led azul ativo Sinal de Alerta
            led_D3=!true;
        } else {
            led_D2=!true;
        }

        //se for dia e estiver entre 0.3 e 0.4 liga vermelho
        if(humid_sensor<0.45f) {
            led_D1=!true; // magenta
        } else {
            led_D1=!false;
        } //Azul entre 0.5 e 0.45 ou Green > 0.5

        //changes LCD every 15 seconds
        /*       if(count>14) {
                //   if(a==0)a=1;
                   else if(a==1)a=0;
                   count=0;
               }*/

//if(a==0) {
        //       lcd.cls();
        disp=light_sensor*100;
/*lcd.*/pc.printf("Light: %d%% and ", disp);
        //      } else if(a==1) {
        disp=humid_sensor*100;
        //lcd.cls();
/*lcd.*/pc.printf("Humidity: %d%%\n", (disp*(10/6)));
        // }
        light_sensor*=voltage;

        pc.printf( "light: %f \r humid: %f \n\r\n\r\n\n\n", light_sensor, humid_sensor );

        rega= verificacao(humid_sensor, (float) light_sensor);
        if(rega) {
            liga_rega(humid_sensor);
        }
        wait_ms(1000);
        //  count++;
    }
}

bool verificacao(float humid_sensor, float light_sensor)
{

    if( (light_sensor<330 && humid_sensor<0.7f) || (humid_sensor< 0.6f)) {

        return true;
    } else return false;
}

void liga_rega(float humid_sensor)
{
    //liga verde
    led_D1=!true;
    led_D2=!true;
    while(humid_sensor<0.20f) {
        humid_sensor = 1-analog_humid.read();
        //LIGAR MOTOR
        sw_s1=ON;
        pc.printf("humid: %f \n\r\n\r", humid_sensor);
        wait(1);
    }
    sw_s1=OFF;
    led_D1=!false;
    led_D2=!false;
    return;
}