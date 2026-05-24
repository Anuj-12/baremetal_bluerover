#include "stm32f401xe.h"
#include "systick.h"
#include "uart.h"
#include "log.h"
#include "uart_reader.h"
#include "rover.h"
#include "gpio.h"
#include "parser.h"

volatile char msg[20] = {};

int main(){
    log_init(115200);
    log_print("Hello\r\n");
}
