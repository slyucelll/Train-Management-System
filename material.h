#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct MaterialType {
    int which_wagon;
    float weight;
    int son_eleman;
    int loaded;  // 0: Not loaded, 1: Loaded çokca basit bir daha yüklenmiş materyaller için ayrı struct kullanmadım 
    struct MaterialType* next;
    struct MaterialType* prev;
} MaterialType;

// Material fonksiyonları
MaterialType* create_one_material(void);
MaterialType* create_multiple_materials(int count);
extern MaterialType* material_head;
extern MaterialType* last_material_g ;


void display_material_status(void);

#endif // MATERIAL_H

