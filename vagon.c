//vagon.c


#include "vagon.h"
#include "stdlib.h"
#include "stdio.h"
#include "train.h"
#include "utility.h"


Wagon* wagon_head = NULL;
Wagon* last_wagon_g = NULL;

Wagon* create_wagon(Train* train) {
    Wagon* new_wagon = (Wagon*)malloc(sizeof(Wagon));
    if (!new_wagon) {
        printf("Memory allocation failed for wagon.\n");
        return NULL;
    }

    new_wagon->wagon_id = train->wagon_count + 1;
    new_wagon->current_weight = 0;
    new_wagon->next = NULL;
    new_wagon->prev = NULL;

    // wagon_head'i başlatıyoruz
    if (wagon_head == NULL) {
        wagon_head = new_wagon;
    }

    // Trenin ilk vagonu ise
    if (train->wagon_count== 0) {
        train->first_wagon = new_wagon;
    } else {
        Wagon* current = train->first_wagon;
        while (current->next) {
            current = current->next;
        }
        current->next = new_wagon;
        new_wagon->prev = current;
    }

    train->wagon_count++;
    return new_wagon;
}

void add_materials_to_wagons(void) {
    if (wagon_head == NULL) {
        printf("Hata: Tren yüklenmeden önce vagon oluşturulmalıdır.\n");
        return;
    }
    
    if (material_head == NULL) {
        printf("Hata: Yüklenecek materyal bulunmamaktadır.\n");
        return;
    }
    
    
    
    Wagon* current_wagon = wagon_head;
    
    MaterialType* temp = material_head;
    
    
  
    int x  = 0;
   
    printf("kaç tane materyal eklenecek :");
    scanf("%d",&x);
    
    
   
    
    printf("Materyaller vagonlara yükleniyor...\n");
    
    
    while (temp->loaded) {
        temp = temp->next;
    }
    
    while (current_wagon->current_weight>=1000) {
        current_wagon = current_wagon->next;
    }

    
    // Son materyale kadar git
    while (temp  && x--)  {
        if (!temp->loaded) {
            if (current_wagon->first_material == NULL) {
                current_wagon->first_material = temp;
                current_wagon->current_weight += temp->weight;
                current_wagon->material_amount++;
                temp->loaded=1;
                temp->which_wagon=current_wagon->wagon_id;
                printf("%.2f kilolu materyal %d numaralı vagona eklendi \n ",temp->weight,current_wagon->wagon_id);
                printf("mevcut vagon ağırlığı %.2f \n ",current_wagon->current_weight);
                temp = temp->next;
                
                
            }else  if (current_wagon->first_material&&(current_wagon->current_weight+temp->weight<1000))  {
                current_wagon->current_weight += temp->weight;
                current_wagon->material_amount++;
                temp->loaded=1;
                temp->which_wagon=current_wagon->wagon_id;
                printf("%.2f kilolu materyal %d numaralı vagona eklendi \n ",temp->weight,current_wagon->wagon_id);
                printf("mevcut vagon ağırlığı %.2f \n ",current_wagon->current_weight);
                temp = temp->next;
                bubbleSortMaterialWeights(current_wagon);
                
            }else if(temp->weight+current_wagon->current_weight>=1000)
            {
                printf("%d numaralı vagon doldu. Yeni vagon ekleniyor...\n",current_wagon->wagon_id);
                
                create_wagon(current_train);
                current_wagon = current_wagon->next;
                current_wagon->current_weight += temp->weight;
                current_wagon->first_material = temp;
                temp->loaded=1;
                current_wagon->material_amount++;
                temp->which_wagon=current_wagon->wagon_id;
                printf("%.2f kilolu materyal %d numaralı vagona eklendi \n ",temp->weight,current_wagon->wagon_id);
                printf("mevcut vagon ağırlığı %.2f \n ",current_wagon->current_weight);
                temp = temp->next;
            }
            
        }}
   
        
}

// Belirli bir vagona materyal yükleme fonksiyonu
void add_material_to_specific_wagon(int wagon_id) {
    // Vagonu bulmak için ilk vagonu tarıyoruz
    Wagon* current_wagon = findVagonByID(wagon_id);
    MaterialType* current_material = findFirstUnloaded();

    while (current_wagon) {
        // Vagon ID'si eşleşirse
        if (current_wagon->wagon_id == wagon_id) {
            // Vagon kapasitesini kontrol et
            if ((current_wagon->current_weight+current_material->weight)>1000  ) {
                // Eğer vagon dolmuşsa
                printf("Vagon %d dolu! Vagon kapasitesi: %.2f kg\n", wagon_id, current_wagon->current_weight);
                return;
            } else {
                // Vagon yer varsa ve materyal sığarsa, yükleme işlemi yap
                current_wagon->current_weight += current_material->weight;
                current_material->loaded = 1;
                current_wagon->material_amount++;
                current_material->which_wagon=current_wagon->wagon_id;
                printf("Materyal %d vagonuna yüklendi. Yeni ağırlık: %.2f kg\n", wagon_id, current_wagon->current_weight);
                return;
            }
        }
        current_wagon = current_wagon->next;  // Bir sonraki vagona geç
    }

    // Eğer vagon bulunamazsa
    printf("Vagon ID'si %d bulunamadı.\n", wagon_id);
}



void unload_last_material_from_last_wagon(void) {
    
    Wagon* current_vagon = wagon_head;
    
    while (current_vagon->next) {
        current_vagon = current_vagon->next;
    }
    
    MaterialType* current = current_vagon->first_material;

    
    if (current_vagon->current_weight>0) {
        while (current->next&&current->next->loaded) {
            
            current=current->next;
            
        }
        
        
        current->loaded=0;
        current_vagon->material_amount=0;
        current->which_wagon=0;
        current_vagon->current_weight-=current->weight;
       
    }
    
    else{
        current_vagon = current_vagon->prev;
        
        current=current_vagon->first_material;
        
        while (current->next&&current->next->loaded) {
            
            current=current->next;
            
        }
                
        current->loaded=0;
        current->which_wagon=0;
        current_vagon->current_weight-=current->weight;
              
    }
    
    
}

void unload_specific_wagon(int wagon_id) {
    Wagon* current_wagon = wagon_head;

    while (current_wagon) {
        if (current_wagon->wagon_id == wagon_id) {
            // Vagonun yükünü sıfırla
            current_wagon->current_weight = 0;
            current_wagon->material_amount=0;

            // Materyalleri boşalt (yüklenmemiş hale getir)
         
            
            MaterialType* current_material = current_wagon->first_material;
            
            
            while (current_material->which_wagon == current_wagon->wagon_id) {
                current_material->loaded = 0;
                current_material->which_wagon = 0;
                
              
                current_material = current_material->next;
                if (current_material == NULL) {
                    break;
                }
            }

            // Vagonun bağlı olduğu düğümleri güncelle
            if (current_wagon->prev) {
                current_wagon->prev->next = current_wagon->next;
            } else {
                // Eğer silinen vagon baş düğümse, başı güncelle
                wagon_head = current_wagon->next;
            }

            if (current_wagon->next) {
                current_wagon->next->prev = current_wagon->prev;
            }

            // Belleği serbest bırak
            free(current_wagon);

            printf("Vagon %d ve içindeki materyaller boşaltıldı.\n", wagon_id);
            Train* current_train1=current_train;
            current_train1->wagon_count--;
            return;
        }
        current_wagon = current_wagon->next;
    }
    
    
    
    printf("Vagon ID'si %d bulunamadı.\n", wagon_id);
}


