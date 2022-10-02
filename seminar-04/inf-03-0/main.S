    .text
    .global f
// x0 A, x1 B, x2 C, x3 x
f:
    mul x0, x0, x3
    add x0, x0, x1
    mul x0, x0, x3
    add x0, x0, x2
    ret