#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void	leaks(void)
{
	system("leaks a.out");
}

int main() {
   char *str;
	atexit(leaks);
   str = readline("minishell: ");
   if (str == NULL) {
      printf("Error reading input\n");
      exit(1);
   }

   printf("You entered: %s\n", str);
   free(str);
   return 0;
}

