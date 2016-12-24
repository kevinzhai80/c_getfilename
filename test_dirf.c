#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define TEST_RUNNING_TIME 1

#if TEST_RUNNING_TIME
long long getSysTimeMs(void){
  struct timespec t;
  clock_gettime(CLOCK_BOOTTIME,&t);
  return (t.tv_sec*1000+t.tv_nsec/(1000*1000));
}
#endif

#define USE_C_INTERFACE 0
#if USE_C_INTERFACE

void fileIsExist(char *file0, char *file1, char *file2){
  if (access(file0,0)!=-1){
    printf("%s is exist\n", file0);
  }else{
    printf("%s is not exist\n", file0);
  }
  if (access(file1,0)!=-1){
    printf("%s is exist\n", file1);
  }else{
    printf("%s is not exit\n", file1);
  }
  if (access(file2,0)!=-1){
    printf("%s is exist\n", file2);
  }else{
    printf("%s is not exist\n", file2);
  }
}

#else
#define FILE_PATH "./test.tmp"

void getDirFiles(void){
  FILE *fp = NULL;
  char *f_name0;
  char *f_name1;
  char *f_name2;

  f_name0 = (char*)malloc(sizeof(char));
  f_name1 = (char*)malloc(sizeof(char));
  f_name2 = (char*)malloc(sizeof(char));

  system("ls ./testp/ | grep file0 > ./test.tmp");
  system("if [ `ls ./testp/ | grep file1` ];then ls ./testp/ | grep file1 >> ./test.tmp;\
    else echo no >> ./test.tmp;fi");
  system("ls ./testp/ | grep file2 >> ./test.tmp");
  fp = fopen(FILE_PATH,"rb");
  if (fp == NULL){
    printf("Open file failed!");
    goto EXIT;
  }
  
  while(1 == fscanf(fp, "%s", f_name0)){
    while(1 == fscanf(fp, "%s", f_name1)){
      while(1 == fscanf(fp, "%s", f_name2)){
        break;
      }
      break;
    }
    break;
  }
  printf("fname0:%s fname1:%s fname2:%s\n",f_name0,f_name1,f_name2);
  fclose(fp);
  system("rm ./test.tmp");
  EXIT:
  free(f_name0);
  free(f_name1);
  free(f_name2);
}
#endif
void main(void){
#if TEST_RUNNING_TIME
  long long t;
  t = getSysTimeMs();
#endif
#if USE_C_INTERFACE
  fileIsExist("./testp/file0","./testp/file1","./testp/file2");
#else
  getDirFiles();
#endif
#if TEST_RUNNING_TIME
  printf("running time:%lld Ms\n",getSysTimeMs()-t);
#endif
}
