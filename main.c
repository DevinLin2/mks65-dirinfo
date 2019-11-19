#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
  DIR * dir;
  struct stat stat_buffer;
  int dirsize = 0;
  if (argc < 2) {
    printf("Enter a valid directory or '.' for current directory");
    exit(1);
  } else {
    dir = opendir(argv[1]);
  }
  struct dirent * stream = readdir(dir);

  printf("Directories: \n" );
  while (stream != NULL) {
    if(stat(stream -> d_name, &stat_buffer) < 0) {
      printf("Error: %s\n", strerror(errno));
    }
    if(S_ISDIR(stat_buffer.st_mode)) { // if is a directory
      printf("%s \n", stream -> d_name);
    }
    stream = readdir(dir);
  }
  closedir(dir);
  printf("\nRegular Files:\n" );
  dir = opendir(argv[1]);
  stream = readdir(dir);
  while (stream != NULL) {
    if(stat(stream -> d_name, &stat_buffer) < 0){
      printf("Error: %s\n", strerror(errno));
    }
    if(!S_ISDIR(stat_buffer.st_mode)){
      printf("%s \n", stream -> d_name);
      dirsize += stat_buffer.st_size;
    }
    stream = readdir(dir);
  }
  printf("\nTotal Size: %d bytes\n", dirsize);
  return 0;
}
