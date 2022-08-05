#include "prompt.h"
#include "headers.h"
char** get_history_arr(char history_path[1000])
{
    char hist_arr[1000][900] = {};
    FILE * fp;
    fp = fopen(history_path,"r+");
    char c[1000] = "";
    int i = 0;
    while((fgets(c,1000,fp)))
    {
        strcpy(hist_arr[i],c);
        // printf("hist_arr[%d] -> %s\n",i,hist_arr[i]);
        i++;
    }
    strcpy(hist_arr[i],"\n");
    fclose(fp);
    char **temp = (char**)malloc(sizeof(char*) * 1000 * 900);
    for(int j = 0; j <= i; j++)
    {
        temp[j] = (char *)malloc(1000*sizeof(malloc));
        strcpy(temp[j],hist_arr[j]);
    }
    return temp;
}
char** store_history(char arr[1000], char history_path[1000])
{
    char new_arr[1000] = "";
    strcpy(new_arr,arr);
    char **history_arr = (char**)malloc(sizeof(char) * 1000 * 100); 
    history_arr = get_history_arr(history_path);
    int j = 0;
    // printf("hist -> %s",history_arr[4]);
    FILE * fp;
    fp = fopen(history_path,"w");
    while(strcmp(history_arr[j],"\n") != 0)
    {
        // printf("hist_arr[%d] -> %s\n",j,history_arr[j]);
        j++;
    }
    if(strcmp(arr,"\n") != 0)
    {
        fputs(new_arr,fp);
        // return history_arr;
    }
    else if(strcmp(arr,history_arr[0]) != 0)
    {
        fputs(new_arr,fp);
    }
    
    for(int i=0;i<j;i++)
    {
        if(i+1>=20)
        {
            break;
        }
        fputs(history_arr[i],fp);
    }
    fclose(fp);
    return history_arr;
}