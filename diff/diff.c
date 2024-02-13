#include<stdio.h>
#include<string.h>
#include <ctype.h>

struct lines{
    char stack_lines1[127];
    char stack_lines2[127];
 };

void toLowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int isBlankLine(const char *line) {
    while (*line != '\0') {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

long countLines(FILE *file) {
    long lines = 0;
    int ch;

    do {
        if (ch == '\n')
            lines++;
    } while (EOF != (ch = getc(file)));

    if (ch != '\n') {
        lines++;
    }

    rewind(file);

    return lines;
}

void main(int argc,char *argv[])
{
    struct lines st[100];
    FILE *file1,*file2;
    char line1[100], line2[100];
    int line_count1=0, flag2[15], flag1[15], line_count2=0;
    int i=0, n=0, m=0, o=0;

    int ignore_case = 0;
    int ignore_blanklines = 0;
 
    file1 = fopen(argv[1],"r");
    file2 = fopen(argv[2],"r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening file");
        return;
    }

    int lines1 = countLines(file1);
    int lines2 = countLines(file2);
    int lines = lines1 < lines2 ? lines1 : lines2; 

    for (int arg = 1; arg < argc; arg++) {
        if (strcmp(argv[arg], "-i") == 0) {
            ignore_case = 1;
        } 
        else if (strcmp(argv[arg], "-B") == 0) {
            ignore_blanklines = 1;
        }
    }

    while(fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL){
        line_count1++;
        line_count2++;

        if (ignore_case) {
            toLowercase(line1);
            toLowercase(line2);
        }

        if (ignore_blanklines && (isBlankLine(line1) || isBlankLine(line2))) {
            if (isBlankLine(line1)) line_count1++;
            if (isBlankLine(line2)) line_count2++;
            continue;
        }
        
        if(strcmp(line1, line2) != 0){
            strcpy(st[i].stack_lines1, line1);
            flag1[m++] = line_count1;
            
            strcpy(st[i].stack_lines2, line2);
            flag2[o++] = line_count2;
            n++;
            i++;
        }
    }

    int len1 = strlen(st[m-1].stack_lines1); 
    if(len1 > 0 && st[m-1].stack_lines1[len1-1] != '\n') {
        st[m-1].stack_lines1[len1] = '\n';
        st[m-1].stack_lines1[len1+1] = '\0';
    }
    int len2 = strlen(st[m-1].stack_lines2); 
    if(len2 > 0 && st[m-1].stack_lines2[len2-1] != '\n') {
        st[m-1].stack_lines2[len2] = '\n';
        st[m-1].stack_lines2[len2+1] = '\0';
    }
    
    for(i = 0; i < m; i++) {
        printf("%dc%d\n", flag1[i], flag2[i]);
        printf("< %s", st[i].stack_lines1);
        printf("---\n");
        printf("> %s", st[i].stack_lines2);
    }

    fclose(file1);
    fclose(file2);
}
