#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define keywordSum 8
const char * keyword[keywordSum] = { "if","else","for","while","do","int",
                               "read","write"};
const char singleword[50] = "{}*();,:";
const char doubleword[50] = "><=!";
const char selfoperator[50] = "+-";
char *Scanin,*Scanout;
FILE * fin,* fout;

void Scanner()
{
    char ch,token[40];
    int i,n;
    int linenum=0;

    
    ch = getc(fin);
    while(ch != EOF)
    {
        while(ch == ' '||ch == '\n' ||ch == '\t'||ch == '\r')
        {
            if(ch == '\n')
                linenum++;
            ch = getc(fin);
        }
        if (isalpha(ch))
        {
            token[0] = ch;
            i = 1;
            ch = getc(fin);
            while(isalnum(ch))
            {
                token[i++] = ch;
                ch = getc(fin);
            }
            token[i] = '\0';
            n = 0;
            while((n<keywordSum)&&strcmp(token,keyword[n]))
                n++;
            if (n >= keywordSum)
                fprintf(fout,"%s\t%s\n","ID",token);
            else
                fprintf(fout,"%s\t%s\n",token,token);
        }
        /* numbers */
        else if (isdigit(ch))
        {
            token[0] = ch;
            i = 1;
            ch = getc(fin);
            while(isdigit(ch))
            {
                token[i++] = ch;
                ch = getc(fin);
            }
            token[i] = '\0';
            fprintf(fout,"%s\t%s\n","NUM",token);
        }
        /* {}*();,: */
        else if (strchr(singleword,ch) > 0)
        {
            token[0] = ch;
            token[1] = '\0';
            ch = getc(fin);
            fprintf(fout,"%s\t%s\n",token,token);
        }
        /* >= <= == != */
        else if (strchr(doubleword,ch) > 0)
        {
            token[0] = ch;
            ch =getc(fin);
            if (ch == '=')
            {
                token[1] = ch;
                token[2] = '\0';
                ch = getc(fin);
            }
            else
                token[1] = '\0';
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if (strchr(selfoperator,ch)>0)
        {
            token[0] = ch;
            ch = getc(fin);
            if(ch == token[0])
            {
                token[1] = ch;
                token[2] = '\0';
                ch = getc(fin);
            }
            else
                token[1] = '\0';
            fprintf(fout,"%s\t%s\n",token,token);
        }
        else if (ch == '/')
        {
            ch = getc(fin);
            if (ch == '*')
            {
                int flag = 0;
                char ch1;
                ch1 = getc(fin);
                do
                {
                    ch = ch1;
                    ch1 = getc(fin);
                    if(ch == '*'&&ch1 == '/')
						flag =1;
                }while((ch!='*'||ch1!='/')&&ch1!=EOF);
                if(!flag)
                    printf("except */  !\n");
                ch = getc(fin);
            }
            else
            {
                token[0] = '/';
                token[1] = '\0';
                fprintf(fout,"%s\t%s\n",token,token);
            }
        }
        else
        {
            token[0] = ch;
            token[1] = '\0';
            ch = getc(fin);
            printf("%s %d %s\t%s\n","ERROR at line:",linenum,"unrec symbol",token);
        }
    }
    fclose(fin);
    fclose(fout);
}

int main(int argc, char * argv[])
{
    if (argc <= 2)
    {
        printf("Please use as : lex Scanin Scanout\n");    
    }
    else if (argc == 3)
    {
        Scanin = argv[1];
        Scanout = argv[2];
    }
    
    if ((fin = fopen(Scanin,"r")) == NULL)
    {
        printf("open error\n");
        exit(-1);
    }
    if ((fout = fopen(Scanout,"w")) == NULL)
    {
        printf("creat file fail\n");
        exit(-1);
    }
    
    Scanner();
 
    return 0;
}      
      
  
