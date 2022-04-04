#include <fcntl.h>

/*
    NOTE(Marko): For open(), we note the following points:
                
                    - In early versions of Unix, there was no optional third 
                      argument. oflag was specified as a binary constant:
                        - 0 -> open for reading
                        - 1 -> open for writing
                        - 2 -> open for both reading and writing

                    - Later on, symbolic representations for oflag were \
                      allowed, and like any flag in C, could be combined using |
                        - O_RDONLY  -> Open for reading only
                        - O_WRONLY  -> Open for writing only
                        - O_RDWR    -> Open for reading and writing
                        - O_NDELAY  -> Do not block on open or read or write
                        - O_APPEND  -> On each write, append to end of file
                        - O_CREAT   -> Create the file if it doesn't exist
                        - O_TRUNC   -> If file exists, truncate length to 0
                        - O_EXCL    -> Error if O_CREAT and file already exists

                    - Most implementations define 
                        - O_RDONLY == 0
                        - O_WRONLY == 1
                        - 0_RDWR   == 2

                    - The third argument, mode, is optional, and required only 
                      if O_CREAT is specified. 

                    - open() returns a file descriptor if successful, otherwise 
                      -1 is returned. 
*/
int open(char *pathname, int oflag [, int mode]);


/*
    NOTE(Marko): For creat(), we note the following:
                    
                    - creat() returns file descriptor if successful, otherwise 
                      -1 is returned. 

                    - mode specifies the low-order 12 bits of file access mode 
                      word.
                        -  This value is then further modified by the low-order 
                           9 bits of the file mode creation mask (see umask 
                           system call:
                                int umask(int cmask);

                    - File's owner ID is set to the effective user ID of the 
                      process.

                    - File's group ID is set to the effective group ID of the 
                      process. 

                    - If the file already exists, then the file's length is 
                      truncated to 0, and the file's mode and owners are not 
                      changed. 
*/
int creat(char *pathname, int mode);


/*
    NOTE(Marko): When a process terminates, all open files are automatically 
                 closed by the kernel. 
*/
int close(int fildes);


// NOTE(Marko): In network programming, it's important to be prepared for a 
//              read() or write() to return some positive value < nbytes. This 
//              can take place because of the buffering that happens in the 
//              network. 

/*
    NOTE(Marko): If read is successful, it returns the number of bytes that was 
                 read. This can be less than the nbytes that was requested. If 
                 the end of file is encountered, zero is returned. If an error 
                 is encountered, -1 is returned. 

                 read() can only read up to INT_MAX-2 bytes, because it must 
                 return an int, and 0 and -1 are reserved.
                 
                 To read more than INT_MAX/2 bytes, nbytes is used as an 
                 unsigned int. Take note that the int returned is signed. 
*/
int read(int fildes, char *buff, unsigned int nbytes);


/*
    NOTE(Marko): Returns actual number of bytes that were written 
                 (usually nbytes number). 
                 Returns -1 upon error.

                 write() can only read up to INT_MAX-2 bytes, because it must 
                 return an int, and 0 and -1 are reserved. 

                 To write more than INT_MAX/2 bytes, nbytes is used as an 
                 unsigned int. Take note that the int returned is signed. 
*/
int write(int fildes, char *buff, unsigned int nbytes);


/*
    NOTE(Marko): - Every open file has a "current byte position" associated 
                   with it, measured in number of bytes from the start of the 
                   file. 

                 - creat() sets the current byte position to the beginning of 
                   the file.

                 - open() sets the current byte position to the beginning of 
                   the file, unless the O_APPEND is specified.

                 - read() and write() update the current byte position by the 
                   number of bytes read or written.

                 - Before read() or write() is call, it is possible to set the 
                   current byte position using lseek()

                 - offset and whence are set as follows:
                    - if whence == 0, then the file's position is set to offset 
                      bytes from the beginning of the file. In this case, 
                      offset > 0.  
                    - if whence == 1, then the file's position is set to the 
                      current byte position plus the offset. In this case, 
                      offset can be positive, zero, or negative. 
                    - If whence == 2, then the file's position is set to the 
                      size of the file plus the offset. In this case, offset 
                      can be positive, zero, or negative. 

                 - offset can be greater than thew current file size, in which 
                   chase the next write to the file will extend the file. 

                 - A file's current byte position >= 0.

                 - lseek() returns the long integer byte offset of the file, or 
                   -1 if an error occured. 
*/
long lseek(int fildes, long offset, int whence);


/*
    NOTE(Marko): - dup() returns a new file descriptor that shares the 
                   following with the original filedes:
                    - both refer to the same file or pipe.
                    - the access mode of the new file descriptor is the same as 
                      that of the original i.e. read, write, or read/write. 
                    - both file descriptors share the same file position. 

                - It is guaranteed that the new file descriptor return by dup() 
                  is the lowest numbered available file descriptor. 

                - 4.3BSD provides a variant, dup2(), which allows 
                  specificiation of the new descriptor value. If this value is 
                  already in use, it is released as if a close() had been done. 
*/  
int dup(int filedes);
int dup2(int oldfiledes, int newfiledes); // 4.3BSD only

// NOTE(Marko): The main difference between fcntl() and ioctl() is that fcntl() 
//              is inteded for use on any open file, while ioctl() is intended 
//              for device-specific operations. 
/*
    NOTE(Marko): - fcntl() changes the properties of a file that is already 
                   open.

                 - cmd is a flag, and arg is an argument to that flag, where 
                   applicable. The allowable cmd (and args, where applicable) 
                   are as follows:
                    - F_DUPFD -- Duplicates the file descriptor, similar to the 
                                 dup() system call. Unlike dup(), however, this 
                                 system call allows us to specify the lowest 
                                 number that the new file descriptor is to 
                                 assume (i.e. arg sets a lower bound on the new file descriptor's value, which is an int). 
                                 This causes fcntl() to return the value of the 
                                 new file descriptor. 
                    - F_SETFD -- Set the close-on-exec flag for the life to the 
                                 low-order bit of arg. 
                                 - If the low-order bit of arg is set, the file 
                                   is closed on an exec system call. 
                                 - If the low-order bit of arg is NOT set, the 
                                   file remains open across an exec system 
                                   call. 
                    - F_GETFD -- Causes fcntl() to return the close-on-exec 
                                 flag for the file as 
                    - F_SETFL -- Sets the status flags for this file to the 
                                 value of arg. A valid arg value can be formed 
                                 by using | to string together the following 
                                 values (i.e. or'ing them):
                                    *******************
                                    ** SYSTEM V ONLY **
                                    *******************
                                    - O_NDELAY -- Set the file for nonblocking 
                                                  I/O. 
                                    - O_APPEND -- Have all writes append to the 
                                                  end of this file. 
                                    - O_SYNC   -- Enable the synchronous write 
                                                  option. 

                                    **************
                                    ** BSD ONLY **
                                    **************
                                    - FNDELAY  -- Set the file for nonblocking 
                                                  I/O. This option is only 
                                                  available for terminals and 
                                                  sockets. 
                                    - FAPPEND  -- Have all writes append to the 
                                                  end of this file. 
                                    - FASYNC   -- Enable the SIGIO signal to be 
                                                  sent to the process group 
                                                  when I/O is possible. This 
                                                  option is only available for 
                                                  terminals and sockets. 
                    - F_GETFL -- Causes fcntl() to return the status flags for 
                                 this file as the value of the system call. 

                    **************
                    ** BSD ONLY **
                    **************
                    - F_GETOWN -- Return the value of the process ID or the 
                                  process group ID that is set to receive the 
                                  SIGIO and SIGURG signals. A positive return 
                                  value indicates a process ID, and a negative 
                                  return value (other than -1) indicates the 
                                  negative of the process group ID. 
                    - F_SETOWN -- Set the process ID or the process group ID to 
                                  receive the SIGIO and SIGURG signals to the 
                                  value of arg. A positive value of arg 
                                  specifies a process ID, and a negative value 
                                  of arg specifies a process group ID. 

                    *******************
                    ** SYSTEM V ONLY **
                    *******************
                    The following commands are for record locking. 
                    - F_GETLK
                    - F_SETLK
                    - F_SETLKW
*/
int fcntl(int filedes, int cmd, int arg);


/*
    NOTE(Marko): - ioctl() is also used the change the bahavior of an opn file. 

                 - In BSD, sys/ioctl.h contains the definitions for request.
                 
                 - In System V, different header files contain different 
                   possible definitions for request, depending on the desired 
                   operation. (e.g. termio.h contains request values for 
                   terminal operations.)
                 
                 - ioctl() is usually used to change terminal characteristics: 
                   baud rate, parity, #bits per char etc. 
                 
                 - Intended for device-specific operations. 
*/
#include <sys/ioctl.h> // BSD Only
int ioctl(int filedes, unsigned long request, char *arg);
