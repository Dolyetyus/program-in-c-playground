#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", *((arr+i*m) + j));
            if (j < m-1) {printf("_");}
        }
        printf("\n");
    }
}

int main() {
    int n, m, x;
    
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
    
    printf("Start up:\n");
    printArray((int *)arr, n, m);

    while (x >= 0) {
        printf("Enter number of people (Negative num to exit): ");
        scanf("%d", &x);
        if (x < 0) {
            printf("Exiting the program...\n");
            break;
        }
        
        int seek_row = 0;
        int last_zero_id = -1;
        int recent_updates[x][2];
        
        while (seek_row < n) {
            for (int j = m - 1; j >= 0; j--) {
                if (arr[seek_row][j] == 0) {
                    last_zero_id = j;
                    break;
                }
            }
            
            if (x > last_zero_id + 1) {
                seek_row++;
                if (seek_row == n) {
                    printf("Not enough space in the movie theater\n");
                    printf("Exiting the program...\n");
                    exit(0);
                }
            } 
            else {
                int count = 0;
                for (int j = last_zero_id; j >= 0 && count < x; j--) {
                    arr[seek_row][j] = 1;
                    recent_updates[count][0] = seek_row;
                    recent_updates[count][1] = j;
                    count++;
                }
    
                printf("X=%d \n", x);
                printArray((int *)arr, n, m);
                
                printf("Seats:");
                for (int i = 0; i < x; i++) {
                    int row = recent_updates[i][0];
                    int col = m - 1 - recent_updates[i][1];
                    char label = 'A' + row;
                    
                    printf("%c%d", label, col + 1);
                    if (i < x-1) {printf(",");}
                }
                printf("\n");
                
                break;
            }
        }
    }
    
    return 0;
}
