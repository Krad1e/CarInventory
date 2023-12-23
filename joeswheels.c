//Alex Brousse
//atbhz7
//CS1050 
//Homework 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getCars( int*, float*, int*, char* );
float reserve( int*, float*, int, int );
void printInventory( int*, float*, int*, int );
void writeToFile( int*, float*, int*, char*, int );

int main( int argc, char** argv )
{
    if (argc != 5 )
    {
        printf( "\nCommand line error! Correct usage: ./a.out <master_input_filename>\n"
                "<number_of_vehicles> <reservation_input_filename> <output_filename>\n" );
        return 0;
    }

    char* input = *(argv + 1 ); //cars.txt
    int count = atoi(*(argv + 2)); //12 
    char* rsv = *(argv + 3 ); // reservations.txt
    char* output = *(argv + 4); //inventory.txt

    int id;
    float profit = 0;
    int* carID = malloc(sizeof(int) * count );
    float* price = malloc(sizeof(float) * count );
    int* miles = malloc(sizeof(int) * count );

    if ( !carID || !price || !miles ) 
    {
        printf( "Error with memory allocation. Exiting...\n" );
        return 0;
    }

    getCars( carID, price, miles, input );
    printInventory( carID, price, miles, count );

    FILE* filePtr = fopen(rsv, "r" );
    if ( !filePtr ) 
    {
        printf( "Error opening the file\n" );

    }
    else
    {
        printf( "\n\nProcessing reservations...\n");
        while ( fscanf(filePtr, "%d", &id ) != EOF)
        {
            profit += reserve(carID, price, id, count );
        }
        printInventory(carID, price, miles, count );

        while ( id != 0 )
        {
            printf( "\nEnter the vehicle ID for the desired rental (0 to exit): " );
            scanf( "%d", &id );
            if(id == 0)
                break;
            profit += reserve(carID, price, id, count );
            printInventory(carID, price, miles, count );
        }

        printf( "\nTotal profits: $%.2f\n",profit );
        writeToFile( carID, price, miles, output, count );

        free(carID);
        free(price);
        free(miles);
        fclose(filePtr);
    }
    return 0;
}
//End main 
//_____________________________________________________________________________________
void getCars( int *carID, float *price, int *miles, char *input )
{
    FILE* filePtr = fopen (input, "r" );

    if ( !filePtr )
    {
        printf( "Error" );
        return;
    }
    int j = 0;

    while (fscanf(filePtr, "%d %f %d", (carID + j), (price + j), (miles + j)) != EOF)
    {
        j++;
    }

    fclose(filePtr); 
}
//End getCars
//____________________________________________________________________________________
float reserve( int *carID, float *price, int id, int size )
{
    int j;
    for ( j = 0; j < size; j++ ) // find matching vehicle in inventory
    {
        if ( *(carID+j) == id )
        {
            *(carID+j) = 0;
            return *(price + j);
        }
    }

    printf( "\nThat vehicle is not in our inventory!\n" );
    return 0;
}
//End reserve
//____________________________________________________________________________________
void printInventory( int *carID, float *price, int *miles, int size) //sort and print inventory
{
    printf( "\n*** Current inventory ***\n\n" );\
        int j;
    for ( j = 0; j < size; j++ ) 
    {
        if( *(carID + j) == 0)
        {
            continue;
        }

        printf( "%d\t$%.2f\t%d\n", *(carID + j), *(price + j), *(miles + j));
        printf( "\n" );
    }
}
//End printInventory
//_____________________________________________________________________________________
void writeToFile( int *carID, float *price, int *miles, char *output, int size )
{
    int j;
    FILE* filePtr = fopen(output, "w" );

    printf( "\nWriting remaining inventory to inventory.txt\n" );
    printf( "\nFreeing memory and exiting...\n\n");
    for ( j = 0; j < size; j++ )
    {
        if( *(carID + j) != 0)
        {

            fprintf(filePtr, "%d %f %d", *(carID + j), *(price + j), *(miles + j));
            fprintf( filePtr, "\n" );
        }
    }

    fclose(filePtr); 
}
//End writeToFile
