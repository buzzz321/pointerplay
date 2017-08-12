#include <stdio.h>
#include <string.h>


void advance ( char **buffer ){
    while( (**buffer) != '\n' && (**buffer) != '\0' ){
        ++(*buffer);
    }
    if((**buffer) == '\n'){
        ++(*buffer);
    }
}

int main(){
    const size_t FILEMAX = 32768;
    char filedata[FILEMAX];
    FILE *file;
    size_t nread;

    memset(filedata, 1, FILEMAX);
    file = fopen("../data.txt", "r");
    if (file) {
        nread = fread(filedata, 1, sizeof filedata, file);
        //fwrite(filedata, 1, nread, stdout);
        if(nread<FILEMAX){
            filedata[nread] = '\0';
        } else {
            filedata[FILEMAX - 1 ] = '\0';
        }

        if (ferror(file)) {
            /* deal with error */
        }
        fclose(file);
    }
    char **pek;
    char *tmp;
    tmp = &filedata[0];
    pek = &tmp;

    while((unsigned char)(**pek) != '\0')
    {
        for(char *lp = *pek; *lp != '\n'; ++lp){
            printf("%c", lp[0]);
        }
        printf("\n");
        advance(pek);
    }

    return 0;
}
