#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void copy_file(char* src,char *dst){

    FILE *fsrc=fopen(src,"rb");
    FILE *fdst=fopen(dst,"wb");

    if(fsrc==NULL || fdst==NULL){
        printf("file access error!\n");
        return;
    }

    long long fSize;
    fseek(fsrc,0,SEEK_END);
    fSize = ftell(fsrc);
    rewind(fsrc);

    char *buffer;
    buffer =  (char*) malloc (sizeof(char)*fSize);

    if(fread (buffer,1,fSize,fsrc)!=fSize){
        printf("reading error!\n");
        return;
    }
    fwrite(buffer,1,fSize,fdst);
    fclose(fsrc);
    fclose(fdst);
}

void getdata(char *path,int level){
    DIR* dir;
    struct dirent* pdir;
    dir = opendir(path);
    printf("===\n");
    if(!dir){printf("error!\n");return;}
    while (pdir = readdir(dir)){

        if(pdir->d_type == DT_DIR){

            if ( !strcmp(pdir->d_name, ".") || !strcmp(pdir->d_name, "..") )continue;
            char new_path[256];
            sprintf(new_path,"%s/%s",path,pdir->d_name);
            getdata(new_path,level+1);
        }
        else{
            printf("%d %s\n", level,pdir->d_name);
        }
    }
}



int main(int argc, char *argv[]){

    getdata(".",0);

}
