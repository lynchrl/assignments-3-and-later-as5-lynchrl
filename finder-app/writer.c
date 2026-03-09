/**
 * writer writes the second string argument to the file specified by the first string argument.
 * If the file does not exist, it will be created. If the file already exists, it will be overwritten.
 * The target directory must already exist.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    // Check for correct number of arguments (2 + program name)
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <filename> <string>\n", argv[0]);
        syslog(LOG_USER | LOG_ERR, "Invalid number of arguments: %d", argc);
        return 1;
    }

    const char *filename = argv[1];
    const char *string = argv[2];

    // O_CREAT to create the file if it doesn't exist.
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error opening file");
        syslog(LOG_USER | LOG_ERR, "Error opening file: %s", filename);
        return 1;
    }

    ssize_t res = write(fd, string, strlen(string));
    if (res == -1)
    {
        perror("Error writing to file");
        syslog(LOG_USER | LOG_ERR, "Error writing to file: %s", filename);
        return 1;
    }
    close(fd);
    syslog(LOG_USER | LOG_DEBUG, "Writing <%s> to <%s>", string, filename);

    return 0;
}