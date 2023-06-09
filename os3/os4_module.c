#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

int ASMD_Operation(int *result, int num1, int num2, char *op)
{
  if (op)
  {
    if (*op == '+')
    {
      *result = num1 + num2;
    }
    else if (*op == '-')
    {
      *result = num1 - num2;
    }
    else if (*op == '*')
    {
      *result = num1 * num2;
    }
    else if (*op == '\\')
    {
      if (num2 != 0)
        *result = num1 / num2;
      else
        printk("dived number can't be zero!\n");
    }
    else
      printk("unrecongized operator %c\n", *op);
  }
  else
  {
    printk("operation is empty.\n");
  }
  return 0;
}

int (*fptr_Operation)(int *, int, int, char *);

static int os4_init(void)
{
  printk(KERN_ALERT "os4 init...\n");
  fptr_Operation = &ASMD_Operation;
  return 0;
}
static void os4_exit(void) { printk(KERN_ALERT "os4 exit...\n"); }

// 导出函数指针
EXPORT_SYMBOL(fptr_Operation);
// 用于 Linux
// 内核编程的宏，它允许一个内核模块导出符号（通常是函数指针），以便其他内核模块可以使用。这样做的目的是实现模块之间的相互通信和功能共享

module_init(os4_init);
module_exit(os4_exit);