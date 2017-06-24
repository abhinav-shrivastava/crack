#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: ./crack hash\n");
        exit(1);
    }
    
    char *hash = argv[1];
    
    char salt[3];
    strncpy(salt, hash, 2);
    salt[2] = '\0';

    char *crack_hash;
    char guess_pass[5];
    guess_pass[4] = '\0';
    for(int i=0; i<58; i++)
        for(int j=-1; j<58; j++)
            for(int k=-1; k<58; k++)
                for(int l=-1; l<58; l++){
                    // Hint: skip that guess for which lower significant bit are -1 and higher are not
                    if( !((j==-1 && (k>-1 || l>-1)) || (k==-1 && l>-1)) ){
                        guess_pass[0] = 'A'+ i;
                        guess_pass[1] = (j==-1) ? 0: 'A' + j;
                        guess_pass[2] = (k==-1) ? 0: 'A' + k;
                        guess_pass[3] = (l==-1) ? 0: 'A' + l;
                        crack_hash = crypt(guess_pass, salt);
                        if(strcmp(crack_hash, hash) == 0){
                            printf("%s\n", guess_pass);
                            exit(0);
                        }
                    }
                }
}