#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define SIZE 310

typedef struct 
{
  char decimal[SIZE];
  int sign;
}BIG_INT;

void remove_zeroes(BIG_INT *num1,BIG_INT *num2)
{
   int start=0;
  while (num1->decimal[start] == '0' && num1->decimal[start + 1] != '\0') 
  {
  start++;
  }
  memmove(num1->decimal, num1->decimal + start, strlen(num1->decimal + start) + 1);

  start=0;
  while (num2->decimal[start] == '0' && num2->decimal[start + 1] != '\0') 
  {
   start++;
  }
  memmove(num2->decimal, num2->decimal + start, strlen(num2->decimal + start) + 1);
}

int max(int n1,int n2)
{ if(n1>n2) return n1;
  else  return n2;}

BIG_INT add(BIG_INT *num1,BIG_INT *num2)
{  
  int len1=strlen(num1->decimal);
  int len2=strlen(num2->decimal);
  int i=len1-1,j=len2-1;
  int carry=0,cur_sum,n=max(len1,len2);
  BIG_INT result;
  result.decimal[n+1]='\0';

 

  while(i>=0 && j>=0)
  {
    cur_sum=carry+(num1->decimal[i]-'0')+(num2->decimal[j]-'0');
    result.decimal[n]=(cur_sum%10)+'0';
    carry=cur_sum/10;
    i--;
    j--;
    n--;
  }
  while(i>=0)
  {
    cur_sum=carry+(num1->decimal[i]-'0');
    result.decimal[n]=(cur_sum%10)+'0';
    carry=cur_sum/10;
    i--;
    n--;
  }

  while(j>=0)
  {
    cur_sum=carry+(num2->decimal[j]-'0');
    result.decimal[n]=(cur_sum%10)+'0';
    carry=cur_sum/10;
    j--;
    n--;
  }
 
  
  if(carry==1){result.decimal[0]='1';}
  
  else result.decimal[0]='0';

  int  start=0;
     while (result.decimal[start] == '0' && result.decimal[start + 1] != '\0') 
     {
        start++;
     }
     memmove(result.decimal, result.decimal + start, strlen(result.decimal + start) + 1);

  
  return result;
}

BIG_INT subtract(BIG_INT *num1,BIG_INT *num2)
{
  int len1=strlen(num1->decimal);
  int len2=strlen(num2->decimal);
  int borrow=0,cur_diff,n=max(len1,len2);
  BIG_INT result;
  result.decimal[n]='\0';
  n--;

  if((strcmp(num1->decimal,num2->decimal)<0 && len1==len2) || len1<len2 )
  {BIG_INT temp;
   temp=*num1;
   *num1=*num2;
   *num2=temp;
   result.sign=0;
   len1=strlen(num1->decimal);
   len2=strlen(num2->decimal);
  }

  else result.sign=1;

  
  int i=len1-1,j=len2-1;

  while(i>=0 && j>=0)
  {
    cur_diff=(num1->decimal[i]-'0')-(num2->decimal[j]-'0')-borrow;
    if(cur_diff<0)
    {borrow=1; 
     cur_diff=10+cur_diff;}
    else borrow=0;

    result.decimal[n]=cur_diff+'0';
    i--;
    j--;
    n--;
  }

  while(i>=0)
  {
    cur_diff=(num1->decimal[i]-'0')-borrow;
    if(cur_diff<0)
    {borrow=1; 
     cur_diff=10+cur_diff;}
    else borrow=0;

    result.decimal[n]=cur_diff+'0';
    i--;
    n--;
  }

  while(j>=0)
  {
    cur_diff=0-(num2->decimal[i]-'0')-borrow;
    if(cur_diff<0)
    {borrow=1; 
     cur_diff=10+cur_diff;}
    else borrow=0;

    result.decimal[n]=cur_diff+'0';
    j--;
    n--;
  }

  int start=0;
     while (result.decimal[start] == '0' && result.decimal[start + 1] != '\0') 
     {
        start++;
     }
     memmove(result.decimal, result.decimal + start, strlen(result.decimal + start) + 1);
    

  return result;
}

void get_value(BIG_INT *num)
{
  int repeat=1;
  
  while(repeat)
  {
   printf("number input:");
   scanf("%s",num->decimal);
   if(num->decimal[0]=='+' || num->decimal[0]=='-' || (num->decimal[0]>='0'&&num->decimal[0]<='9'))
  {
   repeat=0;
   for(int i=1;num->decimal[i]!='\0';i++)
   {
    if(num->decimal[i]<'0' || num->decimal[i]>'9')
    {
      printf("INVALID INPUT\n");
      repeat=1;
      break;
    }

    else repeat=0;
   }
  }

  else printf("INVALID INPUT\n");

 }

  if(num->decimal[0]=='+')
  {num->sign=1;
   num->decimal[0]='0';
   memmove(num->decimal, num->decimal + 1,strlen(num->decimal)+1);
  }
  else if(num->decimal[0]=='-')
  {num->sign=0;
   memmove(num->decimal, num->decimal + 1,strlen(num->decimal)+1);
  }
  else{ num->sign=1; }

}

BIG_INT multiplication(BIG_INT *num1, BIG_INT *num2) {
    BIG_INT result;
    int n = strlen(num1->decimal), m = strlen(num2->decimal);

    int arr1[n], arr2[m];
    int arr3[m + n];
    memset(arr3, 0, sizeof(arr3));

    for (int i = 0; i < n; i++) {
        arr1[i] = num1->decimal[i] - '0';
    }
    for (int i = 0; i < m; i++) {
        arr2[i] = num2->decimal[i] - '0';
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int curr_result = arr2[i] * arr1[j];
            arr3[i + j + 1] += curr_result;
            arr3[i + j] += arr3[i + j + 1] / 10;
            arr3[i + j + 1] %= 10;
        }
    }

    int index = 0;
    int start = 0;

    while (start < m + n - 1 && arr3[start] == 0) {
        start++;
    }

    for (int i = start; i < m + n; i++) {
        result.decimal[index++] = arr3[i] + '0';
    }

    result.decimal[index] = '\0';

    result.sign = (num1->sign == num2->sign) ? 1 : 0;

    return result;
}

void functions_execution(BIG_INT *num1,BIG_INT *num2,BIG_INT *add_result,BIG_INT *sub_result,BIG_INT *multi_result)
{ 
  remove_zeroes(num1,num2);

  if(num1->sign==1 && num2->sign==0)
  {
    *add_result=subtract(num1,num2);
    *sub_result=add(num1,num2);
    sub_result->sign=1;
  }

  else if(num1->sign==0 && num2->sign==1)
  {
    *add_result=subtract(num2,num1);
    *sub_result=add(num1,num2);
    sub_result->sign=0;
  }

  else if(num1->sign==0 && num2->sign==0)
  {
    *add_result=add(num1,num2);
    add_result->sign=0;
    *sub_result=subtract(num2,num1);
  }

  else
  {
    *add_result=add(num1,num2);
    add_result->sign=1;
    *sub_result=subtract(num1,num2);
  }

   *multi_result=multiplication(num1,num2);
}

void print_number(BIG_INT *num)
{
    if(num->sign==0)
    {printf("-%s \n",num->decimal);}

    else
    {printf("%s \n",num->decimal);}
}


int main()
{ 
  int repeat=1;
  printf("+/*+/*+/*+CALCI+/*+/*+/*+\n");
  while(repeat)
  {
  BIG_INT n1,n2,n3,n4,n5;
  get_value(&n1);
  get_value(&n2);
  functions_execution(&n1,&n2,&n3,&n4,&n5);
  
  printf("SUM = ");
  print_number(&n3);
  printf("DIFFERENCE = ");
  print_number(&n4);
  printf("PRODUCT=");
  print_number(&n5);
  printf("want to continue? PRESS 1 ELSE 0\n");
  scanf("%d",&repeat);
  }
  return 0;
}
