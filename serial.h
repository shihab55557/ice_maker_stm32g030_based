

#include "stm32g030xx.h"

void    uart_Init(uint32_t Baud_rate);
void    uart_char(char ch);
void    uart_send_char(char *data);
int32_t uart_send_num(int32_t num);
void    uart_send_num_arr(int32_t arr[10]);
void    uart_flush(void);
void    uart_send_num_bin(uint16_t num);
void    uart_send_num_float(float num);