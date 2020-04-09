#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
char studentList[MAX][50];

void getString(char s[][50], int index){
    getchar();
    int lengthMax = 50;
    int i, c;
    i = 0;
    while((c = getchar()) != '\n' && c != EOF){
        if (i < lengthMax){
            s[index][i] = c;
            i++;
        }
    }
    s[index][i] = '\0';
}
void printMenu(){
    printf("1. Add a student\n");
    printf("2. Remove a student\n");
    printf("3. Search a student\n");
    printf("4. Print the list in ascending order\n");
    printf("5. Quit\n");
    printf("Input number: ");
}

int getChoice(int min, int max){
    int num;

    do {
        scanf("%d", &num);
    } while (num < min && num > max);
    return num;
}
//---------------------------------------------//

void addStudent(int index){
	fflush(stdin);
	printf("Input student's name: ");
	scanf("%[^\n]", studentList[index]);
}

void printStudentList(int index){
	printf("\n\n	STUDENT LIST\n");
	for (int i = 0; i <= index; i++){
		printf("%d- %s\n", i + 1, studentList[i]);
	}
}

void removeStudent(int index, int currentIndex){
	for (int i = index; i < currentIndex; i++){
		strcpy(studentList[i], studentList[i + 1]);
	}
	strcpy(studentList[currentIndex], "");
}

int* searchStudent(char* keyword, int currentIndex){
//	int indexOfResult[100];
	int *indexOfResult = (int *) malloc(50 * sizeof(int));
	int count = 0;
	int checker;
	char *compare = NULL; 
	
	for (int i = 0; i <= currentIndex; i++){
		compare = strstr(studentList[i], keyword);
		if (strstr(studentList[i], keyword) != NULL) {
			indexOfResult[count++] = i;
		}
	}
	indexOfResult[count] = -1;
	return indexOfResult;
}

void swapString(char str1[], char str2[]){
	char temp[50];
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

void sortList(int currentIndex){
	for (int i = 0; i < currentIndex; i++){
		for (int j = currentIndex; j > i; j--){
			if (strcmp(studentList[j], studentList[j - 1]) < 0)
				swapString(studentList[j], studentList[j - 1]);
		}
	}
}
//-----------------------------------//
int main(int argc, char *argv[]) {
    int choice;
    int currentIndex = -1;
    int num;
    int count;
    int* searchResultIndex;
    char *str = (char *) malloc(50 * sizeof(char));

    do {
    	system("cls");
        printMenu();
        switch (choice = getChoice(1, 5)) {
            case 1:
                addStudent(++currentIndex);
                system("cls");
                break;
            case 2:
            	if (currentIndex == -1) {
            		printf("nothing to remove!\n");
            		getchar();
				}
            	
            	else {
            		system("cls");
	                printStudentList(currentIndex);
	                do {
	                	printf("Input index to remove (0 to cancel): ");
	                	scanf("%d", &num);
					} while (num < 0 || num > currentIndex + 1);
	                
	                if (num != 0){
	                	removeStudent(num - 1, currentIndex);
	                	currentIndex--;
					}
				}
                
                break;
            case 3:
                // search
                system("cls");
                fflush(stdin);
                printf("input some word to search: ");
                scanf("%[^\n]", str);
                searchResultIndex = searchStudent(str, currentIndex);   
				printf("\n\tSEARCH RESULT\n"); 
				if (searchResultIndex[0] != -1){
					for (int i = 0; i < MAX && searchResultIndex[i] != -1; i++){
						printf("%d- %s\n", i + 1, studentList[searchResultIndex[i]]);
					}
				} else {
					printf("\n Not found anything!");
				} 
				getchar();
				getchar();
                free(str);
                free(searchResultIndex);
                break;
            case 4:
                // print student list
				system("cls");
				sortList(currentIndex);
				printStudentList(currentIndex);
				
				fflush(stdin);
				getchar();
                break;
        }

    } while (choice != 5);
	return 0;
}
