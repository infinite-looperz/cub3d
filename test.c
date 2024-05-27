#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	double x = 1;
	fmod(x, M_PI * 2);
	printf("%f\n", fmod(x, M_PI * 2));
	return 0;
}
