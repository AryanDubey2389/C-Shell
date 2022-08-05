#include "prompt.h"
#include "headers.h"
int main()
{
    struct utsname uts;
    uname(&uts);
    char *buf;
    buf=(char *)malloc(10*sizeof(char));
    getlogin_r(buf,10);
    printf("<%s@%s:~>",buf,uts.nodename);
    char homepath[1000],path[1000], prevpath[1000][900];
    strcpy(homepath,getcwd(path,1000));
    strcpy(prevpath[0],homepath);
    int i = 1;
    
    // printf("%ld -> %ld\n",strlen(homepath), strlen(prevpath));
    while (1)
    {
        // sleep(1);
        char arr[1000];
        fgets(arr, 1000, stdin);
        if(strcmp(arr,"exit\n") == 0)
            break;
        i = prompt(arr, homepath, prevpath,i);
        // printf("main prevpath -> %s\n",prevpath[0]);
    }
}
