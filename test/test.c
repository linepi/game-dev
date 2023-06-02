#include <stdio.h>
#include <time.h>

int main() {
	clock_t last = clock();
	while (1) {
		if (clock() - last >= CLOCKS_PER_SEC) {
			last = clock();
			printf("passed 1 second...\n");
		}
	}
	return 0;
}