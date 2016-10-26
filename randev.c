#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

int rngesus(){
  int fd = open("/dev/random", O_RDONLY);
  int retval;
  read(fd, &retval, 4);
  return retval;
}

int main(){

  umask(0000);
  
  printf("%d\n", rngesus());

  int rands[10];
  int i;
  printf("Random ints created: \n");
  for (i = 0; i < 10; i++) {
    rands[i] = rngesus();
    printf("    random %d: %d\n", i, rands[i]);
  }
  printf("\n");

  int fd = open("foo", O_CREAT | O_RDWR, 0666);
  printf("writing\n\n");
  write(fd, &rands, 10 * sizeof(int));

  close(fd);

  fd = open("foo", O_RDONLY);
  int readrands[10];
  printf("reading\n\n");
  read(fd, readrands, 10 * sizeof(int));
  printf("In readrands: \n");
  for (i = 0; i < 10; i++) {
    printf("    random %d: %d \n ", i, readrands[i]);
    if (readrands[i] != rands[i]) {
      printf("    (DIFFERENT!)\n");
    } else {
      printf("    (same)\n");
    }
  }
  printf("\n");

  return 0;
}
