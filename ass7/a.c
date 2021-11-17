#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_BUF 1024

int main()
{
  int fd, c = 0;
  char *fifo1 = "fifo1";
  char *fifo2 = "fifo2";
  int fd1;
  int words = 1, lines = 1, chars = 0;
  char buf1[MAX_BUF];
  mkfifo(fifo1, 0666);
  fd = open(fifo1, O_RDWR);
  char str;
  printf("\nEnter the String:");
  while ((str = getchar()) != '#')
    buf1[c++] = str;
  buf1[c] = '\0';
  write(fd, buf1, sizeof(buf1));
  close(fd);
  unlink(fifo1);
  fd1 = open(fifo2, O_RDWR);
  read(fd1, buf1, sizeof(buf1));
  printf("\nThe contents of file are %s", buf1);
  int i = 0;
  while (buf1[i] != '\0')
  {
    if (buf1[i] == ' ' || buf1[i] == '\n')
    {
      words++;
    }
    else
    {
      chars++;
    }
    if (buf1[i] == '\n')
    {
      lines++;
    }
    i++;
  }
  printf("\n No of Words: %d", words);
  printf("\n No of Characters: %d", chars);
  printf("\n No of Lines: %d\n", lines);
  close(fd1);
  return 0;
}
