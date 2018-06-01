#include <sys/types.h>

#ifndef _STRING_H
#define _STRING_H

char  *strcat(char *s1, char *s2);
char  *strncat(char *s1, char *s2, size_t n);
char  *strhcpy(char *dst, char *src);
char  *strcpy(char *dst, char *src);
char  *strncpy(char *dst, char *src, size_t len);
char  *strclr(char *str, int cnt);
char  *strucat(char *s1, char *s2);
char  *strucpy(char *dst, char *src);
char  *index(char *str, int c);
char  *rindex(char *str, int c);
char  *reverse(char *str);
char  *strend(char *str);
int   strcmp(char *s1, char *s2);
int   strncmp(char *s1, char *s2, size_t len);
int   strlen(char *s);
int   strucmp(char *s1, char *s2);
int   strnucmp(char *s1, char *s2, size_t len);
int   patmatch(char *pattern, char *str, char forceCase);
char  *strchr(char *str, int c);
char  *strrchr(char *str, int c);
size_t strspn(char *s1, char *s2);
size_t strcspn(char *s1, char *s2);
char  *strtok(char *str, char *step);
char  *strpbrk(char *s1, char *s2);

void _strass(char *to, char *from, int count);

void *memcpy(void *dst, void *src, size_t len);
void *memset(void *dst, int c, size_t len);
void *memchr(void *data, int c, size_t len);
int memcmp(char *dst, char *src);
int memncmp(char *dst, char *src, size_t len);

/* Convert string to hstring. */
char *strtohstr(char *dst, char *src);
/* Convert hstring to string. */
char *hstrtostr(char *dst, char *src);
/* Print a hstr */
int hputs(char *);

#endif
