#include <inttypes.h>

extern void sum(ITYPE first, ITYPE second, ITYPE *res, int *CF) {
	(*res) = 0u;
	ITYPE carry = 0u;

	uint16_t bits_count = sizeof(ITYPE) * 8;
	for (uint16_t i = 0; i < bits_count; ++i) {
		ITYPE first_bit = ((first >> i) & (ITYPE)(1));
		ITYPE second_bit = ((second >> i) & (ITYPE)(1));
		(*res) |= ((first_bit ^ second_bit ^ carry) << i);
		carry = (first_bit & second_bit) | (first_bit & carry) | (second_bit & carry);
	}

	(*CF) = (int)(carry);
}
