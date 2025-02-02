
 #ifndef VAGON_H
#define VAGON_H

#include "material.h"

// Train türüne ileri bildirim ekliyoruz
typedef struct Train Train;
typedef struct MaterialType MaterialType;


typedef struct Wagon {
    int wagon_id;
    int material_amount;
   float current_weight;
    struct Wagon* next;
    struct Wagon* prev;
    MaterialType* first_material;
} Wagon;

extern Wagon* wagon_head ;

// son vagon olayını sadece file op sayfasında kullandım 
extern Wagon* last_wagon_g ;

Wagon* create_wagon(Train* train);
void add_materials_to_wagons(void);
void add_material_to_specific_wagon( int wagon_id);

void unload_last_material_from_last_wagon(void) ;
void unload_specific_wagon(int wagon_id);

#endif /* VAGON_H */


