#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf(2, "Usage: sleep seconds\n");
        exit();
    }
    else if(argc>2){
        printf(2, "Invalid internal %s\n", argv[2]);
        exit();
    }
    int sleepsec=atoi(argv[1])*100;
    if(sleepsec>0) sleep(sleepsec);
    else printf(2, "Invalid internal %s\n", argv[1]);
    exit();
}
