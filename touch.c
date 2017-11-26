#include <stdio.h>

int main(int argc, char *argv[]){
    int i;
    for(i=1;i<argc;i++){
        FILE *data;
        data = fopen(argv[i],"w+");
        fclose(data);
    }

    return 0;
}
