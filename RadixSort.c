#include "Sort.h"
int number[MAX] = {0};
char list[MAX][128];
int temp[10][MAX] = {0}; 
char charTemp[26][MAX][128];

void radixSort(int flag) {
	int order[10] = {0};
	int charOrder[26] = {0};

	int n = 1;
	if(flag == 0){
		while(n <= 10000){
			int i;
			for(i = 0; i<MAX; i++) {
				int lsd = ((number[i] / n) % 10);
				temp[lsd][order[lsd]] = number[i];
				order[lsd]++;
			} 

			// 重新排列
			int k = 0;
			for(i = 0; i<10; i++) { 
				if(order[i] != 0){
					int j;
					for(j = 0; j < order[i]; j++, k++){ 
						number[k] = temp[i][j]; 
					} 
				}
				order[i] = 0; 
			}

			n *= 10; 
		}
	}
	else{
		for(n = 99; n>=0; n--){
			int i;
			for(i = 0; i<MAX; i++){
				int lsa =(int) (list[i][n] - 97);
				strcpy(charTemp[lsa][charOrder[lsa]], list[i]);
				charOrder[lsa]++;
			}
			int k = 0;
			for(i = 0; i<26; i++){
				if(charOrder[i] != 0){
					int j;
					for(j = 0; j<charOrder[i]; j++, k++){
						strcpy(list[k], charTemp[i][j]);
					}
				}
				charOrder[i] = 0;
			}
		}
	}
}	

int main(){
	struct timeval start;
	struct timeval end;
	unsigned long period;
	int flag = 0;
	FILE *fp1, *fp2;
	fp1 = fopen("RadixSort_dataset1.txt", "w");
	fp2 = fopen("RadixSort_dataset2.txt", "w");

	// 產生亂數資料
	srand(time(NULL));
	int i,j,tmp;
	for(i = 0; i<MAX; i++){
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
	radixSort(flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for integers: %ld\n", period);

	flag = 1;

	gettimeofday(&start, NULL);
	radixSort(flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for characters: %ld\n", period);

	return 0; 
}
