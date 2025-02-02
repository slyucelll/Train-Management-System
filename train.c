

#include "train.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vagon.h"
#include "utility.h"



Train* current_train = NULL;


Train* createTrain(void) {
    if (current_train != NULL) {
        printf("A train already exists. Cannot create another train.\n");
        return NULL;
    }

    current_train = (Train*)malloc(sizeof(Train)); // Tren için bellek tahsisi
    if (!current_train) {
        printf("Memory allocation failed for train.\n");
        return NULL;
    }

    current_train->first_wagon = wagon_head;
    current_train->wagon_count = 0;           // Başlangıçta vagon sayısı 0

    printf("Train created successfully with no wagons.\n");
    return current_train;
}





void display_train_status(void) {
    if (wagon_head == NULL) {
        printf("No wagons exist in the train.\n");
        return;
    }
    
    Wagon* current_wagon = wagon_head;
    MaterialType* temp = material_head;
    
    while (current_wagon) {
        
        printf("Vagon ID: %d\n", current_wagon->wagon_id);
        printf("Toplam Ağırlık: %.2f kg\n", current_wagon->current_weight);
        printf("Materyaller: \n");
        
        while (temp->which_wagon == current_wagon->wagon_id) {
            
        printf("%.2f kilolu materyal %d numaralı vagonda yüklü \n",temp->weight,current_wagon->wagon_id);
                
            temp = temp->next;
       // eğer materyal olmadıysa atlatma
            if (temp==NULL) {
                printf("Materyaller Bunlardır.");
                break;
            }
        }
       
        current_wagon = current_wagon->next;
        if (current_wagon) {
            current_wagon->first_material = temp;
        }

    }
   
   
}

void empty_train(void) {
    Wagon* current_wagon = wagon_head;

    printf("Tüm tren boşaltılıyor...\n");

    
    while (current_wagon) {
        MaterialType* current_material = current_wagon->first_material;

        // Vagon içindeki materyalleri unloaded yap
        while (current_material) {
            current_material->loaded = 0;
            current_material->which_wagon=0;
            current_material = current_material->next;
        }

        // Vagonun ağırlığını sıfırla
        current_wagon->current_weight = 0;

        printf("Vagon %d boşaltıldı.\n", current_wagon->wagon_id);

        current_wagon = current_wagon->next;  // Bir sonraki vagona geç
    }

    printf("Tüm tren başarıyla boşaltıldı.\n");
}


