#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//func declarations--------------------------------------------------------------------------------------
float bmi_calc (float height, float weight){
    float bmi_val = weight / (pow(height,2));
    return bmi_val;
}

void display_table(float mass, float height, float your_bmi, char check_asian, char* status, float mass_change){

    printf("\n");
    printf("--------------------|------------------------\n");
    printf("Asian?              |");
    switch (check_asian) {
        case 'y':
        case 'Y':
            printf("   Yes\n");
            break;
        case 'n':
        case 'N':
            printf("   No\n");
            break;
        default:
            printf("theres an error here!! \n");
            break;
    }

    printf("--------------------|------------------------\n");
    printf("Height?             |   %.2f\n",height);
    printf("--------------------|------------------------\n");
    printf("Mass?               |   %.2f\n", mass);
    printf("--------------------|------------------------\n");
    printf("BMI?                |   %.2f\n", your_bmi);
    printf("--------------------|------------------------\n");
    printf("BMI Status          |   %s\n", status);
    printf("--------------------|------------------------\n");
    printf("Mass to lose        |   %.2f\n", mass_change);
    printf("--------------------|------------------------\n");
    printf("Remarks?            |");

    if (strcmp(status, "Low") == 0 ){
        printf("   You have to eat much more!\n");
    }
    else if (strcmp(status, "Normal")== 0){
        printf("   You are healthy! Keep it up.\n");
    }
    else if (strcmp(status, "Overweight")== 0){
        printf("   a lil chubby dont u think? eat 2 meals a day only from now on #fatphobic\n");
    }
    else if (strcmp(status, "Obese")== 0){
        printf("   fee fi fo fum, someones gotta eat less chum. no meals for a week for you fat boy\n");
    }
    
    
    printf("--------------------|------------------------\n");
}

char* checkBMI (char check_asian, float your_bmi){

    char* bmi_status; //pointer to character

    bmi_status = (char*)malloc(12*sizeof(char)); //allocate memory to store string

    if (check_asian == 'Y' || check_asian == 'y'){ //asian
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
    }

    else if (check_asian == 'N' || check_asian == 'n'){ //Non Asian
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
    }

    return bmi_status;
}

float weight_to_lose(float your_bmi, char check_asian, float height, float mass, char* bmi_status){ //only for overweight and obese

    float bmi_change;
    float mass_change; 

    if ((strcmp(bmi_status, "Low")) && (strcmp(bmi_status, "Normal")) != 0 ){
        if ((check_asian == 'Y' || check_asian == 'y') ){ //asian
            bmi_change = your_bmi - 23;
            mass_change = (bmi_change) * (pow(height,2));}
        else if ((check_asian == 'N' || check_asian == 'n')){ //not asian
            bmi_change = your_bmi - 24.9;
            mass_change = (bmi_change) * (pow(height,2));}
    }
    else{
        mass_change = 0;}
    
    return mass_change;
}
//main code----------------------------------------------------------------------------------------------
int main(void){
    float weight = 0;
    float height = 0;
    char check_asian;
    char* status;
    float mass_change;


    //user input for height
    printf("Enter your height in m: ");
    scanf("%f", &height);
    //assuming 1.2 <= height <= 2.5
    while (height < 1.2 || height > 2.5 ){ //checking for invalid data
        printf("invalid height input, please enter again: "); 
        while(getchar() != '\n');
        scanf("%f", &height);}
    printf("height: %.2f\n", height);


    //user input for weight
    printf("Enter your weight in kg: ");
    scanf("%f", &weight);
    //assuming 30 <= weight <= 200
    while (weight < 30 || weight > 200 ){ //checking for invalid data
        printf("invalid weight input, please enter again: ");
        while(getchar() != '\n');
        scanf("%f", &weight);}
    printf("weight: %.2f\n", weight);


    //user input for Asian
    printf("Are you Asian? (Y/N): ");
    int c;
    while (( c = getchar()) != '\n' && c != EOF); //clearing buffer of unwanted chars
    scanf("%c", &check_asian);
    while (check_asian != 'Y' && check_asian != 'y' && check_asian != 'N' && check_asian != 'n' ) { //checking for invalid data
        printf("Invalid input. Please only enter Y/y for Yes and N/n for No: ");
        // Clear the input buffer in case of invalid input
        while(getchar() != '\n');
        scanf("%c", &check_asian);
    }

    //using pre-declared functions
    float your_bmi = bmi_calc(height,weight);
    status = checkBMI(check_asian, your_bmi);
    mass_change = weight_to_lose(your_bmi, check_asian, height, weight, status);
    display_table(weight, height, your_bmi, check_asian, status, mass_change);

    return 0; //means code ended without any error
}
