#include "patient.h"
#include "list.h"
#define MAX_PATIENTS 4
#define MAX_FLATS 5

struct patient_s
{
    const char * name;
    const char * surname;
    int age;
    const char * disease;
    int seat;
};


struct flat_s
{
    char * name;
//    flat_type_t type;
    int number;
    list_t * patients ;
};


struct clinic_s
{
//    clinic_type_t type;
    list_t * flats;
    list_t * subscribers;
};

typedef struct subscriber_s {
    void * listener;
//    start_fn callback;
} subscriber_t;

patient_t * patient_new ( const char * name, const char * surname, int age, const char * disease)
{
    patient_t * pat = malloc (sizeof (patient_t));
    pat->name = name;
    pat->surname = surname;
    pat->age = age;
    pat->disease = disease;
    pat->seat = 0;
}

void patient_free(patient_t * self) {
    free (self->name);
    free(self->surname);
    free(self->disease);
    free(self);
}

void patient_delete (flat_t * flat, patient_t * self, int seat)
{
    list_remove(flat->patients, seat);
    patient_free (self);
}

flat_t * flat_new(flat_type_t type) {
    flat_t * self = malloc(sizeof(flat_t));
//    self->type = type;
    self->number = 0;
    self->patients = list_new ();
 //   self->type = 1;
    return self;
}

void flat_free(flat_t * self) {
    free(self->patients);
    free(self);
}

clinic_t * clinic_new() {
    clinic_t * self = malloc(sizeof(clinic_t));
//    self->state = CLINIC_FULL;
    self->subscribers = list_new();
    self->flats = list_new();
 //   self->type = 1;
    return self;
}

void clinic_free(clinic_t * self) {
    list_free(self->subscribers);
    list_free(self->flats);
    free(self);
}

// ------------------------FOR CALLBACKS---------------------------

/*void clinic_subscribeStart(clinic_t * self, void * listener, start_fn callback) {
    subscriber_t * sub = malloc(sizeof(subscriber_t));
    sub->listener = listener;
    sub->callback = callback;
    list_push_back(self->subscribers, sub);
}

void clinic_unsubscribeStart(clinic_t * self, void * listener, start_fn callback) {
    for (int i = 0; i < list_getSize(self->subscribers); i++) {
        subscriber_t * subs = (subscriber_t *)list_get(self->subscribers, i);
        if ((subs->listener == listener) && (subs->callback == callback)) {
            list_remove(self->subscribers, i);
            break;
        }
    }
}*/
// ---------------------------ADD NEW----------------------------------

void clinic_addFlat(clinic_t * self, flat_t * flat) {
    if (list_getSize(self->flats) < MAX_FLATS)
    list_push_back(self->flats, flat);
//    else self->type = 0;
}


void flat_addPatient (clinic_t * clinic, flat_t * self, patient_t * pat)
{
    patient_t * pat = malloc (sizeof (patient_t));
    if (list_getSize (self->patients < MAX_PATIENTS))
    {
       pat->seat = list_getSize (self->patients);
       list_push_back(self->patients, patient);
       list_push_back (clinic->flats, self);
    }
    else self->type = 0;
}

list_t * clinic_getFlatList(clinic_t * self) {
    list_t * copy = list_new_copy(self->flats);
    return copy;
}

list_t * flat_getClientList(clinic_t * self, flat_t * flat) {
    list_t * copy = list_new_copy(flat->clients);
    return copy;
}

int __getNumberTotalFlats(clinic_t * self) {
    return list_getSize(self->flats);
}

int __getNumberTotalClients(clinic_t * self) {
    int number = 0;
    for (int i = 0; i < list_getSize(self->flats); i++) {
        flat_t * flat = list_get(self->flats, i);
        number += list_getSize(flat->patiens);
    }
    return number;
}

int __getNumberFlatClients(flat_t * flat) {
    return list_getSize (flat->clients);
}

clinic_state_t _clinicgetState(clinic_t * self) {
    return self->state;
}

flat_type_t flat_getType(flat_t * self) {
    return self->type;
}

const char * flat_type_toString(flat_type_t type) {
    switch (type) {
        case (FLAT_FULL) :  return "FLAT FULL";
        case (FLAT_FREE) :    return "FREE PLACES";
        default :               return NULL;
    }
}

const char * clinic_type_toString(clinic_type_t type) {
    switch (type) {
        case (CLINIC_FULL) :  return "CLINIC FULL";
        case (CLINIC_FREE) :    return "FREE PLACES";
        default :               return NULL;
    }
}
