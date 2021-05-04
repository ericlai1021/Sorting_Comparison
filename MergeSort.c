#include "Sort.h"
int number[MAX]= {0};
char list[MAX][128];
int A[MAX], B[MAX];
char tmpA[MAX][128];
char tmpB[MAX][128];

// Merge two subarrays of A[].
// First subarray is arr[head..mid]
// Second subarray is arr[mid+1..tail]
void merge(int head, int mid, int tail, int flag){
	int lenA = mid - head + 1;
	int lenB = tail - (mid + 1) + 1;

	//Copy data to temp arrays A[] and B[]
	int i, j, k;
	if(flag == 0){
		for(i = 0; i < lenA; i++) {A[i] = number[head + i];}
		for(i = 0; i<lenB; i++) {B[i] = number[mid + 1 + i];}

		// Merge two temp arrays back into arr[head..tail]
		i = 0;
		j = 0;
		k = head;
		//while array A and B haven't finished scanning
		while(i < lenA && j < lenB){
			if(A[i] < B[j]){
				number[k] = A[i];
				i++;
			}
			else{
				number[k] = B[j];
				j++;
			}
			k++;
		}
		//Copy the remaing elements into arr[], if A[] haven't finished scanning
		while(i < lenA){
			number[k] = A[i];
			i++;
			k++;
		}
		//Copy the remaing elements into arr[], if B[] haven't finished scanning
		while(j < lenB){
			number[k] = B[j];
			j++;
			k++;
		}
	}
	else{
		for(i = 0; i < lenA; i++) {strcpy(tmpA[i], list[head + i]);}
		for(i = 0; i<lenB; i++) {strcpy(tmpB[i], list[mid + 1 + i]);}
		i = 0;
		j = 0;
		k = head;
		//while array A and B haven't finished scanning
		while(i < lenA && j < lenB){
			if(strcmp(tmpA[i], tmpB[j]) < 0){
				strcpy(list[k], tmpA[i]);
				i++;
			}
			else{
				strcpy(list[k], tmpB[j]);
				j++;
			}
			k++;
		}
		//Copy the remaing elements into arr[], if A[] haven't finished scanning
		while(i < lenA){
			strcpy(list[k], tmpA[i]);
			i++;
			k++;
		}
		//Copy the remaing elements into arr[], if B[] haven't finished scanning
		while(j < lenB){
			strcpy(list[k], tmpB[j]);
			j++;
			k++;
		}
	}
}

void merge_sort(int head, int tail, int flag){
	if(head < tail){
		int mid = (head + tail) / 2;
		merge_sort(head, mid, flag);
		merge_sort(mid+1, tail, flag);
		merge(head, mid, tail, flag);
	}
}

int main(){
	struct timeval start;
	struct timeval end;
	unsigned long period;
	int flag = 0;
	FILE *fp1, *fp2;

	// 產生亂數資料
	fp1 = fopen("MergeSort_dataset1.txt", "w");
	fp2 = fopen("MergeSort_dataset2.txt", "w");
	int i,j,tmp;
	srand(time(NULL));
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
	merge_sort(0, MAX-1, flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for integers: %ld\n", period);

	flag = 1;

	gettimeofday(&start, NULL);
	merge_sort(0, MAX-1, flag);
	gettimeofday(&end, NULL);
	// 計算執行時間
	period = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("sorting time for characters: %ld\n", period);

	return 0;
}
