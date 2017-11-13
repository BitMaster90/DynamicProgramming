#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int FindMinimumStepsTo1(int);
int FindMin(int, int);
void Test_Steps(void);
void Test_RodCutting();
int RodCutting(int, int*);
int FindMax(int, int);
unsigned long long DP_Steps(unsigned int);
void Test_StringPermutations(char *);
void StringPermutationsDP(char *);
void PermuteString(char, char *, char *, int);
void AddToString(char *, char *, char, int, int);
void CopyToDest(char *, char *, int);
void SwapString(char *, int, int);
void Test_TextJustification(int);
void TextJustificationInternal(char **, int);
void PrintPermutations(char *, int);
void Test_MinOperations();

int main(void) {
	char *ConstStr = "ABCD";
	char *Str;
	int length = 16;
	Str = (char *)malloc(sizeof(char)*strlen(ConstStr) + 1);
	strcpy(Str, ConstStr);
	Test_TextJustification(length);
	Test_Steps();
	Test_RodCutting();
	Test_StringPermutations(Str);
	Test_MinOperations();
	return 1;
}

void Test_MinOperations() {
	int num;
	int result;
	printf("Enter the number to find minimum steps to reach 1 by either substracting with 1, dividing by 2 (if divisible) or dividing by 3 (if divisible) \n");
	scanf_s("%d", &num);
	printf("\nThe number entered is %d \n", num);
	result = FindMinimumStepsTo1(num);
	printf("Number of minimum steps to reach 1 is %d \n", result);
}

int FindMinimumStepsTo1(int num) {
	int i;
	int *LookUpTable;
	int temp = 0;
	int min = 0;
	LookUpTable = (int *)malloc(sizeof(int)*(num+1));
	for (i = 0; i < num; i++) {
		LookUpTable[i] = 0;
	}
	for (i = 2; i <= num; i++) {
		temp = 1 + LookUpTable[i - 1];
		if ((i % 2) == 0) {
			min = FindMin(temp, (1 + LookUpTable[i / 2]));
		}
		if ((i % 3) == 0) {
			min = FindMin(min, (1 + LookUpTable[i / 3]));
		}
		LookUpTable[i] = min;
	}
	return LookUpTable[num];
}

int FindMin(int num1, int num2) {
	if (num1 > num2) {
		return num2;
	}
	else {
		return num1;
	}
}

void Test_TextJustification(int Length) {
	FILE *f;
	char Temp[100];
	char *Table[100];
	int i = 0;
	for (i = 0; i < 100; i++) {
		Table[i] = NULL;
	}
	i = 0;
	f = fopen("textjustification.txt", "r");
	if (f == NULL) {
		printf("cant open file \n");
		return;
	}
	while ((fscanf(f, "%s", Temp)) == 1) {
		Table[i] = (char *)malloc(sizeof(char)*(strlen(Temp) + 1));
		strcpy(Table[i], Temp);
		i++;
	}
	TextJustificationInternal(Table, Length);
}

void TextJustificationInternal(char **Table, int length) {
	int temp;
	int temp2;
	int index = 0;
	int remaininglength = length;
	int i;
	int stride;
	while (Table[index] != NULL) {
		temp = remaininglength - strlen(Table[index]);
		if (temp > 0) {
			if (Table[index + 1] != NULL) {
				temp2 = temp - strlen(Table[index + 1]);
			}
			else {
				temp2 = temp;
			}
			if (temp2 < 0) {
				stride = (remaininglength - strlen(Table[index]));
				for (i = 0; i < stride; i++) {
					printf(" ");
				}
				printf(" %s", Table[index]);
			}
			else {
				printf("%s ", Table[index]);
			}
			remaininglength = temp - 1;
			index++;
		}
		else {
			printf("\n");
			remaininglength = length;
		}
	}
	printf("\n\n");
}



void Test_StringPermutations(char *Str) {
	StringPermutationsDP(Str);
}

void StringPermutationsDP(char *Str) {
	char **LookUpTable;
	int i;
	int size;
	LookUpTable = (char **)malloc(sizeof(char *)*(strlen(Str) + 1));
	for (i = 0; i <= strlen(Str); i++) {
		size = (factorial(i)*i) + 1;
		LookUpTable[i] = (char *)malloc(sizeof(char)*size);
		printf("Bytes allocated is %d \n", size);
		*(LookUpTable[i] + (size - 1)) = '\0';
	}
	for (i = 0; i < strlen(Str); i++) {
		PermuteString(Str[i], LookUpTable[i], LookUpTable[i + 1], i);
	}
	PrintPermutations(LookUpTable[i], i);
}

void PrintPermutations(char *Array, int Digits) {
	int Counter = 0;
	int i = 0;
	printf("\n\n");
	while (Array[i] != '\0') {
		if (Counter == Digits) {
			printf("\n");
			Counter = 0;
		}
		printf("%c", Array[i]);
		Counter++;
		i++;
	}
	printf("\n\n");
}
void PermuteString(char c, char *LpCurrent, char *LpNext, int digit) {
	int i;
	int size;
	int j = 0;
	int CurrentDigits;
	int DestIndex = 0;
	char *TempChars;
	size = sizeof(char)*digit + 2;
	TempChars = (char *)malloc(size);
	size = factorial(digit + 1);//strlen(LpNext);
	printf("strlen is %d \n", size);
	printf("Digits are %d \n", digit);
	CurrentDigits = 0;
	for (i = 0; i < size; i += digit + 1) {
		AddToString(LpCurrent, TempChars, c, CurrentDigits, digit + 1);
		CopyToDest(TempChars, LpNext, DestIndex);
		DestIndex += (digit + 1);
		while (TempChars[j + 1] != '\0') {
			SwapString(TempChars, j, j + 1);
			CopyToDest(TempChars, LpNext, DestIndex);
			DestIndex += (digit + 1);
			j += 1;
		}
		j = 0;
		CurrentDigits += digit;
	}
}

void SwapString(char *src, int a, int b) {
	char temp;
	temp = src[a];
	src[a] = src[b];
	src[b] = temp;
}

void CopyToDest(char *src, char *dest, int index) {
	int size;
	int i;
	size = strlen(src);
	for (i = index; i < index + size; i++) {
		dest[i] = src[i - index];
	}
}

void AddToString(char *src, char *dest, char c, int index, int digit) {
	int i;
	dest[0] = c;
	for (i = 1; i < digit; i++) {
		dest[i] = src[index + (i - 1)];
	}
	dest[i] = '\0';
}

int factorial(int num) {
	int i;
	int temp = 1;
	for (i = num; i > 0; i--) {
		temp *= i;
	}
	return temp;
}

void Test_RodCutting(void) {
	int Length = 8;
	int PriceArray[8] = { 3,5,8,9,10,17,17,20 };
	int Result;
	int i;
	printf("Rod length is %d inches\n", Length);
	for (i = 1; i <= Length; i++) {
		printf("Price for %d inch is $%d\n", i, PriceArray[i - 1]);
	}
	Result = RodCutting(Length, PriceArray);
	printf("\nMaximum value obtained is $%d \n\n", Result);
}

void Test_Steps(void) {
	unsigned int Steps;
	unsigned int i;
	unsigned long long Count;
	printf("This program is going to find in how many different ways you can reach n steps if you had three choices. 1 step, jump 2 steps or jump 3 steps at a time.\n\n");
	printf("Enter the number of steps to get the number of ways for : \n");
	scanf("%u", &Steps);
	printf("Number of steps entered is %u :\n\n", Steps);
	Count = DP_Steps(Steps);
	printf("Number of different ways these steps can be reached is %llu \n\n", Count);
}
unsigned long long DP_Steps(unsigned int Steps) {
	unsigned long long *LookUp;
	int i;
	int j;
	unsigned long long Count = 0;
	LookUp = (unsigned long long *)malloc(Steps * sizeof(unsigned long long));
	LookUp[0] = 0;
	for (i = 1; i <= Steps; i++) {
		for (j = 1; j < 4; j++) {
			if ((i - j) > 0) {//&& ((i != 2) || (j != 1))) {
				Count += LookUp[i - j];
			}
			//		else if ((i == 2) && (j == 1)) {
			//		Count += 1;
			//}
			else if ((i - j) == 0) {
				Count++;
			}
			else {
				break;
			}
		}
		LookUp[i] = Count;
		Count = 0;
	}
	return LookUp[Steps];
}

int RodCutting(int Length, int *PriceArray) {
	int i;
	int j;
	int *LookUpTable = (int *)malloc(sizeof(int)*Length);
	int Max = 0;
	int temp = 0;
	LookUpTable[1] = PriceArray[0];
	for (i = 1; i <= Length; i++) {
		j = 1;
		while ((i - j) >= j) {
			temp = LookUpTable[j] + LookUpTable[i - j];
			if (temp > Max) {
				Max = temp;
			}
			j++;
		}
		temp = PriceArray[i - 1];
		if (temp > Max) {
			Max = temp;
		}
		LookUpTable[i] = Max;
		Max = 0;
		temp = 0;
	}
	return LookUpTable[Length];
}

int FindMax(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}
