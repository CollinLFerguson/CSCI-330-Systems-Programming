/*
Collin L. Ferguson
Collin.l.ferguson@und.edu
CSCI 330 Systems Programming
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float r = 0.22;
    float B = 5000.0;
    float i = 0.00;
    float iPrevious = (r/12) * B;
    float p = 0.0;
    printf("Please enter payment amount: ");
    scanf("%f", &p);


    float iTotal = iPrevious;

    printf("$%.2f, $%4.2f\n", iPrevious, B);
    B = B - p + iPrevious;
    while(B>0)
    {
        i = (r/12.0) * B;
        printf("$%.2f, $%.2f\n", i, B);
        iPrevious = i;
        B = B - p + iPrevious;
        iTotal += i;
    }
    printf("Total interest paid: $%.2f", iTotal);

    return 0;
}
