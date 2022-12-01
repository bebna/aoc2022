#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* cat filename | awk '{ print length }' | sort -n | tail -1 */
#define LINE_LEN 8 

void process_elf(unsigned long *top, unsigned long current_elf) {
	for(int i=0; i<3 ;i++) {
		if (top[i] < current_elf) {
			top[i] ^= current_elf;
			current_elf ^= top[i];
			top[i] ^= current_elf;
		}
	}
}

int main() {
	char buffer[LINE_LEN] = "";
	FILE *fp = fopen("./input.txt", "r");
	unsigned long current_elf = 0;
	unsigned long top[3] = {0};

	if (!fp) {
		perror("file open error");
		return 1;
	}

	while (fgets(buffer, LINE_LEN, fp)) {
		if (buffer[0] == '\n') {
			process_elf(top, current_elf);
			current_elf = 0;
			continue;
		}
		errno = 0; // for strtol
		current_elf += strtoul(buffer, NULL, 10);
		if (errno == EINVAL) {
			perror("strtoul EINVAL");
			fclose(fp);
			return 1;
		} else if (errno == ERANGE) {
			perror("strtoul ERANGE");
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);

	if (current_elf != 0) {
		process_elf(top, current_elf);
	}

	printf("%d\n%d\n", top[0], (top[0]+top[1]+top[2]));
	return 0;
}
