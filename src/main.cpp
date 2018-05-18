/*
#include <mbed.h>
#include <rtos.h>
#include <mbed_events.h>

Serial pc(USBTX, USBRX);

DigitalOut red(LED1,1);
void flash(void){
    red = !red;
}

DigitalOut green(LED2,1);
void blink(void){
    pc.printf("This is not in an ISR so I can do long (time) operations\n");
    green = !green;
}
Thread worker;

EventQueue queue ;

InterruptIn sw(SW2);
int main() {
    sw.rise(flash); /* executes as an ISR
    sw.fall(queue.event(blink));
    worker.start(callback(&queue, &EventQueue::dispatch_forever ));
    while(1){}
}
*/
