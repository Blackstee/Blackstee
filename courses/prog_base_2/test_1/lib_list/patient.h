#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include "list.h"

typedef struct patient_s patient_t;
typedef struct clinic_s clinic_t;
typedef struct flat_s flat_t;

typedef enum {
    CLINIC_FULL,
    CLINIC_FREE,
} clinic_state_t;

typedef enum {
    FLAT_FULL,
    FLAT_FREE,
} flat_type_t;

patient_t * patient_new ( const char * name, const char * surname, int age, const char * disease);
void patient_free(patient_t * self);
void patient_delete (flat_t * flat, patient_t * self, int seat);

flat_t * flat_new(flat_type_t type);
void flat_free(flat_t * self);

clinic_t * clinic_new();
void clinic_free(clinic_t * self);

//void clinic_subscribeStart(clinic_t * self, void * listener, start_fn callback);
//void clinic_unsubscribeStart(clinic_t * self, void * listener, start_fn callback);

void clinic_addFlat(clinic_t * self, flat_t * flat);
void flat_addPatient (clinic_t * clinic, flat_t * self, patient_t * pat);

list_t * clinic_getFlatList(clinic_t * self);
list_t * flat_getClientList(clinic_t * self, flat_t * flat);
int __getNumberTotalFlats(clinic_t * self);
int __getNumberTotalClients(clinic_t * self);
int __getNumberFlatClients(flat_t * flat);
clinic_state_t _clinicgetState(clinic_t * self);
flat_type_t flat_getType(flat_t * self);

//const char * flat_type_toString(flat_type_t type);
//const char * clinic_type_toString(clinic_type_t type);




#endif // PATIENT_H_INCLUDED
