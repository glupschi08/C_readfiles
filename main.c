#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//float error;
int neuron_number=1;
int input_weight=2 + 1; //fuer bias
int output_number=1;
int number_of_weights = 4;
float weight[4];
float weight_correction_const=0.0005; //epsilon from the lesson
int times_of_repeat=5;     //the amount of times the network get trained with the same input data
float input[1000][3];
float input_test[1000][3];
int expected_test_result[1000];
int output_vector[1000];
void read_answer_file_evaluation(void);
void read_input_from_file(void);
void compare_results(int expected_test_result[1000], int number_of_test_input);
void create_random_vector(void);


int main() {
    //printf("Hello, World!\n");
    //test();
    //read_answer_file_evaluation();
    read_input_from_file();
    return 0;
}

void read_input_from_file(void){
    char temp[1000];
    int counter=0;
    int test_flag=0;
    float temp1=0,temp2=0, temp3=0;

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        fprintf(stdout, "Current working dir: %s\n", cwd);
    }else {
        perror("getcwd() error");
    }
    FILE * file;
    file = fopen("../testInput10A.txt" , "r");

    if (file) {

        while (fscanf(file, "%f,%f,%f\n", &temp1, &temp2, &temp3)!=EOF){

            if( (temp1==0)  &&  (temp2==0)  &&  (temp2==0)  ) {
                test_flag=1;
                break;
            }
            input[counter][0]=temp1;
            input[counter][1]=temp2;
            input[counter][2]=temp3;

            counter++;
        }
        temp1=0;
        temp2=0;
        temp3=0;
        counter=0;
        while (fscanf(file, "%f,%f\n", &temp1, &temp2)!=EOF){
            input_test[counter][0]=temp1;
            input_test[counter][1]=temp2;

            counter++;
        }

        fclose(file);


        printf("check one input: %f,%f,%f\n", input[0][0],input[0][1],input[0][2]);
        printf("check one testinput: %f,%f\n", input_test[0][0],input_test[0][1]);
    }
}



void read_answer_file_evaluation(void){
    char temp[1000];
    int counter=0;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);
    else
        perror("getcwd() error");
    FILE * file;
    file = fopen("../testOutput10A.txt" , "r");
    //printf("filestatus: %d", file);

    if (file) {

        while (fscanf(file, "%s\n", temp)!=EOF){
            //printf("%s\n",temp);
            if(temp[0]=='+' && temp[1]=='1'){
                expected_test_result[counter]=1;
            }else if(temp[0]=='-' && temp[1]=='1'){
                expected_test_result[counter]=-1;
            }else{
                printf("default read\n");
            }
            counter++;
        }

        fclose(file);

        create_random_vector(); //for test purpose only....remove this after debugging

        //printf("expected_test_result: %d", expected_test_result[0]);
        printf("number of inputs: %d\n", counter);
        compare_results(expected_test_result, counter);
    }
}
void compare_results(int expected_test_result[1000], int number_of_test_input){
    float counter_right=0;
    float counter_wrong=0;
    float temp=0;
    for(int loop_counter=0;loop_counter<number_of_test_input;loop_counter++){
        if(expected_test_result[loop_counter]== output_vector[loop_counter]){
            printf("expected_test_result: %d   result: %d   correlation: %s\n", expected_test_result[loop_counter],output_vector[loop_counter],"right");
            counter_right++;
        }
        if(expected_test_result[loop_counter]!=output_vector[loop_counter]){
            printf("expected_test_result: %d   result: %d   correlation: %s\n", expected_test_result[loop_counter],output_vector[loop_counter],"wrong");
            counter_wrong++;
        }
    }
    temp =  (counter_right/(counter_right+counter_wrong));
    printf("wrong: %f\n", counter_wrong);
    printf("right: %f\n", counter_right);
    printf("correlation: %.2f %%\n", temp);
}

void create_random_vector(void){

    int number_of_output=1000;
    float temp=0, border=1;

    srand((unsigned int)time(NULL));
    for(int counter=0;counter<number_of_output;counter++) {
        temp = (float) rand() / (float) (RAND_MAX / border);

        if(temp>=0.5){
            output_vector[counter]=1;
        }else{
            output_vector[counter]=-1;
        }
        printf("output_vector[%d]: %d\n", counter ,output_vector[counter]);
    }
}