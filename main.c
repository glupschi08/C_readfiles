#include <unistd.h>
#include <stdio.h>
#include <errno.h>


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
void compare_results(int expected_test_result[1000], int number_of_test_input);
void test(void);

int main() {
    //printf("Hello, World!\n");
    test();
    read_answer_file_evaluation();
    return 0;
}

void test(void){
    int c;
    FILE *file;
    file = fopen("testOutput10A.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
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
    file = fopen("testOutput10A.txt" , "r");
    //printf("filestatus: %d", file);
    /*
    if (file) {

        while (fscanf(file, "%s\n", temp)!=EOF){
            printf("%s",temp);
            if(temp=="+1"){
                expected_test_result[counter]=1;
            }else if(temp=="-1"){
                expected_test_result[counter]=-1;
            }else{
                printf("default read");
            }
            counter++;
        }
         */

        int c;
        while(1) {
            c = fgetc(file);
            if (feof(file)) {
                break;
            }
            printf("%c", c);
        }
        fclose(file);

        fclose(file);
        printf("expected_test_result: %d", expected_test_result[0]);
        //compare_results(expected_test_result, counter);
    //}
}
void compare_results(int expected_test_result[1000], int number_of_test_input){
    for(int counter=0;counter<number_of_test_input;counter++){
        if(expected_test_result[counter]== output_vector[counter]){
            printf("expected_test_result: %d   result: %d   correlation: %s\n", expected_test_result[counter],output_vector[counter],"right");
        }
        if(expected_test_result[counter]!=output_vector[counter]){
            printf("expected_test_result: %d   result: %d   correlation: %s\n", expected_test_result[counter],output_vector[counter],"right");
        }
    }
}