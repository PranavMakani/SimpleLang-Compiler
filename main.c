#include<stdio.h>
#include"lexer.c"
#include"parser.c"
#include"codegen.c"
 

int main(){
    FILE*file=fopen("input.txt","r");

    Token token;
    getNextToken(file,&token);

    Tree_junc*root=Execution(file,&token);
      if (root){
        FILE*file=stdout;
        assemblycode(root,file);
      }
      else{
        printf("error in execution");
      }
      fclose(file);
      return 0;

    
}
