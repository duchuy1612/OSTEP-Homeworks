#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int *huy = (int*) malloc(sizeof(int));
    *huy = 10;
    printf("%d\n", *huy);
    return 0;
}
