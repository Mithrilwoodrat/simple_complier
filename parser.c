#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/*=================================================*/
void show_error(int es);
int TESTparse();
int program();
int compound_stat();
int statement();
int expression_stat();
int expression();
int bool_expr();
int additive_expr();
int additive_expr2();
int term();
int term2();
int factor();
int if_stat();
int while_stat();
int for_stat();
int write_stat();
int read_stat();
int compound_stat();
int declaration_stat();
int declaration_list();
int declaration_list2();
int statement_list();
int statement_list2();
int compound_stat();
/*================================*/
char token[20],token1[40];
char *Scanin;
FILE * fp;

char * ERROR_NUM[] =  { "lack { !\n", "lack } !\n",
                 "lack identifier\n", "lack semicolon - ; !\n",
                 "lack ( \n", "lack ) \n",
                 "lack operand \n"
};

int TESTparse()
{
    return program();
}
/*1) <program>→{<declaration_list><statement_list>}*/
int program()
{
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"{"))
    {
        printf("lack { !\n");
        return 1;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = declaration_list()) !=0)
        return es;
    if ((es = statement_list()) !=0)
        return es;
    if(strcmp(token, "}"))
    {
        printf("lack } !\n");
        return 2;
    }
    return 0;
}
/*
  <declaration_list>→<declaration_list>’  
  <declaration_list>’→ int ID <declaration_list>’ | ε*/
int declaration_list()
{
    return declaration_list2();
}

int declaration_list2()
{
    int es;
    if(strcmp(token,"int")==0)
    {
        if ((es = declaration_stat()) != 0)
            return es;
        if ((es = declaration_list2()) != 0)
            return es;
    }
    return 0;
}

int declaration_stat()
{
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"ID"))
    {
        printf("lack identifier\n");
        return 3;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,";"))
    {
        printf("lack semicolon - ; !\n");
        return 4;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    return 0;
}

/*<statement_list>→<statement_list>’
  <statement_list>’→<statement><statement_list>’| ε*/
int statement_list()
{
    return statement_list2();   
}

int statement_list2()
{
    int es = 0;
    if (feof(fp))
    {
        printf("lack } !\n");
        return 2;
    }
    if(strcmp(token,"}"))
    {
        if ((es = statement()) != 0)
            return es;
        if ((es = statement_list2()) != 0)
            return es;
    }
    return 0;
}
int statement()
{
    int es;
    if(strcmp(token,"if") == 0)
    {
        if ((es = if_stat()) != 0)
            return es;
    }
    if(strcmp(token,"while") == 0)
    {
        if ((es = while_stat()) != 0)
            return es;
    }
    if(strcmp(token,"for") == 0)
    {
        if ((es = for_stat()) != 0)
            return es;
    }
    if(strcmp(token,"read") == 0)
    {
        if ((es = read_stat()) != 0)
            return es;
    }
    if(strcmp(token,"write") == 0)
    {
        if ((es = write_stat()) != 0)
            return es;
    }
    if(strcmp(token,"{") == 0)
    {
        if ((es = compound_stat()) != 0)
            return es;
    }
    if (strcmp(token,"ID") == 0||strcmp(token,"NUM") == 0 ||strcmp(token,"(") == 0|| strcmp(token,";") == 0)
    {
        if ((es = expression_stat()) != 0)
            return es;
    }
    return 0;
}

int if_stat()
{
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"("))
    {
        printf("lack ( \n");
        return 5;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = expression()) != 0)
        return es;
    if(strcmp(token,")"))
    {
        printf("lack ) \n");
        return 6;
    }
    
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    
    if ((es=statement()) != 0)
        return es;
    
    if(strcmp(token,"else") == 0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = statement()) != 0)
            return es;
    }
    return 0;
}
int while_stat()
{
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"("))
    {
        printf("lack ( \n");
        return 5;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = expression()) != 0)
        return es;
    if(strcmp(token,")"))
    {
        printf("lack ) \n");
        return 6;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = statement()) != 0)
        return es;
    return 0;
}
/* <for_stat>:::=for(<expr>;<expr>;<expr>)<statment>*/
int for_stat()
{
    int i;
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"("))
    {
        printf("lack ( \n");
        return 5;
    }
    for(i=0;i<2;i++)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = expression()) != 0)
            return es;
        if(strcmp(token,";"))
        {
            printf("lack semicolon - ; !\n");
            return 4;
        }
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = expression()) != 0)
        return es;
    if(strcmp(token,")"))
    {
        printf("lack ) \n");
        return 6;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = statement()) != 0)
        return es;
    return 0;
}
/*<write_stat>::=write<expression>;*/
int write_stat()
{
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = expression()) != 0)
        return es;
    if(strcmp(token,";"))
    {
        printf("lack semicolon - ; !\n");
        return 4;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    return 0;
}
/* <read_stat>:: = read ID;*/
int read_stat()
{
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,"ID"))
    {
        printf("lack identifier\n");
        return 3;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if(strcmp(token,";"))
    {
        printf("lack semicolon - ; !\n");
        return 4;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    return 0;
}
/*<compound_stat>::={<statement_list>}*/
int compound_stat()
{
    int es;
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    if ((es = statement_list()) != 0)
        return es;
    if(strcmp(token,"}"))
    {
        printf("lack } !\n");
        return 2;
    }
    fscanf(fp,"%s %s\n",&token,&token1);
    printf("%s %s\n", token,token1);
    return es;
}
/*<expression_stat>::=<expression>;|;*/
int expression_stat()
{
    int es = 0;
    if(strcmp(token,";")==0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        return 0;
    }
    
    if ((es = expression()) != 0)
        return es;
    if(strcmp(token,";")==0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        return 0;
    }
    else
        return 4;
    return 0;
}

/*<expr>::=ID=<bool_expr>|<bool_expr>*/
int expression()
{
    int fileadd1=ftell(fp),fileadd2;
    char token2[20],token3[40];
    int es;
    if(strcmp(token,"ID")==0)
    {
        fileadd2 = ftell(fp);
        fscanf(fp,"%s %s\n",&token2,&token3);
        //printf("%s %s\n", token2,token3);
        if(strcmp(token2,"=")==0) //if symbol is "=" print it
        {
            printf("%s %s\n", token2,token3);
            fscanf(fp,"%s %s\n",&token,&token1);
            printf("%s %s\n", token,token1);
            if ((es = bool_expr()) != 0)
                return es;
        }
        else
        {
            fseek(fp,fileadd2,0);
            //printf("%s %s\n",token,token1);
            if ((es = bool_expr()) != 0)
                return es;
            
        }
    }
    else
        if ((es = bool_expr()) != 0)
            return es;

    return 0;
}
/*<bool_expr>:=<additive_expr>|<additive_expr>(>|<|>=|<=|==|!=)<additive_expr>*/
int bool_expr()
{
    int es;
    if ((es = additive_expr()) != 0)
        return es;
    if(strcmp(token,">")==0||strcmp(token,">=")==0||
       strcmp(token,"<")==0||strcmp(token,"<=")==0||
       strcmp(token,"==")==0||strcmp(token,"!=")==0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = additive_expr()) != 0)
            return es;
    }
    return 0;
}
/* < additive_expr>→< term >< additive_expr>’
   < additive_expr>’→ (+<term>|-<term>)< additive_expr>’ | ε*/
int additive_expr()
{
    int es;
    if ((es = term()) != 0)
        return es;
    if ((es = additive_expr2()) != 0)
        return es;
    return 0;
}
int additive_expr2()
{
    int es;
    if(strcmp(token,"+") == 0||strcmp(token,"-") == 0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = term()) != 0)
            return es;
        
        if ((es = additive_expr2()) != 0)
            return es;
    }
    return 0;
}
/* < term >→< factor >< term >’
   < term >’→(*<factor>|/<factor>)< term >’ | ε */
int term()
{
    int es;
    if ((es = factor()) != 0)
        return es;
    if ((es = term2()) != 0)
        return es;
    return 0;
}
int term2()
{
    int es;
    if(strcmp(token,"*")== 0||strcmp(token,"/") == 0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = factor()) != 0)
            return es;
        if ((es = term2()) != 0)
            return es;
    }
    return 0;
}
/*<factor>::=(<expression>)|ID|NUM*/
int factor()
{
    int es;
    if(strcmp(token,"(")==0)
    {
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
        if ((es = expression()) != 0)
            return es;
        if(strcmp(token,")"))
        {
            printf("lack ) \n");
            return 6;
        }
        fscanf(fp,"%s %s\n",&token,&token1);
        printf("%s %s\n", token,token1);
    }
    else
    {
        if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0)
        {
            fscanf(fp,"%s %s\n",&token,&token1);
            printf("%s %s\n", token,token1);
            return 0;
        }
        else
        {
            printf("lack operand \n");
            return 7;
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please use as : parser Scanin\n");    
    }
    else if (argc == 2)
    {
        Scanin = argv[1];
    }
    
    if ((fp = fopen(Scanin,"r")) == NULL)
    {
        printf("open error\n");
        exit(-1);
    }
    int es = TESTparse();
    printf("=========Parse result======");
    if(!es)
        printf("parse success!\n");
    else
        printf("error,exit(%d)\n",es);
    
    fclose(fp);
    return 0;
}  
