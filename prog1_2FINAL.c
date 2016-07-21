#include<stdio.h>
#include<string.h>
#include<ctype.h>
int parse(char *expr,int X,int *res)
{
	int i=0,j,oppos,flagneg=0;
	int no1,no2,no;
	char op;
	if(isalpha(expr[i])){
		no1=X;
	}
	else{
		if(expr[i]=='-')
		{
			i++;
			flagneg=1;
		}
		no1=(expr[i]-48);
		while(isdigit(expr[i+1]))
		{
			i++;
			no1=(no1*10)+(expr[i]-48);
		}
		if(flagneg)
			no1=(-no1);
	}
	i++;
	while(i<strlen(expr))
	{
		oppos=i;
		char op=expr[oppos];
		i++;
		if(expr[i-1]==expr[i] && expr[i]=='-')
		{
			op='+';
			i++;
		}
		printf("%c,%c\n",expr[i-1],expr[i]);
		no2=0;
		if(isalpha(expr[i]))
			no2=X;
		else if(isdigit(expr[i]) && i<strlen(expr)){
			no2=(expr[i]-48);
			while(isdigit(expr[i+1]))
			{
				i++;
				no2=(no2*10)+(expr[i]-48);
			}
		}
		switch(op){
			case '+': no1=no1+no2;
						break;
			case '-': no1=no1-no2;
						break;
			case '*': no1=no1*no2;
						break;
			case '/': no1=no1/no2;
						break;
			case '^': no=no1;
						for(j=2;j<=no2;j++){
							no1*=no;
						}
						break;
		}
		printf("%dno1:\n",no1);
	}
	*res=no1;
	return 0;
}
int bracketparse(char *expr,int X,int *res)
{
	int i=0,j=0,temp,k;
	while(expr[i]!='('&& expr[i]!='\0'){i++;}
	if(expr[i]=='\0'){
		parse(expr,X,res);
		return 2;
	}	//to signify 
	while(expr[i]=='('){i++;}
	char exp[100];
	k=i;//save start of bracket
	while(expr[i]!=')'){
		exp[j]=expr[i];
		//printf("%c",exp[j]);
		j++;i++;	
	}
	exp[j]='\0';
	parse(exp,X,&temp);
	//find digit length and convert to string
	printf("%dtenmp\n",temp);
	int len=1,divisor=10;
	while(temp/divisor!=0){
		len++;
		divisor*=10;	
	}
	char tempno[10];
	int q=0,temppos;
	if(temp<0)
		temppos=-1*temp;
	else
		temppos=temp;
	divisor/=10;
	for(q=0;q<len;q++){
		tempno[q]=(temppos/divisor)+48;
		temppos=temppos%divisor;
		divisor/=10;
	}
	tempno[q]='\0';
	printf("%s\n",tempno);
	for(j=0;j<k-1;j++){
		exp[j]=expr[j];
	}
    if(temp<0){
		len++;
        exp[k-1]='-';
        for(q=k;q<(k+len-1);q++)
            exp[q]=tempno[q-k];
    }
	else{
		for(q=k-1;q<(k+len-1);q++){	
			exp[q]=tempno[q-k+1];
		}
	}
	for(j=(k+len-1);expr[j]!='\0';j++){
		exp[j]=expr[++i];
	}
	printf("%s\n",exp);
	bracketparse(exp,X,res);
	return 0;
}
int main()
{	
	char str[100];
	int result;
	int status;
	int no=0;
	scanf("%s",str);	
	while(no!=1000){
		scanf("%d",&no);
		if(no!=1000){
			status=bracketparse(str,no,&result);
			printf("%d\n",result);
		}
	}
	return 0;
}
