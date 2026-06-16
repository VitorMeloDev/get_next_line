// Source - https://stackoverflow.com/a/68156485
// Posted by love4shells___, modified by community. See post 'Timeline' for change history
// Retrieved 2026-06-16, License - CC BY-SA 4.0

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int fd = open("file.txt", O_RDWR | O_CREAT, 0777);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buf[BUFSIZ+1];
    ssize_t n = 0;
    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        buf[n] = '\0';
        if ((write(STDOUT_FILENO, buf, n)) == -1) {
            perror("write");
            exit(1);        
        }        
    }
    if (n == -1) {
        perror("read");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);    
    }
    exit(0);
}
