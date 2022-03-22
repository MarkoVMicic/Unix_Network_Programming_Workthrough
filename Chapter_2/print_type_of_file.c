#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    struct stat statbuffer;
    char *ptr;
    for(int i = 0; i < argc; i++)
    {
        printf("%s: ", argv[i]);
        
        // NOTE(Marko): int stat(char *filename, struct stat *buffer) returns 0 
        //              on success, -1 on failure. 
        if(stat(argv[i], &statbuffer) < 0)
        {
            err_sys("fstat error");
        }

        // NOTE(Marko): bitwise AND the sm_mode of the stat struct with S_IFMT 
        //              to extract the file type. 
        switch(statbuffer.sm_mode & S_IFMT)
        {
            case S_IFREG:
            {
                ptr = "regular";
            } break;
            case S_IFDIR:
            {
                ptr = "directory";
            } break;
            case S_IFCHR:
            {
                ptr = "character special";
            } break;
            case S_IFBLK:
            {
                ptr = "block special";
            } break;
            // NOTE(Marko): The rest are not necessarily defined on all Unix 
            //              systems so we need to check that the #define 
            //              actually exists to prevent compilation errors.
#ifdef S_IFLNK
            case S_IFLNK:
            {
                ptr = 
            } break;
#endif

#ifdef S_IFSOCK
            case S_IFSOCK:
            {
                ptr = 
            } break;
#endif

#ifdef S_IFIFO
            case S_IFIFO:
            {
                ptr = 
            } break;
#endif
            default
            {

            }
        }
        printf("%s\n", ptr);
    }
    return(0);
}