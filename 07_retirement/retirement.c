#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
    int months;
    double contribution;
    double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement (int startAge, double initial,retire_info working, retire_info retired) {
    int age = startAge / 12;
    int month = startAge % 12;
    double money = initial;
    for (int i = 0; i < working.months; i ++) {
        printf("Age %3d month %2d you have $%.2lf\n", age, month, money);
        month ++;
        if (month > 11) {
            month = 0;
            age ++;
        }
        money = money * (1 + working.rate_of_return / 12) + working.contribution;
    }

    for (int i = 0; i < retired.months; i ++) {
        printf("Age %3d month %2d you have $%.2lf\n", age, month, money);
        month ++;
        if (month > 11) {
            month = 0;
            age ++;
        }
        money = money * (1 + retired.rate_of_return / 12) + retired.contribution;
    }
}



int main(void) {
    retire_info working;
    retire_info retired;
    int initialAge = 327;
    double balance = 21345;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01;
    retirement(initialAge, balance, working, retired);
    return 0;
}

