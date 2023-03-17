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
  // variables
  
  // dipslay process
  printf( "Adding new ptient: %s\n\n", nameSet );     
  
  // check if array needs to be resized
  checkForResize( heap );
  
  // add value at size
  setPatientFromData( &heap->array[ heap->size ], nameSet, prioritySet, timeSet  );
  
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
  	PatientType child, parent, temp;	
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
         heap->array[currentIndex] = heap->array[ parentIndex ];

         // overwrite parents data with child
         setPatientFromStruct( &heap->array[parentIndex], child );

         if( heap->displayFlag )
           {
           getPatientInfo( parentStr, parent );
           getPatientInfo( childStr, child );    
               
           printf( "   Bubbling up\n" );
           printf( "    - swaping parent: %s\n", parentStr );
           printf( "    - with child: %s\n\n", childStr );    
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
  // variables
  
  // set the other heap memebers appropriatly
  heapPtr->size = 0;
  heapPtr->capacity = initialCapacity;
  
  // set display flag to false with function	
  setDisplayFlag( heapPtr, false );
  
  // allocate memory of array
  heapPtr->array = ( PatientType *)malloc( initialCapacity * sizeof( PatientType ) );
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
  // vairbales 
  
  // assign value at index 0 to the remove pointer 
  setPatientFromStruct( removed, heap->array[0] );       	  
    
  if( heap->displayFlag )
    {
    printf( "Removing patient: %s\n", removed );
        
    }  
      
  // grab value at size -1 and put into index 0     
  setPatientFromStruct( &heap->array[0], heap->array[ heap->size - 1 ] );    
  
  // decrement size
  heap->size--;      
  
  // now trickle down and restructure the max heap 
  trickleDownArrayHeap( heap, 0 );	

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
  int leftChildIndex, rightChildIndex, parentIndex = currentIndex;
  char parentStr[ STD_STR_LEN ], 
        leftChildStr[ STD_STR_LEN ], rightChildStr[ STD_STR_LEN ];
  
  // calculate children
  leftChildIndex = parentIndex * 2 + 1;
  rightChildIndex = parentIndex * 2 + 2;
  
  // set the children and parents to variables
  setPatientFromStruct( &parent, heap->array[ parentIndex ] );
    
  // check if right child index is less than size
  if( rightChildIndex < heap->size )
    {
    // set the children to variables    
    setPatientFromStruct( &leftChild, heap->array[ leftChildIndex ] );
    setPatientFromStruct( &rightChild, heap->array[ rightChildIndex ] );

    // check if either of the children are larger than the parent
    if( comparePriority( parent, leftChild ) < 0 )
      {
      // swap the parent with the larger child
      heap->array[ parentIndex ] = leftChild;
      heap->array[ leftChildIndex ] = parent;
      
      // check if verbose is true
      if( heap->displayFlag )
        {
        // get the data at the node
        getPatientInfo( parentStr, parent );
        getPatientInfo( leftChildStr, leftChild );    
               
        // display operation
        printf( "   - Trickle down swap:\n" );
        printf( "     - moving down parent: %s\n", parentStr );
        printf( "     - moving up left child: %s\n\n", leftChildStr );    
        }
        
      // call again recursivly with that childs index
      trickleDownArrayHeap( heap, leftChildIndex );
      }
      
    // else if 
    else if( comparePriority( parent, rightChild ) < 0  )
      {
      // swap the parent with the larger child
      heap->array[ parentIndex ] = rightChild;
      heap->array[ rightChildIndex ] = parent;
       
      // check if verbose is true
      if( heap->displayFlag )
        {
        // grab the data at the nodes
        getPatientInfo( parentStr, parent );
        getPatientInfo( rightChildStr, rightChild );    
               
        // display operations
        printf( "   - Trickling down\n" );
        printf( "     - moving down parent: %s\n", parentStr );
        printf( "     - moving up right child: %s\n\n", rightChildStr );    
        } 
        
      // call again recursivly with that childs index
      trickleDownArrayHeap( heap, rightChildIndex );   
      }
    }
      
  
  // otherwise, check if left is within bounds
  else if( leftChildIndex < heap->size )
    {
    setPatientFromStruct( &leftChild, heap->array[ leftChildIndex ] );   
          
    // check if either of the children are larger than the parent
    if( comparePriority( parent, leftChild ) < 0 )
      {
      // swap the parent with the larger child
      heap->array[ parentIndex ] = leftChild;
      heap->array[ leftChildIndex ] = parent;
      
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
        
      // call again recursivly with that childs index
      trickleDownArrayHeap( heap, leftChildIndex );
      }
    }      
  }
