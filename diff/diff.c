#include<stdio.h>
#include<string.h>

struct lines{
    char stack_lines1[127];
    char stack_lines2[127];
 };

void main(int argc,char *argv[])
{
    struct lines st[100];
    FILE *file1,*file2;
    char line1[100], line2[100];
    int line_count1=0,flag2[10],flag1[10],line_count2=0;
    int i=0,n=0,m=0,o=0;
 
    file1 = fopen(argv[1],"r");
    file2 = fopen(argv[2],"r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening file");
        return;
    }

    while(fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL){
        line_count1++;
        line_count2++;
        
        if(strcmp(line1, line2) != 0){
            strcpy(st[i].stack_lines1, line1);
            flag1[m++] = line_count1;
            
            strcpy(st[i].stack_lines2, line2);
            flag2[o++] = line_count2;
            n++;
            i++;
        }
    }
    
    for(i=0;i<m;i++){
        printf("%d",flag1[i]);
    }
    printf("c");
    
    for(i=0;i<o;i++){
        printf("%d",flag2[i]);
    }
    printf("\n");
    
    for(i = 0; i < m; i++) {
        printf("< %s", st[i].stack_lines1);
    }
    printf("\n---\n");
    for(i = 0; i < o; i++) {
        printf("> %s", st[i].stack_lines2);
    }
    
    fclose(file1);
    fclose(file2);
}
