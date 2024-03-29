/*
MA4830 Realtime Software for Mechatronic System xinzhi branch
AY2023/24 S2
CA1 Minor Assessment
Loh Xin Zhi
Loke Kum Yew
Thio Zheng Yeng
*/

// input headerfiles here

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




// define global constants
const float bmi_checkpoints[2][3] = {{18.5, 24.9, 29.9 }, {18.5, 23.0, 27.5 }}; // represent the list of values to check for each weight category
                                                                                //bmi_checkpoint[0] for non-asian, bmi_checkpoint[1] for asian

// define functions used 
float computeBMI(float mass, float height){ // mass in kg, height in m
    return mass / pow(height, 2);
}

char* returnBMIStatus(float bmi, int asian){ // function to return the status as string from the bmi value and race (asian or non-asian)
    char* bmi_status;
    
                                                                           
    bmi_status = (char*)malloc(12*sizeof(char)); //allocate memory to store string
    if (bmi_status == NULL){ // check memory is allocated correctly
        printf("Not Enough Memory! Exiting Program\n");
        exit(1);
    }

    // check which category the user falls into based on their bmi value and race
    if (bmi < bmi_checkpoints[asian][0]) strcpy(bmi_status, "Low");
    else if (bmi < bmi_checkpoints[asian][1]) strcpy(bmi_status, "Normal");
    else if (bmi <= bmi_checkpoints[asian][2]) strcpy(bmi_status, "Overweight");
    else strcpy(bmi_status, "Obese");

    return bmi_status;
}

void printStatusTable(float mass, float height, float bmi, int asian, char* state, char* remarks){ // function to print the status as table
    printf("\n");
    printf("|----------------|------------------------\n");
    printf("|Mass:           |%.2f\n", mass);
    printf("|----------------|------------------------\n");
    printf("|Height:         |%.2f\n", height);
    printf("|----------------|------------------------\n");
    printf("|BMI:            |%.2f\n", bmi);
    printf("|----------------|------------------------\n");
    printf("|Asian/Non-Asian:|");
    if (asian) {
        printf("Asian\n");
    }
    else {
        printf("Non-Asian\n");
        }
    printf("|----------------|------------------------\n");
    printf("|BMI State:      |%s\n", state);
    printf("|----------------|------------------------\n");
    printf("|Remarks:        |%s\n", remarks);
    printf("|----------------|------------------------\n");

}

void parse_arg(int argc, char const *argv[] ,float *mass, float *height, int *asian){
    int i;
    for (i=1; i< argc; i++){
        if (strcmp(argv[i], "-mass")==0) *mass = atof(argv[++i]);
        else if (strcmp(argv[i], "-height")==0) *height = atof(argv[++i]);
        else if (strcmp(argv[i], "-asian")==0){
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
                    *asian = 3; //error
                    printf("Invalid input argument for Asian. Key in manually later\n\n");
                    break;
            }
        }
    
    }
}


int main(int argc, char const *argv[]){
    float mass = 0.0;
    float height = 0.0;
    int asian = 3;
    float bmi;
    float cut;
    char remarks[100];
    char* status;
    char temp_asian = 'n';

    parse_arg(argc, argv, &mass, &height, &asian);

    // input error from command line checking
    if (mass<20 || mass > 200){
        printf("Enter your mass in kg: ");
        scanf("%f", &mass);
        while (mass < 20 || mass > 200 ){ //checking for invalid data
            printf("Invalid mass input, please enter again: ");
            while(getchar() != '\n');
            scanf("%f", &mass);
        }
    }
    if (height <0.5 || height > 2.8){
        printf("Enter your height in m: ");
        scanf("%f", &height);
        while (height < 0.5 || height > 2.8 ){ //checking for invalid data
            printf("Invalid height input, please enter again: "); 
            while(getchar() != '\n');
            scanf("%f", &height);
        }
    }
    while (asian == 3){
        printf("Are you Asian? (y/n): ");
        scanf("%s", &temp_asian);
        switch (temp_asian){
            case 'y':
            case 'Y':
                asian = 1;
                break;
            case 'n':
            case 'N':
                asian = 0;
                break;
            default:
                asian = 3; //error
                printf("Invalid input argument for Asian. Key in again\n\n");
                break;
        }
    }

    bmi = computeBMI(mass, height);

    status  = returnBMIStatus(bmi, asian);

    cut = (bmi-bmi_checkpoints[asian][1]) * pow(height, 2); // mass to cut to become normal
    if (cut > 0)  sprintf(remarks, "You are fat! Please reduce your weight by %.2fkg to remain in the Normal range!", cut);  
    else sprintf(remarks, "You are in the healthy weight range. Maintain your weight you don't want to be a fat ass");

    printStatusTable(mass, height, bmi, asian, status, remarks);

    free((void*) status);

    return 0;
}
