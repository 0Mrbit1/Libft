#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//#define BUFFER_SIZE 42

int ft_strlen(char *str)
{
    int i ;

    i = 0 ;
    while(str[i])
        i++;
    return i;
}

char *ft_strjoin(char *chunk1 , char *chunk2)
{
    int i ; 
    int j;
    char *new_str; 

    i = 0;
    j = 0;
    new_str = (char*)malloc( sizeof(char)  * ( ft_strlen(chunk1) + ft_strlen(chunk2)  +1 )    ) ;
    if(!new_str)
        exit(1); 
    if (!new_str)
        exit(1);
    if (!new_str)
        return NULL; 
    while(chunk1[i])
    {
        new_str[j] = chunk1[i] ; 
        j++;
        i++;
    }
    i = 0 ;
    while(chunk2[i])
    {
        new_str[j] = chunk2[i] ; 
        i++;
        j++;
    }

    new_str[j] = '\0' ;
    free(chunk1) ;
    free(chunk2) ;
    return new_str ;
}

char *ft_strdup(char *str)
{
    int i;
    char *new_str;

    i = 0;
    new_str = malloc(ft_strlen(str) +  1 );
    if(!new_str)
        exit(1);
    if(!new_str)
        exit(1);
    while(str[i])
    {
        new_str[i] = str[i] ; 
        i++;
    }
    new_str[i] = '\0' ; 
    return new_str; 
}

char*  build_line(char *last_line , char *buffer , short *line_found)
{
    int  i;
    char *line;
    char *new_line; 

    i = 0;
    line = (char*)malloc(sizeof(char)*(ft_strlen(buffer) + 1) ); 
    if (!line)
        exit(1);
    if(!line)
        exit(1);
    while(buffer[i])
    {
        line[i] = buffer[i]; 
        if(line[i] == '\n')
        {
            *line_found = i + 1; 
            line[++i] = '\0'; 
             if (!last_line) 
                    return line;
            new_line = ft_strjoin(last_line , line); 
            return new_line; 
        }
        i++;
    }
    line[i] = '\0'; 
    if (!last_line) 
        return line; 
   
    new_line = ft_strjoin(last_line , line); 
    return new_line; 
}

char *get_next_line(int fd )
{
    if (fd < 0)
        return NULL ; 
    int bytes_read ;
    char *line ; 
    short line_found; 
    static char  *buffer;
    char *new_buffer; 

    line_found = 0;
    line = NULL;
    if (buffer)
    {
        line = build_line(line , buffer , &line_found );    
        if(line_found)
        {
            new_buffer = ft_strdup (     &(buffer[line_found])   ) ;
            free(buffer);
            buffer = new_buffer;
            if (!(*buffer))
            {
                free(buffer);
                buffer = NULL ; 
            } 
            return line; 
        }
    }
    free(buffer);
    buffer = malloc(sizeof(char)*(BUFFER_SIZE + 1 ) ) ; 

    while (1)
    {
        bytes_read = read(fd , buffer , BUFFER_SIZE );
        if (bytes_read < 0)
        {
            free(buffer);
            return NULL ; 
        }
        buffer[bytes_read] = '\0'; 
        if (!bytes_read)
        {
            free(buffer) ;
            buffer = NULL ; 
            return line ; 
        }
        line = build_line(line , buffer , &line_found);
        if(line_found)
        {
            new_buffer = ft_strdup(     &(buffer[line_found])   ) ;  
            free(buffer);
            buffer = new_buffer;
            if (!*buffer)
            {
                free(buffer);
                buffer = NULL ; 
            }
            return line ; 
        }
    }
    free(buffer);
    return line ; 

}
