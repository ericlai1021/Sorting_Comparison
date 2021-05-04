#include "Sort.h"
#define SWAP(x,y) {int t; t = x; x = y; y = t;}
int number[MAX] = {0};
char list[MAX][128];

void SWAP_CHAR(char x[], char y[]){
	char tmp[128];
	strcpy(tmp, x);
	strcpy(x, y);
	strcpy(y, tmp);
}

int partition(int left, int right, int flag) { 
	int i = left - 1; 
	int j;

	if(flag == 0){
		for(j = left; j < right; j++) { 
			if(number[j] <= number[right]) { 
				i++;
				SWAP(number[i], number[j]);
			}
		}
		SWAP(number[i+1], number[right]);
	}
	else{
		i = left - 1;
		for(j = left; j<right; j++){
			if(strcmp(list[j], list[right]) <= 0){
				i++;
				SWAP_CHAR(list[i], list[j]);
			}
		}
		SWAP_CHAR(list[i+1], list[right]);
	}

	return i+1; 
} 

void quickSort(int left, int right, int flag) { 
	if(left < right) { 
		int q = partition(left, right, flag); 
		quickSort(left, q-1, flag); 
		quickSort(q+1, right, flag); 
	} 
} 

int main(){
	struct timeval start;
	struct timeval end;
	unsigned long period;
	int flag = 0;
	FILE *fp1, *fp2;
	fp1 = fopen("QuickSort_dataset1.txt", "w");
	fp2 = fopen("QuickSort_dataset2.txt", "w");

	// 產生亂數資料
	int i, j, tmp;
	srand(time(NULL)); 
	for(i = 0; i < MAX; i++) { 
		number[i] = rand();
		fprintf(fp1, "%d\n", number[i]);
		for(j = 0; j<100; j++){
			tmp = rand() % 26;
			list[i][j] =(char) (tmp + 97);
		}
		list[i][j] = '\0';
		fprintf(fp2, "%s\n", list[i]);
	}

	// 排序
	gettimeofday(&start, NULL);
	quickSort(0, MAX-1, flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for integers: %ld\n", period);

	flag = 1;

	gettimeofday(&start, NULL);
	quickSort(0, MAX-1, flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for characters: %ld\n", period);

	return 0; 
} 
