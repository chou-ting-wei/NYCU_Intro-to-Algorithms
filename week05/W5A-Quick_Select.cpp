/* probID: W5-A-Quick-Select */

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

int quick_select(int A[], int left, int right, int k){
    if(left == right) return A[left];
    int tmp = left + rng() % (right - left + 1);
    int key = In_Place_Partition(A, left, right, tmp);
    if(key == k - 1) return A[key];
    else if(key > k - 1) return quick_select(A, left, key - 1, k);
    else return quick_select(A, key + 1, right, k);
}
