#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// testing out parsearg function

void parse_arg(int argc, char const *argv[] ,float *mass, float *height, int *asian){
    // *mass = atof(argv[1]);
    // *height = atof(argv[2]);
    // *asian = atoi(argv[3]);
    int i;
    for (i=1; i< argc; i++){
        if (strcmp(argv[i], "-mass") == 0) *mass = atof(argv[++i]);
        else if (strcmp(argv[i], "-height")== 0 ) *height = atof(argv[++i]);
        else if (strcmp(argv[i], "-asian")== 0){
            char a = argv[++i][0];
            switch (a){
                case 'y':
                case 'Y':
                    *asian = 1;
                    break;
                case 'n':
                case 'N':
                    *asian = 0;
                    break;
                default:
                    printf("Invalid input argument for Asian");
                    break;
            }
        }
    
    }
}

int main(int argc, char const *argv[])
{

    float mass = 90.0;
    float height = 1.72;
    int asian = 1;
    // int argc_1 = 7;
    // char const *argv_1[] = {"something", "-mass", "55.0", "-height", "1.55", "-asian", "n"};
    parse_arg(argc, argv, &mass, &height, &asian);


    printf("mass = %f\n",mass);
    printf("height = %f\n",height);
    printf("asian = %d\n",asian);


    return 0;
}
