/*********************************************************************
   Program  : miniShell                   Version    : 1.3
 --------------------------------------------------------------------
   skeleton code for linix/unix/minix command line interpreter
 --------------------------------------------------------------------
   File			: minishell.c
   Compiler/System	: gcc/linux

********************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define NV 20			/* max number of command tokens */
#define NL 100			/* input buffer size */
char            line[NL];	/* command input buffer */


/*
	shell prompt
 */

void prompt(void)
{
  //fprintf(stdout, "\n msh> "); //submission purpose
  fflush(stdout);

}


int main(int argk, char *argv[], char *envp[])
/* argk - number of arguments */
/* argv - argument vector from command line */
/* envp - environment pointer */

{
  int             frkRtnVal;	/* value returned by fork sys call */
  //int             wpid;		/* value returned by wait */
  char           *v[NV];	/* array of pointers to command line tokens */
  char           *sep = " \t\n";/* command line token separators    */
  int             i;		/* parse index */
  int inBack = 0; //Check for background
  int bgCount = 0;

  /* prompt for and process one command line at a time  */

  while (1) {			/* do Forever */
    prompt();
    fgets(line, NL, stdin);
    fflush(stdin);

    inBack = 0; //Reset bg state

    if (feof(stdin)) {		/* non-zero on EOF  */

      // fprintf(stderr, "EOF pid %d feof %d ferror %d\n", getpid(),
	    //   feof(stdin), ferror(stdin)); //submission purposes
      exit(0);
    }
    if (line[0] == '#' || line[0] == '\n' || line[0] == '\000')
      continue;			/* to prompt */

    v[0] = strtok(line, sep);
    for (i = 1; i < NV; i++) {
      v[i] = strtok(NULL, sep);
      if (v[i] == NULL)
	break;
    }
    /* assert i is number of tokens + 1 */

    for(int i=0 ; i<NL ; i++) {
      if(line[i] == '&') {
        inBack = 1;
        //line[i] = NULL;
      }
    }
  if(!strcmp(v[0] , "cd")) {
    char currentDir[256];
    //char dir[20];



    if(chdir(v[1]) != 0) {
      perror("cd failed");
    }

    if(getcwd(currentDir , sizeof(currentDir)) == NULL) {
        perror("getcwd() error");
    } else {
        //printf("Currnet directory is: %s\n", currentDir);
    };


  } else if(inBack == 1) {
      /* fork a child process to exec the command in v[0] */
    bgCount++;
    switch (frkRtnVal = fork()) {
    case -1:			/* fork returns error to parent process */
        {
      perror("Fork failed");
    break;
        }
    case 0:			/* code executed only by child process */
        {
      if(execvp(v[0], v)) {
        perror("execvp from background failed");
      }; // Can run an executable file
      //kill(getppid() , SIGTERM);
      break;
        }
    default:			/* code executed only by parent process */
      printf("[%d] %d\n", bgCount , getpid());
      wait(0);
      printf("[%d]+ Done %s %s\n", bgCount , v[0] , v[1]);
        {
      //wpid = wait(0);
    //printf("%s background done \n", v[0]); //submission purposes
    break;
        }
    }				/* switch */

  } else { //Default case will execute the command
    switch (fork())
    {
    case -1:
      perror("Fork for main process failed");
      break;
    
    case 0:
      if(execvp(v[0], v)){ 
        perror("execvp failed");
      };
      break;

    default:
      continue;
    }

    //printf("%s done \n", v[0]); //submission purposes
    break;
  }       //inBack
    
  }				/* while */
  return 0;
}				/* main */
