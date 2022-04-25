int main(int argc, char **argv)
{
    int childpid;

    if((childpid = fork()) == -1)
    {
        perror("can't fork");
        exit(1);
    }
    else if(childpid == 0)
    {
        // NOTE(Marko): This is the child process.
        printf("child process. child pid = %d, parent pid = %d\n", 
               getpid(), getppid());
        exit(0);
    }
    else
    {
        // NOTE(Marko): This is the parent process. 
        printf("parent process. child pid = %d, parent pid = %d\n",
               childpid, getpid());
        exit(0);
    }

    return(0);
}
