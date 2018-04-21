#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void PrintByte(char data) {
    int i;
    for (i = 7; i >= 0; i--) {
        printf("%d", (data & (1 << i)) >> i);
    }
}

void PrintBitwiseRepresentation (void* data, int size) {
    printf("The bitwise representation looks like:\n");
    int i;
    for (i = size - 1; i >=0; i--) {
        PrintByte(*((char*) data + i));
        printf(" ");
    }
    printf("\n");
}

void testDouble() {
    printf("Enter the double:\n");
    double d;
    scanf("%f", &d);
    PrintBitwiseRepresentation(&d, sizeof(double));
}

void testFloat() {
    printf("Enter the float:\n");
    float f;
    scanf("%f", &f);
    PrintBitwiseRepresentation(&f, sizeof(float));
}

void testInt() {
    printf("Enter the int:\n");
    int i;
    scanf("%d", &i);
    PrintBitwiseRepresentation(&i, sizeof(int));
}

void testUnInt() {
    printf("Enter the unsigned int:\n");
    unsigned int uni;
    scanf("%d", &uni);
    PrintBitwiseRepresentation(&uni, sizeof(unsigned int));
}

void stTest() {
    double d = 0.52;
    float f = 0.125;
    int i = 342;
    unsigned int uni = 342;
    PrintBitwiseRepresentation(&d, sizeof(double));
    PrintBitwiseRepresentation(&f, sizeof(float));
    PrintBitwiseRepresentation(&i, sizeof(int));
    PrintBitwiseRepresentation(&uni, sizeof(unsigned int));
}

int main() {
    printf("Enter 1 for double type, 2 for float type, 3 for int, 4 for unsigned int, 5 for standard tests or 0 to finish the program:\n");
    int type;
    while (type != 0) {
        scanf("%d", &type);
        assert(type <= 5 && type >= 0);
        if (type == 1) testDouble();
        if (type == 2) testFloat();
        if (type == 3) testInt();
        if (type == 4) testUnInt();
        if (type == 5) stTest();
    }
    return 0;
}





