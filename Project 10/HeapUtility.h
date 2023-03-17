#ifndef HEAP_UTILITY_H
#define HEAP_UTILITY_H

#include "PatientUtility.c"
#include <stdlib.h>
#include <stdbool.h>

// constants

// data structures
typedef struct HeapStruct
   {
    PatientType *array;    

    int size, capacity;

    bool displayFlag;
   } HeapType;

// function prototypes

/*
Name: addHeapItem
Process: adds item to heap, reports action, updates size,
         calls bubble up to reset heap
Function input/parameters: heap data (HeapType *), patient name (char *),
                           patient priority (int), time in (time_t)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: patient addition action displayed as specified
Dependencies: checkForResize, setPatientFromData, printf,
              bubbleUpArrayHeap (recursively)
*/
void addHeapItem( HeapType *heap, char *nameSet, 
                                              int prioritySet, time_t timeSet );

/*
Name: bubbleUpArrayHeap
Process: recursively rebalances heap after new data is added,
         displays bubble up actions
Function input/parameters: heap data (HeapType *), current index (int)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: bubble up operations displayed as specified
Dependencies: setPatientFromStruct, comparePriority, getPatientInfo,
              bubbleUpArrayHeap (recursively), others acceptable
*/
void bubbleUpArrayHeap( HeapType *heap, int currentIndex );

/*
Name: checkForResize
Process: checks for need to resize (increase capacity of) array,
         if necessary, creates new array with double the previous capacity,
         updates array, then returns previous data memory to OS
Function input/parameters: heap data (HeapType *)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof, setPatientFromStruct, free
*/
void checkForResize( HeapType *heap );

/*
Name: clearHeap
Process: frees heap array, sets all other data members appropriately
Function input/parameters: heap data (HeapType *)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: free
*/
void clearHeap( HeapType *heap );

/*
Name: initializeHeap
Process: initializes heap, creates heap array from given capacity,
         sets other heap members appropriately,
         display flag is set to false
Function input/parameters: heap data (HeapType *), initial capacity (int)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof
*/
void initializeHeap( HeapType *heapPtr, int initialCapacity );

/*
Name: isEmpty
Process: reports if heap is empty
Function input/parameters: heap data (const HeapType)
Function output/parameters: none
Function output/returned: Boolean result of test (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( const HeapType heap );

/*
Name: removeItem
Process: removes item from heap, reports removal action, adjusts data, 
         displays removal action, updates size, calls trickle down to reset heap
Function input/parameters: heap data (HeapType *)
Function output/parameters: updated heap data (HeapType *),
                            patient data removed (PatientType *)
Function output/returned: none
Device input/---: none
Device output/monitor: removal action displayed as specified
Dependencies: setPatientFromStruct, getPatientInfo, printf,
              trickleDownArrayHeap, others acceptable
*/
void removeItem( PatientType *removed, HeapType *heap );

/*
Name: setDisplayFlag
Process: sets Boolean flag to drive bubble up, trickle down displays
Function input/parameters: heap data (HeapType *), flag (bool)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void setDisplayFlag( HeapType *heap, bool flagSet );

/*
Name: showArray
Process: displays array as is, from lowest index to highest
Function input/parameters: heap data (HeapType)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: array displayed as specified
Dependencies: getPatientInfo, printf
*/
void showArray( HeapType heap );

/*
Name: trickleDownArrayHeap
Process: recursively rebalances heap after data removal,
         every child has a lower priority or later arrival time than its parent,
         displays trickle down actions to screen
Function input/parameters: heap data (HeapType *), current index (int)
Function output/parameters: updated heap data (HeapType *)
Function output/returned: none
Device input/---: none
Device output/monitor: trickle down operations displayed as specified
Dependencies: setPatientFromStruct, comparePriority, getPatientInfo,
              printf, trickleDownArrayHeap (recursively), others acceptable
*/
void trickleDownArrayHeap( HeapType *heap, int currentIndex );


#endif   // HEAP_UTILITY_H

