#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dump_mem(void *ptr, size_t len)
{
    unsigned char *p = (unsigned char *)ptr;
    for (size_t i = 0; i < len; i++)
        printf("%02X ", p[i]);
}

void swap(void *n, void *r, size_t size)
{
    char *p = n, *q = r, tmp;
    while (size--)
    {
        tmp = *p;
        *p++ = *q;
        *q++ = tmp;
    }
}

int main()
{
    char s[] = "HELLO \0 WROLD";
    int n, leng;
    float r;
    char *ptr = (char *)&n;
    unsigned char *ptr2 = (unsigned char *)&r;
    char *ptr3 = s;

    printf("Enter the value of N\n");
    scanf("%d", &n);
    printf("Content of memory region of variable num\n");
    for (int i = 0; i < sizeof(n); i++)
    {
        printf("%p :0x%02x\n", ptr, *ptr);
        ptr++;
    }
    printf("Enter the value of R\n");
    scanf("%f", &r);
    printf("The memory address of r is %p\n", &r); // display the memory address of float
    for (int i = 0; i < sizeof(r); i++)
        printf("%02x\n", *(ptr2 + i));
    for (int i = 0; s[i] != '\0'; i++)
        printf("%c\n", s[i]);
    printf("Before sawp\n n = %d \n r=%f\n", n, r);
    printf("n = [");
    dump_mem(&n, sizeof(n));
    printf("]\n");
    printf("r = [");
    dump_mem(&r, sizeof(r));
    printf("]\n");
    swap(&n, &r, sizeof(n) > sizeof(r) ? sizeof(n) : sizeof(r));
    printf("n = [");
    dump_mem(&n, sizeof(n));
    printf("]\n");
    printf("r = [");
    dump_mem(&r, sizeof(r));
    printf("]\n");
    printf("After swap value casting: a = %f, b = %d\n", (float)n, (int)r);
    printf("After swap pointer casting: a = %f, b = %d\n", *((float *)&n), *((int *)&r));
}
