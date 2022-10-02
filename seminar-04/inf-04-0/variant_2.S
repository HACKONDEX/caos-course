// Variant 1 - section extern
// As we know that global variables {A, B, C, D} are defined in other compilation module
// We can use them with qualifier 'extern'
// In C language we have qualifier 'extern'
// IN assembly we have section '.extern'

    .data               // Section .data
    .global R           // Section .global, for global variables names
R:      
	.space 8, 0         // A 8 byte cell, with value 0x0000000000000000

    .extern A           // Declare extern global var A, compiler will search label 'A' in other compilation modules
    .extern B           // This is equivalent to 'extern uint64_t A;' in C language
    .extern C
    .extern D

    .text
    .global calculate

calculate:   
    adr x0, A 		    // Load address of label 'A', which compiler will get from other compitlation module
    ldr x1, [x0]		// Load value under address in x0, in x0 we have loaded the address of global var 'A'

    adr x0, B           // Same for 'B'
    ldr x2, [x0]

    adr x0, C           // For 'C'
    ldr x3, [x0]

    adr x0, D           // 'D'
    ldr x4, [x0]

    mul x1, x1, x2      // Store in x1, A * B
    mul x3, x3, x4      // Store in x3, C * D
    add x1, x1, x3     	// Store in x1, A * B + C * D

    adr x0, R           // store in x0, the address of glabal var R
	str x1, [x0]        // store in cell with address in x0 the value in x1

	ret
