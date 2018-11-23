#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 50 
#define RANGE 80 /*  The maximum  size of the command */


char history[10][BUFFER_SIZE]; //buffer to store history  in array, max length is 10 to store.
int count = 0;//initial conut is zero
void record()
{
    int i;//variable initalized for loop 
    int j = 0;//variable initalized for loop
    int historyCount = count;//count the history and save in
 
    printf(" history of Shell command :\n");
       
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
        printf("\n");//after printing history command move to next line
        j = 0;
        historyCount--;//decrement in history variable
        if (historyCount ==  0)//check history buffer is complete 
            break;
    }
    printf("\n");
} 

int setup(char inputBuffer[], char *args[],int *background)
{

   	int length; // # of chars in command line
    	int i;     // loop index for inputBuffer
    	int go;  // index of beginning of next command
    	int ct = 0; // index of where to place the next parameter into args[]
    	int hist;
		
 	length = read(STDIN_FILENO, inputBuffer, RANGE);	
 
   
    go = -1;
    if (length == 0)
        exit(0);   //end of command
    if (length < 0)
    {
        printf("Command not read\n");
        exit(-1);  //terminate
    }
	
   //examine each character
    for (i=0;i<length;i++)
    {
        switch (inputBuffer[i])
        {
            case ' ':
            case '\t' :               // check spaces
                if(go != -1)
                {
                    args[ct] = &inputBuffer[go];    
                    ct++;
                }
                inputBuffer[i] = '\0'; // terminate string
                go = -1;
                break;
                
            case '\n':                 //last char 
                if (go != -1)
                {
                    args[ct] = &inputBuffer[go];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; // no more args
                break;
                
            default :           
                if (go == -1)
                    go = i;
              }
    }
    args[ct] = NULL; //if the input line was > 80
 
      if(strcmp(args[0],"history")==0)
        {		
               if(count>0)
		{
		
                record();
		}
		else
		{
		printf("\nList is Empty\n");
		}
		return -1;
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
        if(setup(inputBuffer,args,&background)!=-1) //goes to next commant if first one is correct	{
		pid = fork();//creating c child process 
        
        	
        
       		 else if (pid == 0)
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