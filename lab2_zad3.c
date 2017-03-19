#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void exchange(int *a1, int *a2);
void quicksortYaro(int *a, int left, int right);
void swap(int *A, int i, int j);
void sort(int *A, int left, int right);

int main(){

  // int i, aa[] = {123, 1, 4, 5, 2, -12};
  // mergeSort(aa, 0, 5);
  int i, aa[] = {134, -12, 123};
  // mergeSort(aa, 0, 4);
    // int n = sizeof(a)/sizeof(a[0]);
  // int *aa =  insertionSort(a, 5);
  // quicksort(aa, 0, 2);
  // quicksortYaro(aa, 0, 3);
   sort(aa, 0, 2);

    for(i = 0; i <= 2; i++){
      printf("%d\n",aa[i] );
    }
    // printf("\n");
    // merge(aa, 0, 2, 4);


  return 0;
}

void exchange(int *a1, int *a2){
  int buffor = *a1;
  *a1 = *a2;
  *a2 = buffor;
}

void quicksortYaro(int *a, int left, int right){
  int p = a[left], q = a[right], l = left + 1, k = l, g = right - 1;
  int buffor;
  while(k <= g){
    if(a[k] < p){
      // exchange(&a[k], &a[l]);
      buffor = a[k];
      a[k] = a[l];
      a[l] = buffor;

      l++;
    }
    else{
      if(a[k] > q){
        while((a[g] > q) && (k < g)){
          g--;
        }
        // exchange(&a[k], &a[g]);

        buffor = a[k];
        a[k] = a[g];
        a[g] = buffor;

        g--;
        if(a[k] < p){
          // exchange(&a[k], &a[l]);
          buffor = a[k];
          a[k] = a[l];
          a[l] = buffor;

          l++;
        }
      }
    }
    k++;
  }
  l--;
  g++;
  // exchange(&a[left], &a[l]);
  buffor = a[left];
  a[left] = a[l];
  a[l] = buffor;


  // exchange(&a[right], &a[g]);
  buffor = a[right];
  a[right] = a[g];
  a[g] = buffor;


  quicksortYaro(a, left, l - 1);
  quicksortYaro(a, l + 1, g - 1);
  quicksortYaro(a, g + 1, right);
}


void sort(int *A, int left, int right) {
    if (right > left) {
        // Choose outermost elements as pivots
        if (A[left] > A[right]) swap(A, left, right);
        int p = A[left], q = A[right];

        // Partition A according to invariant below
        int l = left + 1, g = right - 1, k = l;
        while (k <= g) {
            if (A[k] < p) {
                swap(A, k, l);
                ++l;
            } else if (A[k] >= q) {
                while (A[g] > q && k < g) --g;
                swap(A, k, g);
                --g;
                if (A[k] < p) {
                    swap(A, k, l);
                    ++l;
                }
            }
            ++k;
        }
        --l; ++g;

        // Swap pivots to final place
        swap(A, left, l); swap(A, right, g);

        // Recursively sort partitions
        sort(A, left, l - 1);
        sort(A, l + 1, g - 1);
        sort(A, g + 1, right);
    }
}

void swap(int *A, int i, int j) {
   int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
}
