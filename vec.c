#include "vec.h"
#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

vector *vecmake(size_t elsz, size_t icap)
{
  vector *x = malloc(sizeof(vector));
  if(!x)
    return NULL;
  *x = (vector){.cap = icap, .sz = 0, .dat = malloc(icap * elsz), .elsz = elsz};
  if(!x->dat)
  {
    free(x);
    return NULL;
  }
  return x;
}

int vecpush(vector *vc, void *val)
{
  if(!val)
    return 0;
  if(vc->sz >= vc->cap)
  {
    size_t ncap = (vc->cap == 0) ? 2 : vc->cap * 2;
    void *ndat = realloc(vc->dat, ncap * vc->elsz);
    if(!ndat)
      return 0;
    vc->dat = ndat;
    vc->cap = ncap;
  }
  memcpy((unsigned char *)vc->dat + vc->sz * vc->elsz, val, vc->elsz);
  vc->sz += 1;
  return 1;
}

int vecpop(vector *vc, void *out)
{
  if(!vc->sz)
    return 0;
  vc->sz -= 1;
  if(out)
    memcpy(out, (unsigned char *)vc->dat + vc->sz * vc->elsz, vc->elsz);
  return 1;
}

void *vecrpop(vector *vc)
{
  if(!vc->sz)
    return NULL;
  vc->sz -= 1;
  void *out = malloc(vc->elsz);
  if(!out)
    return NULL;
  if(out)
    memcpy(out, (unsigned char *)vc->dat + vc->sz * vc->elsz, vc->elsz);
  return out;
}

void *vecget(const vector *vc, size_t idx)
{
  if(idx >= vc->sz)
    return NULL;
  return (unsigned char *)vc->dat + idx * vc->elsz;
}

size_t veclen(const vector *vc)
{
  return vc->sz;
}

int vecshrink(vector *vc)
{
  if(!vc || vc->sz == 0)
  {
    free(vc->dat);
    vc->dat = NULL;
    vc->cap = 0;
    return 1;
  }
  if(vc->cap == vc->sz)
    return 1;
  void *ndat = realloc(vc->dat, vc->sz * vc->elsz);
  if(!ndat && vc->sz > 0)
  {
    return 0;
  }
  vc->dat = ndat;
  vc->cap = vc->sz;
  return 1;
}

void vecfree(vector *vc)
{
  if(!vc)
    return;
  free(vc->dat);
  free(vc);
}

void vecreset(vector *vc)
{
  if(!vc)
    return;
  free(vc->dat);
  vc->dat = NULL;
  vc->sz = 0;
  vc->cap = 0;
}