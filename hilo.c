#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//define a struct of int variables
struct args {
  int a;
  int b;
};

//define a struct of operations to do
struct results {
  int sum;
  int difference;
  int product;
};

void *
calculator (void *_args)
{

    struct args *args = (struct args *) _args;

    //define a struct to define what operation belongs to sum, difference and product
    struct results *results = calloc (sizeof (struct results), 1);
    results->sum        = args->a + args->b;
    results->difference = args->a - args->b;
    results->product    = args->a * args->b;

    free (args);
    pthread_exit (results);
}

int main(void){
pthread_t hilo;

//define a struct to define values for a and b
struct args *args = calloc (sizeof (struct args), 1);
    args->a = 20;
    args->b = 30;

    assert (pthread_create (&hilo, NULL, calculator, args) == 0);

//define a struct to print all results from the operations
struct results *results = calloc (sizeof (struct results), 1);
    
    pthread_join (hilo, (void **)&results);

    //print all operations on console
    /*printf ("Suma +:%3d;   ", results->sum);
    printf ("Resta-:%3d;   ", results->difference);
    printf ("Multiplicacion*:%3d;   ", results->product);

    free (results);*/

    //define the file name to print and save all the operations
    char *fileName = "operations.txt";
    char *type ="w";
    FILE *file = fopen(fileName,type);

    if(file==NULL){
        printf("Something went wrong %s",fileName);
        return 1;
    }

    fprintf(file,"Sum: %d\n", results->sum);
    fprintf(file,"Diffference: %d\n", results->difference);
    fprintf(file,"Product: %d\n", results->product);


    fclose(file);
    puts("File successfully writen");
}