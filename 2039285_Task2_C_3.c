#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <stdlib.h>

#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>

#include <time.h>
#include <pthread.h>
#include <math.h>


int count=0;     

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    
  char plain[7];   
  char *enc;      

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
       //for(m='A'; m<='Z'; m++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		
        } 
      }
    }
  }
  
}
int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}



int main(int argc, char *argv[]){
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  crack("$6$AS$Ay7JzH.Dh50PF86hCri.bmPNqWB.oz.1LdwkbKmhcYa5GjtJoyFDXWBF.mS00WXvRWHhQMwyH1hrkF5sMGWPt");	
  printf("%d solutions explored\n", count);
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
                                         
                                         
return 0;
}
