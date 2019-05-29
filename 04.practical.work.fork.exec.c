#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int forkval = fork();
	if(forkval == 0)
	{
		printf("Hello, I'm a child :3. I'm launching ps -ef\n");
		char *args[] = {"ps","-ef",NULL};
		execvp("ps",args);
	} 
	else{
		printf("Parent hereeee!!\n");
		wait(NULL);
		forkval = fork();
		if (forkval == 0)
		{
			printf("Hey, I'm a child, launching free -h\n");
			char *args[]= { "free", "-h" , NULL};
			execvp("free", args);
		}
		else
		{
			printf("I'm Parent!!\n");
			wait(NULL);
		}
	}

	return 0;
}