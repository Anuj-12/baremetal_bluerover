#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "uart_reader.h"
#include "rover.h"
#include "gpio.h"
#include "parser.h"

// Maybe needs to be volatile
volatile char msg[20] = {};

int main(){
    uart2_init(115200);
    uart1_init(115200);

    uart2_write("=== UART2 -> UART1 TEST ===\n");

    // Wire PA2 (UART2 TX) to PB7 (UART1 RX)
    uart2_write("HELLO\n");

    for(volatile int i = 0; i < 500000; i++);

    // bypass getline completely
    char c = uart1_read();
    if(c == '\0') uart2_write("BUFFER EMPTY\n");
    else{
        uart2_write("GOT: ");
        uart2_write_ch(c);
        uart2_write("\n");
    }

    while(1);
}
