#ifndef PATIENT_UTILITY_H
#define PATIENT_UTILITY_H

// header files
#include <time.h>
#include <stdio.h>
#include "StandardConstants.h"

// constants

// data structure
typedef struct PatientStruct
   {
    char patientName[ STD_STR_LEN ];

    int priority;

    time_t timeIn;
   } PatientType;

// prototypes
int comparePriority( const PatientType one, const PatientType other );
void copyPatient( PatientType *destPatient, const PatientType sourcePatient );
void copyString( char *dest, const char *source );
void getPatientInfo( char *patientStr, PatientType PatientType );
void setPatientFromData( PatientType *patientNode, 
                         const char *nameSet, int prioritySet, time_t timeSet );
void setPatientFromStruct( PatientType *patientNode, const PatientType source );










#endif   // PATIENT_UTILITY_H