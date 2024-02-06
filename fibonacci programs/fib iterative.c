#include <stdio.h>

void fibonacci(int n){
    int first = 0;
    int second = 1;
    int sum = 1;
    
    while (n>0){
        printf("%d ", sum);
        sum=first+second;
        first=second;
        second=sum;
        n--;
    }
}

int main()
{
    int n;
    
    printf("Enter n ");
    scanf("%d", &n);
    fibonacci(n);

    return 0;
}
