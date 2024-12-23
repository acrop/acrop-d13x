#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include "rtdevice.h"
#include "aic_hal_gpio.h"

#define DATABASE_NAME "/data/test.db"

int test_acrop_device();

/* 回调函数，用于处理查询结果 */
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        rt_kprintf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    rt_kprintf("\n");
    return 0;
}

int acrop_main_test(void)
{
  printf("Hello World:%d!\n", test_acrop_device());
  uint32_t pin = 0;
  pin = rt_pin_get("PE.6");
  rt_pin_mode(pin, PIN_MODE_OUTPUT);
  rt_pin_write(pin, PIN_HIGH);

  return 0;
}

void gpio_demo(void) {
  uint32_t pin = 0;
  pin = rt_pin_get("PE.10");
  rt_pin_mode(pin, PIN_MODE_INPUT);
  while (1) {
    int status = rt_pin_read(pin);
    printf("gpio read: %d\r\n", status);
    rt_thread_mdelay(1000);
  }
}

/* 创建一个线程来运行 gpio demo */
int gpio_test_demo(void)
{
    rt_thread_t thread = rt_thread_create("gpio_demo", gpio_demo, RT_NULL, 1024, 10, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    return 0;
}

void uart_demo(void) {
  static rt_device_t serial;
  rt_err_t ret = RT_EOK;
  uint8_t buffer[100] = {0};
  serial = rt_device_find("uart5");
  if (!serial)
  {
      printf("find uart1 failed!\n");
      return;
  }

  ret = rt_device_open(serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
  if (ret != RT_EOK)
  {
      printf("open uart1 failed : %d !\n", ret);
      return;
  }

  char sendcmd[10] = "AT\r\n";

  while (1) {
    rt_device_write(serial, 0, sendcmd, strlen(sendcmd));
    printf("send AT\r\n");
    rt_thread_mdelay(200);
    memset(buffer, 0, sizeof(buffer));
    int len = rt_device_read(serial, 0, buffer, 100);
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
