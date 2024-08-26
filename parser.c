#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexer.c"

typedef enum{
    type_Variable_decelaration,type_Assignment,type_Operator,type_Conditionals,
    type_Equal
}junc_type;

typedef struct Tree_junc
{
junc_type type;
char name[MAX_TOKEN_LEN];
struct Tree_junc*LHS;
struct Tree_junc*RHS;
struct Tree_junc *condition;
struct Tree_junc *content;
int value;
operator;
char compare[2];
}Tree_junc;

Tree_junc* newjunc(junc_type type)
{
    Tree_junc*junc=(Tree_junc*) malloc(sizeof(Tree_junc));
    junc->type=type;
    junc->LHS=junc->RHS=junc->condition=junc->content=NULL;
    return junc;
}


Tree_junc* Variable_decelaration(FILE*file,Token*Available_Token)
{
    Tree_junc*junc=newjunc(type_Variable_decelaration);
    getNextToken(file,Available_Token);
    if (Available_Token->type==TOKEN_INT){
        strcpy(junc->value,Available_Token->text);
        getNextToken(file,Available_Token);
        if(Available_Token->type==TOKEN_IDENTIFIER){
           strcat(junc->name,Available_Token->text);
        }
    }
    else{
        printf("No variable decelared\n");
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_SEMICOLON){
        printf("Expected ';'\n");
    }
    return junc;
}

Tree_junc*Arithematic_operators(FILE*file,Token*Available_Token)
{
    Tree_junc*junc=newjunc(type_Operator);
    if(Available_Token->type==TOKEN_IDENTIFIER){
        junc->LHS=newjunc(TOKEN_IDENTIFIER);
        strcpy(junc->LHS,Available_Token->text);
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type==TOKEN_PLUS||Available_Token->type==TOKEN_MINUS||Available_Token->type==TOKEN_MULTIPLY||Available_Token->type==TOKEN_DIVIDE){
        junc->operator=*Available_Token;
    }
    else{
        printf("missing operator\n");
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type==TOKEN_IDENTIFIER||Available_Token->type==TOKEN_NUMBER){
        junc->RHS=newjunc(Available_Token->type);
         strcpy(junc->RHS,Available_Token->text);

    }
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_SEMICOLON){
        printf("Expected ';'\n");
    }
    return junc; 
}



Tree_junc*Assignment(FILE*file,Token*Available_Token)
{
    Tree_junc*junc=newjunc(type_Assignment);
    if(Available_Token->type==TOKEN_IDENTIFIER){
        junc->LHS=newjunc(TOKEN_IDENTIFIER);
        strcpy(junc->RHS,Available_Token->text);
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type==TOKEN_ASSIGN){
        junc->operator=*Available_Token;
    }
    else{
        printf("missing asignment\n");
    }
    getNextToken(file,Available_Token);
    junc->RHS=Arithematic_operators(file,Available_Token);
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_SEMICOLON){
        printf("Expected ';'\n");
    }
    return junc; 
}

Tree_junc*Equal(FILE*file,Token*Available_Token){
    Tree_junc*junc=newjunc(type_Equal);
    if (Available_Token->type==TOKEN_IDENTIFIER){
        junc->LHS=newjunc(TOKEN_IDENTIFIER);
        strcpy(junc->LHS,Available_Token->text);
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type==TOKEN_COMPARE){
        junc->compare[0]='=';
        junc->compare[1]='=';
    }
    else{
        printf("missing comparison\n");
    }
    getNextToken(file,Available_Token);
    junc->RHS=Arithematic_operators(file,Available_Token);
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_SEMICOLON){
        printf("Expected ';'\n");
    }
    return junc;
}



Tree_junc*Conditionals(FILE*file,Token*Available_Token){
    Tree_junc*junc=newjunc(type_Conditionals);
    if(Available_Token->type!=TOKEN_LPARAN){
        printf("expected'('\n");
    }
    getNextToken(file,Available_Token);
    junc->condition=Equal(file,Available_Token);
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_RPARAN){
        printf("expected')'\n");
    }
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_LBRACE){
        printf("expected'{'\n");
    }
    getNextToken(file,Available_Token);
    junc->content=Arithematic_operators(file,Available_Token);
    getNextToken(file,Available_Token);
    if(Available_Token->type!=TOKEN_RBRACE){
        printf("expected'}'\n");
    }
    return junc;
}


Tree_junc*Execution(FILE*file,Token*Available_Token){
    getNextToken(file,Available_Token);
    if(Available_Token->type==TOKEN_IDENTIFIER){
        return Assignment(file,Available_Token);
    }
    if(Available_Token->type==TOKEN_INT){
        return Variable_decelaration(file,Available_Token);
    }
    if(Available_Token->type==TOKEN_IF){
        return Conditionals(file,Available_Token);
    }
    else{
        printf("unknown declaration\n");
    }
    return 0;
}
