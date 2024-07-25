#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
int main(int argc , char **argv)
{
    char *line ;
    int fd ;


    fd = open(argv[1] , O_RDONLY) ;


    line = get_next_line(fd);

    while(line)
    {
        printf("%s" , line);
        free(line);
        line = get_next_line(fd);


    }
}