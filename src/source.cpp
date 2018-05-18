#include <mbed.h>
#include <C12832.h>
#include <mbed_events.h>
#include <FXOS8700Q.h>


//vars
Thread thread;    //a thread
C12832 lcd(D11, D13, D12, D7, D10);
unsigned static counter =0;
EventQueue queue ;
InterruptIn leftButton(SW2);
InterruptIn rightButton(SW3);
I2C i2c(PTE25, PTE24);
FXOS8700QAccelerometer acc(i2c, FXOS8700CQ_SLAVE_ADDR1);

void increaseCounter(void)
{
  counter++;
}

void decreaseCounter(void)
{
  counter--;
}

void updateLCD(void)
{
    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("Guten Tag: ");

    lcd.printf("%d", counter);
}

void updateAccelLcd(void)
{
  motion_data_units_t acc_data;
  acc.getAxis(acc_data);
  lcd.locate(0, 15);
  lcd.printf("X=%+1.3f Y=%+1.3f Z=%+1.3f \t",
    acc_data.x, acc_data.y, acc_data.z);
}

int main()
{
  acc.enable();

  leftButton.rise(queue.event(increaseCounter));
  rightButton.fall(queue.event(decreaseCounter));

  queue.call_every(1000, updateLCD);
  queue.call_every(1000, updateAccelLcd);
  queue.dispatch_forever();
  thread.start(updateLCD);

}
