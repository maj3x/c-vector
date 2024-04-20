#include "cVector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

hVector createVectorWithCap(size_t cap) {
  hVector hvec = (hVector)malloc(sizeof(Vector));
  if (!hvec) {
    return NULL;
  }

  hvec->msize = 0;
  hvec->mcap = cap;
  hvec->mp = (datatype *)malloc(cap * sizeof(datatype));
  if (!hvec->mp) {
    free(hvec);
    return NULL;
  }

  return hvec;
}

hVector createVector(void) { return createVectorWithCap(DEFAULT_CAPACITY); }

hVector createVectorWithArray(const datatype *p, size_t size) {
  hVector hvec = createVectorWithCap(size);
  if (!hvec) {
    return NULL;
  }

  hvec->msize = size;
  memmove(hvec->mp, p, size * sizeof(datatype));

  return hvec;
}

hVector createFilledVector(size_t size, datatype val) {
  hVector hvec = createVectorWithCap(size);
  if (!hvec) {
    return NULL;
  }

  hvec->msize = size;
  for (size_t i = 0; i < size; ++i) {
    hvec->mp[i] = val;
  }

  return hvec;
}

void destroyVector(hVector hvec) {
  free(hvec->mp);
  free(hvec);
}

bool setCap(hVector hvec, size_t newCap) {
  if (newCap < hvec->mcap) {
    return false;
  }
  if (newCap == hvec->mcap) {
    return true;
  }

  datatype *ptemp = (datatype *)realloc(hvec->mp, newCap * sizeof(datatype));
  if (!ptemp) {
    return false;
  }

  hvec->mp = ptemp;
  hvec->mcap = newCap;

  return true;
}

bool pushBack(hVector hvec, datatype val) {

  if (hvec->msize == hvec->mcap && !setCap(hvec, hvec->mcap * 2)) {
    return false;
  }

  hvec->mp[hvec->msize] = val;
  ++hvec->msize;
  return true;
}

// 2 4 7 9 1 5 8

bool insertElement(hVector hvec, size_t idx, datatype val) {
  if (idx > hvec->msize) {
    return false;
  }

  if (hvec->msize == hvec->mcap && !setCap(hvec, hvec->mcap * 2)) {
    return false;
  }

  memmove(hvec->mp + idx + 1, hvec->mp + idx,
          (hvec->msize - idx) * sizeof(datatype));

  hvec->mp[idx] = val;
  ++hvec->msize;
  return true;
}

bool popBack(hVector hvec) {
  --hvec->msize;
  return true;
}

datatype at(hVector hvec, size_t idx) { return hvec->mp[idx]; }

bool eraseElement(hVector hvec, size_t idx) {
  if (idx >= hvec->msize) {
    return false;
  }

  memmove(hvec->mp + idx, hvec->mp + idx + 1,
          (hvec->msize - idx - 1) * sizeof(datatype));

  --hvec->msize;
  return true;
}

void printVector(hVector h) {
  printf("size = %zu  capacity = %zu\n", h->msize, h->mcap);
  for (size_t idx = 0; idx < h->msize; ++idx) {
    printf("%d ", h->mp[idx]);
  }
  printf("\n");
}

void shrink(hVector hvec) {
  if (hvec->mcap == hvec->msize) {
    return;
  }

  hvec->mp = (datatype *)realloc(hvec->mp, hvec->msize * sizeof(datatype));
  hvec->mcap = hvec->msize;
}

size_t find(hVector hvec, datatype val) {
  for (size_t idx = 0; idx < hvec->msize; ++idx) {
    if (hvec->mp[idx] == val) {
      return idx;
    }
  }

  return NOT_FOUND;
}