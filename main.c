#include <stdio.h>

int main() {
    int n, m;
    int x;
    
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

    while (x >= 0) {
        printf("Number of people in the group: ");
        scanf("%d", &x);
        if (x < 0) {
            break;
        }
        
        printf("X=%d \n", x);
        
        int seek_row = 0;
        int last_zero_id = -1;
        
        for (int j = m - 1; j >= 0; j--) {
            if (arr[seek_row][j] == 0) {
                last_zero_id = j;
                break;
            }
        }
        
        int count = 0;
        for (int j = last_zero_id; j >= 0 && count < x; j--) {
            arr[seek_row][j] = 1;
            count++;
        }
        
        printf("Updated array:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
        
    }

    return 0;
}
