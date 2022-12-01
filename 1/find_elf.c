#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

/* How I chose the LINE_LEN:
 * $ cat input.txt | awk '{ print length }' | sort -n | tail -1
 * 5
 */
#define LINE_LEN 8 

void swap(unsigned long *a, unsigned long *b) {
	unsigned long tmp = *a;
	*a = *b;
	*b = tmp;
}

void process_elf(unsigned long *top, unsigned long current_elf) {
	for(int i=0; i<3 ;i++) {
		if (top[i] < current_elf) {
			swap(&top[i], &current_elf);
		}
	}
}

int main() {
	char buffer[LINE_LEN] = "";
	unsigned long top[3] = {0};
	unsigned long current_elf = 0;
	unsigned long current_line = 0;
	FILE *fp = fopen("./input.txt", "r");

	if (!fp) {
		perror("cannot read file ./input.txt");
		return 1;
	}

	while (fgets(buffer, LINE_LEN, fp)) {
		// empty line -> end of one elf
		if (buffer[0] == '\n') {
			process_elf(top, current_elf);
			current_elf = 0;
			continue;
		}
		
		// shouldn't happen, but make sure that line wasn't longer than buffer
		if (strchr(buffer, '\n') == NULL) {
			perror("line length longer than expected");
			return 1;
		}

		errno = 0; // for strtoul
		current_line = strtoul(buffer, NULL, 10);
		if (errno == EINVAL) {
			perror("could not parse number");
			return 1;
		} else if (errno == ERANGE) {
			perror("read number exceeds my capacity");
			return 1;
		}
		
		// shouldn't happen, but make sure that sum isn't larger than type limit
		if (current_line > 0 && current_elf > (ULONG_MAX - current_line)) {
			perror("total number of one elf exceeds my capacity");
			return 1;
		}
		current_elf += current_line;
		current_line = 0;
	}

	if (current_elf != 0) {
		process_elf(top, current_elf);
	}
	if ((top[1] > 0 && top[2] > (ULONG_MAX - top[1])) ||
	    ((top[1] + top[2]) > 0 && top[0] > (ULONG_MAX - (top[1]+top[2])))) {
		perror("total of the top 3 elves exceeds my capacity");
		return 1;
	}

	printf("%ld\n%ld\n", top[0], (top[0]+top[1]+top[2]));
	return 0;
}
