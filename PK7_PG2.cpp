#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
char employeeList[MAX][50];
char employeeCode[MAX][50];
double salary[MAX];
double allowance[MAX];

void printMenu(){
    printf("1. Add new employee\n");
    printf("2. Remove an employee based on a code inputted\n");
    printf("3. Find data about employees using a name inputted\n");
    printf("4. Print the list in descending order based on salary + allowance\n");
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

void addEmployee(int index){
	fflush(stdin);
	printf("Input employee code: ");
	scanf("%[^\n]", employeeCode[index]);
	fflush(stdin);
	printf("Input employee name: ");
	scanf("%[^\n]", employeeList[index]);
	fflush(stdin);
	printf("Input employee salary: ");
	scanf("%lf", &salary[index]);
	fflush(stdin);
	printf("Input employee allowance: ");
	scanf("%lf", &allowance[index]);
}

void printEmployeeList(int index){
	printf("\n\n	EMPLOYEE LIST\n");
	for (int i = 0; i <= index; i++){
		printf("%d.\n", i + 1);
		printf("  Code: %s\n", employeeCode[i]);
		printf("  Name: %s\n", employeeList[i]);
		printf("  Salary: %lf\n", salary[i]);
		printf("  Allowance: %lf\n\n", allowance[i]);
	}
}

void removeEmployee(int index, int currentIndex){
	for (int i = index; i < currentIndex; i++){
		strcpy(employeeCode[i], employeeCode[i + 1]);
		strcpy(employeeList[i], employeeList[i + 1]);
		salary[i] = salary[i + 1];
		allowance[i] = allowance[i + 1];
	}
	strcpy(employeeList[currentIndex], "");
	salary[currentIndex] = 0;
	allowance[currentIndex] = 0;
}
int searchCode(char code[], int currentIndex){
	for (int i = 0; i <= currentIndex; i++){
		if (strcmp(code, employeeCode[i]) == 0){
			return i;
		}
	}
	return -1;
}
int* searchEmployee(char* keyword, int currentIndex){
	int *indexOfResult = (int *) malloc(50 * sizeof(int));
	int count = 0;
	int checker;
	char *compare = NULL; 
	
	for (int i = 0; i <= currentIndex; i++){
		compare = strstr(employeeList[i], keyword);
		if (strstr(employeeList[i], keyword) != NULL) {
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
void swapNumber(double *num1, double *num2){
	double temp;
	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void sortList(int currentIndex){
	for (int i = 0; i < currentIndex; i++){
		for (int j = currentIndex; j > i; j--){
			if ((salary[j] + allowance[j]) > (salary[j - 1] + allowance[j - 1])){
				swapString(employeeList[j], employeeList[j - 1]);
				swapString(employeeCode[j], employeeCode[j - 1]);
				swapNumber(&salary[j], &salary[j + 1]);
				swapNumber(&allowance[j], &allowance[j + 1]);
			}
				
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
                addEmployee(++currentIndex);
                system("cls");
                break;
            case 2:
            	if (currentIndex == -1) {
            		printf("nothing to remove!\n");
            		fflush(stdin);
            		getchar();
            	
				}
            	
            	else {
            		system("cls");
	                printEmployeeList(currentIndex);
	                
                	printf("Input code to remove: ");
                	scanf("%s", str);
					num = searchCode(str, currentIndex);
	                if (num != -1){
	                	removeEmployee(num, currentIndex);
	                	currentIndex--;
					} else {
						printf("\nNOT FOUND!");
						fflush(stdin);
						getchar();
					}
				}
                
                break;
            case 3:
                // search
                system("cls");
                fflush(stdin);
                printf("input some word to search: ");
                scanf("%[^\n]", str);
                searchResultIndex = searchEmployee(str, currentIndex);   
				printf("\n\tSEARCH RESULT\n"); 
				if (searchResultIndex[0] != -1){
					for (int i = 0; i < MAX && searchResultIndex[i] != -1; i++){
						printf("%d.\n", i + 1);
						printf("  Code: %s\n", employeeCode[searchResultIndex[i]]);
						printf("  Name: %s\n", employeeList[searchResultIndex[i]]);
						printf("  Salary: %lf\n", salary[searchResultIndex[i]]);
						printf("  Allowance: %lf\n\n", allowance[searchResultIndex[i]]);
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
				printf("test 4");
				printEmployeeList(currentIndex);
				
				fflush(stdin);
				getchar();
                break;
        }

    } while (choice != 5);
	return 0;
}
 



