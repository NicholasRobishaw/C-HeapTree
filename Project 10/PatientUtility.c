// header file
#include "PatientUtility.h"

int comparePriority( const PatientType one, const PatientType other )
   {
    int priorityDiff = one.priority - other.priority;

    if( priorityDiff != 0 )
       {
        return priorityDiff;
       }
  
    return (int)( other.timeIn - one.timeIn );
   }

void copyPatient( PatientType *destPatient, const PatientType sourcePatient )
   {
    copyString( destPatient->patientName, sourcePatient.patientName );

    destPatient->priority = sourcePatient.priority;

    destPatient->timeIn = sourcePatient.timeIn;
   }

/*
Name: copyString
Process: copies string from source to destination
Function input/parameters: source string (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyString( char *dest, const char *source )
   {
    int index = 0;

    while( source[ index ] != NULL_CHAR )
       {
        dest[ index ] = source[ index ];

        index++;

        dest[ index ] = NULL_CHAR;
       }
   }

void getPatientInfo( char *patientStr, PatientType patientNode )
   {     
    char timeStr[ MIN_STR_LEN ];
    int index, timeOffset = 11, timeStrLen = 8;

    // get time string, includes day, date, etc.
    copyString( timeStr, ctime( &patientNode.timeIn ) );

    // filter out only the time component
    for( index = 0; index < timeStrLen; index++ )
       {
        timeStr[ index ] = timeStr[ index + timeOffset ];
        
        timeStr[ index + 1 ] = NULL_CHAR;
       }
    
    sprintf( patientStr, "Name: %s, Priority: %d, Time in: %s", 
                     patientNode.patientName, patientNode.priority, timeStr );
   }

void setPatientFromData( PatientType *patientNode, 
                          const char *nameSet, int prioritySet, time_t timeSet )
   { 
    copyString( patientNode->patientName, nameSet );

    patientNode->priority = prioritySet;

    patientNode->timeIn = timeSet;
   }

void setPatientFromStruct( PatientType *patientNode, const PatientType source )
   {
    setPatientFromData( patientNode, source.patientName, 
                                               source.priority, source.timeIn );
   }

   
