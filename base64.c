#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

//function from http://bradconte.com/base64_c

unsigned char charset[]={"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

unsigned char revchar(char ch)
{
   if (ch >= 'A' && ch <= 'Z')
      ch -= 'A';
   else if (ch >= 'a' && ch <='z')
      ch = ch - 'a' + 26;
   else if (ch >= '0' && ch <='9')
      ch = ch - '0' + 52;
   else if (ch == '+')
      ch = 62;
   else if (ch == '/')
      ch = 63;
   return(ch);
}

int base64_encode(unsigned char in[], unsigned char out[], int len, int newline_flag, int separator)
{
   int idx,idx2,blks,left_over;

   blks = (len / 3) * 3;
   for (idx=0,idx2=0; idx < blks; idx += 3,idx2 += 4) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[((in[idx] & 0x03) << 4) + (in[idx+1] >> 4)];
      out[idx2+2] = charset[((in[idx+1] & 0x0f) << 2) + (in[idx+2] >> 6)];
      out[idx2+3] = charset[in[idx+2] & 0x3F];
      
      if (!(idx2 % separator) && newline_flag) {
         out[idx2+4] = '\n';
         idx2++;
      }
   }
   left_over = len % 3;
   if (left_over == 1) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[(in[idx] & 0x03) << 4];
      out[idx2+2] = '=';
      out[idx2+3] = '=';
      idx2 += 4;
   }
   else if (left_over == 2) {
      out[idx2] = charset[in[idx] >> 2];
      out[idx2+1] = charset[((in[idx] & 0x03) << 4) + (in[idx+1] >> 4)];
      out[idx2+2] = charset[(in[idx+1] & 0x0F) << 2];
      out[idx2+3] = '=';
      idx2 += 4;
   }
   out[idx2] = '\0';
   return(idx2);
}


int base64_decode(unsigned char in[], unsigned char out[], int len)
{
   unsigned char ch;
   int idx,idx2,blks,left_over;

   if (in[len-1] == '=')
      len--;
   if (in[len-1] == '=')
      len--;

   blks = (len / 4) * 4;
   for (idx=0,idx2=0; idx2 < blks; idx += 3,idx2 += 4) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4) + (revchar(in[idx2+2]) >> 2);
      out[idx+2] = (revchar(in[idx2+2]) << 6) + revchar(in[idx2+3]);
   }
   left_over = len % 4;
   if (left_over == 2) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4);
      idx += 2;
   }
   else if (left_over == 3) {
      out[idx] = (revchar(in[idx2]) << 2) + ((revchar(in[idx2+1]) & 0x30) >> 4);
      out[idx+1] = (revchar(in[idx2+1]) << 4) + (revchar(in[idx2+2]) >> 2);
      out[idx+2] = revchar(in[idx2+2]) << 6;
      idx += 3;
   }
   out[idx] = '\0';
   return(idx);
}

int main(int argc, char *argv[]){
   char data[], output[];
   int jum=0;
   if (argc == 1){
      printf(1, "USAGE:\n");
      printf(1, "./base64 file -> for eecode data\n"); 
      printf(1, "./base64 D file -> for decode data\n"); 
      printf(1, "./base64 E file -> for encode data\n"); 
      printf(1, "./base64 W n file -> for encode and add newline every n characters\n"); 
      printf(1, "./base64 W n E file -> for encode and add newline every n characters\n");
      printf(1, "./base64 W n D file -> for dencode and add newline every n characters\n");

   }
   else if(argc == 2){
      int inputfile;
      char buffer[128];
      inputfile = open(argv[1], O_RDONLY);
      while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
         data[jum] = buffer;
         jum=jum+1;
      }
      base64_encode(data, output, jum, 0, 77);
   }
   else if(argc == 3){
      if (argv[1] == 'D' ){
         int inputfile;
         char buffer[128];
         inputfile = open(argv[2], O_RDONLY);
         while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
            data[jum] = buffer;
            jum=jum+1;
         }
         base64_encode(data, output, jum, 0, 77);
      }
      else if (argv[1] == 'E' ){
         int inputfile;
         char buffer[128];
         inputfile = open(argv[2], O_RDONLY);
         while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
            data[jum] = buffer;
            jum=jum+1;
         }
         base64_dencode(data, output, jum);
      }
   }
   else if(argc == 4){
      if (argv[1] == 'W' ){
         int inputfile;
         char buffer[128];
         inputfile = open(argv[3], O_RDONLY);
         while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
            data[jum] = buffer;
            jum=jum+1;
         }
         base64_encode(data, output, jum, 0, argv[2]);
      }
   }
   else if(argc == 5){
       if (argv[3] == 'E' ){
         int inputfile;
         char buffer[128];
         inputfile = open(argv[4], O_RDONLY);
         while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
            data[jum] = buffer;
            jum=jum+1;
         }
         base64_encode(data, output, jum, 0, argv[2]);
      }
      else if (argv[3] == 'D' ){
         int inputfile;
         char buffer[128];
         inputfile = open(argv[4], O_RDONLY);
         while( ( buff_len=read(inputfile,buffer,sizeof(buffer)) )> 0  ){
            data[jum] = buffer;
            jum=jum+1;
         }
         base64_dencode(data, output, jum);
      }
   }

   close(inputfile);
   return 0
}
