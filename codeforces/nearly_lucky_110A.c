#include <stdio.h>

int isLucky(int num) {
    while (num != 0) {
        int digit = num % 10;
        if (digit != 4 && digit != 7) {
            return 0; // Not a lucky digit
        }
        num = num / 10;
    }
    return 1; // All digits are lucky
}

int main() {
    printf("to check if a number is nearly lucky\n================\nEnter the number:")
    long long int n;
    int digit, count = 0, x = 1; // Initialize x to 1

    scanf("%lld", &n); // Input

    do { // Checks number of 4 and 7
        digit = n % 10;
        if (digit == 7 || digit == 4) {
            count++;
        }
        n = n / 10;
    } while (n != 0);

    do { // Checks for 4 and 7
        digit = count % 10;
        if (digit != 7 && digit != 4) {
            x = 0; // If not lucky, set x to 0
            break; // Break out of the loop when a non-4 or non-7 digit is encountered
        }
        count = count / 10;
    } while (count != 0);

    if (x == 0) {
        printf("NO\n");
    } else {
        printf(isLucky(count) ? "YES\n" : "NO\n");
    }

    return 0;
}
