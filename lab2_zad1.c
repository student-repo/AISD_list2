#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include <time.h>

int *insertionSort(int *a, int n); //a - array, n - length
void merge2(int *a, int p, int q, int r); //a - array p -first index, q - array length middle r - last array index
void mergeSort2(int *a, int p, int r); //a - array p -first index, r - last array index
int partition(int *a, int p, int r);
void quicksort2(int *a, int p, int r);//a - array p -first index, r - last array index
void swap(int *A, int i, int j);
int *getRandomArray(int n, int range);
int *getSortedArray(int n, int range);
void reverseArray(int *a, int n);
void displayArray(int *a, int n);
int *copyArray(int *a, int n);
void quicksort(int *a, int p, int r);
void compareArrays(int *a, int *aa, int n);
void merge(int *A,int *L,int leftCount,int *R,int rightCount);
void mergeSort(int *A,int n);
void resetCounrers();
double getInsertionSortTime(int *a, int n);
double getMergesortTime(int *a, int n);
double getQuicksortTime(int *a, int n);

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
  if(arrayType == '1'){
    a = getRandomArray(i * 100, range);
  }
  else{
    a = getSortedArray(i * 100, range);
  }

  fprintf(fp, "%d,",i * 100);
  fprintf(fp, "%.10e,",getInsertionSortTime(a, i * 100));
  fprintf(fp, "%.10e,", getMergesortTime(a, i * 100));
  fprintf(fp, "%.10e\n",getQuicksortTime(a, i * 100));
  free(a);
  insertionSortCounter[i - 1].comparisonNumber = insertionSortInfo.comparisonNumber;
  insertionSortCounter[i - 1].swapNumber = insertionSortInfo.swapNumber;
  mergeSortCounter[i - 1].comparisonNumber = mergeSortInfo.comparisonNumber;
  mergeSortCounter[i - 1].swapNumber = mergeSortInfo.swapNumber;
  quicksortCounter[i - 1].comparisonNumber = quicksortInfo.comparisonNumber;
  quicksortCounter[i - 1].swapNumber = quicksortInfo.swapNumber;
  resetCounrers();
}


printf("\n\n" );

// fp = fopen("test.csv", "w+");
fprintf(fp, "Data size,Insertionsort comparison,Mergesort comparison,Quicksort comparison,     ,Data size,Insertionsort swap,Mergesort swap,Quicksort swap\n");
for(i = 0; i < foo; i++){
  fprintf(fp, "%d,%d,%d,%d,    ,%d,%d,%d,%d\n", (i + 1) * 100, insertionSortCounter[i].comparisonNumber, mergeSortCounter[i].comparisonNumber, quicksortCounter[i].comparisonNumber, (i + 1) * 100, insertionSortCounter[i].swapNumber, mergeSortCounter[i].swapNumber, quicksortCounter[i].swapNumber);
}
 fclose(fp);




int naa = 10001;
 int *aaa1 = getRandomArray(naa, 123121);
 int *aaa2 = copyArray(aaa1, naa);
 int *aaa3 = copyArray(aaa1, naa);

 insertionSort(aaa2, naa);
 // quicksort(aaa1, 0, naa - 1);
 mergeSort(aaa1 ,naa);
 // mergeSort2(aaa1, 0, naa - 1);
 compareArrays(aaa1, aaa2, naa);


// displayArray(aaa, 100);

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

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}



void quicksort(int *a, int p, int r){
    int i = p, j = r, x, q = a[(p + r) / 2];
    do{
      quicksortInfo.comparisonNumber++;
    while (a[i] < q){
      i++;
      quicksortInfo.comparisonNumber++;
    }
    quicksortInfo.comparisonNumber++;
    while (a[j] > q){
      quicksortInfo.comparisonNumber++;
      j--;
    }
    if (i <= j){
      quicksortInfo.swapNumber += 2;
      swap(a, i, j);
      i++; j--;
    }
    }while (i<=j);
    if (j > p) quicksort(a, p, j);
    if (i < r) quicksort(a, i, r);
  }



  void merge(int *a,int *p,int np,int *r,int rc) {
  	int i,j,k;
  	i = 0; j = 0; k =0;

  	while(i < np && j< rc) {
  		if(p[i]  < r[j]) a[k++] = p[i++];
  		else a[k++] = r[j++];
      mergeSortInfo.comparisonNumber++;
      mergeSortInfo.swapNumber++;
  	}
  	while(i < np) a[k++] = p[i++];
  	while(j < rc) a[k++] = r[j++];
  }

  void mergeSort(int *a,int n) {
  	int q,i, *p, *r;
  	if(n < 2) return;
  	q = n/2;
  	p = (int*)malloc(q * sizeof(int));
  	r = (int*)malloc((n - q) * sizeof(int));

  	for(i = 0;i < q; i++) p[i] = a[i];
  	for(i = q;i < n; i++) r[i - q] = a[i];

  	mergeSort(p, q);
  	mergeSort(r,n - q);
  	merge(a, p, q, r, n - q);
          free(p);
          free(r);
  }

















  void merge2(int *a, int p, int q, int r){
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

    void mergeSort2(int *a, int p, int r){
      int q;
      if(p < r){
        q = (int)((p + r) / 2);
      mergeSort2(a, p, q);
      mergeSort2(a, q + 1, r);
      merge2(a, p, q, r);
    }
  }

  void quicksort2(int *a, int p, int r){
    int q;
    if(p < r){
      q = partition(a, p, r);
      quicksort2(a, p, q - 1);
      quicksort2(a, q + 1, r);
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


















  void compareArrays(int *a, int *aa, int n){
    int i;
    for(i = 0; i < n; i++){
      if(a[i] != aa[i]){
        printf("NOT THE SAME !!!\n");
        printf("NOT THE SAME !!!\n");
        printf("NOT THE SAME !!!\n");
        break;
      }
    }
    printf("TABLES ARE THE SAME !!!\n" );
    printf("TABLES ARE THE SAME !!!\n" );
    printf("TABLES ARE THE SAME !!!\n" );
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

void resetCounrers(){
  insertionSortInfo.comparisonNumber = 0;
  insertionSortInfo.swapNumber = 0;
  mergeSortInfo.comparisonNumber = 0;
  mergeSortInfo.swapNumber = 0;
  quicksortInfo.comparisonNumber = 0;
  quicksortInfo.swapNumber = 0;
}

double getInsertionSortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  insertionSort(aa, n);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getMergesortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  mergeSort(aa, n);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}

double getQuicksortTime(int *a, int n){
  clock_t start = clock();
  clock_t end = clock();
  int *aa;
  double seconds;
  aa = copyArray(a, n);
  start = clock();
  quicksort(aa, 0, n - 1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  free(aa);
  return seconds;
}
