#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LIVE "/var/www/html/live"
#define BACKUP "/var/www/html/backup"
#define DEV "/var/www/html/dev/index.html"

void backup()
{
        printf("Backing up live site...\n");
        system("rsync -avu " LIVE " " BACKUP);
        printf("Backup complete!\n");
}
void update()
{
        printf("updating live site...\n");
        remove("/var/www/html/live/index.html");
        system("rsync -avu " DEV " " LIVE);
        printf("Live update complete!\n");
}