#include <signal.h>

// NOTE(Marko): signal() is a function that returns a pointer to a function 
//              that returns an int.

// NOTE(Marko): The func argument specifies the address of the function that 
//              doesn't return anything (i.e. a void function)

// NOTE(Marko): The func argument has two possible special values:
//                  1) SIG_DFL -> specifies that the signal is to be handled in 
//                                the default way. 
//                  2) SIG_IGN -> specifies that the signal is to be ignored. 

// NOTE(Marko): The signals SIGIO, SIGPOLL, and SIGURG require the process to 
//              execute additional system calls if it wants to catch the 
//              signal. 

// NOTE(Marko): The signal system call always returns the previous value of 
//              func for the specified signal.
// NOTE(Marko): signal() is a function that returns a pointer to a function 
//              that takes in an int and returns and int. 
// NOTE(Marko): the func parameter is a pointer to a function that takes an 
//              int, and doesn't return anything. 
int (*signal(int sig, void (*func) (int))) (int);

// NOTE(Marko): Specifies that SIGUSR1 signal is to be ignored.
signal(SIGUSR1, SIG_IGN);

// NOTE(Marko): myintr() is called when SIGINT is generated.
extern void myintr(); 

if(signal(SIGINT, SIG_IGN) != SIG_IGN)
{
    signal(SIGINT, myintr); 
}

//
// NOTE(Marko): Specific Signals
//

/*
    NOTE(Marko): Signal list:
                    - SIGALRM
                    - SIGBUS
                    - SIGCLD (aka SIGCHLD)
                    - SIGCONT
                    - SIGEMT
                    - SIGFPE
                    - SIGHUP
                    - SIGILL
                    - SIGINT
                    - SIGIO
                    - SIGIOT
                    - SIGKILL
                    - SIGPIPE
                    - SIGPOLL
                    - SIGPROF
                    - SIGPWR
                    - SIGQUIT
                    - SIGSEGV
                    - SIGSTOP
                    - SIGSYS
                    - SIGTERM
                    - SIGTRAP
                    - SIGTSTP
                    - SIGTTIN
                    - SIGTTOU
                    - SIGURG
                    - SIGUSR1
                    - SIGUSR2
                    - SIGVTALRM
                    - SIGWINCH
                    - SIGXCPU
                    - SIGXFSZ
*/

/////////////
// SIGALRM //
/////////////
// NOTE(Marko): alarm() specifies the number of seconds to elapse before the 
//              kernel is to send the process a SIGALRM signal. 
unsigned int alarm(unsigned int sec);

// NOTE(Marko): sleep() function usually sets a SIGALRM signal, which it then 
//              also catches. 
unsigned int sleep(unsigned int sec);

/////////////////
// SIGNAL MASK // (BSD)
/////////////////
int mask;
mask = sigmask(SIGQUIT) | sigmask(SIGINT);

/////////////////////////
// SIGNAL (UN)BLOCKING //
/////////////////////////
// NOTE(Marko): Can block using a signal mask
// NOTE(Marko): Adds mask to set of signals that are currently blocked.
// NOTE(Marko): sigblock() returns the signal mask that was in effect before it 
//              was called. 
int sigblock(int mask);

// NOTE(Marko): Counterintuitively, you can unblock a signal by sending a mask 
//              to sigsetmask that does NOT contain the signal you want to 
//              unblock. That's because sigsetmask just sets the mask afresh, 
//              and the mask represents the set of blocked signals. 
int sigsetmask(int mask); 

// 
// EXAMPLE: Selective Signal Blocking (BSD)
//
// NOTE(Marko): Here we block signals only for a critical piece of code, which 
//              we don't want to have interrupted, for example. 
int oldmask;
// NOTE(Marko): Remember that sigblock() returns the blocked signals BEFORE it 
//              was called, hence the name oldmask
oldmask = sigblock(sigmask(SIGQUIT) | sigmask(SIGINT));
/*
    Critical code goes here
*/
sigsetmask(oldmask);

// Equivalent in System V:
sighold(SIGQUIT);
sighold(SIGINT);
/*
    Critical code goes here
*/
sigrelse(SIGQUIT);
sigrelse(SIGINT);

////////////////////////////////////////////
// BSD race condition handling of signals //
////////////////////////////////////////////
/*
    NOTE(Marko): Without reliable signal handling, we would write something 
                 like this:

                    // NOTE(Marko): flag is a global variable set when SIGINT 
                    //              occurs.
                    int flag = 0;

                    ...

                    for(;;)
                    {
                        while(flag == 0)
                        {
                            // NOTE(Marko): Wait for the signal to occur
                            pause();
                        }
                        // NOTE(Marko): Once we exit the above while loop, the 
                        //              signal has occured, and we need to then 
                        //              process it here
                    }

                 There is an error here. If the signal occurs after the test of 
                 the flag variable, but before the call to pause(), the signal 
                 can be lost.
*/

// NOTE(Marko): flag is a global variable set when SIGINT occurs. 
int flag = 0;

for(;;)
{
    // NOTE(Marko): Blocking the SIGINT signal BEFORE testing the flag variable 
    //              prevents the race condition mentioned above from occurring. 
    sigblock(sigmask(SIGINT));

    while(flag == 0)
    {
        // NOTE(Marko): Wait for the signal to occur.
        // NOTE(Marko): sigpause() is a system call that sets a new signal mask 
        //              (arugment of 0) and waits for a signal to occur. 
        // NOTE(Marko): sigpause() combines the unblocking of the signal and 
        //              the pause into a single system call, to prevent race 
        //              conditions between two separate system calls. 
        sigpause(0);
    }
    // NOTE(Marko): Once we exit the above while loop, the signal has occured, 
    //              and we need to then process it here
}

/////////////////////////
// System V equivalent //
/////////////////////////

// NOTE(Marko): flag is a global variable set when SIGINT occurs. 
int flag = 0;

for(;;)
{
    sighold(SIGINT);
    while(flag == 0)
    {
        // NOTE(Marko): Wait for the signal to occur, and simultaneously 
        //              unblock it when it does occur. 
        sigpause(SIGINT);
    }
}

// NOTE(Marko): sigpause() differs between BSD and System V in its argument. 
//                  - in BSD, it sets a signal mask (can handle multiple 
//                    signals at once).
//                  - in System V, it can only be used with a single signal. 
