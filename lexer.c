#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAX_TOKEN_LEN 100
typedef enum{TOKEN_INT, TOKEN_IDENTIFIER,TOKEN_NUMBER,TOKEN_ASSIGN,TOKEN_PLUS,TOKEN_MINUS,TOKEN_MULTIPLY,TOKEN_SEMICOLON,TOKEN_DIVIDE,TOKEN_IF,TOKEN_LBRACE,TOKEN_RBRACE,TOKEN_LPARAN,TOKEN_RPARAN,TOKEN_UNKNOWN,TOKEN_EOF,TOKEN_COMPARE}TokenType;
typedef struct {TokenType type;
char text[MAX_TOKEN_LEN];
}Token;
void getNextToken(FILE*file, Token *token)
{
    int c;
    while ((c= fgetc(file))!=EOF)
    {
        if (isspace(c))
        continue;

        if (c=='=')
        {
            int character=fgetc(file);
            if (character =='='){
            token->type=TOKEN_COMPARE;
            strcpy(token->text,"==");
            return;
            }
            ungetc(character, file);
            token->type= TOKEN_ASSIGN;
            token->text[0]= '=';
            token->text[1]= '\0';
            return;
        }  
         if(isalpha(c)){
            int len=0;
            token->text[len++]=c;
            while (isalnum(c=fgetc(file)))
            {
                if (len<MAX_TOKEN_LEN-1) token->text[len++]=c;
            }
            ungetc(c,file);
            token->text[len]='\0';
            
            if(strcmp(token->text,"if")==0)
            token->type= TOKEN_IF;
            if(strcmp(token->text,"int")==0)
            token->type= TOKEN_INT;
            else token->type= TOKEN_IDENTIFIER;
            return;
         }

         if(isdigit(c)){
            int len=0;
            token->text[len++]=c;
            while (isalnum(c=fgetc(file)))
            {
                if (len<MAX_TOKEN_LEN-1) token->text[len++]=c;
            }
            ungetc(c,file);
            token->text[len]='\0';
            token->type=TOKEN_NUMBER;
            return;
         }

         switch (c)
         {
            case'+':token->type=TOKEN_PLUS;token->text[0]='+';token->text[1]='\0';return;
            case'-':token->type=TOKEN_MINUS;token->text[0]='-';token->text[1]='\0';return;
            case'*':token->type=TOKEN_MULTIPLY;token->text[0]='*';token->text[1]='\0';return;
            case'/':token->type=TOKEN_DIVIDE;token->text[0]='/';token->text[1]='\0';return;
            case'}':token->type=TOKEN_RBRACE;token->text[0]='}';token->text[1]='\0';return;
            case'{':token->type=TOKEN_LBRACE;token->text[0]='{';token->text[1]='\0';return;
            case')':token->type=TOKEN_RPARAN;token->text[0]=')';token->text[1]='\0';return;
            case'(':token->type=TOKEN_LPARAN;token->text[0]='(';token->text[1]='\0';return;
            case';':token->type=TOKEN_SEMICOLON;token->text[0]=';';token->text[1]='\0';return;
            default:token->type=TOKEN_UNKNOWN;token->text[0]=c;token->text[1]='\0';return;
         }
         token->type=TOKEN_EOF;
         token->text[0]='\0';
    }
    }
        


    

