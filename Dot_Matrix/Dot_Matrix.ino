#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define MAX_DEVICES 4
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10
MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
void setup(void)
{
P.begin();
}
void loop(void)
{
P.print("Hello");
delay(500);
/*P.print(1234, DEC);
delay(500);
P.print(1234, HEX);
delay(500);
P.print(12.5); // float not supported by Arduino Print class
delay(WAIT_TIME);
P.print(9876l);
delay(WAIT_TIME);
P.println("end"); // only get the /r/n characters - avoid using println
delay(WAIT_TIME);
P.write('A');
delay(WAIT_TIME);
P.write('B');
delay(WAIT_TIME);
P.write('C');
delay(WAIT_TIME);*/
}
