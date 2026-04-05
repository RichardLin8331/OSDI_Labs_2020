
int strcmp (const char* p1, const char* p2) {
    const char* s1 = p1;
    const char* s2 = p2;
    char* c1 = (char*)s1;
    char* c2 = (char*)s2;
    while (*c1 == *c2) {
        if (*c1 == '\0') return 0;
        c1++;
        c2++;
    }

    return c1 - c2;
}


int get_length(char* c) {
    int i = 0;
    while (*c++ != '\0') i++;
    return i;
}


void string_concat(char* d, char* s) {
    char* d_tmp = d;
    
    while(*++d_tmp != '\0');
    while(*s != '\0') *d_tmp++ = *s++;
    *d_tmp = '\0';
}
void reverse_string(char *s) {
    char tmp;
    int l = get_length(s);
    for (int i = 0; i < l / 2; i++) {
        tmp = s[l - i - 1];
        s[l - i - 1] = s[i];
        s[i] = tmp;
    }
}

void itos(unsigned long long i, char *s) {
    unsigned long long tmp = i;
    char *s_start = s;
    if (tmp == 0) {
        *s++ = '0';
    } else {
        while (tmp ) {
            *s++ = (tmp % 10) + '0';
            tmp /= 10;
        }      
    }
    
    *s = '\0';
    reverse_string(s_start);
}

void ftos(float f, char* s) {
    char *s_start = s;
    int int_part = (int) f;
    float float_part = f - int_part;
    itos(int_part, s);
    while(int_part /= 10) s++;
    char pnt[] = ".";
    string_concat(s_start, pnt);
    s++;
    for (int cnt = 0; cnt < 6; cnt++)    float_part *= 10;
    char float_string[7];
    itos((int)float_part, float_string);
    string_concat(s_start, float_string);
}

void htos(unsigned int h, char* s) {

    for (int i = 7; i >= 0; i--) {
        unsigned int tmp = h&0xF;
        *(s+i+2) = tmp + (tmp > 0x9? ('A' - 10) : '0');
        h >>= 4;
    }
}