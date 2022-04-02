char CommandBuffer[1024];
char DirectoryName[1024];

// NOTE(Marko): sprintf() is from the standard I/O library. 
sprintf(CommandBuffer, "mkdir %s", DirectoryName);

// NOTE(Marko): int system(char *string); is supplied by the C standard 
//              library, and returns 0 upon success. 
if(system(CommandBuffer) != 0)
{
    // ERROR HANDLING
}