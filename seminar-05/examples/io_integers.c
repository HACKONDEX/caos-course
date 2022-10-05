#include <inttypes.h>
#include <stdio.h>
	
int main() {
	int32_t signed_value = 0;
	uint32_t unsigned_value = 0;
	
	scanf("%" PRId32, &signed_value);
	scanf("%" PRIu32, &unsigned_value);

	++signed_value;
	--unsigned_value;

	printf("signed value == %" PRId32 "\n", signed_value);
	printf("unsigned_value == %" PRIu32 "\n", unsigned_value);

	return 0;
}
