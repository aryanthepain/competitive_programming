#include<stdio.h>

int main() {
    int matrix[3][3];
    int light[3][3];

    // Initialize lights to all 1
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            light[i][j] = 1;
        }
    }

    // Input matrix
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Toggle lights based on matrix values
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(matrix[i][j] % 2 == 1) {
                light[i][j] = 1 - light[i][j]; // Toggle the light

                //toggle only if within bounds
                if(j + 1 < 3)
                    light[i][j + 1] = 1 - light[i][j + 1];
                if(j - 1 >= 0)
                    light[i][j - 1] = 1 - light[i][j - 1];
                if(i + 1 < 3)
                    light[i + 1][j] = 1 - light[i + 1][j];
                if(i - 1 >= 0)
                    light[i - 1][j] = 1 - light[i - 1][j];
            }
        }
    }

    // Output lights
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d", light[i][j]);
        }
        printf("\n");
    }

    return 0;
}
