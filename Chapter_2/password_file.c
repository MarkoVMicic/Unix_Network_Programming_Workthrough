// NOTE(Marko): Password file located at /etc/passwd

// NOTE(Marko): Every line in /etc/passwd has the following format:
// login-name:encrypted-password:user-ID:group-ID:miscellany:login-directory:shell

#include <pwd.h>

// NOTE(Marko): pwd.h provides a structure  that looks like this:

struct passwd
{
    char *pw_name;
    char *pw_password;
    int pw_uid;
    int pw_gid;

    // NOTE(Marko): pw_quota is used only in BSD (and even then, it's not used)
    int pw_quota;

    // NOTE(Marko): Used in System-V only; represents password age
    char *pw_age;

    // NOTE(Marko): pw_comment is not used
    char *pw_comment;

    // NOTE(Marko): pw_gecos is miscellany. God knows why...
    char *pw_gecos

    char *pw_dir;
    char *pw_shell;
};

// NOTE(Marko): The order of these elements may be different, depending on the 
//              system. 

// NOTE(Marko): Functions to obtain matching user-ID or login-name:

struct passwd *getpwuid(int uid);
struct passwd *getpwnam(char *name);

// NOTE(Marko): It's possible that on different systems you use the same 
//              login-name, but are assigned different user-IDs.
// NOTE(Marko): Suppose a client and server are communicating, and a client and 
//              server are passing a login name between them. The client must 
//              obtain the login name using the following code:

struct passwd *pwd;
pwd = getpwuid(getuid());


// NOTE(Marko): After this, the server can use getpwnam() to turn the name into 
//              the user-ID
