#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main()
{
  int status, pid1, pid2;
  printf("Main before fork()\n");
  pid1 = fork();
  if(pid1 == 0)
  {
    printf("I am the first child\nNow run ps -ef\n");
    char *args[]= {"/bin/ps", "-ef", NULL};
    execvp("/bin/ps", args);
    printf("Finished runing ps -ef\n");
  }
  else 
  {
    waitpid(pid1, NULL, 0);
    printf("I am parent after fork, child is %d\n\tContinue to create another child\n", pid1);
    pid2 = fork();
    if(pid2 == 0)
    {
      printf("I am the second child\nNow run free -h\n");
      char* args[] = {"/usr/bin/free", "-h", NULL};
      execvp("/usr/bin/free", args);
      printf("Finished running free -h\n");
    }
   }
   else 
   {
      printf("I am parent after 2 forks, second child is %d\nDone.\n", pid2);
      waitpid(pid2, NULL, 0);
   }
  return 0;
}
