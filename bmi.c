/*
MA4830 Realtime Software for Mechatronic System
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


// define global variables
float bmi_checkpoints[2][3] = {{18.5, 24.9, 29.9 }, {18.5, 23.0, 27.5 }}; // represent the list of values to check for each weight category

// define functions used 
float computeBMI(float mass, float height){ // mass in kg, height in m
    return mass / pow(height, 2);
}

char* returnBMIStatus(float bmi, int asian){ // function to return the status as string from the bmi value and race (asian or non-asian)
    char* bmi_status;
    
                                                                            //bmi_checkpoint[0] for non-asian, bmi_checkpoint[1] for asian
    bmi_status = (char*)malloc(10*sizeof(char)); //allocate memory to store string
    if (bmi < bmi_checkpoints[asian][0]) strcpy(bmi_status, "Low");
    else if (bmi < bmi_checkpoints[asian][1]) strcpy(bmi_status, "Normal");
    else if (bmi <= bmi_checkpoints[asian][2]) strcpy(bmi_status, "Overweight");
    else strcpy(bmi_status, "Obese");

    return bmi_status;
}

void printStatusTable(float bmi, int asian, char* state, char* bmi_status){ // function to print the status as table
    printf("\n");
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
    printf("|Remarks:        |%s\n", bmi_status);
    printf("|----------------|------------------------\n");

}

int main(int argc, char const *argv[]){
    //! input mass, height and asian status via scanf
    float mass = 90.7;
    printf("Enter your mass in kg: ");
    scanf("%f", &mass);
    float height = 1.79;
    printf("Enter your height in m: ");
    scanf("%f", &height);
    char temp_asian = "n";
    printf("Are you Asian? (y/n): ");
    scanf("%s", &temp_asian);
    int asian = 0;
    if (temp_asian == 'y') asian = 1;


    //! computes BMI and returns the status
    float bmi = computeBMI(mass, height);
    float cut;
    printf("Mass(kg): %.2f\n",mass);
    printf("Height(m): %.2f\n",height);
    printf("BMI: %.2f\n",bmi);

    if (asian) printf("Race: %s\n", "Asian");
    else printf("Race: %s\n", "Non-Asian");

    char* state  = returnBMIStatus(bmi, asian);
    printf("BMI State: %s\n", state);
    char bmi_status[100];
    printf("Remarks: ");
    cut = (bmi-bmi_checkpoints[asian][1]) * pow(height, 2); // mass to cut to become normal
    if (cut > 0)  sprintf(bmi_status, "You are fat! Please reduce your weight by %.2fkg to remain in the Normal range!\n", cut);  
    else sprintf(bmi_status, "You are in the healthy weight range. Maintain your weight you don't want to be a fat ass\n\n");

    printf(bmi_status);
    //! print the status as table
    printStatusTable(bmi, asian, state, bmi_status);
    return 0;
}
