#include <stdio.h>

void staircase(unsigned int n) {
    for (int i = 1; i<=n; i++){
        for(int ii = n-i; ii>0; ii--){
            printf(" ");
        }
        for(int iii = i; iii>0; iii--){
            printf("#");
        }
        printf("\n");
    }
}

int main()
{
    unsigned int n;
    
    scanf("%u", &n);

    staircase(n);

    return 0;
}
