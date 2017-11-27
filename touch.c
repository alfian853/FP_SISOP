#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"


int main(int argc, char *argv[]){


for(int i=1;i<argc;++i){
    open(argv[i],O_CREATE|O_RDWR);
}

exit();
}
