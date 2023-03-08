#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

void	test_function()
{
	printf("I am here in test function\n");
}

void	*print_stuff()
{
	void	*str;
	printf("hello there\n");
	// sleep(2);
	test_function();
	return str;
}

int	main(void)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, &print_stuff, NULL);
	pthread_create(&t2, NULL, &print_stuff, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("I am here in main\n");
}