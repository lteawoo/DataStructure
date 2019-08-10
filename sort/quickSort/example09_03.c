#include <stdio.h>
#include <stdlib.h>

int partitionQuickSort(int value[], int start, int end);
int partitionMedianQuickSort(int value[], int start, int end);
void printArray(int value[], int count);

void quickSort(int value[], int start, int end)
{
	int pivot = 0;
	if (start < end) {
		printf("start-----\n");
		pivot = partitionMedianQuickSort(value, start, end);
		quickSort(value, start, pivot - 1);
		quickSort(value, pivot + 1, end);
	}
}

int partitionQuickSort(int value[], int start, int end)
{
	int pivot = 0;
	int temp = 0, left = 0, right = 0;

	left = start;
	right = end;
	pivot = end;

	while (left < right) {
		while ((value[left] < value[pivot]) && (left < right)) {
			left++;
		}

		while ((value[right] >= value[pivot]) && (left < right)) {
			right--;
		}

		if (left < right) {
			temp = value[right];
			value[right] = value[left];
			value[left] = temp;

			printf("start-[%d]. end-[%d], left-[%d], right-[%d], pivot-[%d],in-loop,", start, end, left, right, value[pivot]);

			printArray(value, end - start + 1);
		}
	}

	temp = value[pivot];
	value[pivot] = value[right];
	value[right] = temp;

	printf("start -[%d]. end-[%d], left-[%d], right-[%d], pivot-[%d],out-loop,", start, end, left, right, value[right]);

	printArray(value, end - start + 1);

	return right;
}

int partitionMedianQuickSort(int value[], int start, int end)
{
	int pivot = 0;
	int temp = 0, left = 0, right = 0;

	left = start;
	right = end;
	pivot = value[(start + end) / 2];

	while (1) {
		while ((value[left] < pivot) && (left < end)) {
			left++;
		}

		while ((value[right] > pivot) && (right > start)) {
			right--;
		}

		if (left >= right) break;

		temp = value[right];
		value[right] = value[left];
		value[left] = temp;

		printf("start-[%d]. end-[%d], left-[%d], right-[%d], pivot-[%d],in-loop,", start, end, left, right, pivot);

		printArray(value, 8);
	}

	return right;
}

int main(int argc, char *argv[]) {
	int values[] = { 80, 50, 70, 10, 60, 20, 40, 30 };

	printf("Before Sort\n");
	printArray(values, 8);

	quickSort(values, 0, 7);

	printf("\nAfter Sort\n");
	printArray(values, 8);

	return 0;
}

void printArray(int value[], int count)
{
	int i = 0;
	for (i = 0; i < count; i++) {
		printf("%d ", value[i]);
	}
	printf("\n");
}