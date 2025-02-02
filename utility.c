#include "utility.h"
#include <stdlib.h>
#include "material.h"
#include "vagon.h"



int get_random_value(void) {
    // 100, 150 ve 200 arasında rastgele bir değer döndürür
    int values[] = {100, 150, 200};
    return values[rand() % 3];  // 0, 1 veya 2'yi rastgele seçer
}

    
MaterialType* findFirstUnloaded(void) {
    MaterialType* current = material_head;
    
    // Tüm materyalleri gez
    while (current != NULL) {
        if (current->loaded == 0) {  // Yüklenmemiş materyali bul
            return current;
        }
        current = current->next;  // Sonraki materyale geç
    }
    
    // Eğer hepsi yüklenmişse, ilk materyali döndür
    return material_head;
}


Wagon* findVagonByID(int id) {
    Wagon* current = wagon_head;

    // Tüm vagoları gez
    while (current) {
        if (current->wagon_id == id) {
            return current;
        }
        current = current->next;  // Sonraki vagona geç
    }

    // Eğer vagon bulunamazsa NULL döndür
    return NULL;
}


void reset_wagons(void) {
    Wagon* current_wagon = wagon_head;
    Wagon* next_wagon;

    // Tüm vagoları gez
    while (current_wagon != NULL) {
        next_wagon = current_wagon->next;  // Bir sonraki vagona geç

        // Vagonu serbest bırak
        free(current_wagon);

        current_wagon = next_wagon;  // Bir sonraki vagona geç
    }

    // Wagon listesini sıfırla
    wagon_head = NULL;  // İlk vagon işaretçisini NULL yapıyoruz
}




void reset_materials(void) {
    MaterialType* current_material = material_head;
    MaterialType* next_material;

    // Tüm materyalleri gez
    while (current_material != NULL) {
        next_material = current_material->next;  // Bir sonraki materyale geç

        // Materyali serbest bırak
        free(current_material);

        current_material = next_material;  // Bir sonraki materyale geç
    }

    // Material listesini sıfırla
    material_head = NULL;  // İlk materyal işaretçisini NULL yapıyoruz
}

int material_amount_each_vagon(int id){
    
    MaterialType* temp =material_head;
    Wagon* temp_wagon = wagon_head;
    
    
    
    while (temp_wagon) {
        
        while (temp->next) {
            
            if (temp->which_wagon==temp_wagon->wagon_id) {
                temp_wagon->material_amount++;
            }
            temp=temp->next;
        }
        temp_wagon=temp_wagon->next;
        temp=material_head;
        
    }
     temp_wagon = wagon_head;
    
    while (temp_wagon) {
        if (temp_wagon->wagon_id==id) {
            return temp_wagon->wagon_id;
        }
        temp_wagon=temp_wagon->next;
    }
    
    return 0;
    // bu fonksiyonu yazıyorum belki kullanırım 
    
}

void bubbleSortMaterialWeights(Wagon* current_wagon) {
    if (!current_wagon || !current_wagon->first_material) return;

    int swapped;
    do {
        swapped = 0;
        MaterialType* ptr = current_wagon->first_material;
        
        while (ptr && ptr->next) {
            if (ptr->weight < ptr->next->weight) {
                // Sadece ağırlıkları değiştir
                int temp_weight = ptr->weight;
                ptr->weight = ptr->next->weight;
                ptr->next->weight = temp_weight;
                swapped = 1;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}












int how_many_materials_per_wagon(Wagon* current_wagon){
    
    MaterialType* temp = current_wagon->first_material;
    int counter = 0;
    
    
    while (temp->which_wagon == current_wagon->wagon_id) {
        
        counter++;
        temp=temp->next;
    }
    
    return counter;
    
    
    
}

// Bağlı listeyi büyükten küçüğe sıralayan Bubble Sort

// Bağlı listeyi yazdıran fonksiyon
