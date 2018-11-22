#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 50 
#define RANGE 80 /*  The maximum  size of the command */


char history[10][BUFFER_SIZE]; //buffer to store history  in array, max length is 10 to store.
int count = 0;//initial conut is zero
//history method 
void record()
{
    int i;//variable initalized for loop 
    int j = 0;//variable initalized for loop
    int historyCount = count;//count the history and save in
 
    printf(" history n");
       
    //loop for print history
    for (i = 0; i<10;i++)
    {
        //print  the number of command which is avilable in history
        printf("%d.  ", historyCount);
        while (history[i][j] != '\n' && history[i][j] != '\0')
        {	
		//print command of history
            printf("%c", history[i][j]);
            j++;
        }
        j = 0;
        historyCount--;//decrement in history variable
        if (historyCount ==  0)//check history buffer is complete 
            break;
    }
} 

int setup(char inputBuffer[], char *args[],int *background)
{
if(strcmp(args[0],"history")==0)
        {		
               if(count>0)
		{
		
                record();
		}
}
}

int main(void)
{
    char inputBuffer[RANGE]; /* enter command in buffer  */
    int background; //  background equals 1 if a command is followed by "&" it work like a flag
    char *args[RANGE/2 + 1];/* number of arguments */    
    pid_t pid,tpid;//process id
    int i;
   
    
    while (1) //loop for shell to work again before not taking signals 
    {            
        background = 0; //initially zero
        printf("COMMAND->");
        fflush(stdout);
        if(setup(inputBuffer,args,&background)!=-1) //goes to next commant if first one is correct	
		pid = fork();//creating c child process 
        
        
       	 if (pid == 0)
        	{
            
        
                		printf("Error to execute command :(\n");
        	 }
        
       		 // if background is equal to 0  parent will wait,otherwise move  to the setup() method.
        	else
        	{
            		i++;
           	 	if (background == 0)
           		 {
                		i++;
                		wait(NULL);
           		 }
        	}
   	 }
     
     return 0;

}
