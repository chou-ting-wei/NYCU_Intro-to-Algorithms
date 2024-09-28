/* probID: W3-A-QuickSort */

#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

int In_Place_Partition(int A[], int left, int right, int key){
    swap(A[key], A[left]);
    int i = left + 1, j = right;
    while(i <= j){
        while(i <= j && A[i] <= A[left]) i ++;
        while(i <= j && A[j] > A[left]) j --;
        if(i < j){
            swap(A[i], A[j]);
            i ++;
            j --;
        }
    }
    swap(A[left], A[j]);
    return j;
}

void rec_quick_sort(int A[], int l, int r){
    if(l >= r) return;
    int tmp =  l + rng() % (r - l + 1);
    int key = In_Place_Partition(A, l, r, tmp);
    rec_quick_sort(A, l, key - 1);
    rec_quick_sort(A, key + 1, r);
}

void quick_sort(int A[], int n){
    rec_quick_sort(A, 0, n-1);
}
