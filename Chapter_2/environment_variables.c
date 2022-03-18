#include <stdio.h>
//////////////////
// UNIX VERSION //
//////////////////
// NOTE(Marko): Unix gives access to a global variable char **environ to allow 
//              you to access the environment variables from anywhere in the 
//              program without having to pass it around as a parameter. 
extern char **environ;

/////////////////////
// WINDOWS VERSION //
/////////////////////
// NOTE(Marko): Unix version also allows for the char **envp
// NOTE(Marko): char **envp is widely supported, but I'm not sure it's 
//              guaranteed by the C spec?
int main(int argc, char **argv, char **envp)
{
    for(int i = 0;
        envp[i] != 0;
        i++)
    {
        printf("%s\n", envp[i]);
    }
    
    return(0);
}

// NOTE(Marko): We can use getenv() to find the specific environment variable 
//              we are looking for, instead of just iterating through the envp/
//              environ list. 

