#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int verificaOrdemCrescente(int n, int v[]);
void geraVetorAleatorio(int n, int v[]);
void imprimeVetor(int n, int v[]);
void ordenaInsercao(int n, int v[]);
void ordenaSelecao(int n, int v[]);
void ordenaBolha(int n, int v[]);
void ordenaMerge(int n, int v[]);
void ordenaShell(int n, int v[]);
void ordenaHeap(int n, int v[]);
void ordenaQuick(int v[], int esq, int dir);

void merge(int arr[], int l, int m, int r);
void mergeSortRec(int arr[], int l, int r);
void heapify(int arr[], int n, int i);
int partition(int arr[], int low, int high);
void swap(int* a, int* b);

int main()
{
    setlocale(LC_ALL,"Portuguese");
    int V[N], Opcao;
    srand(time(NULL));

    do
    {
        printf("\t\tSelecione o método de ordenação:\n");
        printf("\t\t\t1 - Método de Inserção Simples\n");
        printf("\t\t\t2 - Método de Seleção Direta\n");
        printf("\t\t\t3 - Método da Bolha\n");
        printf("\t\t\t4 - Método Mergesort\n");
        printf("\t\t\t5 - Método Shellsort\n");
        printf("\t\t\t6 - Método Heapsort\n");
        printf("\t\t\t7 - Método Quicksort\n");
        
        printf("\t\t\tInforme o método: ");
        scanf("%i", &Opcao);
        
    } while (Opcao < 1 || Opcao > 7);
    
    geraVetorAleatorio(N, V);
    printf("Vetor gerado:\n");
    imprimeVetor(N, V);

    switch (Opcao)
    {
        case 1: 
            ordenaInsercao(N, V);
            printf("\nOrdenação - Método de Inserção Simples"); 
            break;
        case 2: 
            ordenaSelecao(N, V);
            printf("\nOrdenação - Método de Seleção Direta");
            break;
        case 3: 
            ordenaBolha(N, V);
            printf("\nOrdenação - Método da Bolha");
            break;
        case 4: 
            ordenaMerge(N, V);
            printf("\nOrdenação - Método Mergesort");
            break;
        case 5: 
            ordenaShell(N, V);
            printf("\nOrdenação - Método Shellsort");
            break;
        case 6: 
            ordenaHeap(N, V);
            printf("\nOrdenação - Método Heapsort");
            break;
        case 7: 
            ordenaQuick(V, 0, N-1);
            printf("\nOrdenação - Método Quicksort");
            break;
        default: printf("\n\nOpção inválida");
    }

    if (verificaOrdemCrescente(N, V) == 0)
        printf("\n--> Vetor em ordem crescente!");
    else
        printf("\n--> Erro de ordenação!");
    
    printf("\n");
    imprimeVetor(N, V);

    return 0;
}

void geraVetorAleatorio(int n, int v[]) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100;
    }
}

void imprimeVetor(int n, int v[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int verificaOrdemCrescente(int n, int v[]) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i+1]) {
            return 1;
        }
    }
    return 0;
}

void ordenaInsercao(int n, int v[]) {
   for (int i = 1; i < n; ++i) {
       int x = v[i];
       int j;
       for (j = i-1; j >= 0 && v[j] > x; --j) 
            v[j+1] = v[j];
       v[j+1] = x;
   }
}

void ordenaSelecao(int n, int v[]) {
    for (int i = 0; i < n-1; ++i) {
      int min = i;
      for (int j = i+1; j < n; ++j)
         if (v[j] < v[min])  
            min = j;
      int x = v[i]; 
      v[i] = v[min]; 
      v[min] = x;
   }
}

void ordenaBolha(int n, int v[]) {
   int Aux, Troca = 1;
   for (int i = 0; i < n && Troca > 0; i++) {
      Troca = 0;
      for (int j = 0; j < n-i-1; ++j) 
          if (v[j] > v[j+1]) {
              Aux = v[j];
              v[j] = v[j+1];
              v[j+1] = Aux;
              Troca = Troca + 1;
          }
      }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSortRec(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRec(arr, l, m);
        mergeSortRec(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void ordenaMerge(int n, int v[]) {
    mergeSortRec(v, 0, n - 1);
}

void ordenaShell(int n, int v[]) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void ordenaHeap(int n, int v[]) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (int i = n - 1; i >= 0; i--) {
        int temp = v[0];
        v[0] = v[i];
        v[i] = temp;
        heapify(v, i, 0);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void ordenaQuick(int v[], int esq, int dir) {
    if (esq < dir) {
        int pi = partition(v, esq, dir);
        ordenaQuick(v, esq, pi - 1);
        ordenaQuick(v, pi + 1, dir);
    }
}
