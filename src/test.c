#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_test
{
	int f_int;
	char *f_string;
	float f_float;
} t_test;

typedef struct s_int
{
	int a;
} t_int;

typedef struct s_float
{
	float a;
} t_float;

typedef struct s_string
{
	char *a;
} t_string;

typedef struct s_object
{
	t_string *a;
} t_object;

int main(void) {
	t_test *t = &(t_test){256, "ogo00000000000go", 3.784000001f};
	t_test *t2;
	char *t_int = (char *)malloc(sizeof(int) + sizeof(char *) + sizeof(float));
	char *res = t_int;
	t2 = (t_test *)res;
	memcpy(t_int, &t->f_int, 4);
	t_int += 8;
	char *tmp = (char *)malloc(6);
	memcpy(tmp, &t->f_string, 6);
	memcpy(t_int, tmp, sizeof(char *));
	t_int += 8;
	memcpy(t_int, &t->f_float, 4);
	printf("t1 -> size: %zu\n  f_int: %d\n  f_string: %s\n  f_float: %f\n", sizeof(*t), t->f_int, t->f_string, t->f_float);
	printf("t2 -> size: %zu\n  f_int: %d\n  f_string: %s\n  f_float: %f\n", sizeof(*t2), t2->f_int, t2->f_string, t2->f_float);
	return 0;
}