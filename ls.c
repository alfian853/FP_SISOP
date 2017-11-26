#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
//#define _GNU_SOURCE
#include <dirent.h>


int main(){
    char *path="/bin";
    DIR* dir;
    struct dirent* pdir;
    dir = opendir(path);
    FILE *filenya=fopen("output.txt","w");
    while (pdir = readdir(dir)){
        if ( !strcmp(pdir->d_name, ".") || !strcmp(pdir->d_name, "..") )
        {
            // do nothing
        } else{
            fprintf(filenya,strcat(pdir->d_name,"\n"));
        }
    }
   pid_t child_id;
    child_id=fork();
    if(child_id==0){
        char *argv[5]= {"zip", "-rm", "output.zip","output.txt",NULL};
        execv("/usr/bin/zip", argv);
    }
}
