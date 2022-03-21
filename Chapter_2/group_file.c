#include <grp.h>

// NOTE(Marko) grp.h contains the following structure: 
struct group
{
    char *gr_name;
    char *gr_password;
    int gr_gid;

    // NOTE(Marko): Array of pointers to user list. 
    char **gr_mem;

};

// NOTE(Marko): Get group using a real group ID
struct group *getgrgid(int gid);

// NOTE(Marko): Get group using the group name. 
struct group *getgrnam(char *name);

// NOTE(Marko): Both return NULL if group is not found. 
