#ifndef R_STRING_H
#define R_STRING_H

int strcmp(const char* p1, const char* p2);
void itos(unsigned long long i,char* s);
void ftos(float f,char* s);
int get_length(char str[]);
void reverse_string(char *str);
void string_concat(char* d, char* s);
void htos(unsigned int h, char* s);

#endif  /*_STRING_H */