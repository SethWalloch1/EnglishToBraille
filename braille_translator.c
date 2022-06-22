/**
 * Name:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR (90)

FILE* in_file;
FILE* out_file;

/*This method will write the Braille letters either horizontally or vertically
 to the output_file.
 
 @param braille_line: an array of int arrays(Braille letters).
 @param length: length of braille_line, number of Braille letters in line.
 
 @return 1 on success, -1 if an error occurs*/
int write_braille_to_file(int **braille_line, int length){
    
    if(out_file = fopen("out_file.txt", "w")){
        for(int i = 0; i < length; i++){
            fprintf(out_file, "%d %d \n", braille_line[i][0], braille_line[i][3]);
            fprintf(out_file, "%d %d \n", braille_line[i][1], braille_line[i][4]);
            fprintf(out_file, "%d %d \n", braille_line[i][2], braille_line[i][5]);
            fprintf(out_file, "\n");
        }
        fclose(out_file);
        return 1;
    }else{
        return -1;
    }

}

/*This method translates an ASCII char to an array of 6 ints(a Brailler letter):
 0 3
 1 4
 2 5
 
 @param letter: the ASCII char to be translated.
 
 @return an int* that represents a Braille char, or NULL if that char is invalid.*/
int *ASCII_to_braille(char letter){

    int *braille = malloc(sizeof(int *) * 6);
    for(int i = 0; i < 6; i++){
        braille[i] = 0;
    }

    if(letter == ' '){
        return braille;
    }
    

    if((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')){
        int row = (letter - 'a') / 10;
        int column = (letter - 'a') % 10;

        if((letter == 'x' || letter == 'y' || letter == 'z')){
            column = column - 1;
        }

        if(row == 0){
            //Do Nothing
        }else if(row == 1){
            braille[2] = 1;        
        }else if(row == 2){
            braille[2] = 1;
            braille[5] = 1;
        }

        if(column == 0){
            braille[0] = 1;
        }else if(column == 1){
            braille[0] = 1;
            braille[1] = 1;
        }else if(column == 2){
            braille[0] = 1;
            braille[3] = 1;
        }else if(column == 3){
            braille[0] = 1;
            braille[3] = 1;
            braille[4] = 1;
        }else if(column == 4){
            braille[0] = 1;
            braille[4] = 1;
        }else if(column == 5){
            braille[0] = 1;
            braille[3] = 1;
            braille[1] = 1;
        }else if(column == 6){
            braille[0] = 1;
            braille[1] = 1;
            braille[3] = 1;
            braille[4] = 1;
        }else if(column == 7){
            braille[0] = 1;
            braille[1] = 1;
            braille[4] = 1;
        }else if(column == 8){
            braille[3] = 1;
            braille[1] = 1;
        }else if(column == 9){
            braille[1] = 1;
            braille[3] = 1;
            braille[4] = 1;
        }

        if(letter == 'w' || letter == 'W'){
            braille[0] = 0;
            braille[2] = 0;
            braille[3] = 1;
            braille[1] = 1;
            braille[4] = 1;
            braille[5] = 1;
        }

    }else{
        return NULL;
    }
    return braille;
    free(braille);
}

/*This method reads from in_file up to MAX_CHAR per call to fread(), then builds an 
 array of Braille letters by calling ASCII_to_braille(). It will write the Braille
 to out_file by calling write_braille_to_file().
 
 @return 1 on success, and -1 if an error occurs.*/
int translate_to_braille(){
    char buffer[MAX_CHAR];
    int pass = fread(&buffer, sizeof(char), MAX_CHAR, in_file);
    fclose(in_file);
    int **holder = malloc(sizeof(int *) * MAX_CHAR);

    for(int i = 0; i < sizeof(buffer); i++){
        holder[i] = ASCII_to_braille(buffer[i]);
    }

    write_braille_to_file(holder, sizeof(holder));

    free(holder);
    return 1;
}

/*The program should validate that only one argument was supplied, and that it opens
 a valid file. The in_file will be translated from ASCII to Braille. It will create 
 the output file, and call translate_to_braille().

 The program should output the translation to a file named in_file.txt.output.
 e.g.: in_file: some_text.txt 
       out_file: some_text.txt.output
 
 @return 0 on success, and a 1 on error, exiting.*/
int main(int argc, char **argv)
{
    if(argc > 2){
        printf("Usage: ./braille <src_file_name> \n");
    }

    in_file = fopen(argv[1], "r");

    translate_to_braille();


    
    return 0;
}
