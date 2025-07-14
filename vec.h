#pragma once

#include <stddef.h>

struct vector
{
  void *dat;
  size_t cap;
  size_t sz;
  size_t elsz;
};

typedef struct vector vector;

vector *vecmake(size_t elsz, size_t icap);
int vecpush(vector *vc, void *val);
int vecpop(vector *vc, void *out);
void *vecrpop(vector *vc);
void *vecget(const vector *vc, size_t idx);
int vecshrink(vector *vc);
void vecfree(vector *vc);
void vecreset(vector *vc);
size_t veclen(const vector *vc);

#define veceach(typ, idx, vc, ...)                                             \
  for(typ idx = 0; idx < veclen(vc); idx++)                                    \
  {                                                                            \
    typ *item = (typ *)vecget(vc, idx);                                        \
    __VA_ARGS__                                                                \
  }

#if defined(__GNUC__) || defined(__clang__)
#define vec(vcn, typ) vector *vcn = vecmake(sizeof(typeof(typ)), 10)
#define veccap(vcn, typ, cap) vector *vcn = vecmake(sizeof(typeof(typ)), cap)
#else
#define vec(vcn, typ) vector *vcn = vecmake(sizeof(typ), 10)
#define veccap(vcn, typ, cap) vector *vcn = vecmake(sizeof(typ), cap)
#endif