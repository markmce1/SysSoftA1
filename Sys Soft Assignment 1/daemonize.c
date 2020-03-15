#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/wait.h>
#include <time.h>
#include "backup.h"
#include "skeleton.h"

int main()
{
    daemonskeleton();
    
    time_t current;
    struct tm current_time;
    double seconds;
    
    time(&current);
    current_time = *localtime(&current);
    current_time.tm_hour = 11;
    current_time.tm_min = 47;
    current_time.tm_sec = 0;
   
    syslog (LOG_NOTICE, "First daemon started.");

    while (1)
    {
        sleep (1);
        time(&current);
        seconds = difftime(current,mktime(&current_time));
        if(seconds == -31)
        {
            printf("System will begin running process");
        }
        if(seconds > -31 && seconds < 0)
        {
            printf("\n%.f", seconds);
        }
        if (seconds == 0)
        {
            //Create Child Process
            int pid = fork();
            
            if (pid > 0)
            {
                printf("This is the parent process\n");
            }
            else if (pid == 0)
            {
                printf("This is the child process\n");
                pid = fork();
                if( pid > 0)
                {
                    char *argv[] = {"chmod","000", "var/www/html",NULL};
                    execvp("chmod",argv);
                    printf("File Locked\n");
                }
                else if( pid == 0)
                {
                    sleep(1);
                    backup();
                    printf("Files transfering from Live to backup\n");
                    update();
                    printf("Files coming from Dev to live");
                    char *argx[] = {"chmod","777", "var/www/html",NULL};
                    execvp("chmod",argx);
                    printf("File unlocked\n");
                }
            }
        }
    }
    
    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();
    
    return EXIT_SUCCESS;
}

