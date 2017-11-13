#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long LL;

typedef struct{
    LL f;//factor
    int p;//power of factor
}data;
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
        printf("Usage: factor [NUMBER]...\n"
               "   or:  factor OPTION\n"
               "Print the prime factors of each specified integer NUMBER.  If none\n"
               "are specified on the command line, read them from standard input.\n"
               " \n"
               "    --help     display this help and exit\n"
               "    --version  output version information and exit\n"
        );

        exit(0);
    }
    else if( strlen(arg) < 10 ){
        valid = 1;
        for(int i=0;i<strlen(arg);++i){
            if(arg[i]!=version[i]){valid=0;break;}
        }
    }

    if(valid){
        printf("factor , Version : 1.0\n"
               "This is free software: you are free to change and redistribute it.\n"
               "\n"
               "Written by Operation System final project Team 3 (FPE 3)\n");

        exit(0);
    }

    printf("factor: unrecognized option '%s'\n",arg);
    puts("Try 'factor --help' for more information.");
    exit(0);

}

int main(int argc,char *argv[]){
    data fp[500];
    LL nf;
    LL k;
    LL tf;
    LL d;
    LL n;
    LL input[argc];
    int num_count=0;

//option checking
for(int c=1;c<argc;++c){

    if(argv[c][0]=='-'){
        if(argv[c][1]=='-'){check_option(argv[c]);}
        else if( strlen(argv[c]) > 1 ){
            printf("factor: invalid option -- '%c'\n",argv[c][1]);
            puts("Try 'factor --help' for more information.");
        }
    }
}
//valid positive integer checking
for(int c=1;c<argc;++c){

    n = atoll(argv[c]);
    if(n==0 && strcmp(argv[c],"0") ){
        printf("factor: \‘%s\’ is not a valid positive integer\n",argv[c]);
    }
    else{
        input[num_count++] = n;
    }

}
for(int c=0;c<num_count;++c){

    n = input[c];
    printf("%lld:",n);
    nf = 0;
    k = 0;
    tf = 2;
    d = 1;
    fp[0].f=0;
    fp[0].p=0;

    if(n > 1){

    while(tf*tf <= n){                 // main loop
        if(n%tf == 0){

            if(tf == fp[k].f){fp[k].p++;}
            else{
                k++;
                fp[k].f = tf;
                fp[k].p = 1;
            }
            n = n/tf;                        // compute new n
            continue;
        }

        tf = tf + d;                       // increment trial factor
        if(tf < 7)d = 2;
        else d = 6-d;
    }                                    // end main loop

        if( n == fp[k].f){
            fp[k].p+=1;
        }
        else {
            k++;
            fp[k].f = n;
            fp[k].p = 1;
        }

    for(int i=1; i<=k; i++){
        while(fp[i].p--){
            printf(" %lld",fp[i].f);
        }
    }
    printf("\n");
    }//main else close
}//argc loop
    return 0;
}
