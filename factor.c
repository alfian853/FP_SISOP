#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"


struct data{
    int f;//factor
    int p;//power of factor
};
/*
--help
--version

*/
char help[6]={'-','-','h','e','l','p'};
char version[9]={'-','-','v','e','r','s','i','o','n'};


void check_option(char *arg){
    int valid=1;
    if( strlen(arg) < 7 ) {
        for(int i=0;i<strlen(arg);++i){
            if(arg[i]!=help[i]){valid=0;break;}
        }
    }
    else{
        valid=0;
    }

    if(valid){
        printf(1,"Usage: factor [NUMBER]...\n"
               "   or:  factor OPTION\n"
               "Print the prime factors of each specified integer NUMBER.  If none\n"
               "are specified on the command line, read them from standard input.\n"
               " \n"
               "    --help     display this help and exit\n"
               "    --version  output version information and exit\n"
        );

        exit();
    }
    else if( strlen(arg) < 10 ){
        valid = 1;
        for(int i=0;i<strlen(arg);++i){
            if(arg[i]!=version[i]){valid=0;break;}
        }
    }

    if(valid){
        printf(1,"factor , Version : 1.0\n"
               "This is free software: you are free to change and redistribute it.\n"
               "\n"
               "Written by Operation System final project Team 3 (FPE 3)\n");

        exit();
    }

    printf(1,"factor: unrecognized option '%s'\n",arg);
    printf(1,"Try 'factor --help' for more information.");
    exit();

}

int main(int argc,char *argv[]){
    int k=0;
    int tf=0;
    int d=0;
    int n=0;
    int factor=-1;
    int input[argc];

    int num_count=0;
////option checking
for(int c=1;c<argc;++c){

    if(argv[c][0]=='-'){
        if(argv[c][1]=='-'){check_option(argv[c]);}
        else if( strlen(argv[c]) > 1 ){
            printf(1,"factor: invalid option -- '%c'\n",argv[c][1]);
            printf(1,"Try 'factor --help' for more information.\n");
        }
    }
}
////valid positive integer checking
for(int c=1;c<argc;++c){
    n = atoi(argv[c]);
    if(n==0 && strcmp(argv[c],"0") ){
        printf(1,"factor: ‘%s’ is not a valid positive integer\n",argv[c]);
    }
    else{
        input[num_count++] = n;
    }
}
for(int c=0;c<num_count;++c){
    n = input[c];
    printf(1,"%d:",n);
    k = 0;
    tf = 2;
    d = 1;

    if(n > 1){

    while(tf*tf <= n){
        if(n%tf == 0){
            if(tf == factor){printf(1," %d",tf);}
            else{
                k++;
                printf(1," %d",tf);
                factor=tf;
            }
            n = n/tf;
            continue;
        }

        tf = tf + d;
        if(tf < 7)d = 2;
        else d = 6-d;
    }

    if( n == factor){
        printf(1," %d",tf);
    }
    else {
        k++;
        factor=n;
        printf(1," %d",n);
    }
    printf(1,"\n");
    }//end main else
}//argc loop


    exit();
}

