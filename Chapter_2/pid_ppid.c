// NOTE(Marko): getppid() doesn't exist in Windows
#if _MSC_VER
    #define getppid() 0
                      
#endif

// TODO(Marko): I've no idea what getpid() does in windows. Find out! 

int main(int argc, char **argv)
{
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    return(0);
}