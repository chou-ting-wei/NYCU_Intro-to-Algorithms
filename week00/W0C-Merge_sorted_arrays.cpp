/* probID: W0-C-MergeSortedArrays */

void MergeSortedArrays(int A[], int n, int B[], int m, int C[]){
    int cnta = 0, cntb = 0, cntc = 0;
    while(cnta < n && cntb < m){
        if(A[cnta] < B[cntb]){
            C[cntc] = A[cnta];
            cnta ++;
            cntc ++;
        }
        else{
            C[cntc] = B[cntb];
            cntb ++;
            cntc ++;
        }
    }
    while(cnta < n){
        C[cntc] = A[cnta];
        cnta ++;
        cntc ++;
    }
    while(cntb < m){
        C[cntc] = B[cntb];
        cntb ++;
        cntc ++;
    }
}
