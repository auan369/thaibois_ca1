#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//func declarations--------------------------------------------------------------------------------------
float bmi_calc (float height, float weight){
    float bmi_val = weight / (pow(height,2));
    return bmi_val;
}

void display_table(float mass, float height, float your_bmi, char asian, char* status, float mass_change){

    printf("\n");
    printf("--------------------|------------------------\n");
    printf("Asian?              |");
    if (asian == 1){
        printf("   Yes\n");
    }
    else if (asian == 0){
        printf("   No\n");
    }
    printf("Height?             |   %f\n",height);
    printf("--------------------|------------------------\n");
    printf("Mass?               |   %f\n", mass);
    printf("--------------------|------------------------\n");
    printf("BMI?                |   %f\n", your_bmi);
    printf("--------------------|------------------------\n");
    printf("BMI Status          |   %s\n", status);
    printf("--------------------|------------------------\n");
    printf("Mass to lose        |   %f\n", mass_change);
    printf("--------------------|------------------------\n");
    printf("What to do next?    |");

    if (strcmp(status, "Low") == 0 ){
        printf("   smlj eat more\n");
    }
    else if (strcmp(status, "Normal")== 0){
        printf("   Who is a good boy? you are!!\n");
    }
    else if (strcmp(status, "Overweight")== 0){
        printf("   a lil chubby dont u think? eat 2 meals a day only from now on\n");
    }
    else if (strcmp(status, "Obese")== 0){
        printf("   fee fi fo fum, someones gotta eat less chum. no meals for a week for you fat boy\n");
    }
    
    
    printf("--------------------|------------------------\n");
}

char* checkBMI (int asian, float your_bmi){

    char* bmi_status; //pointer to character

    bmi_status = (char*)malloc(12*sizeof(char)); //allocate memory to store string
    /* printf("asian = %d\n", asian);
    printf("your bmi = %f\n", your_bmi);
    printf("your bmi status = %s\n", bmi_status); */

    if (asian = 1){ //asian
        if (your_bmi < 18.5){
            bmi_status = "Low";
        }
        else if ((your_bmi>= 18.5) & (your_bmi < 23.0)){
            bmi_status = "Normal";
        }
        else if ((your_bmi>= 23.0) & (your_bmi < 27.5)){
            bmi_status = "Overweight";
        }
        else if (your_bmi>= 27.5){
            bmi_status = "Obese";
        }
        else{  
            printf("Wrong input!!"); //not sure if this would work as exception handling
        }
        //printf("%s\n", bmi_status);
    }

    else if (asian = 0){ //Non Asian
        if (your_bmi < 18.5){
            bmi_status = "Low";
        }
        else if ((your_bmi>= 18.5) & (your_bmi < 24.9)){
            bmi_status = "Normal";
        }
        else if ((your_bmi>= 24.9) & (your_bmi < 29.9)){
            bmi_status = "Overweight";
        }
        else if (your_bmi>= 29.9){
            bmi_status = "Obese";
        }
        else{  
            printf("Wrong input!!"); //not sure if this would work as exception handling
        }
    }

    return bmi_status;
}

float weight_to_lose(float your_bmi, int asian, float height, float mass){ //only for overweight and obese

    float bmi_change;
    float mass_change; 

    if (asian == 1){
        bmi_change = your_bmi - 23;
        mass_change = (bmi_change) * (pow(height,2));
    }

    else if (asian == 0){
        bmi_change = your_bmi - 24.9;
        mass_change = (bmi_change) * (pow(height,2));
    }
    
    return mass_change;
}

//main code----------------------------------------------------------------------------------------------
int main(void){
    float weight = 0;
    float height = 0;
    char check_asian;
    char* status;
    int asian = -1;
    float mass_change;

    printf("Enter your height in m: ");
    scanf("%f", &height);
    //assuming 1.2<= height <= 2.5
    while (height < 1.2 || height > 2.5 ){
        printf("invalid height input, please enter again: ");
        while(getchar() != '\n');
        scanf("%f", &height);}
    printf("height: %f\n", height);

    printf("Enter your weight in kg: ");
    scanf("%f", &weight);
    //assuming 30<= weight <= 200
    while (weight < 30 || weight > 200 ){
        printf("invalid weight input, please enter again: ");
        while(getchar() != '\n');
        scanf("%f", &weight);}
    printf("weight: %f\n", weight);

    printf("Are you Asian? (Y/N): ");
    scanf(" %c", &check_asian); // Notice the space before %c to catch any preceding whitespace
    // Check if the character is within the valid range
    while (check_asian != 'Y' || check_asian != 'y' || check_asian != 'N' || check_asian != 'n' ) {
        printf("Invalid input. Please only enter Y/y for Yes and N/n for No: ");
        // Clear the input buffer in case of invalid input
        while(getchar() != '\n');
        scanf("%c", &check_asian);
    }

    switch (check_asian) {
        case 'y':
        case 'Y':
            asian = 1;
            break;
        case 'n':
        case 'N':
            asian = 0;
            break;
        default:
            printf("Invalid input. Please enter Y for Yes or N for No.\n");
            break;
    }

    float your_bmi = bmi_calc(height,weight);
    //printf("your_bmi: %f\n", your_bmi);

    status = checkBMI(asian, your_bmi);
    //printf("%s\n", status);

    mass_change = weight_to_lose(your_bmi, asian, height, weight);

    display_table(weight, height, your_bmi, asian, status, mass_change);

    return 0; //means code ended without any error
}
