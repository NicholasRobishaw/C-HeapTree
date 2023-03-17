#include "HeapUtility.h"

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
                                              int prioritySet, time_t timeSet )
  {
  // display process
  if( heap->displayFlag )
    {
    printf( "\nAdding new patient: %s\n\n", nameSet );     
    }
  
  // check if array needs to be resized
  checkForResize( heap );
  
  // add value at size
  setPatientFromData( &heap->array[ heap->size ], 
                        nameSet, prioritySet, timeSet  );
  
  // bubble up and rebalance heap
  bubbleUpArrayHeap( heap, heap->size );
  
  // increment size by 1
  heap->size++;		
  }

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
void bubbleUpArrayHeap( HeapType *heap, int currentIndex )
  {
  // variables
  int parentIndex;	
  PatientType child, parent;	
  char parentStr[ STD_STR_LEN ], childStr[STD_STR_LEN];
      	
  // check for current index greater than 0
  if( currentIndex > 0 )
    {       
    // calculate parent's index
    parentIndex = (( currentIndex - 1 ) / 2);

    // set the child and parent variables
    setPatientFromStruct( &child, heap->array[ currentIndex ] );
    setPatientFromStruct( &parent, heap->array[ parentIndex ] );

    // check if current child's value is less than parent value
    if( comparePriority( parent, child ) < 0 )
      { 	
      // set childs data to parents data
      setPatientFromStruct( &heap->array[currentIndex], heap->array[ parentIndex] );

      // overwrite parents data with child
      setPatientFromStruct( &heap->array[parentIndex], child );

      // check if display verbose is true
      if( heap->displayFlag )
        {
        // grab the strings from nodes
        getPatientInfo( parentStr, parent );
        getPatientInfo( childStr, child );    
               
        // display operation
        printf( "   - Bubble up:\n" );
        printf( "     - Swapping parent: %s\n", parentStr );
        printf( "     - with child: %s\n\n", childStr );    
        }

      // call the function recursively with the parent's index
      bubbleUpArrayHeap( heap, parentIndex );
      }
    }
  }

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
void checkForResize( HeapType *heap )
  {
  // variables
  PatientType *newArray;
  int newCapacity, index;
  
  // check if array is full
  if( heap->size == heap->capacity )
    {
    // double capacity
	newCapacity = heap->capacity * 2;	
    heap->capacity = newCapacity;
    	
    // create new array
    newArray = ( PatientType *)malloc( newCapacity * sizeof( PatientType ) );
    
    // copy data into new array
    for( index = 0; index < heap->size; index++ )
      {
      // copy current node from old array to new array	
      setPatientFromStruct( &newArray[ index ], heap->array[ index ] );
      }
	
    // free the memory of old array
    free( heap->array );
	
    // link new array to heap
    heap->array = newArray;
    }	
  }

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
void clearHeap( HeapType *heap )
  {	
  // free the array
  free( heap->array );
  
  // set all other data members appropriatly
  heap->capacity = 0;
  heap->size = 0;
  }

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
void initializeHeap( HeapType *heapPtr, int initialCapacity )
  {
  // set the other heap memebers appropriatly
  heapPtr->size = 0;
  heapPtr->capacity = initialCapacity;
  
  // set display flag to false with function	
  setDisplayFlag( heapPtr, false );
  
  // allocate memory of array
  heapPtr->array = ( PatientType *)malloc( 
               initialCapacity * sizeof( PatientType ) );
  }

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
bool isEmpty( const HeapType heap )
  {
  // return if the heap tree is empty	
  return heap.size == 0;
  }

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
void removeItem( PatientType *removed, HeapType *heap )
  {
  // variables
  char returnStr[ STD_STR_LEN ];   
    
  if( heap->size > 0 )
    {
    // assign value at index 0 to the remove pointer 
    setPatientFromStruct( removed, heap->array[0] );       	  
   
    // check if verbose is true  
    if( heap->displayFlag )
      {
      // display operation    
      getPatientInfo( returnStr , *removed );
      printf( "\nRemoving patient: %s\n", returnStr );
      }  
      
    // grab value at size -1 and put into index 0     
    setPatientFromStruct( &heap->array[0], heap->array[ heap->size - 1 ] );    
  
    // decrement size
    heap->size--;      
  
    // now trickle down and restructure the max heap 
    trickleDownArrayHeap( heap, 0 );	
    }
  }

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
void setDisplayFlag( HeapType *heap, bool flagSet )
  {
  // set display flag    
  heap->displayFlag = flagSet;		
  }

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
void showArray( HeapType heap )
  {
  // variables
  int index;
  char data[STD_STR_LEN];
  
  // iterate through array
  for( index = 0; index < heap.size; index++ )
    {
    // display patient data at index
    getPatientInfo( data, heap.array[index] );
    
    printf( "%s\n ", data );	
    }		
  }

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
void trickleDownArrayHeap( HeapType *heap, int currentIndex ) 
  {		
  // variables
  PatientType leftChild, rightChild, parent;
  int leftChildIndex = currentIndex * 2 + 1, rightChildIndex = currentIndex * 2 + 2;
  char parentStr[ STD_STR_LEN ], 
        leftChildStr[ STD_STR_LEN ], rightChildStr[ STD_STR_LEN ];
  bool leftLarger = false, rightLarger = false;
  
  // grab the data from parent pointer and assign to a temp
  setPatientFromStruct( &parent, heap->array[ currentIndex ] );
    
  // check right child index is within size
  if( rightChildIndex < heap->size )
    {
    // assign right and left childrens data to temp storage
    setPatientFromStruct( &rightChild, heap->array[ rightChildIndex ] );
    setPatientFromStruct( &leftChild, heap->array[ leftChildIndex ] );
    
    // check if right child has higher priority than left and parent
    if( comparePriority( parent, rightChild ) < 0 && comparePriority( leftChild, rightChild ) < 0 )
      {
      // set right child bool to true
      rightLarger = true;
      
      // set left child bool to false    
      leftLarger = false;
      }
      
    // otherwise check if left is larger than parent and right
    else if( comparePriority( parent, leftChild ) < 0 && comparePriority( rightChild, leftChild ) < 0 )
      {
      // set left to true
      leftLarger = true;
      
      // set right to false
      rightLarger = false;
      }
    }
    
  // otherwise check if left index is within size
  else if( leftChildIndex < heap->size )
    {
    // set the left child data to temp storage
    setPatientFromStruct( &leftChild, heap->array[ leftChildIndex ] );
    
    // check if left is larger than parent
    if( comparePriority( parent, leftChild ) < 0 )
      {
      // set left to true
      leftLarger = true;   
      }
    }
    
  // check if right was the largest
  if( rightLarger )
    {
    // check if verbose is true
    if( heap->displayFlag )
      {
      // get the data at the node
      getPatientInfo( parentStr, parent );
      getPatientInfo( rightChildStr, rightChild );    
               
      // display operations
      printf( "   - Trickling down\n" );
      printf( "     - moving down parent: %s\n", parentStr );
      printf( "     - moving left child: %s\n\n", rightChildStr );
      }
    
    // swap data of parent with right child
    setPatientFromStruct( &heap->array[currentIndex], rightChild );
    setPatientFromStruct( &heap->array[rightChildIndex], parent );
    
    // recurse with right child
    trickleDownArrayHeap( heap, rightChildIndex );
    }
    
  // otherwise check if the left was the largest
  else if( leftLarger )
    {
    // check if verbose is true
    if( heap->displayFlag )
      {
      // get the data at the node
      getPatientInfo( parentStr, parent );
      getPatientInfo( leftChildStr, leftChild );    
               
      // display operations
      printf( "   - Trickling down\n" );
      printf( "     - moving down parent: %s\n", parentStr );
      printf( "     - moving left child: %s\n\n", leftChildStr );
      }
    
    // swap data of parent with left child
    setPatientFromStruct( &heap->array[currentIndex], leftChild );
    setPatientFromStruct( &heap->array[leftChildIndex], parent );
    
    // recurse with left child
    trickleDownArrayHeap( heap, leftChildIndex );   
    }
  }
