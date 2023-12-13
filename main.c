#include <stdio.h>

int main() {
    int n, m;
    
    printf("Enter the number of rows (n): ");
    scanf("%d", &n);
    printf("Enter the number of columns (m): ");
    scanf("%d", &m);

    int arr[n][m];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = 0;
        }
    }
    printf("Start up:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    while (1) {
        int x;
        
        printf("Number of people in the group: ");
        scanf("%d", &x);

        if (x < 0) {
            break;
        }
        
        printf("X=%d \n", x);
    }

    return 0;
}
