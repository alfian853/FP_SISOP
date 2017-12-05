#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void traverse_dir(char *path){
    if(chdir(path)<0){
        printf(2,"rm: cannot open %s\n",path);
    }
    char *new_path=malloc(256*sizeof(char));
    char *new_src=malloc(256*sizeof(char));//[256];
    char *new_dst=malloc(256*sizeof(char));//[256];

    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(".", 0)) < 0){
        printf(2, "rm: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf(2, "rm: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(2 + DIRSIZ + 1 > sizeof buf){
        printf(1, "rm: path too long\n");
        return;
    }
    strcpy(buf, ".");
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)continue;

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf(1, "rm: cannot stat %s\n", buf);
            continue;
        }
        char *obj_name=buf+1;//karna buf = './namafile'
        if(!strcmp(obj_name,"/.") || !strcmp(obj_name,"/.."))continue;
//        printf(1,"reading %s\n",obj_name);
        if(st.type == 1){

            *new_path='\0';
            ++obj_name;
            _strcat(new_path,destination_path);
            _strcat(new_path,"/");
            _strcat(new_path,path);
            _strcat(new_path,"/");
            _strcat(new_path,obj_name);

            mkdir(new_path);


            *new_path='\0';
            _strcat(new_path,path);
            _strcat(new_path,obj_name);

            char *temp_pdir=malloc(256*sizeof(char));
            strcpy(temp_pdir,parent_dir);
            _strcat(parent_dir,obj_name);//pdir->d_name);
            _strcat(parent_dir,"/");
            traverse_dir(obj_name);
            unlink(obj_name);
            strcpy(parent_dir,temp_pdir);
        }
        else{
            *new_dst='\0';
            *new_src='\0';

            _strcat(new_src,obj_name);

            _strcat(new_dst,destination_path);
            _strcat(new_dst,parent_dir);
            _strcat(new_dst,new_src);
  //          printf(2,"copy file %s to %s\n",obj_name+1,new_dst);
            unlink(obj_name+1);
        }
    }
    close(fd);
    chdir("..");
    unlink(path);
}


int main(int argc, char *argv[]){
    int i;
    if(!strcmp(argv[1],"-rf") || !strcmp(argv[1],"-fr")){
    	traverse_dir(argv[2])
    }
    else{
    	for(i=1;i<argc;i++){
        	unlink(argv[i]);
    	}
    }

    return 0;
}
