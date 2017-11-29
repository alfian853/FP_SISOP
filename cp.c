
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"



int recursively=0;

char source_path[256],destination_path[256];

void copy_file(char* dst,char *src){

    int fdr,fdw;

    if ( (fdr=open(src,O_RDONLY)) < 0 ){
        printf(1,"returned read %s\n",src);
        return;
    }
    if ( (fdw=open(dst,O_CREATE|O_RDWR)) < 0 ){
        printf(1,"returned write\n");
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
traverse_dir(char *path)
{
    if(chdir(path)<0){
        printf(2,"chdir %s error\n",path);
    }
    else{
        printf(2,"success\n");
    }
    char *new_path=malloc(256*sizeof(char));
    char *new_src=malloc(256*sizeof(char));//[256];
    char *new_dst=malloc(256*sizeof(char));//[256];

  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(".", 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    //printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(2 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, ".");
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0){
    continue;
    }
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "---ls: cannot stat %s\n", buf);
        continue;
      }
      char *obj_name=buf+1;//karna buf = './namafile'
      if(!strcmp(obj_name,"/.") || !strcmp(obj_name,"/.."))continue;
      printf(2,"%s read %s\n",path,obj_name);
      if(st.type == 1){
//            printf(2,"bangsat\n");
            *new_path='\0';
//ssassddads
            ++obj_name;//=obj_name+1;
            //_strcat(obj_name,"/");
            _strcat(new_path,destination_path);
            _strcat(new_path,"/");
            _strcat(new_path,path);
            _strcat(new_path,"/");
            _strcat(new_path,obj_name);

            if(mkdir(new_path)<0){
                printf(2,"gagal %s\n",new_path);
            }

            *new_path='\0';
            _strcat(new_path,path);
            _strcat(new_path,"/");
            _strcat(new_path,obj_name);

            char *temp_pdir=malloc(256*sizeof(char));
            strcpy(temp_pdir,parent_dir);
            _strcat(parent_dir,"/");
            _strcat(parent_dir,obj_name);//pdir->d_name);

            traverse_dir(obj_name);
            strcpy(parent_dir,temp_pdir);

      }
      else{
        *new_dst='\0';
        *new_src='\0';

        _strcat(new_src,obj_name);

        _strcat(new_dst,destination_path);
        _strcat(new_dst,parent_dir);
        _strcat(new_dst,new_src);
        printf(2,"copy file %d %s from %d %s\n",strlen(obj_name),new_dst,strlen(obj_name),obj_name);
        copy_file(new_dst,obj_name+1);
      }

//        printf(2,"get %s\n",obj_name);
//      printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
    }
    break;
  }
  close(fd);
  chdir("..");
}


int main(int argc, char *argv[]){

    if(argc==1){
        printf(1,"cp: missing file operand\n\
        Try 'cp --help' for more information.\n");
        exit();
    }
    else if(argc==2){
        printf(1,"cp: missing destination file operand after '%s'\n\
        Try 'cp --help' for more information.\n",argv[1]);
        exit();
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
//    recursively=1;
    if(recursively){
        int fdr;//,fdw;

        if ( (fdr=open(source_path,O_RDONLY)) < 0 ){
            printf(1,"can't read %s\n",source_path);
            exit();
        }

        char *new_path=malloc(256*sizeof(char));
        parent_dir=malloc(256*sizeof(char));
        strcpy(parent_dir,argv[1]);
        _strcat(new_path,destination_path);
        _strcat(new_path,"/");
        _strcat(new_path,source_path);
        printf(1,"first mkdir %s\n",new_path);
        mkdir(new_path);
        traverse_dir(source_path);
       // traverse_dir(argv[1]);
    }

//copy_file(argv[2],argv[1]);


/*    recursively=1;
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


    traverse_file(source_path);
*/

exit();
}

