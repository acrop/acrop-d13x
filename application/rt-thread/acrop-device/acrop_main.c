#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include "rtdevice.h"
#include "aic_hal_gpio.h"

#include <lwip/sio.h>

void uart_demo(void) {
  uint8_t buffer[1024] = {};
  uint8_t sendcmd[] = "hello";
  sio_fd_t fd = sio_open(5, 9600);

  while (1) {
    sio_write(fd, sendcmd, strlen(sendcmd));
    rt_thread_mdelay(200);
    memset(buffer, 0, sizeof(buffer));
    int len = sio_tryread(fd, buffer, 1024);
    if (len > 0) {
      printf("receive %s \n", buffer);
    }
    rt_thread_mdelay(200);
  }
}

/* 创建一个线程来运行 gpio demo */
int uart_test_demo(void)
{
    rt_thread_t thread = rt_thread_create("uart_demo", uart_demo, RT_NULL, 1024*10, 10, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    return 0;
}

//INIT_APP_EXPORT(acrop_main_test);
MSH_CMD_EXPORT(uart_test_demo, uart demo);
