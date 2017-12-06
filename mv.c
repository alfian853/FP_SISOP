#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char *source_path,*destination_path;

void copy_file(char* dst,char *src){
    int fdr,fdw,fdc;
//    printf(1,"gogo\n");
    if ( (fdr=open(src,O_RDONLY)) < 0 ){
        printf(1,"can't read from %s\n",src);
        return;
    }
    if ( (fdc=open(dst,O_CREATE)) < 0 ){
        printf(1,"can't create %s\n",dst);
        return;
    }
    else{
//        printf(1,"can create %s %s\n",dst,src);
        close(fdc);
    }
    if ( (fdw=open(dst,O_WRONLY)) < 0 ){
        printf(1,"can't write to %s\n",dst);
        return;
    }
    int buff_len;
    char buffer[128];
    while( ( buff_len=read(fdr,buffer,sizeof(buffer)) )> 0  ){
        write(fdw,buffer,buff_len);
    }
    close(fdr);
    close(fdw);
}

//asd
void _strcat(char *dst,char *src){
    int j=strlen(dst);
    for(int i=0;i<strlen(src);++i,j++){
        dst[j]=src[i];
    }
    dst[j]='\0';
return;
}

char *parent_dir;

void
traverse_dir(char *path){
    if(chdir(path)<0){
        printf(2,"mv: cannot open %s\n",path);
    }
    char *new_path=malloc(256*sizeof(char));
    char *new_src=malloc(256*sizeof(char));//[256];
    char *new_dst=malloc(256*sizeof(char));//[256];

    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(".", 0)) < 0){
        printf(2, "mv: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        printf(2, "mv: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(2 + DIRSIZ + 1 > sizeof buf){
        printf(1, "mv: path too long\n");
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
            printf(1, "mv: cannot stat %s\n", buf);
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
            copy_file(new_dst,obj_name+1);
            unlink(obj_name+1);
        }
    }
    close(fd);
    chdir("..");
    unlink(path);
}

int is_file(char *path){
    struct stat st;
    int fd;

    if((fd = open(path, 0)) < 0){
        return 1;
    }

    if(fstat(fd, &st) < 0){
        return 1;
    }
    close(fd);
    if(st.type==2)return 1;

    return 0;

}


char* getdir_name(char *path){
    int i=strlen(path)-2;// karna bisa jadi case dir1/dir2/ atau dir1/dir2
    for(; i > -1 && path[i]!='/';--i);
    if(path[0]=='/')
        return path+i+1;
    return path;
}



int main(int argc, char **argv){
    parent_dir=malloc(128*sizeof(char));
    source_path=malloc(128*sizeof(char));
    destination_path=malloc(128*sizeof(char));

    if(argc==1){
        printf(1,"mv: missing file operand\n\
        Try 'mv --help' for more information.\n");
        exit();
    }
    else if(argc==2){
        printf(1,"mv: missing destination file operand after '%s'\n\
        Try 'mv --help' for more information.\n",argv[1]);
        exit();
    }
    strcpy(source_path,argv[1]);
    strcpy(destination_path,argv[2]);


    if(!strcmp(source_path,"*")){
        strcpy(parent_dir,"/");
        traverse_dir(".");
        exit();

    }


    if(!is_file(source_path)){
        source_path=getdir_name(source_path);
        char *new_path=malloc(256*sizeof(char));
        if(source_path[ strlen(source_path)-1 ]!='/'){_strcat(source_path,"/");}

        if(is_file(destination_path)){
//            printf(1,"rename\n");
            strcpy(parent_dir,getdir_name(destination_path));
            if(parent_dir[ strlen(parent_dir)-1 ]!='/'){_strcat(parent_dir,"/");}
            strcpy(new_path,destination_path);
            if(new_path[ strlen(new_path)-1 ]!='/'){_strcat(new_path,"/");}

            for(int i=strlen(destination_path)-1;i>-1 && destination_path[i]!='/';destination_path[i--]='\0');
            mkdir(new_path);

            traverse_dir(source_path);
            exit();
        }
        else{
//            printf(1,"not rename\n");
            strcpy(parent_dir,source_path);
            if(destination_path[ strlen(destination_path)-1 ]!='/'){_strcat(destination_path,"/");}
            _strcat(new_path,destination_path);
            _strcat(new_path,source_path);
            mkdir(new_path);
            traverse_dir(parent_dir);
        }
    }
    else{
        copy_file(destination_path,source_path);
        unlink(source_path);
    }

exit();
}


