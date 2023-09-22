#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const char DATA_FILE_NAME[] = "TestData.txt";

typedef struct functionRuntimes
{
    char *szName;            //name of the function being tested
    double **arrRuntimes;    //run times
    double *arrAvg;          //average runtime
    int iNumRepeats;         //number of times to repeat each test size
    int iNumTestCaseSizes;   //number of test case sizes
    int *arrTestSizes;       //array containing the test case sizes
} functionRuntimes;

//Functions used to test the runtimes
functionRuntimes timeAlgorithm( char*, int, int, int[], void (*f)(FILE *) );
FILE *generateTestInput( int, int, int );
void computeAvg( functionRuntimes fRT );
void printRuntimeTable( functionRuntimes fRT );
void freeFunctionRuntimes( functionRuntimes fRT );

//Functions whose runtime will be tested (and helper functions)
void insertionSortInitial( FILE* input );
void insertionSort( int* points, int low, int high );
void quickSortOptInitial( FILE* input );
void quickSortOpt( int* points, int low, int high );
int partition( int* points, int low, int high );

void mysteryRuntime1( FILE* input );
void mysteryRuntime2( FILE* input );
void mysteryRuntime3( FILE* input );

/*
 * Provided code - DO NOT CHANGE THIS METHOD OTHER THAN TO ADD YOUR NAME AND YOUR PARTNER'S NAME
 * (if you make alterations for the sake of testing be sure to revert them before submission)
 */
int main( int argc, char *argv[] )
{
    functionRuntimes fRT;

    int sizes1[] = { 500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};

    /* TODO : Fill in your name */
    printf("This solution was completed by:\n");
    printf("<student name>\n");

    srand(time(0));

    fRT = timeAlgorithm("Insertion Sort", 6, 5, sizes1, insertionSortInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("quicksort (uses insertion sort when sorting <30 numbers)", 12, 8, sizes1, quickSortOptInitial );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 1", 3, 6, sizes1, mysteryRuntime1 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 2", 3, 5, sizes1, mysteryRuntime2 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    fRT = timeAlgorithm("Mystery 3", 3, 8, sizes1, mysteryRuntime3 );
    printRuntimeTable(fRT);
    freeFunctionRuntimes(fRT);

    return 0;
}

/*************************************** Functions to have their runtimes tested *********************************************/

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime1( FILE* input )
{
    int temp;
    int size;
    int n;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    for( i=0; i<size; i++ )
    {
        for( n=size-1; n>1; n/=1.01 )
        {
            array[n-1] = array[n];
        }
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime2( FILE* input )
{
    int temp;
    int size;
    int i=0, j=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    i=0;
    while( j<size )
    {
        array[j] = array[i];

        i++;
        if( i>=size )
        {
            j++;
            i=0;
        }
    }

    free(array);
}

/* provided code - DO NOT CHANGE
 */
void mysteryRuntime3( FILE* input )
{
    int temp;
    int size;
    int i=0;
    int *array;

    if( fscanf( input, "%d", &size ) != 1 )
    {
        exit(-1);
    }
    array = (int *) malloc( size*sizeof(int) );
    if( array == NULL )
    {
        exit(-1);
    }

    while( fscanf( input, "%d", &temp ) == 1 && i<size)
    {
        array[i] = temp;
        i++;
    }

    while( size>1 )
    {
        size = size/2;
        array[size/2] = array[size];
    }

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSortInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc( size*sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    insertionSort( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i])
        {
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void insertionSort( int* points, int low, int high )
{
    int i, j;
    double temp;

    for( i = low+1; i <= high; i++)
    {
        for( j = i; j > low && points[j]<points[j-1]; j--)
        {
            temp = points[j];
            points[j] = points[j-1];
            points[j-1] = temp;
        }
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOptInitial( FILE* input )
{
    int i;
    int size;
    int *array;

    fscanf( input, "%d", &size );
    array = (int *) malloc( size*sizeof(int) );

    for( i=0; i<size; i++)
    {
        fscanf( input, "%d", &array[i] );
    }

    quickSortOpt( array, 0, size-1 );

    //Error check to verify the array is sorted
    /*for( i=1; i<size; i++)
    {
        if(array[i-1]>array[i]){
            printf("Not sorted!");
            exit(-1);
        }
    }*/

    free(array);
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
void quickSortOpt( int* points, int low, int high )
{
    if( high < low+30 )
    {
        insertionSort( points, low, high );
    }
    else
    {
        int pivot = partition( points, low, high );

        quickSortOpt( points, low, pivot-1 );
        quickSortOpt( points, pivot+1, high );
    }
}

/*
 * Provided code - DO NOT CHANGE THIS METHOD
 */
int partition( int* points, int low, int high )
{
    int pivot = rand() % (high - low + 1) + low;
    int pivotValue = points[pivot];
    int i = low+1;
    int j = high;
    int temp;

    points[pivot] = points[low];
    points[low] = pivotValue;

    while( i<j )
    {
        while( i<=high && points[i] <= pivotValue )
        {
            i++;
        }
        while( j>=low && points[j] > pivotValue )
        {
            j--;
        }
        if(i<j)  //swap out of order elements
        {
            temp = points[i];
            points[i] = points[j];
            points[j] = temp;
        }
    }
    if( i<=high && points[i] <= pivotValue )
    {
        i++;
    }

    points[low] = points[i-1];
    points[i-1] = pivotValue;

    return i-1;
}

/*************************************** Functions for finding and printing runtime *********************************************/

/*
TODO: Give your asymptotic estimates for the runtimes of the following 3 functions:

mysteryRuntime1:  O(size * log(size))
mysteryRuntime2:  O(size^2)
mysteryRuntime3:  O(size)
*/


/* TO BE COMPLETED BY YOU
 * Fill in the missing parts of the code (see TODOs below)
 */
functionRuntimes timeAlgorithm( char *szName, int iNumRepeats, int iNumTestCaseSizes, int arrTestSizes[], void (*f)(FILE *) )
{
    clock_t start, end;
    int i, j;
    FILE *testData;

    functionRuntimes fRT;
    strcpy(fRT.szName, szName);
    fRT.iNumRepeats = iNumRepeats;
    fRT.iNumTestCaseSizes = iNumTestCaseSizes;
    fRT.arrTestSizes = (int *) malloc(iNumTestCaseSizes * sizeof(int));
    for(i=0; i<iNumTestCaseSizes; i++)
        fRT.arrTestSizes[i] = arrTestSizes[i];

    fRT.arrRuntimes = (double **) malloc(iNumTestCaseSizes * sizeof(double *));
    for( i=0; i<iNumTestCaseSizes; i++ )
    {
        fRT.arrRuntimes[i] = (double *) malloc(iNumRepeats * sizeof(double));

        for( j=0; j<iNumRepeats; j++ )
        {
            testData = generateTestInput( 0, arrTestSizes[i], arrTestSizes[i] );
            start = clock();
            f( testData );
            end = clock();
            fclose(testData);
            fRT.arrRuntimes[i][j] = (double)(end - start) / CLOCKS_PER_SEC;
        }
    }

    fRT.arrAvg = (double *) malloc(iNumTestCaseSizes * sizeof(double));
    computeAvg(&fRT);

    return fRT;
}

void computeAvg( functionRuntimes *fRT )
{
    int i, j;
    for(i=0; i<fRT->iNumTestCaseSizes; i++)
    {
        double sum = 0.0;
        for(j=0; j<fRT->iNumRepeats; j++)
            sum += fRT->arrRuntimes[i][j];
        fRT->arrAvg[i] = sum / fRT->iNumRepeats;
    }
}

void printRuntimeTable( functionRuntimes fRT )
{
    int i, j;
    printf("%-15s", "Test Size");
    for(j=0; j<fRT.iNumRepeats; j++)
        printf("%-15s", "Runtime");
    printf("%-15s\n", "Average");

    for(i=0; i<fRT.iNumTestCaseSizes; i++)
    {
        printf("%-15d", fRT.arrTestSizes[i]);
        for(j=0; j<fRT.iNumRepeats; j++)
            printf("%-15.3f", fRT.arrRuntimes[i][j]);
        printf("%-15.3f\n", fRT.arrAvg[i]);
    }
}

void freeFunctionRuntimes( functionRuntimes *fRT )
{
    int i;
    free(fRT->arrTestSizes);
    
    for(i=0; i<fRT->iNumTestCaseSizes; i++)
        free(fRT->arrRuntimes[i]);
    
    free(fRT->arrRuntimes);
    
    free(fRT->arrAvg);
}

