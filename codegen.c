#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"parser.c"
void assemblycode(Tree_junc*junc,FILE*file)
{
    switch(junc->type)
    {
      case type_Variable_decelaration:
      if(strcmp(junc->name,"a")==0){
        fprintf(file,"ldi ro,%d\n",junc->value);
      }
      if(strcmp(junc->name,"b")==0){
        fprintf(file,"ldi r1,%d\n",junc->value);
      }
      if(strcmp(junc->name,"a")==0){
        fprintf(file,"ldi r2,%d\n",junc->value);
      }
      break;
    

    case type_Assignment:
    if(strcmp(junc->LHS,"a")==0){
        fprintf(file,"mov r0,r1\n");
    }
    if(strcmp(junc->LHS,"b")==0){
        fprintf(file,"mov r1,r2\n");
    }
    if(strcmp(junc->LHS,"c")==0){
        fprintf(file,"mov r2,r3\n");
    }
    break;


    case type_Operator:
    assemblycode(junc->LHS,file);
    assemblycode(junc->RHS,file);
    switch(junc->operator)
    {
        case TOKEN_PLUS:
        fprintf(file,"add R0,R1\n");
        break;
        case TOKEN_MINUS:
        fprintf(file,"sub R0,R1\n");
        break;
        default:
        fprintf(file,"unkown operator");
    }
    break;

    case type_Equal:
    assemblycode(junc->LHS,file);
    assemblycode(junc->RHS,file);
    fprintf(file,"cmp r0,r1\n");
    fprintf(file,"je LABLE r2,%d\n");
    break;


    case type_Conditionals:
    fprintf(file,"lable_if:\n");
    assemblycode(junc->condition,file);
    fprintf(file,"jne Lable\n");
    assemblycode(junc->content,file);
    fprintf(file,"lable:\n");
    break;    
    }
}   

