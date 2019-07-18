#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libjtoc.h>

typedef struct s_test2
{
	int e;
	int f;
} t_test2;

typedef struct s_test
{
	int a;
	int b;
	char *c;
	float d;
	t_test2	*inside;
} t_test;

//static void	print(char *t, int c)
//{
//	printf("res: \n");
//	for (int i = 0; i < c; i++)
//		printf("%d%d%d%d%d%d%d%d ",
//			   (t[i] >> 7) & 1,
//			   (t[i] >> 6) & 1,
//			   (t[i] >> 5) & 1,
//			   (t[i] >> 4) & 1,
//			   (t[i] >> 3) & 1,
//			   (t[i] >> 2) & 1,
//			   (t[i] >> 1) & 1,
//			   (t[i] >> 0) & 1
//		);
//	printf("\n\n");
//}

int main(void) {
//	t_test *p = &(t_test){1, "faf", 23};
//	char *cp = (char *)p;
//	t_test *p;
//	printf("%lu\n", sizeof(*p));
//	for (int i = 0; i < 24; ++i)
//		printf("%d ", cp[i]);
//	printf("\n");
	t_jnode *root = jtoc_read("./test.json");
	t_test *t = jtoc_get_raw_data(root);
	(void)t;
	if (!t)
		return 1;
//	printf("%d %d %d", t->a, t->b, t->c);
	int a = 5;
	char *ac = (char *)&a;
	(void)ac;
	printf("%zu\n", sizeof(t_test));
	t_test *test = &(t_test){123, 3, "ttt", 1.33, &(t_test2){1, 2}};
//	printf((char *)t, sizeof(t_test));
//	print((char *)test, sizeof(t_test));
	printf("target:\t%d\t%d\t%s\t%f\t%d\t%d\n", test->a, test->b,
			test->c, test->d, test->inside->e, test->inside->f);
	printf("my:\t\t%d\t%d\t%s\t%f\t%d\t%d\n", t->a, t->b, t->c, t->d,
			t->inside->e, t->inside->f);
	return 0;
}