#include <stdarg.h>
#include <stdio.h>
#include <math.h>

//reverse a string
//strrev is not available for all C compilers
void reverse(char * str, int len) {
    int temp;

    for (int i = 0; i < len/2; i++)  
    {
        temp = str[i];  
        str[i] = str[len - i - 1];  
        str[len - i - 1] = temp;  
    }  
}

//convert int to str 
int int_to_str(int num, char * str, int num_of_digits) {
  int i = 0, flag = 0;

  if (num < 0) {
    str[i++] = '-';
    flag = 1;
  }

  while(num != 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }

  while(i < num_of_digits) {
    str[i++] = '0';
  }

  reverse(&str[flag], num_of_digits);

  str[i] = '\0';

  return i;
}

//convert long int to str 
int long_int_to_str(long int num, char * str, int num_of_digits) {
  int i = 0, flag = 0;

  if (num < 0) {
    str[i++] = '-';
    flag = 1;
  }

  while(num != 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }

  while(i < num_of_digits) {
    str[i++] = '0';
  }

  reverse(&str[flag], num_of_digits);

  str[i] = '\0';

  return i;
}

//convert long long int to str 
int long_long_int_to_str(long long int num, char * str, int num_of_digits) {
  int i = 0, flag = 0;

  if (num < 0) {
    str[i++] = '-';
    flag = 1;
  }

  while(num != 0) {
    str[i++] = (num % 10) + '0';
    num /= 10;
  }

  while(i < num_of_digits) {
    str[i++] = '0';
  }

  reverse(&str[flag], num_of_digits);

  str[i] = '\0';

  return i;
}

//convert float to str
void float_to_str(float num, char * str, int precision) {
  int Floor = floor(num);
  float fraction = num - (float) Floor;

  int num_of_digits = ((Floor==0) ? 1 : log10((Floor < 0) ? -Floor : Floor) + 1);

  int floor_end_index = int_to_str(Floor, str, num_of_digits);

  if (precision != 0) {
    str[floor_end_index] = '.';

    fraction = fraction * pow(10, precision);

    int_to_str((int) fraction, &str[floor_end_index+1], precision);
  }
}

//convert double to str
void double_to_str(double num, char * str, int precision) {
  int Floor = floor(num);
  double fraction = num - (double) Floor;

  int num_of_digits = ((Floor==0) ? 1 : log10((Floor < 0) ? -Floor : Floor) + 1);

  int floor_end_index = int_to_str(Floor, str, num_of_digits);

  if (precision != 0) {
    str[floor_end_index] = '.';

    fraction = fraction * pow(10, precision);

    long_int_to_str((long int) fraction, &str[floor_end_index+1], precision);
  }
}

//custom printf
int my_printf (char * format, ...) {

  va_list ap;
  va_start(ap, format);

  int i = 0, num_of_digits, temp_int;
  long int temp_long_int;
  long long int temp_long_long_int;
  char str[50];

  while(format && format[i] && format[i] != '\0') {

    while(format[i] != '%') {
      putchar(format[i++]);
    }

    i++;

    switch (format[i])
    {
    case 'c':
      putchar(va_arg(ap, int));
      break;

    case 'd':
      temp_int = va_arg(ap, int);
      num_of_digits = ((temp_int==0) ? 1 : log10((temp_int < 0) ? -temp_int : temp_int) + 1);
      int_to_str(temp_int, str, num_of_digits);
      fputs(str, stdout);
      break;

    case 'f':
      float_to_str(va_arg(ap, double), str, 6);
      fputs(str, stdout);
      break;

    case 'l':
      temp_long_int = va_arg(ap, long int);
      num_of_digits = ((temp_long_int==0) ? 1 : log10((temp_long_int < 0) ? -temp_long_int : temp_long_int) + 1);
      long_int_to_str(temp_long_int, str, num_of_digits);
      fputs(str, stdout);
      break;

    case 'L':
      temp_long_long_int = va_arg(ap, long long int);
      num_of_digits = ((temp_long_long_int==0) ? 1 : \
                log10((temp_long_long_int < 0) ? -temp_long_long_int : temp_long_long_int) + 1);
      long_long_int_to_str(temp_long_long_int, str, num_of_digits);
      fputs(str, stdout);
      break;

    case 'D':
      double_to_str(va_arg(ap, double), str, 15);
      fputs(str, stdout);
      break;

    case 's':
      fputs(va_arg(ap, char *), stdout);
      break;

    case '%':
      putchar('%');
      break;
    }

    i++;
  }

  va_end(ap);
}

int main(){

    printf("Sum of five int params = %d\n", sum_int(5, 1, 2, 3, 4, 5));

    printf("Sum of five char params = %d\n", sum_char(5, '1', '2', '3', '4', '5'));

    long l1 = 1; long l2 = 2; long l3 = 3; long l4 = 4; long l5 = 5;
    printf("Sum of five long params = %ld\n", sum_long(5, l1, l2, l3, l4, l5));

    long long ll1 = 1; long long ll2 = 2; long long ll3 = 3; long long ll4 = 4; long  long ll5 = 5;
    // Note: Ignore the warning given by the GCC compiler for the format specifier %lld
    printf("Sum of five long long params = %lld\n", sum_long_long(5, ll1, ll2, ll3, ll4, ll5));

    float f1 = 1.0; float f2 = 2.0; float f3 = 3.0; float f4 = 4.0; float f5 = 5.0;
    printf("Sum of five float values passed as double = %f\n", sum_float(5, f1, f2, f3, f4, f5));

    double d1 = 1.0; double d2 = 2.0; double d3 = 3.0; double d4 = 4.0; double d5 = 5.0;
    printf("Sum of five double values passed = %f\n", sum_double(5, d1, d2, d3, d4, d5));

    char *str1 = "String 1.\n";
    char *str2 = "String 2.\n";
    my_print_strs(2, str1, str2);

    my_printf("The generic tests are %c, %d, %f, %l, %L, %D, %s, %%", 'a', 145, 43.256, 234566, 234567865, 3222.56787888, "Sample string");

    return 0;
 } // end of main()


