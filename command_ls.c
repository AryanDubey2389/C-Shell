#include "prompt.h"
#include "headers.h"
void command_ls(char ** fin1, char homepath[1000],int idx)
{
        // printf("fin -> %s\n",fin1[idx]);

    idx++;
    char path[1000];
    int k = 0, l = 0;
    while(fin1[k]!=NULL)
    {
        k++;
        l++;
    }
    // printf("k -> %d\n",k);
    int flg3 = -1, itr;
    for(int j = 0; j < k; j++)
    {
        // printf("fin1[%d] -> %s\n",j,fin1[j]);
        if(strcmp(fin1[j],">") == 0)
        {
            itr = j;
            flg3 = 0;
            break; 
        }
        else if(strcmp(fin1[j],"<") == 0)
        {
            itr = j;
            flg3 = 1; 
            break; 
        }
        else if(strcmp(fin1[j],">>") == 0)
        {
            itr = j;
            flg3 = 2; 
            break; 
        }
    }
    int flg1 = 0, flg2 = 0;
    if(flg3 != -1)
        k = itr - 1;
    l = k;
    while(1)
    {
        int temp1 = 0,temp2 = 0;
        // printf("fin -> %s\n",fin1[idx]);
        if(fin1[idx] == NULL || strcmp(fin1[idx],".") == 0)
        {
            int chk_lst = 0;
            if(k>2)
                chk_lst = 1;
            if(flg1 == 1 && flg2 ==1)
                listing_l(".",0,chk_lst,fin1);
            else
                listing(".",1,chk_lst,fin1);
        }
        else if(fin1[idx][0] == '~')
        {   
            if(strlen(fin1[idx]) == 1)
            {
                int chk_lst = 0;
                if(k>2)
                    chk_lst = 1;
                if(flg1 == 1 && flg2 ==1)
                    listing_l(homepath,1,chk_lst,fin1);
                else
                    listing(homepath,1,chk_lst,fin1);
            }
            else
            {
                // printf("hi\n");
                int chk_lst = 0;
                if(k>2)
                    chk_lst = 1;
                char s[1000] = "";
                s[0] = '.';
                for(int i = 1; i < strlen(fin1[idx]); i++)
                {
                    s[i] = fin1[idx][i];
                }
                // printf("s->%s\n",s);
                if(flg1 == 1 && flg2 ==1)
                    listing_l(s,0,chk_lst,fin1);
                else
                    listing(s,1,chk_lst,fin1);
            }
        }
        else if(fin1[idx][0] != '-')
        {
            int chk_lst = 0;
            if(k>2)
                chk_lst = 1;
            if(flg1 == 1 && flg2 == 1)
                listing_l(fin1[idx],0,chk_lst,fin1);
            else
                listing(fin1[idx],1,chk_lst,fin1);
        }
        else if(strcmp(fin1[idx],"-a") == 0)
        {
            // if(cd_len > 5)
            //     token = strtok(NULL, "\n");
            // printf("token -> %s\n",token);
            // printf("token leng -> %lu",strlen(token));
            flg1 = 1;
            idx++;
            getcwd(path, 1000);
            int flg = -1;
            // if(token != "~")
            flg = chdir(fin1[idx]);
            // printf("flg -> %d\n", flg);
            chdir(path);
            if(fin1[idx] == NULL || strcmp(fin1[idx],".") == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                if(flg1 == 1 && flg2 ==1)
                    listing_l(".",0,chk_lst,fin1);
                else
                    listing(".",0,chk_lst,fin1);
            }
            else if(fin1[idx][0] == '~')
            {
                if(strlen(fin1[idx]) == 1)
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    if(flg1 == 1 && flg2 ==1)
                        listing_l(homepath,0,chk_lst,fin1);
                    else
                        listing(homepath,0,chk_lst,fin1);
                }
                else
                {
                    // printf("hi\n");
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    char s[1000] = "";
                    s[0] = '.';
                    for(int i = 1; i < strlen(fin1[idx]); i++)
                    {
                        s[i] = fin1[idx][i];
                    }
                    // printf("s->%s\n",s);
                    if(flg1 == 1 && flg2 ==1)
                        listing_l(s,0,chk_lst,fin1);
                    else
                        listing(s,0,chk_lst,fin1);
                }
            } 
            else if(strcmp(fin1[idx],"-l") == 0)
            {
                flg2 = 1;
                // printf(" token -> %s\n", (token));
                idx++;
                // int tk_len = strlen(token);
                // char* part = strtok(token," ");
                // // printf(" part -> %s\n", (part));
                // if(tk_len > 2)
                //     part = strtok(NULL,"");
                // else
                
                if(fin1[idx] == NULL)
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(".",0,chk_lst);
                    temp1 = 1;
                }
                else if(fin1[idx][0] == '-')
                {
                    // printf("hi\n");
                    while(fin1[idx][0] == '-')
                    {
                        // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
                        idx++;
                        k--;
                        // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
                        if(fin1[idx] == NULL)
                            break;
                    }
                    // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
                        // if(fin)
                }
                if(fin1[idx] == NULL)
                {
                    if(temp1 == 0)
                    {
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        listing_l(".",0,chk_lst,fin1);
                    }
                    // temp1 = 1;
                }
                else if(fin1[idx][0] == '~')
                {
                    if(strlen(fin1[idx]) == 1)
                    {
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        listing_l(homepath,0,chk_lst,fin1);
                    }
                    else
                    {
                        // printf("hi\n");
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        char s[1000] = "";
                        s[0] = '.';
                        for(int i = 1; i < strlen(fin1[idx]); i++)
                        {
                            s[i] = fin1[idx][i];
                        }
                        // printf("s->%s\n",s);
                        listing_l(s,0,chk_lst);
                    }
                }
                else
                {
                    // printf("hi\n");
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(fin1[idx],0,chk_lst,fin1);
                }
            }
            else if(flg == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                if(flg1 == 1 && flg2 ==1)
                    listing_l(fin1[idx],0,chk_lst,fin1);
                else
                    listing(fin1[idx],0,chk_lst,fin1);
            }
            else if(flg != 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                if(flg1 == 1 && flg2 ==1)
                    listing_l(fin1[idx],0,chk_lst,fin1);
                else
                    listing(fin1[idx],0,chk_lst,fin1);
            }
        }
        else if(strcmp(fin1[idx],"-l") == 0)
        {
            flg2 = 1;
            idx++;
            // if(cd_len > 5)
            //     token = strtok(NULL, "\n");
            // printf("length token -> %lu\n", strlen(token));
            getcwd(path, 1000);
            // int flg = -1;
            // if(token != "~")
            int flg = -1;
            flg = chdir(fin1[idx]);
            // printf("flg -> %d\n", flg);
            chdir(path);
            if(fin1[idx] == NULL || strcmp(fin1[idx],".") == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                listing_l(".",1,chk_lst,fin1);
            }
            else if(fin1[idx][0] == '~')
            {
                if(strlen(fin1[idx]) == 1)
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(homepath,0,chk_lst,fin1);
                }
                else
                {
                    // printf("hi\n");
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    char s[1000] = "";
                    s[0] = '.';
                    for(int i = 1; i < strlen(fin1[idx]); i++)
                    {
                        s[i] = fin1[idx][i];
                    }
                    // printf("s->%s\n",s);
                    listing_l(s,0,chk_lst,fin1);
                }
            }
            else if(strcmp(fin1[idx],"-a") == 0)
            {
                flg1 = 1;
                idx++;
                // int tk_len = strlen(token);
                // // printf(" token -> %s\n", (token));
                // char* part = strtok(token," ");
                // // printf(" token -> %s\n", (part));
                // if(tk_len > 2)
                //     part = strtok(NULL,"");
                // else
                if(fin1[idx] == NULL)
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(".",0,chk_lst,fin1);
                    temp2 = 1;
                }
                else if(fin1[idx][0] == '-')
                {
                    // printf("hi\n");
                    while(fin1[idx][0] == '-')
                    {
                        // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
                        idx++;
                        k--;
                        if(fin1[idx] == NULL)
                            break;
                    }
                    // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
                        // if(fin)
                }
                if(fin1[idx] == NULL)
                {
                    if(temp2 == 0)
                    {
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        listing_l(".",0,chk_lst,fin1);
                    }
                }
                else if(fin1[idx][0] == '~')
                {
                    if(strlen(fin1[idx]) == 1)
                    {
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        listing_l(homepath,0,chk_lst,fin1);
                    }
                    else
                    {
                        // printf("hi\n");
                        int chk_lst = 0;
                        if(k>3)
                            chk_lst = 1;
                        char s[1000] = "";
                        s[0] = '.';
                        for(int i = 1; i < strlen(fin1[idx]); i++)
                        {
                            s[i] = fin1[idx][i];
                        }
                        // printf("s->%s\n",s);
                        listing_l(s,0,chk_lst,fin1);
                    }
                }
                else
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(fin1[idx],0,chk_lst,fin1);
                }
            }
            else if(flg == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                if(flg1 == 1 && flg2 == 1)
                    listing_l(fin1[idx],0,chk_lst,fin1);
                else
                    listing_l(fin1[idx],1,chk_lst,fin1);
            }
            else if(flg != 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                listing_l(fin1[idx],0,chk_lst,fin1);
            }
        }
        else if(strcmp(fin1[idx],"-al") == 0 || strcmp(fin1[idx],"-la") == 0)
        {
            flg1 = 1;
            flg2 = 1;
            idx++;
            // if(cd_len > 6)
            //     token = strtok(NULL, "\n");
            getcwd(path, 1000);
            int flg = -1;
            // if(token != "~")
                flg = chdir(fin1[idx]);
            // printf("flg -> %d\n", flg);
            chdir(path);
            if(fin1[idx] == NULL || strcmp(fin1[idx],".") == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                listing_l(".",0,chk_lst,fin1);
            }
            else if(fin1[idx][0] == '~')
            {
                if(strlen(fin1[idx]) == 1)
                {
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    listing_l(homepath,0,chk_lst,fin1);
                }
                else
                {
                    // printf("hi\n");
                    int chk_lst = 0;
                    if(k>3)
                        chk_lst = 1;
                    char s[1000] = "";
                    s[0] = '.';
                    for(int i = 1; i < strlen(fin1[idx]); i++)
                    {
                        s[i] = fin1[idx][i];
                    }
                    // printf("s->%s\n",s);
                    listing_l(s,0,chk_lst,fin1);
                }
            }
            else if(flg == 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                listing_l(fin1[idx],0,chk_lst,fin1);
            }
            else if(flg != 0)
            {
                int chk_lst = 0;
                if(k>3)
                    chk_lst = 1;
                listing_l(fin1[idx],0,chk_lst,fin1);
            }
        }
        if(idx >= l-1)
            break;
        if(k>2)
            printf("\n");
        idx++;
        // printf("fin1[%d] -> %s\n",idx,fin1[idx]);
    }
}