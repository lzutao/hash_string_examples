#include <stdio.h>
#include <inttypes.h>

static int hash_class_objc(const char *str);
static unsigned long long r_str_hash64(const char *s);
static unsigned int r_str_hash(const char *s);
static unsigned long sdbm(const char *str);
static size_t fnv1a_hash(const char *cp);

int
main(void)
{
  int hash;
  unsigned int hash1;
  unsigned long long hash2;
  unsigned long hash3;
  size_t hash4;
  size_t i = 0;
  const char *oses[] = { "Linux", "OpenBSD", "FreeBSD", "Mach", "Windows" };
  size_t oses_len = sizeof(oses) / sizeof(oses[0]);
  for (i = 0; i < oses_len; ++i) {
    hash = hash_class_objc(oses[i]);
    hash1 = r_str_hash(oses[i]);
    hash2 = r_str_hash64(oses[i]);
    hash3 = sdbm(oses[i]);
    hash4 = fnv1a_hash(oses[i]);
    printf("========= Round %zu ========================\n", i);
    printf("%" PRIX32 "\n", hash);
    printf("%" PRIX32 "\n", hash1);
    printf("%llX\n", hash2);
    printf("%" PRIX64 "\n", hash3);
    printf("%zX\n", hash4);
  }
  return 0;
}

static int
hash_class_objc(const char *str)
{
  int hash = 0;
  int c;
  while ((c = *str++)) {
    hash = (hash << 4) ^ (hash >> 28) ^ c;
  }
  hash = (hash ^ (hash >> 10) ^ (hash >> 20)) & 1023;
  return hash;
}

static unsigned long long
r_str_hash64(const char *s)
{
  unsigned long long h = 5381;
  int c;
  while ((c = *s++)) {
    h = (h ^ (h << 5)) ^ c; /* hash * 33 + c */
  }
  return h;
}

static unsigned int
r_str_hash(const char *s)
{
  return (unsigned int) r_str_hash64 (s);
}

static unsigned long
sdbm(const char *str)
{
  unsigned long hash = 0;
  int c;

  while ((c = *str++)) {
    hash = c + (hash << 6) + (hash << 16) - hash; /* hash * 65599 + c */
  }

  return hash;
}

/* Fowler/Noll/Vo (FNV) hash function, variant 1a */
static size_t
fnv1a_hash(const char *cp)
{
    size_t hash = 0x811c9dc5;
    while (*cp) {
        hash ^= (unsigned char) *cp++;
        hash *= 0x01000193;
    }
    return hash;
}
