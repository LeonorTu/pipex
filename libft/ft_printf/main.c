#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	test_pointer(char *str, unsigned long arg)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg);
	ft = ft_printf(str, arg);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int	test_pointer_triple(char *str, unsigned long arg, unsigned long arg2, unsigned long arg3)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg, arg2, arg3);
	ft = ft_printf(str, arg, arg2, arg3);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int test_single(char *str, int arg)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg);
	ft = ft_printf(str, arg);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int test_single_u(char *str, unsigned arg)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg);
	ft = ft_printf(str, arg);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int test_double(char *str, int arg, int arg2)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg, arg2);
	ft = ft_printf(str, arg, arg2);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int test_triple(char *str, int arg, int arg2, int arg3)
{
	int ft;
	int std;

	//printf("%s\n", desc);

	std = printf(str, arg, arg2, arg3);
	ft = ft_printf(str, arg, arg2, arg3);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int test_noarg(void *str)
{
	int ft;
	int std;

	std = printf(str);
	ft = ft_printf(str);

	printf("std: %d\nft %d\n", std, ft);
	printf("\n");
}

int	main()
{
		test_noarg(NULL);
		printf("% koolio");
		//c format
		printf("-------- c FORMAT--------\n");
		test_single("%c\n", 'x');
		test_single(" %c\n", 'x');
		test_single("%c \n", 'x');
		test_triple("%c%c%c\n", 'a', '\t', 'b');
		test_triple("%cc%cc%c\n", 'a', '\t', 'b');
		test_triple("%cs%cs%c\n", 'c', 'b', 'a');

		//d format
		printf("-------- d FORMAT--------\n");
		test_single("%d\n", 0);
		test_single("%d\n", -10);
		test_single("%d\n", -200000);
		test_single("%d\n", -6000023);
		test_single("%d\n", 10);
		test_single("%d\n", 10000);
		test_single("%d\n", 100023);
		test_single("%d\n", INT_MAX);
		test_single("%d\n", INT_MIN);
		test_single("dgs%dxx\n", 10);
		test_triple("%d%dd%d\n", 1, 2, -3);

		//i format
		printf("-------- i FORMAT--------\n");
		test_single("%i\n", 0);
		test_single("%i\n", -10);
		test_single("%i\n", -200000);
		test_single("%i\n", -6000023);
		test_single("%i\n", 10);
		test_single("%i\n", 10000);
		test_single("%i\n", 100023);
		test_single("%i\n", INT_MAX);
		test_single("%i\n", INT_MIN);
		test_single("dgs%ixx\n", 10);
		test_triple("%i%id%i\n", 1, 2, -3);

		//u format
		printf("-------- u FORMAT--------\n");
		test_single("%u\n", 0);
		test_single("%u\n", -10);
		test_single("%u\n", -200000);
		test_single("%u\n", -6000023);
		test_single("%u\n", 10);
		test_single("%u\n", 10000);
		test_single("%u\n", 100023);
		test_single("%u\n", INT_MAX);
		test_single("%u\n", INT_MIN);
		test_single("dgs%uxx\n", 10);

		//x format
		printf("-------- x FORMAT--------\n");
		test_single("%x\n", 0);
		test_single("%x\n", -10);
		test_single("%x\n", -200000);
		test_single("%x\n", -6000023);
		test_single("%x\n", 10);
		test_single("%x\n", 10000);
		test_single("%x\n", 100023);
		test_single("%x\n", INT_MAX);
		test_single("%x\n", INT_MIN);
		test_single("dgs%xxx\n", 10);

		//X format
		printf("-------- X FORMAT--------\n");
		test_single("%X\n", NULL);
		test_single("%X\n", 0);
		test_single("%X\n", -10);
		test_single("%X\n", -200000);
		test_single("%X\n", -6000023);
		test_single("%X\n", 10);
		test_single("%X\n", 10000);
		test_single("%X\n", 100023);
		test_single("%X\n", INT_MAX);
		test_single("%X\n", INT_MIN);
		test_single("dgs%Xxx\n", 10);

		//p format
		printf("-------- p FORMAT--------\n");
		test_pointer("%p\n", "");
		test_pointer("%p\n", NULL);
		test_pointer("%p\n", (void *)-14523);
		test_pointer("0x%p-\n", (void *)ULONG_MAX);
		test_pointer_triple("'%p'pff'%p''%p'\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);

		//% format
		printf("-------- %% FORMAT--------\n");
		test_noarg("%%\n");
		test_noarg(" %%\n");
		test_noarg("%%c\n");
		test_noarg("%%%%%%\n");
		test_single("%%%c\n", 'x');

		//noformat special
		test_noarg("");
		test_noarg("\x01\x02\a\v\b\f\r\n");
	return (0);
}
