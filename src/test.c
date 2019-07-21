#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libjtoc.h>


typedef struct s_hard
{
	char *title;
	t_vec2 *vector;
	char *text;
	t_fvec2 *fvector;
	t_list *list;
} t_hard;

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
//	t_jnode *root = jtoc_read("./test.json");
//	t_test *t = jtoc_get_raw_data(root);
//	(void)t;
//	if (!t)
//		return 1;
////	printf("%d %d %d", t->a, t->b, t->c);
//	int a = 5;
//	char *ac = (char *)&a;
//	(void)ac;
//	printf("%zu\n", sizeof(t_test));
////	t_test *test = &(t_test){123, 3, "ttt", 1.33, &(t_test2){1, 2}};
////	printf((char *)t, sizeof(t_test));
////	print((char *)test, sizeof(t_test));
////	printf("target:\t%d\t%d\t%s\t%f\t%d\t%d\n", test->a, test->b,
////			test->c, test->d, test->inside->e, test->inside->f);
//	printf("%zu\n", sizeof(t_test2));
//	printf("my:\t\t%d\t%d\t%s\t%f\t%d\t%d\t%d\t%d\n", t->a, t->b, t->c, t->d,
//			t->inside[0]->e, t->inside[0]->f, t->inside[1]->e,
//			t->inside[1]->f);
//	printf("%zu", sizeof(size_t));
	t_jnode *root = jtoc_read("./test.json");
	if (jtoc_write(root, "./test2.json"))
		return (-1);
//	t_hard *t = jtoc_get_raw_data(root);
//	(void)t;
//	if (!t)
//		return 1;
//	printf("%d\n", (int)jtoc_node_get_by_path(root, "list.next")->data);
//	printf("hard done: \n%s\n%d\n%d\n%s\n%f\n%f\n", t->title, t->vector->x,
//			t->vector->y, t->text, t->fvector->x, t->fvector->y);
//	printf("add: %d %zu %s", (*(int *)t->list->content),
//			t->list->content_size, (char *)t->list->next);
	return 0;
}