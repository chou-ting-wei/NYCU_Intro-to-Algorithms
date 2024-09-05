/* probID: W1-A-InPlacePartition */

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
