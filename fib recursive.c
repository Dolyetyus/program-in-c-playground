#include <stdio.h>

int fibonacci(int n, int first, int second, int sum){
    
    if (n==0){
        return sum;
    }
    
    printf("%d ", sum);
    sum=first+second;
    first=second;
    second=sum;
    n--;
    fibonacci(n, first, second, sum);
}

int main()
{
    int n;
    
    printf("Enter n ");
    scanf("%d", &n);
    fibonacci(n, 0, 1, 1);

    return 0;
}
