all: QuickSort.c MergeSort.c RadixSort.c Sort.h
	gcc -g -o QuickSort QuickSort.c
	gcc -g -o MergeSort MergeSort.c
	gcc -g -mcmodel=medium -o RadixSort RadixSort.c
clean:
	rm *.txt QuickSort MergeSort RadixSort
