// Variant 1 - tricky addressing
// You can handle global vars from other compilation module 
// using addresses	

	.data			// Section .data
	.global R       // Section .global, for global variables names
R:
	.space 8, 0     // a 8 byte cell, with value 0x0000000000000000

	.text			
	.global calculate // global function calculate

calculate:
	adr x0, .globals  // x0 will hold address of label '.globals'
	ldr x1, [x0]      // load value under address in x0, which is the address of 'A'
	ldr x1, [x1]	  // load value under address in x1, which is the value of 'A'

	add x0, x0, 8	  // .quad defines 8byte data, that's why we add 8 to get next address
	ldr x2, [x0]      // load value under address x0 + 8, which is the address of 'B'
	ldr x2, [x2]	  // load value under address in x2. which is the valude of 'B'

	add x0, x0, 8
	ldr x3, [x0]      // same steps for 'C'
	ldr x3, [x3]

	add x0, x0, 8
	ldr x4, [x0]      // for 'D'
	ldr x4, [x4]

	mul x1, x1, x2    // store in x1, A * B
	mul x3, x3, x4    // store in x3, C * D
	add x1, x1, x3    // store in x1, A * B + C * D

	adr x0, R         // store in x0, the address of glabal var R
	str x1, [x0]      // store in cell with address in x0 the value in x1

	ret

.globals:
	.quad A           // After compiltaion we will have here raw address of label 'A' defined in other compilation module
	.quad B           // Here will be address of label 'B',
	.quad C
	.quad D
