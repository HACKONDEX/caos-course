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

     Type     memory(bytes)      Max                 Min
    int8_t          1            127                -128
    int16_t         2           32767              -32768
    int32_t         4         2147483647         -2147483648
    int64_t         8     9223372036854775807 -9223372036854775808
----------------
    uint8_t         1            255                  0
    uint16_t        2           65535                 0
    uint32_t        4         4294967295              0
    uint64_t        8     18446744073709551615        0

<font size="6"> 

Bitwise operations
====================

- Bitwise operations are defined for __positive__ operands. For __negative__ operands operators have undefined behavior. The result for positive operands of signed integer types is implementation defined.
  
- You should use **bitwise operations** only for unsigned integer types not to get in trap. Even with "negative zero" can be problems.
  
### Operations

- `&` __-__ does **AND** on every bit of two numbers. The result of **AND** is 1 only if both bits are 1.

- `|` __-__ does **OR** on every bit of two numbers. The result of **OR** is 1 if any of the two bits is 1. 

- `^` __-__ does **XOR** on every bit of two numbers. The result of **XOR** is 1 if the two bits are different. 

- `~` __-__ **inverts** all bits of the number;
 
- `<<` __-__ **left** shifts the bits of the first operand, the second operand decides the number of places to shift. 

- `>>` __-__ **right** shifts the bits of the first operand, the second operand decides the number of places to shift. 

Integer overflow
==========

- In `C` only for unsigned types overflow is defined. If After some arithmetic operation the value is bigger than the possible maximum of the type, it will return the value as in ring **Z**<sub>MAX_VALUE</sub>.

</font>

```C
%%file overflow.c
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

int check_signed(int x) {
    return (x + 1) > x;
}

int check_unsigned(unsigned int x) {
    return (x + 1) > x;
}

int main() {
    printf("check unsigned for UINTMAX returned  %d\n", check_unsigned(UINT_MAX));

    int64_t value = INT64_MAX;
    printf("INT64_MAX + 1 == %" PRId64 "\n", value + 1);
    ++value;
    printf("after increment value == %" PRId64 "\n", value);

    uint64_t uint_value = 0;
    printf("uint 0 - 1 == %" PRIu64 "\n", uint_value - 1u);
    --uint_value;
    printf("uint 0 after decrement == %" PRIu64 "\n", uint_value);

    printf("check signed for INTMAX returned  %d\n", check_signed(INT_MAX));

    return 0;
}
```

<div class="output stream stdout">

    check unsigned for UINTMAX returned  0
    INT64_MAX + 1 == -9223372036854775808
    after increment value == -9223372036854775808
    uint 0 - 1 == 18446744073709551615
    uint 0 after decrement == 18446744073709551615
    check signed for INTMAX returned  1

</div>


<font size="6"> 

# floats & doubles

- __float__ in memory occupies __`32`__ bits
  
  - Three abstract parts starting from most signigicant byte
    
    1. Sign **-** __`1`__ bit
    2. Exponenta **-** __`8`__ bits
    3. Mantissa **-** __`23`__ bits

    - Counting formula **:**  &nbsp; (-1)<sup>_S_</sup> 2<sup>*E* - 2<sup>(*b* - 1)</sup>+1</sup>(1+*M*/2<sup>23</sup>), where _b_ is a constant shift defined for processor

- __double__ in memory occupies at *least* __`32`__ bits, __`64`__ on Intel_x86_64 

  - Three abstract parts starting from most signigicant byte
    
    1. Sign **-** __`1`__ bit
    2. Exponenta **-** __`11`__ bits
    3. Mantissa **-** __`52`__ bits
    - Counting formula **:** &nbsp;  (-1)<sup>_S_</sup> 2<sup>_E_ - 2<sup>(*b* - 1)</sup>+1</sup>(1+*M*/2<sup>52</sup>), where _b_ is a constant shift defined for processor


### Not regular float and double values


|_S_|[|_Exp_|]|[|_Mantissa_|]|<center>_Type_</center>|
|-|-|---|-|-|------|-|---------------------|
|0|0|.......|0|0|... ... ... ... ...|0|<center>__PlusZero__</center>|
|1|0|.......|0|0|... ... ... ... ...|0|<center>__MinusZero__</center>|
|0|0|.......|0|x|... ... ... ... ...|x|<center>__PlusDenormalized__</center>|
|1|0|.......|0|x|... ... ... ... ...|x|<center>__MinusDenormalized__</center>|
|0|1|.......|1|0|... ... ... ... ...|0|<center>__PlusInf__</center>|
|1|1|.......|1|0|... ... ... ... ...|0|<center>__MinusInf__</center>|
|x|1|.......|1|1|x. ... ... ... .x|x|<center>__QuietNaN__</center>|
|x|1|.......|1|0|x. ... ... ... .x|x|<center>__SignalingNaN__</center>|


- You can read more details in [IEEE 754](http://www.softelectro.ru/ieee754.html)

 </font>


