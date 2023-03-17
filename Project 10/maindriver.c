// header files
#include <time.h>
#include <stdio.h>
#include <Windows.h>  // use <unistd.h> for Linux  
#include "HeapUtility.c"

// constants
const int DEFAULT_CAPACITY = 10;
const int LOWEST_PRIORITY = 1;
const int HIGHEST_PRIORITY = 10;
const int ONE_SECOND = 1;

// prototypes
void delay(int numSeconds );
int getRandBetween( int low, int high );

int main( int argc, char *argv[] )
   {
    HeapType heap;
    PatientType removedPatient;
    int priority;
    time_t currentTime; 

    // title
    printf( "\nPatient Queue/Heap Test\n" );
    printf( "=======================\n" );

//    char dispStr[ STD_STR_LEN ];

    srand( time( NULL ) );

    
    initializeHeap( &heap, DEFAULT_CAPACITY );
    
    
    // set display flag
    setDisplayFlag( &heap, true );


    // create patients
    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    time( &currentTime );
    addHeapItem( &heap, "Johnson, Robert", priority, currentTime );
    
    
    showArray( heap );
   

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Elliott, Cayley", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND ); 
    time( &currentTime );
    addHeapItem( &heap, "Reyes, Connor", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Sanchez, Susan", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Penn, Frederick", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    time( &currentTime );
    addHeapItem( &heap, "Deangelis, Shawna", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Shafer, Tristan", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND ); 
    time( &currentTime );
    addHeapItem( &heap, "Ruan, Francisco", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Werner, Riley", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Davis, Glen-Andrew", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    time( &currentTime );
    addHeapItem( &heap, "Thomas, Sena", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Nash, Tim", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND ); 
    time( &currentTime );
    addHeapItem( &heap, "Hack, Jacque", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Ortega, Jane", priority, currentTime );
    showArray( heap );

    priority = getRandBetween( LOWEST_PRIORITY, HIGHEST_PRIORITY );
    delay( ONE_SECOND );
    time( &currentTime );
    addHeapItem( &heap, "Catania, DeMarco", priority, currentTime );
    showArray( heap );

    

    // remove patients
    while( !isEmpty( heap ) )
       {
        removeItem( &removedPatient, &heap );

       }

    
  
    // end program

       // clear heap
       clearHeap( &heap );

       // display end program
       printf( "\nEnd Program\n" );
 
       // return success
       return 0;

   }

/*
Name: delay
Process: delays program operation for number of seconds
Function input/parameters: number of seconds (int)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: clock
*/
void delay( int numSeconds )
   {
    // Converting time into milli_seconds
    int mSeconds = 1000 * numSeconds;
 
    // Storing start time
    clock_t startTime = clock();
 
    // looping till required time is not achieved
    while ( clock() < startTime + mSeconds );
   }

/*
Name: getRandBetween
Process: returns random number generated between two limits, inclusive
Function input/parameters: low and high limits (int)
Function output/parameters: none
Function output/returned: random value generated (int)
Device input/---: none
Device output/---: none
Dependencies: rand
*/
int getRandBetween( int low, int high )
   {
    int range = high - low + 1;

    return rand() % range + low;
   }
