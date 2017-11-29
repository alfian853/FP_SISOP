#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>



int recursively=0;

char source_path[256],destination_path[256];

void copy_file(char* dst,char *src){

    FILE *fsrc=fopen(src,"rb");
    FILE *fdst=fopen(dst,"wb");

    if(fsrc==NULL || fdst==NULL){
        if(fsrc==NULL)printf("source error");
        if(fdst==NULL)printf("dst error");

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

void _strcat(char *dst,char *src){
    int j=strlen(dst);
    for(int i=0;i<strlen(src);++i,j++){
        dst[j]=src[i];
    }
    dst[j]='\0';
return;

}
char *parent_dir;

void traverse_dir(char *path){
    chdir(path);
    char *new_path=malloc(256*sizeof(char));
    char *new_src=malloc(256*sizeof(char));//[256];
    char *new_dst=malloc(256*sizeof(char));//[256];


    DIR* dir;
    struct dirent* pdir;
    dir = opendir(".");





    while (pdir = readdir(dir)){

        if(pdir->d_type == DT_DIR && recursively){
            if ( !strcmp(pdir->d_name, "..") || !strcmp(pdir->d_name, ".")  ){continue;}
            *new_path='\0';

            _strcat(new_path,destination_path);
            _strcat(new_path,"/");
            _strcat(new_path,path);
            _strcat(new_path,"/");
            _strcat(new_path,pdir->d_name);

            mkdir(new_path,0777);

            *new_path='\0';
            _strcat(new_path,path);
            _strcat(new_path,"/");
            _strcat(new_path,pdir->d_name);

            char *temp_pdir=malloc(256*sizeof(char));
            strcpy(temp_pdir,parent_dir);
            _strcat(parent_dir,pdir->d_name);
            _strcat(parent_dir,"/");

            traverse_dir(pdir->d_name);
            strcpy(parent_dir,temp_pdir);

        }
        else{
            *new_dst='\0';
            *new_src='\0';

            _strcat(new_src,pdir->d_name);

            _strcat(new_dst,destination_path);
            _strcat(new_dst,parent_dir);
            _strcat(new_dst,new_src);

//            printf("masuk3 %s %s\n",new_dst,new_src);
            copy_file(new_dst,pdir->d_name);
        }
    }
    chdir("..");
}



int main(int argc, char *argv[]){


    if(argc<3){
        printf("error\n");
        return 1;
    }

    recursively=0;
    for(int i=1;i<argc;++i){
        if(!strcmp(argv[i],"-R")){
            recursively=1;
            break;
        }
        else if( strlen(source_path)==0 ){
            strcpy(source_path,argv[i]);
        }
        else{
            strcpy(destination_path,argv[i]);
        }
    }

    if(recursively){

        char *new_path=malloc(256*sizeof(char));
        parent_dir=malloc(256*sizeof(char));
        strcpy(parent_dir,argv[1]);
        _strcat(new_path,destination_path);
        _strcat(new_path,"/");
        _strcat(new_path,source_path);
        printf("first mkdir %s\n",new_path);
        mkdir(new_path,0777);

        traverse_dir(argv[1]);
    }

}


