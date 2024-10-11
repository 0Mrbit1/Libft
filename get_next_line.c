#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE 
    #define BUFFER_SIZE 42
#endif

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    int i;
    char *new_str; 

    new_str = malloc(sizeof(char)*( ft_strlen(str) +1  ) ); 
    if(!new_str)
        return NULL; 
    i = 0;
    while(str[i])
    {
        new_str[i] = str[i]; 
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}

char *ft_strjoin(char *s1 , char *s2)
{
    char *new_str;
    int i ;
    int j ;

    new_str = malloc(sizeof(char)*( ft_strlen(s1) + ft_strlen(s2) + 1  ) ) ;
    if(!new_str)
        return NULL;
    i = 0 ;
    j = 0 ;
    while(s1[i])
    {
        new_str[j] = s1[i];
        i++;
        j++;
    } 
    i = 0 ;
    while(s2[i])
    {
        new_str[j] = s2[i];
        i++;
        j++;
    }
    new_str[j] = '\0';
    free(s1);
    free(s2) ; 
    return new_str;
}

char *find_line(char *last_line , char *buffer, short *line_found)
{
    int i; 
    char *line;

    if (!*buffer)
        return last_line;
    i = 0 ; 
    line = malloc(sizeof(char) * ( ft_strlen(buffer) + 1 )   ) ;
    if(!line)
        return NULL;
    while(buffer[i])
    {
        line[i] = buffer[i];  
        if(line[i] == '\n')
        {
            line[++i] = '\0';
            if (last_line)
                line = ft_strjoin(last_line , line );
            *line_found = i; 
            return line; 
        }
        i++;
    }
    line[i] = '\0';
    if (last_line)
        line = ft_strjoin(last_line , line );
    return line;
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    int bytes_read;
    short line_found;
    char *resize;

    line_found = 0; 
    line = NULL; 
    if (buffer)
    {
        line = find_line(line , buffer , &line_found);
        if(line_found)
        {
            resize = buffer;
            buffer = ft_strdup(  &(buffer[line_found]));
            free(resize);
            return line;       
        }
        free(buffer);
    }
    buffer = malloc(sizeof(char)*(BUFFER_SIZE + 1)); 
    if(!buffer)
        return NULL;
    while(1)
    {
        bytes_read = read(fd , buffer , BUFFER_SIZE) ;
        buffer[bytes_read] = '\0';
        line = find_line ( line , buffer , &line_found);
        if(line_found)
        {
            resize = buffer;
            buffer = ft_strdup(&(buffer[line_found]));
            free(resize);
            return line;
        }
        if(!bytes_read)
        {
           free(buffer);
            buffer = NULL ;
            return line;
        }
    }
}
