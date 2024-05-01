#include <stdio.h>
#include <unistd.h>

int	func(char *str)
{
	printf("%s\n", str);
	return(10);
}

void	ana(int(*dom)(char*))
{
	int sayi = (*dom)("domates");
	printf("%d\n", sayi);
}



int main()
{
	ana(&func);
	return 0;
}
