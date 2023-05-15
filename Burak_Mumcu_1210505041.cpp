#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <random>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

//Max deger icin sonsuz sayi
#define INF INT_MAX

void generate(int a[], int size);
void quicksort(int a[], int low, int high);
int partition(int a[], int low, int high);
int kadane(int a[], int size);
void dijkstra(int g[][G_SIZE], int d[][G_SIZE], int size);
void print1(int a[], int size);
void print2(int g[][G_SIZE], int size);
void print3(int g[][G_SIZE], int size, int t);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
        { 0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
        {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
        { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},
        { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},
        { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},
        { 5,  0,  4,  0,  6,  0,  9,  3,  0,  0},
        { 0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
        {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
        { 0,  0,  0,  0, 19,  0,  0,  8,  0,  5},
        {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int d[G_SIZE][G_SIZE];
    int t;

   

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    print1(a, A_SIZE);

    quicksort(a, 0, A_SIZE - 1);
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = kadane(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

    dijkstra(g, d,  G_SIZE);
    printf("\nFunction3 Sonuc:\n");
    print2(d, G_SIZE);
    printf("\n%d icin sonuc:\n", t);
    print3(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}




void generate(int a[], int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-MAX_W, MAX_W);

    for (int i = 0; i < size; i++) {
        a[i] = dis(gen);
    }
}




void quicksort(int a[], int low, int high) {
if (low < high) {
int pi = partition(a, low, high);
quicksort(a, low, pi - 1);
quicksort(a, pi + 1, high);
}
}

int partition(int a[], int low, int high) {
int pivot = a[high];
int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

int kadane(int a[], int size) {
int max_sum = 0;
int current_sum = 0;
    for (int i = 0; i < size; i++) {
        current_sum = current_sum + a[i];
        if (current_sum < 0) {
            current_sum = 0;
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

void dijkstra(int g[][G_SIZE], int d[][G_SIZE], int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (i == j) {
d[i][j] = 0;
}
else if (g[i][j] != 0) {
d[i][j] = g[i][j];
}
else {
d[i][j] = INF;
}
}
}
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

void print1(int a[], int size) {
for (int i = 0; i < size; i++) {
printf("%d ", a[i]);
if ((i + 1) % 10 == 0) {
printf("\n");
}
}
}

void print2(int g[][G_SIZE], int size) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (g[i][j] == INF) {
printf("INF ");
}
else {
printf("%3d ", g[i][j]);
}
}
printf("\n");
}
}

void print3(int d[][G_SIZE], int size, int t) {
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
if (i != j && d[i][j] < t) {
printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);
}
}
}
}
