#ifndef utility_h
#define utility_h

#include <stdio.h>
#include "material.h"
#include "vagon.h"

// Yardımcı Fonksiyonlar
int get_random_value(void);
MaterialType* findFirstUnloaded(void);
Wagon* findVagonByID(int id);
void reset_wagons(void);
void reset_materials(void) ;
int material_amount_each_vagon(int id);
void bubbleSortMaterialWeights(Wagon* current_wagon);



#endif /* utility_h */


