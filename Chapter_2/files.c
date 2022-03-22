#include <sys/types.h>
#include <sys/stat.h>

// NOTE(Marko): /sys/stat.h defines the following struct
struct stat
{
    // NOTE(Marko): /sys/types.h defines the types we see below:

    // NOTE(Marko): st_mode is the file type, and file access permissions 
    ushort st_mode;

    // NOTE(Marko): i-node number.
    ino_t st_ino;

    // NOTE(Marko): ID of device that contains a directory entry for this file
    dev_t st_dev;

    // NOTE(Marko): Number of links
    short st_nlink;

    ushort st_uid;
    ushort st_gid;

    // NOTE(Marko): ID of device for character special or block special files
    dev_t st_rdev;

    // NOTE(Marko): file size in bytes
    off_t st_size;

    // NOTE(Marko): a = access
    //              m = modified
    //              c = status change
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;

    //
    // NOTE(Marko): 4.3 BSD ONLY:
    //
    // NOTE(Marko): optimal block size for filesystem operations
    long st_blksize;

    // NOTE(Marko): actual number of blocks allocated. 
    long st_blocks;
};

// NOTE(Marko): both stat() and fstat() return 0 on success, and -1 on failure.
//              buf represents the stat struct memory passed into the function 
//              which gets filled out. 
int stat(char *pathname, struct stat *buf);
// NOTE(Marko): fildes = file descriptor = integer assigned by kernel when file 
//              is opened for I/O
int fstat(int fildes, struct stat *buf);

// NOTE(Marko): stat.st_mode is a bitfield. It defines
//                  - file access permissions (9 bits)
//                  - set-user-ID bit
//                  - set-groud-ID bit
//                  - sticky bit

// NOTE(Marko): /sys/stat.h defines the following for for the file access 
//              permissions (9 bits) 
#define S_IFMT      0170000     // Type of file
#define S_IFREG     0100000     // Regular
#define S_IFDIR     0040000     // Directory
#define S_IFCHR     0020000     // Character special
#define S_IFBLK     0060000     // Block special
#define S_IFLNK     0120000     // symbolic link -- BSD only
#define S_IFSOCK    0140000     // socket -- BSD only
#define S_IFIFO     0010000     // FIFO -- System V only
