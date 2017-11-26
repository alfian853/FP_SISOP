#include <stdio.h>
#include <dirent.h>

void getdata(char path[]){
    DIR* dir;
    struct dirent* pdir;
    dir = opendir(path);
    while (pdir = readdir(dir)){
        if ( !strcmp(pdir->d_name, ".") || !strcmp(pdir->d_name, "..") || pdir->d_name[0] == "."){
            // do nothing
        }
        else{
            printf("%s\n", pdir->d_name);
        }
    }
}


int main(int argc, char *argv[]){
    if(argc == 1){
        getdata(".");
    }
    else if(argc == 2){
        getdata(argv[1]);
    }
    else{
        int i;
        for(i=1;i<argc;i++){
            printf("%s\n",argv[i]);
            getdata(argv[i]);
        }
    }

}
