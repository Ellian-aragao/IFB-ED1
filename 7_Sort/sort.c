#include "sort.h"
#include <stdio.h>


#define getAddrres(vector, position, size) ((vector) + ((position) * (size)))

static inline void printVector(const int *vector, const int tamVector)
{
  putchar('[');
  for (int i = 0; i < tamVector; i++)
    printf(i == tamVector - 1 ? "%d" : "%d, ", vector[i]);
  puts("]");
}

static int compareInteger(void *i1, void *i2)
{
  return (*(int *)i1 > *(int *)i2) ? 1 : 0;
}

static inline void *createTmpPointer(size_t *size)
{
  void *tmp = malloc(*size);
  if (!tmp)
    exit(EXIT_FAILURE);
  return tmp;
}

static inline void swap(void *item1, void *item2, void *tmp, size_t *size)
{
  memcpy(tmp, item1, *size);
  memcpy(item1, item2, *size);
  memcpy(item2, tmp, *size);
}

void bubbleSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  u_long boolean = 1;
  void *tmp = createTmpPointer(&SizeValuesVector);
  while (boolean != 0)
  {
    u_long i;
    for (boolean = 0, i = 0; i < tamVector - 1; i++)
    {
      if (comparator(getAddrres(vector, i + 1, SizeValuesVector), getAddrres(vector, i, SizeValuesVector)))
      {
        swap(getAddrres(vector, i, SizeValuesVector), getAddrres(vector, i + 1, SizeValuesVector), tmp, &SizeValuesVector);
        boolean = i;
      }
    }
#ifdef DEBUG
    printVector(vector, tamVector);
#endif
    tamVector--;
  }
  free(tmp);
}

void insertionSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  void *tmp = createTmpPointer(&SizeValuesVector);
  for (long j, i = 1; i < tamVector; i++)
  {
#ifdef DEBUG
    printVector(vector, i + 1);
#endif
    memcpy(tmp, getAddrres(vector, i, SizeValuesVector), SizeValuesVector);
    for (j = i - 1; j >= 0 && comparator(tmp, getAddrres(vector, j, SizeValuesVector)); j--)
      memcpy(getAddrres(vector, j + 1, SizeValuesVector), getAddrres(vector, j, SizeValuesVector), SizeValuesVector);
    memcpy(getAddrres(vector, j + 1, SizeValuesVector), tmp, SizeValuesVector);
  }
  free(tmp);
}

void insertionSortItem(void *vector, u_long tamVector, void *item, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  memcpy(getAddrres(vector, tamVector - 1, SizeValuesVector), item, SizeValuesVector);
  insertionSort(vector, tamVector, SizeValuesVector, comparator);
}

static void quicksortRecursive(void *vector, u_long *init, u_long *final, size_t *SizeValuesVector, int (*comparator)(void *, void *), void *tmp, void *pivo)
{
  memcpy(pivo, getAddrres(vector, (*init + *final) / 2, *SizeValuesVector), *SizeValuesVector);
  u_long i = *init;
  u_long j = *final - 1;
  while (i <= j)
  {
    while (comparator(getAddrres(vector, i, *SizeValuesVector), pivo) && i < *final)
      i++;
    while (comparator(pivo, getAddrres(vector, j, *SizeValuesVector)) && j > *init)
      j--;
    if (i <= j)
    {
      swap(getAddrres(vector, i, *SizeValuesVector), getAddrres(vector, j, *SizeValuesVector), tmp, SizeValuesVector);
      i++;
      j--;
    }
  }
#ifdef DEBUG
  printVector(vector, *final);
#endif
  if (j++ > *init)
    quicksortRecursive(vector, init, &j, SizeValuesVector, comparator, tmp, pivo);
  if (i < *final)
    quicksortRecursive(vector, &i, final, SizeValuesVector, comparator, tmp, pivo);
}

void quickSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  void *tmp = createTmpPointer(&SizeValuesVector);
  void *pivo = createTmpPointer(&SizeValuesVector);
  u_long init = 0;
  quicksortRecursive(vector, &init, &tamVector, &SizeValuesVector, comparator, tmp, pivo);
  free(tmp);
  free(pivo);
}

void selectionSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  void *tmp = createTmpPointer(&SizeValuesVector);
  for (u_long min, i = 0; i < tamVector - 1; i++)
  {
    min = i;
    for (u_long j = i + 1; j < tamVector; j++)
      if (comparator(getAddrres(vector, j, SizeValuesVector), getAddrres(vector, min, SizeValuesVector)))
        min = j;
#ifdef DEBUG
    printVector(vector, min + 1);
#endif
    if (memcmp(getAddrres(vector, i, SizeValuesVector), getAddrres(vector, min, SizeValuesVector), SizeValuesVector))
      swap(getAddrres(vector, i, SizeValuesVector), getAddrres(vector, min, SizeValuesVector), tmp, &SizeValuesVector);
  }
  free(tmp);
}

void shellSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  const u_long NUMERO_MAGICO = 3;
  void *tmp = createTmpPointer(&SizeValuesVector);

  u_long h = 1;
  while (h < tamVector)
    h = NUMERO_MAGICO * h + 1;

  while (h > 0)
  {
    for (u_long j, i = h; i < tamVector; i++)
    {
      memcpy(tmp, getAddrres(vector, i, SizeValuesVector), SizeValuesVector);
      for (j = i; j > h - 1 && comparator(tmp, getAddrres(vector, j - h, SizeValuesVector)); j -= h)
        memcpy(getAddrres(vector, j, SizeValuesVector), getAddrres(vector, j - h, SizeValuesVector), SizeValuesVector);
      memcpy(getAddrres(vector, j, SizeValuesVector), tmp, SizeValuesVector);
    }
    h /= NUMERO_MAGICO;
#ifdef DEBUG
    printVector(vector, tamVector);
#endif
  }
  free(tmp);
}

static inline void mergeVectors(void *vector, const u_long *init, const u_long *mid, const u_long *end, void *tmpV, const size_t *SizeValuesVector, int (*comparator)(void *, void *))
{
  u_long left = *init;
  u_long right = *mid;
  for (u_long i = *init; i < *end; i++)
  {
    if ((left < *mid) && ((right >= *end) || comparator(getAddrres(vector, left, *SizeValuesVector), getAddrres(vector, right, *SizeValuesVector))))
    {
      memcpy(getAddrres(tmpV, i, *SizeValuesVector), getAddrres(vector, left, *SizeValuesVector), *SizeValuesVector);
      left++;
    }
    else
    {
      memcpy(getAddrres(tmpV, i, *SizeValuesVector), getAddrres(vector, right, *SizeValuesVector), *SizeValuesVector);
      right++;
    }
  }
  for (u_long i = *init; i < *end; ++i)
    memcpy(getAddrres(vector, i, *SizeValuesVector), getAddrres(tmpV, i, *SizeValuesVector), *SizeValuesVector);
#ifdef DEBUG
  printVector(vector, *end);
#endif
}

static void mergeSortRecursive(void *vector, const u_long *init, const u_long *end, void *tmpV, const size_t *SizeValuesVector, int (*comparator)(void *, void *))
{
  if ((*end - *init) >= 2)
  {
    const u_long mid = ((*init + *end) / 2);
    mergeSortRecursive(vector, init, &mid, tmpV, SizeValuesVector, comparator);
    mergeSortRecursive(vector, &mid, end, tmpV, SizeValuesVector, comparator);
    mergeVectors(vector, init, &mid, end, tmpV, SizeValuesVector, comparator);
  }
}

void mergeSort(void *vector, const u_long tamVector, const size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  size_t var = SizeValuesVector * tamVector;
  void *tmp = createTmpPointer(&var);
  var = 0;
  mergeSortRecursive(vector, &var, &tamVector, tmp, &SizeValuesVector, comparator);
}

void heapSort(void *vector, u_long tamVector, size_t SizeValuesVector, int (*comparator)(void *, void *))
{
  void *tmp = createTmpPointer(&SizeValuesVector);
  u_long i = tamVector / 2;
  while (1)
  {
    if (i > 0)
    {
      i--;
      memcpy(tmp, getAddrres(vector, i, SizeValuesVector), SizeValuesVector);
    }
    else
    {
      tamVector--;
      if (tamVector <= 0)
        return;
      memcpy(tmp, getAddrres(vector, tamVector, SizeValuesVector), SizeValuesVector);
      memcpy(getAddrres(vector, tamVector, SizeValuesVector), getAddrres(vector, 0, SizeValuesVector), SizeValuesVector);
    }
#ifdef DEBUG
    printVector(vector, tamVector);
#endif

    u_long root = i;
    u_long node = i * 2 + 1;
    while (node < tamVector)
    {
      if ((node + 1 < tamVector) && comparator(getAddrres(vector, node, SizeValuesVector), getAddrres(vector, node + 1, SizeValuesVector)))
        node++;
      if (comparator(tmp, getAddrres(vector, node, SizeValuesVector)))
      {
        memcpy(getAddrres(vector, root, SizeValuesVector), getAddrres(vector, node, SizeValuesVector), SizeValuesVector);
        root = node;
        node = root * 2 + 1;
      }
      else
        break;
    }
    memcpy(getAddrres(vector, root, SizeValuesVector), tmp, SizeValuesVector);
  }
}

void countingSort(int *vector, const u_long tamVector, const u_long maxItemVector)
{
  int *bucketV = calloc(maxItemVector, sizeof(int));
  if (!bucketV)
    exit(EXIT_FAILURE);

  for (int i = 0; i < tamVector; i++)
    bucketV[vector[i]]++;

  for (int i = 0, j = 0; j < maxItemVector; j++)
    while (bucketV[j]--)
      vector[i++] = j;

  free(bucketV);
}

#define tam_bucket 10
#define num_bucket 10
#define max 10
typedef struct
{
  int qtd;
  int valores[tam_bucket];
} Bucket;

void bucketSort(int *vector, const u_long tamVector)
{

  int maior, menor;
  for (u_long i = 0, menor = maior = vector[i]; i < tamVector; i++)
  {
    if (vector[i] > maior)
      maior = vector[i];
    if (vector[i] < menor)
      menor = vector[i];
  }

  size_t nBuckets = ((maior - menor) / tam_bucket + 1);
  Bucket *bucket = calloc(nBuckets, sizeof(Bucket));
  if (!bucket)
    exit(EXIT_FAILURE);

  for (u_long i = 0; i < tamVector; i++)
  {
    int pos = (vector[i] - menor) / tam_bucket;
    bucket[pos].valores[bucket[pos].qtd] = vector[i];
    bucket[pos].qtd++;
  }

  for (u_long i = 0, pos = 0; i < num_bucket; i++)
  {
    quickSort(bucket[i].valores, bucket[i].qtd, sizeof(int), compareInteger);
    for (u_long j = 0; j < bucket[i].qtd; j++, pos++)
      vector[pos] = bucket[i].valores[j];
  }
  free(bucket);
}

#ifndef LIB
#include <stdio.h>
int main()
{
  int vector[] = {19, 1234, 58, 34, 17, 68, 345, 63, 234, 67, 38};
  const int tam = sizeof(vector) / sizeof(vector[0]);

  printVector(vector, tam);

  heapSort(vector, tam, sizeof(vector[0]), compareInteger);

  printVector(vector, tam);
  return 0;
}
#endif