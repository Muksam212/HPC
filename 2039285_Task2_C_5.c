#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>



int n_password=1;     // A counter used to track the number of combinations explored so far
char *encrypted_passmuksam[]={
   "$6$AS$Ay7JzH.Dh50PF86hCri.bmPNqWB.oz.1LdwkbKmhcYa5GjtJoyFDXWBF.mS00WXvRWHhQMwyH1hrkF5sMGWPt"

};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void thread_posix(){
int i;
pthread_t t1,t2;

void *kernel_function_1();
void *kernel_function_2();
for(i=0;i<n_password;i++){
pthread_create(&t1,NULL,kernel_function_1,encrypted_passmuksam[i]);
pthread_create(&t2,NULL,kernel_function_2,encrypted_passmuksam[i]);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
}
void *kernel_function_1(char *salt_and_encrypted){
	int m,u,k;
	char salt[7];
	char plain[7];
	char *enc;
	int count=0;
	
	substr(salt, salt_and_encrypted,0,6);
	for (m='A'; m<='M'; m++){
	for (u='A'; u<='Z'; u++){
	for (k=0; k<=99 ; k++){
	sprintf(plain, "%c%c%02d", m,u,k);
	enc=(char *) crypt(plain,salt);
	count++;
	if(strcmp(salt_and_encrypted, enc)==0){
		printf("#%-8d%s %s\n", count, plain, enc);
	}else{
           printf("%-8d%s %s\n", count, plain, enc);
	}
	}
	}
	}
printf("%d solutions explored\n", count);
}


void *kernel_function_2(char *salt_and_encrypted){
  int m,u,k;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;  
  int count=0;     // Pointer to the encrypted password
  
  substr(salt, salt_and_encrypted, 0, 6);

  for(m='N'; m<='Z'; m++){
    for(u='A'; u<='Z'; u++){
      for(k=0; k<=99; k++){
        sprintf(plain, "%c%c%02d", m, u, k); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
		
        } else{
            printf("%-8d%s %s\n", count, plain, enc);
        }
        
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
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
  thread_posix();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time taken was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));
  return 0;
}

