#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *str = malloc(3);
    str[5] = 'a';
	printf("%c\n", str[5]);
    return 0;
}