#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <time.h>

int *insertionSort(int *a, int n); //a - array, n - length
void merge(int *a, int p, int q, int r); //a - array p -first index, q - array length middle r - last array index
void mergeSort(int *a, int p, int r); //a - array p -first index, r - last array index
int partition(int *a, int p, int r);
void quicksort(int *a, int p, int r);//a - array p -first index, r - last array index
void swap(int *A, int i, int j);
int *getRandomArray(int n, int range);
int *getSortedArray(int n, int range);
void reverseArray(int *a, int n);
void displayArray(int *a, int n);
int *copyArray(int *a, int n);
void quicksort2(int *tablica, int lewy, int prawy);

void Merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers.
void MergeSort(int *A,int n) {
	int mid,i, *L, *R;
	if(n < 2) return; // base condition. If the array has less than two element, do nothing.

	mid = n/2;  // find the mid index.

	// create left and right subarrays
	// mid elements (from index 0 till mid-1) should be part of left sub-array
	// and (n-mid) elements (from mid to n-1) will be part of right sub-array
	L = (int*)malloc(mid*sizeof(int));
	R = (int*)malloc((n- mid)*sizeof(int));

	for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

	MergeSort(L,mid);  // sorting the left subarray
	MergeSort(R,n-mid);  // sorting the right subarray
	Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}
typedef struct Counter{
  int comparisonNumber;
  int swapNumber;
}Counter;

Counter insertionSortInfo = {0, 0}, mergeSortInfo = {0, 0}, quicksortInfo = {0, 0};

int main(){
  int *a, *insertionSortArray, *mergeSortArray, *quicksortArray, range, arraySize, foo, i, *aa;
  char arrayType;
  double seconds;
  FILE *fp;
  clock_t start = clock();
  clock_t end = clock();
  printf("1. Generate random array\n");
  printf("2. Generate sorted array\n");
  printf("chose: ");
  scanf("%c", &arrayType);
  while(arrayType != '1' && arrayType != '2'){
    printf("Incorrect intput! \n");
    printf("choose: ");
    scanf("%c", &arrayType);
  }
  printf("Value range: ");
  scanf("%d", &range);
  range++;

  printf("Data size: ");
  scanf("%d",&arraySize);

if(arrayType == '1'){
  a = getRandomArray(arraySize, range);
}
else{
  a = getSortedArray(arraySize, range);
}

foo = arraySize / 100;
Counter *insertionSortCounter, *mergeSortCounter, *quicksortCounter;
insertionSortCounter = malloc((foo) * sizeof(Counter));
mergeSortCounter = malloc((foo) * sizeof(Counter));
quicksortCounter = malloc((foo) * sizeof(Counter));

fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Insertionsort time time,Mergesort time,Quicksort time,     ,\n");

for(i = 1; i <= foo; i++){
  fprintf(fp, "%d,",i * 100);
  aa = copyArray(a, i * 100 );
  start = clock();
  insertionSort(a, i * 100);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  fprintf(fp, "%.10e,",seconds);
  // displayArray(a, i *100);
  free(aa);
  aa = copyArray(a, i * 100 );
  start = clock();
  // mergeSort(a, 0, i * 100 - 1);
  MergeSort(a, i * 100);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  fprintf(fp, "%.10e,",seconds);
  free(aa);
  aa = copyArray(a, i * 100);
  start = clock();
  quicksort2(a, 0, i * 100 -1);
  // quicksort(a, 0, i * 100 -1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  fprintf(fp, "%.10e\n",seconds);
  free(aa);
  // printf("Insertion sort comparison number: %d swap number: %d\n", insertionSortInfo.comparisonNumber, insertionSortInfo.swapNumber );
  // printf("Merge sort comparison number: %d swap number: %d\n", mergeSortInfo.comparisonNumber, mergeSortInfo.swapNumber );
  // printf("Quicksort sort comparison number: %d swap number: %d\n", quicksortInfo.comparisonNumber, quicksortInfo.swapNumber );
  insertionSortCounter[i - 1].comparisonNumber = insertionSortInfo.comparisonNumber;
  insertionSortCounter[i - 1].swapNumber = insertionSortInfo.swapNumber;
  mergeSortCounter[i - 1].comparisonNumber = mergeSortInfo.comparisonNumber;
  mergeSortCounter[i - 1].swapNumber = mergeSortInfo.swapNumber;
  quicksortCounter[i - 1].comparisonNumber = quicksortInfo.comparisonNumber;
  quicksortCounter[i - 1].swapNumber = quicksortInfo.swapNumber;
  insertionSortInfo.comparisonNumber = 0;
  insertionSortInfo.swapNumber = 0;
  mergeSortInfo.comparisonNumber = 0;
  mergeSortInfo.swapNumber = 0;
  quicksortInfo.comparisonNumber = 0;
  quicksortInfo.swapNumber = 0;
}

// start = clock();
//   getNodeByValue(foo, &l1);
//   end = clock();
//   seconds = (double)(end - start) / CLOCKS_PER_SEC;
//   printf("random acces: %.10e s\n",seconds );


printf("\n\n" );

// fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Insertionsort comparison,Mergesort comparison,Quicksort comparison,     ,Data size,Insertionsort swap,Mergesort swap,Quicksort swap\n");
for(i = 0; i < foo; i++){
  // printf("%d %d\n", insertionSortCounter[i].comparisonNumber, insertionSortCounter[i].swapNumber);
  // printf("%d %d\n", mergeSortCounter[i].comparisonNumber, mergeSortCounter[i].swapNumber);
  // printf("%d %d\n", quicksortCounter[i].comparisonNumber, quicksortCounter[i].swapNumber);
  fprintf(fp, "%d,%d,%d,%d,    ,%d,%d,%d,%d\n", (i + 1) * 100, insertionSortCounter[i].comparisonNumber, mergeSortCounter[i].comparisonNumber, quicksortCounter[i].comparisonNumber, (i + 1) * 100, insertionSortCounter[i].swapNumber, mergeSortCounter[i].swapNumber, quicksortCounter[i].swapNumber);

}
 fclose(fp);

 system("libreoffice --calc test.csv &");
 free(insertionSortCounter);
 free(mergeSortCounter);
 free(quicksortCounter);

  return 0;
}

int *insertionSort(int *a, int n){
  int j, i, key;
  for(j = 1; j < n; j++){
    key = a[j];
    i = j - 1;
    insertionSortInfo.comparisonNumber++;
    while((i >= 0) && (a[i] > key)){
      a[i + 1] = a[i];
      i--;
      insertionSortInfo.comparisonNumber++;
      insertionSortInfo.swapNumber++;
    }
    a[i + 1] = key;
    insertionSortInfo.swapNumber++;
  }
    return a;
}

void merge(int *a, int p, int q, int r){
  int n1 = q - p + 1, n2 = r - q, *ll, *rr, i, j, k;
  ll = malloc((n1 + 1) * sizeof(int));
  rr = malloc((n2 + 1) * sizeof(int));

  for(i = 1; i <= n1; i++){
    ll[i - 1] = a[p + i - 1];
  }
  for(i = 1; i <= n1; i++){
      rr[i - 1] = a[q + i];
  }
  ll[n1] = INT_MAX;
  rr[n2] = INT_MAX;

  i = 0;
  j = 0;

  for(k = p; k <= r; k++){
    if(ll[i] < rr[j]){
      a[k] = ll[i];
      i++;
    }
    else{
      a[k] = rr[j];
      j++;
    }
    mergeSortInfo.comparisonNumber++;
    mergeSortInfo.swapNumber++;
  }

}

  void mergeSort(int *a, int p, int r){
    int q;
    if(p < r){
      q = (int)((p + r) / 2);
    mergeSort(a, p, q);
    mergeSort(a, q + 1, r);
    merge(a, p, q, r);
  }
}

void quicksort(int *a, int p, int r){
  int q;
  if(p < r){
    q = partition(a, p, r);
    quicksort(a, p, q - 1);
    quicksort(a, q + 1, r);
  }
}

int partition(int *a, int p, int r){
  int x = a[r], i = p - 1, j, buffor;
  for(j = p; j <= r - 1; j++){
    quicksortInfo.comparisonNumber++;
    if(a[j] <= x){
      i = i + 1;
      swap(a, i, j);
      quicksortInfo.swapNumber += 2;
    }
  }
  swap(a, i + 1, r);
  quicksortInfo.swapNumber += 2;
  return i + 1;
}

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}

int *getRandomArray(int n, int range){
  int *a, r, k, i;
  a = malloc(n * sizeof(int));
  srand(time(NULL));
  for(i = 0; i < n; i++){
    r = rand() % range;
    k = rand() % 2;
    if(k == 1){
      r*=( -1);
    }
    a[i] = r;
}
return a;
}

int *getSortedArray(int n, int range){
  int *a, i, j;
  a = getRandomArray(n, range);
  quicksort(a, 0, n - 1);
  reverseArray(a, n);
  quicksortInfo.comparisonNumber = 0;
  quicksortInfo.swapNumber = 0;
  return a;
}

void reverseArray(int *a, int n){
  int i, j;
  i = n - 1;
  j = 0;
  while(i > j){
    swap(a, i, j);
    i--;
    j++;
  }
}

void displayArray(int *a, int n){
  int i;
  printf("[");
  for(i = 0; i < n; i++){
    printf("%d", a[i]);
    printf(",");
  }
  printf("]\n" );
}

int *copyArray(int *a, int n){
  int *aa, i;
  aa = malloc((n + 1) * sizeof(int));
  for(i = 0; i < n; i++){
    aa[i] = a[i];
  }
  return aa;
}


void quicksort2(int *tablica, int lewy, int prawy)
{
int v=tablica[(lewy+prawy)/2];
int i,j,x;
i=lewy;
j=prawy;
do{
  quicksortInfo.comparisonNumber++;
while (tablica[i]<v){
  i++;
  quicksortInfo.comparisonNumber++;
}
quicksortInfo.comparisonNumber++;
while (tablica[j]>v){
  quicksortInfo.comparisonNumber++;
  j--;
}
if (i<=j){
  quicksortInfo.swapNumber += 2;
x=tablica[i];
tablica[i]=tablica[j];
tablica[j]=x;
i++; j--;
}
}while (i<=j);
if (j>lewy) quicksort2(tablica,lewy, j);
if (i<prawy) quicksort2(tablica, i, prawy);
}
