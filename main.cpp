#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
using namespace std;

void swap(long *x, long *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

void sortareanaiva(long v[], int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if(v[i] > v[j])
                swap(&v[i], &v[j]);
        }
    }
}

void bubblesort(long v[], int n)
{
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (v[j] > v[j + 1])
                swap(&v[j], &v[j+1]);
        }
    }
}

int getmax(long v[], int n)
{
    int max = v[0];
    for (int i = 1; i < n; ++i) {
        if (v[i] > max)
            max = v[i];
    }
    return max;
}

void countsort(long v[], int n)
{
    int max = getmax(v,n);
    int w[max + 1];
    for (int i = 0; i < max + 1; ++i) {
        w[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        w[v[i]]++;
    }
    int aux[n + 1];
    for (int i = max; i > 0 ; --i) {
        w[i] = w[i-1];
    }
    w[0] = 0;
    for (int i = 1; i < max + 1; ++i) {
        w[i] = w[i] + w[i-1];
    }
    for (int i = 0; i < n; ++i) {
        aux[w[v[i]]] = v[i];
        w[v[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        v[i] = aux[i];
    }

}

void countsortradix(long v[], int n, int x)
{
    int* w = new int[1000001];
    int i;
    int* count = new int[1000001];
    for (int j = 0; j < n; ++j) {
        count[j] = 0;
    }
    for (i = 0; i < n; i++)
        count[(v[i] / x) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        w[count[(v[i] / x) % 10] - 1] = v[i];
        count[(v[i] / x) % 10]--;
    }
    for (i = 0; i < n; i++)
        v[i] = w[i];
}

void radixsort(long v[], int n)
{
    int m = getmax(v, n);
    for (int x = 1; m / x > 0; x *= 10)
        countsortradix(v, n, x);
}

void merge(long v[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i)
        L[i] = v[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = v[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(long v[],int l,int r){
    if(l>=r)
        return;
    int m = l + (r - l) / 2;
    mergesort(v,l,m);
    mergesort(v,m+1,r);
    merge(v,l,m,r);
}

int partition (long v[], int l, int r)
{
    long pivot = v[r];
    int i = (l - 1);
    for (int j = l; j < r; ++j)
    {
        if (v[j] < pivot)
        {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[r]);
    return (i + 1);
}
void quicksort(long v[], int l, int r)
{
    if (l < r)
    {
        int p = partition(v, l, r);
        quicksort(v, l, p - 1);
        quicksort(v, p + 1, r);
    }
}


int main() {
    cout << "0 - sortareanaiva" << endl << "1 - bubblesort" << endl << "2 - countsort" << endl << "3 - radixsort"
    << endl << "4 - mergesort" << endl << "5 - quicksort" << endl << "Alegeti sortarea dorita:";
    int x;
    cin >> x;
    int n;
    n = 1;
    while( n!=100000){
        n *= 10;
        long* v = new long[10000001];
        for (int i = 0; i < n; ++i) {
            v[i] = 1 + (rand() % 10);
        }
        const auto t1 = std::chrono::high_resolution_clock::now();
        if(x == 0)
            sortareanaiva(v,n);
        else
            if (x == 1)
                bubblesort(v, n);                        //bubblesort
            else
                if (x == 2)
                    countsort(v, n);                         //countsort
                else
                    if (x == 3)
                        radixsort(v, n);                     //radixsort
                    else
                        if (x == 4)
                            mergesort(v, 0, n - 1);                   //mergesort
                        else{
                            quicksort(v, 0, n);                       //quicksort
                        }
        const auto t2 = std::chrono::high_resolution_clock::now();
        int ok = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (v[i] > v[i + 1]) {
                cout << "not sorted\n";
                ok = 0;
                break;
            }
        }
        if(ok == 1) {
            cout<<"sorted\n";
        }
        std::cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()) << " nanoseconds \n";
    }
}