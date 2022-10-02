#include <inttypes.h>
#include <stdio.h>

uint64_t A = 2;
uint64_t B = 3;
uint64_t C = 2;
uint64_t D = 2;

extern uint64_t R;

void calculate();

int main() {
	calculate();
	printf("%" PRIu64 "\n", R);
	return 0;
}