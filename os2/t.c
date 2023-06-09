#include <stdio.h>
#include <sys/syscall.h> // 这里能找到之前写在内核的代码
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

long my_oper(int *result, int num1, int num2, char *op)
{
  if (op)
  {
    if (*op == '+')
      *result = num1 + num2;
    else if (*op == '-')
      *result = num1 - num2;
    else if (*op == '*')
      *result = num1 * num2;
    else if (*op == '\\')
    {
      if (num2 != 0)
        *result = num1 / num2;
      else
        printf("divided number can't be zero.\n");
    }
  }
  else
    printf("operator is empth.\n");

  return 0;
}

// 用户态代码
long optime(int count)
{
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);
  count = 1000000000;
  int result;
  int i;
  for (i = 0; i < count; i++)
  {
    char op_add = '+';
    my_oper(&result, 10, 10, &op_add);
  }

  for (i = 0; i < count; i++)
  {
    char op_sub = '-';
    my_oper(&result, 20, 10, &op_sub);
  }

  for (i = 0; i < count; i++)
  {
    char op_mul = '*';
    my_oper(&result, 10, 10, &op_mul);
  }

  for (i = 0; i < count; i++)
  {
    char op_div = '\\';
    my_oper(&result, 20, 10, &op_div);
  }

  gettimeofday(&tend, NULL);
  printf("total time:%ld usec\n", 1000000 * (tend.tv_sec - tstart.tv_sec) +
                                      (tend.tv_usec - tstart.tv_usec));
  return 0;
}

int main()
{
  int count = 10000 * 10000;

  optime(count);
  return 0;
}
