#include <iostream>

using namespace std;
 
template <class T>
void Print(T& vec, int n, string s){
    cout << s << ": [" << flush;
    for (int i=0; i<n; i++){
        cout << vec[i] << flush;
        if (i < n-1){
            cout << ", " << flush;
        }
    }
    cout << "]" << endl;
}
 
void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
 
void BubbleSort(int A[], int n){
    int flag = 0;
    for (int i=0; i<n-1; i++){
        for (int j=0; j<n-1-i; j++){
            if (A[j] > A[j+1]){
                swap(&A[j], &A[j+1]);
                flag = 1;
            }
        }
        if (flag == 0){
            return;
        }
    }
}

void InsertionSort(int A[], int n){
    for (int i=1; i<n; i++){
        int j = i-1;
        int x = A[i];
        while (j>-1 && A[j] > x){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = x;
    }
}

void SelectionSort(int A[], int n){
    for (int i=0; i<n-1; i++){
        int j;
        int k;
        for (j=k=i; j<n; j++){
            if (A[j] < A[k]){
                k = j;
            }
        }
        swap(&A[i], &A[k]);
    }
}

int partition(int A[], int low, int high){
    int pivot = A[low];
    int i = low;
    int j = high;
 
    do {
        do {i++;} while (A[i] <= pivot);
 
        do {j--;} while (A[j] > pivot);
 
        if (i < j){
            swap(&A[i], &A[j]);
        }
    } while (i < j);
 
    swap(&A[low], &A[j]);
    return j;
}
 
void QuickSort(int A[], int low, int high){
    if (low < high){
        int j = partition(A, low, high);
        QuickSort(A, low, j);
        QuickSort(A, j+1, high);
    }
}
 
void Merge(int A[], int low, int mid, int high){
    int i = low;
    int j = mid+1;
    int k = low;
    int B[high+1];
    while (i <= mid && j <= high){
        if (A[i] < A[j]){
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }
    while (i <= mid){
        B[k++] = A[i++];
    }
    while (j <= high){
        B[k++] = A[j++];
    }
    for (int i=low; i<=high; i++){
        A[i] = B[i];
    }
}
 
void MergeSort(int A[], int n){
    int p;
    for (p=2; p<=n; p=p*2){
        for (int i=0; i+p-1<n; i=i+p){
            int low = i;
            int high = i+p-1;
            int mid = (low+high)/2;
            Merge(A, low, mid, high);
        }
    }
    if (p/2 < n){
        Merge(A, 0, p/2-1, n-1);
    }
} 
 
int main() {
 
    int A[] = {3, 7, 9, 10, 6, 5, 12, 4, 11, 2};
    int n = sizeof(A)/sizeof(A[0]);
 	int choice;
    do
    {
        int x;
        system("cls");
        cout<<"Enter your choice.\n1.Bubble Sort.\n2.Insertion Sort.\n3.Selection Sort.\n4.Quick Sort.\n5.Merge Sort\n6.Exit.\n";
        cin>>choice;

        switch(choice)
        {
            case 1: system("cls");
            			Print(A, n, "\t\tA");
            			cout<<"After Bubble Sort\n";
                        BubbleSort(A, n);
    					Print(A, n, " Sorted A");
    					system("pause");
                        break;

            case 2: system("cls");
            			Print(A, n, "\t\tA");
                        InsertionSort(A, sizeof(A)/sizeof(A[0]));
                        cout<<"After insertion Sort\n";
    					Print(A, sizeof(A)/sizeof(A[0]), "Sorted A");
                        system("pause");
                        break;

            case 3: system("cls");
            			Print(A, n, "\t\tA");
                        SelectionSort(A, n);
                        cout<<"After Selection Sort\n";
    					Print(A, n, " Sorted A");
                        system("pause");
                        break;

            case 4: system("cls");
            			Print(A, n, "\t\tA");
                        QuickSort(A, 0, n-1);
                        cout<<"After Quick Sort\n";
						Print(A, n-1, " Sorted A");
					    cout << endl;
                        system("pause");
                        break;
                        
            case 5: system("cls");
            			Print(A, n, "\t\tA");
                        MergeSort(A, n);
                        cout<<"After Merge Sort\n";
    					Print(A, n, " Sorted A");
                        system("pause");
                        break;

            case 6: system("cls");
                        exit(0);
                        break;

            default:system("cls");
                cout<<"Enter correct choice.";
            }
    }while(true);
 
    return 0;
}
