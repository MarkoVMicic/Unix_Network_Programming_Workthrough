// NOTE(Marko): debug is an initialized read-write variable. 
int debug = 1;

// NOTE(Marko): progname is an uninitialized read-write variable. 
char *progname;

int main(int argc, char **argv)
{
    // NOTE(Marko): i, ptr are called automatic variables. They are stored on 
    //              the stack while the function main() is executing. 
    int i,
    char *ptr;
    progname = argv[0];

    // NOTE(Marko): The string literal "argc = %d\n" is stored as read-only 
    //              data.
    printf("argc = %d\n", argc);

    for(i = 1; i < argc; i++)
    {
        // NOTE(Marko): storage space allocated by malloc() is stored on the 
        //              heap. 
        ptr = malloc(strlen(argv[i]) + 1);
        strcpy(ptr, argv[i]);
        if(debug)
        {
            // NOTE(Marko): The string literal "%s\n" is stored as read-only 
            //              data. 
            printf("%s\n", ptr);
        }
    }

    return(0);
}

// NOTE(Marko): The machine instructions comprising the following functions are 
//              stored in the text segment of the user context:
//                  - main
//                  - printf
//                  - strlen
//                  - strcpy
//                  - malloc

/* 
    Typical arrangement of user process:

            USER CONTEXT                        KERNEL CONTEXT
        |---------------------|             |---------------------|
        |       STACK         |             |    KERNEL DATA      |
        |- - - - - - - - - - -|             |---------------------|
        |         |           |
        |         |           |
        |         V           |
        |   SHARED MEMORY     |
        |         ^           |
        |         |           |
        |         |           |
        |- - - - - - - - - - -|
        |        HEAP         |
        |---------------------|
        |    UNINITIALIZED    |
        |        DATA         |
        |---------------------|
        |     INITIALIZED     |
        |   READ-WRITE DATA   |
        |---------------------|
        |     INITIALIZED     |
        |    READ-ONLY DATA   |
        |---------------------|
        |       TEXT          |
        |---------------------|


*/