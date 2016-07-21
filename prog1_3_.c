#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int operation(char op,int no1,int no2){
    int no=no1,j;
    switch(op){
        case '+': return no1+no2;
        case '-': return no1-no2;
        case '*': return no1*no2;
        case '/': return no1/no2;
        case '^': for(j=2;j<=no2;j++){
							no1*=no;
						}
                    return no1;
    }
    return -1;
}

int eval(char *expr,int X){
    int operands[strlen(expr)];
    char operators[strlen(expr)];
    int tos1=-1,tos2=-1;//1 is operands 2 is operators
    int i=0,q;
    int temp,no1,no2;
    while(expr[i]!='\0'){
        if(isalpha(expr[i])){
            operands[tos1+1]=X;
            tos1++;i++;
        }
        else if(isdigit(expr[i])){
            operands[tos1+1]=expr[i]-'0';
            tos1++;
            while(isdigit(expr[i+1])){
                operands[tos1]=(operands[tos1]*10)+(expr[++i]-'0');
            }
            i++;
        }
        else if(tos2==-1)
            operators[++tos2]=expr[i++];
        else if(expr[i]==')'){
            while(operators[tos2]!='('){
                temp=operation(operators[tos2--],operands[tos1-1],operands[tos1]);
                operands[tos1-1]=temp;
                tos1--;
            }
            tos2--;//to delete the (
			i++;
        }
        else if(expr[i]=='^'){
            if(operators[tos2]=='^'){
                temp=operation(operators[tos2],operands[tos1-1],operands[tos1]);
                operands[tos1-1]=temp;
                operators[tos2]=expr[i];
                tos1--;i++;
            }
            else
                operators[++tos2]=expr[i++];
        }
        else if(expr[i]=='('){
            operators[++tos2]=expr[i++];
        }
        else if(expr[i]=='*'||expr[i]=='/'){
            if(operators[tos2]=='^'||operators[tos2]=='*'||operators[tos2]=='/'){
                temp=operation(operators[tos2],operands[tos1-1],operands[tos1]);
                operands[tos1-1]=temp;
                operators[tos2]=expr[i];
                tos1--;i++;
            }
            else
                operators[++tos2]=expr[i++];
        }
        else if(expr[i]=='+'||expr[i]=='-'){
            if(operators[tos2]!='('){
                temp=operation(operators[tos2],operands[tos1-1],operands[tos1]);
                operands[tos1-1]=temp;
                operators[tos2]=expr[i];
                tos1--;i++;
            }
            else
                operators[++tos2]=expr[i++];
        }
	/*for(q=0;q<=tos1;q++)
		printf("operands%d\t",operands[q]);
	for(q=0;q<=tos2;q++)
		printf("operators%c\t",operators[q]);
	printf("%c\n",expr[i]);*/
    }
    while(tos1>0 && tos2>-1){
		temp=operation(operators[tos2--],operands[tos1-1],operands[tos1]);
        operands[tos1-1]=temp;
        tos1--;
	}
	return operands[tos1];
}

int main() {

    char expr[100];
	int result;
	int no=0;
	scanf("%s",expr);	
	while(no!=1000){
		scanf("%d",&no);
		if(no!=1000){
			result=eval(expr,no);
			printf("%d\n",result);
		}
	}   
    return 0;
}
