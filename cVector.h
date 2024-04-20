#ifndef NVECTOR_H
#define NVECTOR_H

#include <stdbool.h>
#include <stddef.h>

#define DEFAULT_CAPACITY 12
#define NOT_FOUND ((size_t)-1)

typedef int datatype;

typedef struct tagVector {
  datatype *mp;
  size_t msize;
  size_t mcap;
} Vector, *hVector;

hVector createVector(void);
hVector createVectorWithCap(size_t cap);
hVector createVectorWithArray(const datatype *, size_t size);
hVector createFilledVector(size_t size, datatype val);
void destroyVector(hVector);
datatype at(hVector, size_t idx);
bool pushBack(hVector, datatype val);
bool popBack(hVector);
bool insertElement(hVector, size_t idx, datatype val);
bool eraseElement(hVector, size_t idx);
bool eraseValue(hVector, datatype val);
bool eraseVals(hVector, datatype val);
bool isempty(hVector);
void clear(hVector);
size_t find(hVector, datatype val);
void shrink(hVector);
bool setCap(hVector, size_t newCap);
void printVector(hVector h);

// functional macros
#define get_size(h) ((h)->msize)
#define get_cap(h) ((h)->mcap)
#define get_address(h) ((h)->mp)

#endif
