#include <stdio.h>

int get_line(char buffer[], int buffer_length, FILE *fptr);
int line_cpy(char destiny[], char buffer[], int destiny_size);
int line_reset(char line[], int line_length);
int line_cmp(char line1[], char line2[]);

int main(){
    char buffer[250];
    char longest_line[250];
    int length;
    int longest_length;
    char filename[100];

    FILE *fptr;
    start:
    line_reset(buffer, sizeof(buffer));
    line_reset(longest_line, sizeof(longest_line));
    line_reset(filename, sizeof(filename));
    length = 0;
    longest_length = 0;

    printf("File name : ");
    scanf("%99s", filename);

    if(line_cmp(filename, "exit") == 0)
        return 0;

    fptr = fopen(filename, "r");
    if(fptr == NULL){
        fprintf(stderr, "Error! file not found!\n\n");
        goto start;
    }


    while((length = get_line(buffer, sizeof(buffer), fptr)) != EOF){
//        printf("Length = %d | %s\n", length, buffer);
//        printf("Longest_length = %d | length = %d\n", longest_length, length);
        if(longest_length < length){
            line_cpy(longest_line, buffer, length);
            longest_length = length;
//            printf("new Longest_length = %d | %s\n", longest_length, longest_line);
        }
    }
    longest_length--;

    printf("Longest_line : %s\n", longest_line);
    printf("Longest_length = %d\n\n", longest_length);

    fclose(fptr);
    goto start;

}

int get_line(char buffer[], int buffer_length, FILE *fptr){
    int c;
    for(int i = 0; i < buffer_length; i++)  //reset the buffer on every call
        buffer[i] = 0;

    for(int i = 0; i < buffer_length; i++){
        c = fgetc(fptr);
        //putchar(c);
        if(c == EOF){
            if(i != 0){  //If we have EOF but with characters before it we return the characters
                buffer[i] = '\0';
                return i + 1;
            }else if(i == 0){//if we have EOF and no characters before we return EOF
                return EOF;
            }
        }
        if(c == '\n'){
            buffer[i] = '\0';
            return i+1;
        }
        else{
            buffer[i] = c;
        }
    }
}

int line_cpy(char destiny[], char buffer[], int destiny_size){
    for(int i = 0; i < destiny_size; i++) //reset destiny[]
        destiny[i] = 0;
    for(int i = 0; i < destiny_size; i++) //copy the value
        destiny[i] = buffer[i];
}


int line_reset(char line[], int line_length){
    for(int i = 0; i < line_length; i++)
        line[i] = 0;
}

int line_cmp(char line1[], char line2[]){
    for(int i = 0; line1[i] != '\0' || line2[i] != '\0'; i++){
        if(line1[i] != line2[i])
            return -1;
    }
    return 0;
}
