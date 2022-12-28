#include <iostream>
#include <pthread.h>
using namespace std;
const int MAX_SIZE = 50;
int array[MAX_SIZE];
int size;

void merge(int arr[], int l, int m, int r){
int i, j, k;
int n1 = m - l + 1;
int n2 = r - m;
int L[n1], R[n2];

for (i = 0; i < n1; i++)
L[i] = arr[l + i];
for (j = 0; j < n2; j++)
R[j] = arr[m + 1 + j];
i = 0;
j = 0;
k = l;
while (i < n1 && j < n2){
if (L[i] <= R[j]) {
arr[k] = L[i];
i++;}
 
else{
arr[k] = R[j];
j++;}
k++;}

while (i < n1){
arr[k] = L[i];
i++;
k++;}

while (j < n2){
arr[k] = R[j];
j++;
k++;}}

void mergeSort(int arr[], int l, int r){
if (l < r) {
int m = l + (r - l) / 2;
mergeSort(arr, l, m);
mergeSort(arr, m + 1, r);
merge(arr, l, m, r);}}

void *mergeSortThread(void *args){
int *arr = (int *) args;
int l = arr[0];
int r = arr[1];
mergeSort(array, l, r);
return NULL;
}

int main(){
cout << "ENTER SIZE OF THE ARRAY: ";
cin >> size;
cout << "ENTER ARRAY ELEMENTS: ";
for (int i = 0; i < size; i++)
cin >> array[i];

pthread_t thread1, thread2;
int arr1[2] = {0, size/2 - 1};
int arr2[2] = {size/2, size - 1};
pthread_create(&thread1, NULL, mergeSortThread, (void *) arr1);
pthread_create(&thread2, NULL, mergeSortThread, (void *) arr2);
pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

merge(array, 0, size/2 - 1, size - 1);
cout << "SORTED ARRAY: ";
for (int i = 0; i < size; i++)
cout << array[i] << " ";
cout << endl;
return 0;
}
