#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> /* malloc */
#include <string.h>
#include <sys/wait.h>

int sendinfo_subproc(int fd, char *info);
int readinfo_baseproc(int fd, char *infobuf, int n);
void mysig(int);

int signal_count = 0;

char *filename;
char *copied_filename;
int main(int argc, char* argv[]) {
    char *system_cmd;
    int stat;

    struct sigaction msig;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    msig.sa_mask = mask;
    msig.sa_handler = mysig;
    sigaction(SIGINT, &msig, 0);

    if(argc <= 1) {
        fprintf(stderr, "Provide the name of file\n");
        exit(1);
    }
    filename = argv[1];

    /* Designate free space for copied filename
     * +5 characters -- '_copy'
     */
    copied_filename = (char *)malloc(sizeof(char) * (strlen(filename) + 5));
    sprintf(copied_filename, "%s_copy", filename);

    /* Create a copy of file 'filename':
     * First we create a shell commandline as 
     * cp 'filename' 'copied_filename'
     * 
     * And fire up a system!
     * +20 for shell command
     */
    system_cmd = (char *)malloc(sizeof(char) * ((strlen(filename) + strlen(copied_filename) + 20)));
    sprintf(system_cmd, "cp %s %s", filename, copied_filename);

    /* Finally copy file! */
    if(system(system_cmd) != 0) {
        fprintf(stderr, "An error occured while copying file\n");
        exit(1);
    }
    
    /* Create pipe 
     * fd[0] -- read from pipe
     * fd[1] -- write to pipe 
     */
    int fd[2];
    if(pipe(fd) != 0) {
        fprintf(stderr, "Failed to create a pipe\n");
        exit(1);
    }

    if(fork() == 0) {
        /* SUBprocess */
        close(fd[1]);
        char readbuf[8192]; /* 8192 is the max num of bytes that can be sent through pipe */

        /* Receive the info from base process */
        readinfo_baseproc(fd[0], readbuf, 8191);

        /* Compare two files using diff utility
         * If files are identical, diff will return 0
         */
        char *diff_str = (char *)malloc(sizeof(char) * (strlen(readbuf) + 20));
        sprintf(diff_str, "diff %s", readbuf);

        if(system(diff_str) == 0) {
            /* No differences were found */
            /* Then we remove original file */
            char *rm_str = (char *)malloc(sizeof(char) * (strlen(filename) + 20));
            sprintf(rm_str, "rm %s", filename);

            system(rm_str);
            free(rm_str);
        }

        free(diff_str);
        exit(0);
    } else {
        /* BASE process */
        close(fd[0]);

        /* Prepare the information to be sent to child process */
        char *sendinfo = (char *)malloc(sizeof(char) * (strlen(filename) + strlen(copied_filename) + 5));
        sprintf(sendinfo, "%s %s", filename, copied_filename);

        sendinfo_subproc(fd[1], sendinfo);
        free(sendinfo);

        /* Wait for subprocess to finish */
        wait(&stat);
        
    }
    
    sleep(15);
    sleep(15);
    sleep(15);

    /* And free dynamically allocated memory */
    free(system_cmd);
    free(copied_filename);
    return 0;
}

int sendinfo_subproc(int fd, char *info) {
    if(write(fd, info, sizeof(char) * strlen(info)) == (-1)) {
        fprintf(stderr, "Failed to write info to subprocess\n");
        return 1;
    }
    return 0;
}

int readinfo_baseproc(int fd, char *infobuf, int n) {
    if(read(fd, infobuf, n) == (-1)) {
        fprintf(stderr, "Failed to read info from baseproc\n");
        return 1;
    }
    return 0;
}

/* Signal handler */
void mysig(int a) {
    signal_count++;
    if (signal_count == 1) {
        printf("Caught first SIGINT: renaming %s to %s\n", copied_filename, filename);
        char *act = (char *)malloc(sizeof(char) * (strlen(filename) + strlen(copied_filename) + 20));
        sprintf(act, "mv %s %s", copied_filename, filename);

        system(act);
        free(act);
    }
}
