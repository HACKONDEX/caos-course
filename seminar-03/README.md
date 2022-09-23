Arithmetics, Integers & floats
============================
 <font size="6">
    
# Signed integer types
</font> 
    
 <font size="6"> 

***

#### &nbsp; &nbsp; &nbsp;_type_ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; _minimal memory_
    
- __char__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;at least **__8__** bits
    

- __short__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;at least **__16__** bits
    

- __int__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp; at least **__16__** bits

    
- __long__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; at least **__32__** bits


- __long long__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; at least **__64__** bits
    
   
 </font> 
    
*****
    
<font size="4"> 

You can find out type's memory size using `sizeof()` in your code.

</font> 

```C
#include <stdio.h>

int main() {
    printf("char      occupies  %d  byte\n", sizeof(char));
    printf("short     occupies  %d  byte\n", sizeof(short ));
    printf("int       occupies  %d  byte\n", sizeof(int));
    printf("long      occupies  %d  byte\n", sizeof(long));
    printf("long long occupies  %d  byte\n", sizeof(long long));

    return 0;
}

```

<div class="output stream stdout">

    char      occupies 1 byte
    short     occupies 2 byte
    int       occupies 4 byte
    long      occupies 8 byte
    long long occupies 8 byte

</div>

<font size="4"> 

Since, depending on the processor architecture, the size of the occupied memory may be different, it is better
    to use types with explicit sizes from `<inttypes.h>`. There we have `int8_t`, `int16_t`, `int32_t`, `int64_t`.

`sizeof()` can be called not only from type, but also for variable.

</font> 

```c
#include <inttypes.h>
#include <stdio.h>

int main() {
    int8_t byte_1;
    int16_t byte_2;
    int32_t byte_4;
    int64_t byte_8;
    intmax_t byte_max_cnt;
    printf("int8_t   occupies  %d  byte\n", sizeof(byte_1));
    printf("int16_t  occupies  %d  byte\n", sizeof(byte_2));
    printf("int32_t  occupies  %d  byte\n", sizeof(byte_4));
    printf("int64_t  occupies  %d  byte\n", sizeof(byte_8));
    printf("intmax_t occupies  %d  byte\n", sizeof(byte_max_cnt));

    return 0;
}
```

<div class="output stream stdout">

    int8_t   occupies  1  byte
    int16_t  occupies  2  byte
    int32_t  occupies  4  byte
    int64_t  occupies  8  byte
    intmax_t occupies  8  byte

</div>

<font size="4"> 



For signed types in binary representation of number, all bits except the most significant are forming number's value. The most significant bit is for sign. 

That's why maximal value of `int32_t` is __2<sup>31</sup> - 1__ and minimal value is __-2<sup>31</sup>__

To use maximal and minimal values of different types, use defines from `<limits.h>`

</font> 

```C
#include <limits.h>
#include <stdio.h>

int main() {
    printf("Maximum value of  char:  %d\n", CHAR_MAX);
    printf("Minimum value of  char:  %d\n", CHAR_MIN);
    printf("Maximum value of  int:  %d\n", INT_MAX);
    printf("Minimum value of  int:  %d\n", INT_MIN);
    printf("Maximum value of  long long:  %lld\n", LLONG_MAX);
    printf("Minimal value of  long long:  %lld\n", LLONG_MIN);

    return 0;
}
```

<div class="output stream stdout">

    Maximum value of  int:  127
    Minimum value of  int:  -128
    Maximum value of  int:  2147483647
    Minimum value of  int:  -2147483648
    Maximum value of  long long:  9223372036854775807
    Minimal value of  long long:  -9223372036854775808

</div>

</font> 
    
 <font size="6"> 

***

Unsigned integer types
----------------

#### &nbsp; &nbsp; &nbsp;_type_ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;_minimal memory_
    
- __unsigned char__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;at least **__8__** bits
    

- __unsigned short__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; &nbsp;at least **__16__** bits
    

- __unsigned int__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp; at least **__16__** bits

    
- __unsigned long__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; at least **__32__** bits


- __unsigned long long__ &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; at least **__64__** bits
    
   
 </font>