#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void table(int length, char letter[]);
void underscore(int position);

int main(){
    FILE *list;
    int length=1;
    int position=0;
    int g;
    int loop=0;
    char letter[30]="                              ";
    char buffer[30];
    int count=0;
    int word=0;
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //prints user manual//
    printf("\t*CROSSWORD HELPER*\n\n(   ^   ) Add letter block\n(   v   ) Delete letter block\n(  </>  ) Select letter block\n(any key) Insert letter\n( enter ) Confirm\n\nPress any key to continue");
    g=_getch();
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //prints letters table and indicator//
    while(loop==0){
        system("cls");
        table(length, letter);
        underscore(position);
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //scans what operation the user wants to make//
        g=_getch();
        if(g==224){
            switch(_getch()){
                case 77:                                //right arrow to move the indicator one position to the right//
                    if(position!=(length-1)){
                        position++;
                }
                break;
                case 75:                                //left arrow to move the indicator one position to the left//
                    if(position!=0){
                        position--;
                }
                break;
                case 72:                                //up arrow to add 1 block to the letters table//
                    if(length!=30){
                        length++;
                    }
                break;
                case 80:                                //down arrow to delete 1 block from letters table//
                    if(length!=1){
                        letter[length-1]=' ';
                        length--;
                        if(position==length){            //if the indicator is under last letter block, the indicator move 1 position left//
                            position--;
                        }
                    }
                break;
            }
        }
        if(g!=224 && g!=0 && g!=8 && g!=13 && g!=9){    //any non-special key entered is placed inside letter block//
            letter[position]=g;
        }
        if(g==13){                                      //enter to confirm//
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //find and prints matching words//
            printf("\n");
            list=fopen("wordlist.txt", "r");
            if(list==NULL){                                                                 //prints error if database not detected//
                printf("ERROR Database is not detected\n");
                g=_getch();
                return 0;
            }
            while(!feof(list)){
                fgets(buffer, sizeof(buffer), list);
                if((length+1)==strlen(buffer)){                                             //checks if the word length matches//
                        for(int i=0; i<length; i++){
                            if(letter[i]=='\0' || letter[i]==' ' || letter[i]==buffer[i]){  //checks if every letter matches//
                                count=count+1;
                                if(count==length){
                                    printf("%s", buffer);                                   //prints matching word//
                                    word++;
                                }
                            }
                        }
                    count=0;
                }
            }
                fclose(list);
                printf("\n*%d matching results found\n", word);                              //prints how many words matched//
                word=0;
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //scans if the user wants to close the program or to continue//
                printf("\n*Do you want to continue searching? (up/down)\n*If you want to modify the input, press any other key\n");
                g=_getch();
                if(g==224){
                    switch(_getch()){
                        case 72:                        //up arrow to continue, reset the program//
                            length=1;
                            position=0;
                            for(int i=0; i<30; i++){
                                letter[i]=' ';
                            }
                        break;
                        case 80:                        //down arrow to close the program//
                            loop=1;
                        break;
                    }
                }
        }
    }
    return 0;
    }
//--------------------------------------------------------------------------------------------------------------------------------//
                                            //outer functions//
void table(int length, char letter[]){                          //prints the letters table//
    printf("\n+");
    for(int i=0; i<length; i++){
        printf("---+");
    }
    printf("\n|");
    for(int i=0; i<length; i++){
        printf(" %c |",letter[i]);
    }
    printf("\n+");
    for(int i=0; i<length; i++){
        printf("---+");
    }
    printf("\n");
}
void underscore(int position){                                  //prints the indicator under the letters table//
    for(int i=0; i<position; i++){
        printf("    ");
    }
    printf("  ^");
}
