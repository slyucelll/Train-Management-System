//
//  file_opr.c
//  TrainProjectNew
//
//  Created by Sule Yucel on 31.12.2024.
//

#include "file_opr.h"


#include "train.h"
#include "vagon.h"
#include "material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

void save_train_status_to_file(const char* filename, Train* train) {
    FILE* file = fopen(filename, "w");  // Dosyayı yazma modunda aç
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    // Tren başlığını yazalım
    fprintf(file, "Train Status\n");
    fprintf(file, "Total Wagons: %d\n", train->wagon_count);

    // Vagonları yazma
    Wagon* current_wagon = wagon_head;
    while (current_wagon) {
        fprintf(file, "Wagon ID: %d, MaterialAmount: %d Current Weight: %.2f kg\n", current_wagon->wagon_id, current_wagon->material_amount,current_wagon->current_weight);

        // Eğer materyal yüklendiyse, materyalin bilgilerini yaz
        MaterialType* material = current_wagon->first_material;  // İlk materyali al
        while (material->which_wagon == current_wagon->wagon_id) {
            if (material->loaded) {
    fprintf(file, " Weight: %.2f kg, Loaded: %s Wagon ID: %d \n",  material->weight, material->loaded ? "Yes" : "No",material->which_wagon);
            }
            material = material->next;
            if (material == NULL) {
                break;
            }
        }

        current_wagon = current_wagon->next; 
        if (current_wagon == NULL ) {
            break;
        }// Sonraki vagona geç
    }

    fclose(file);  // Dosyayı kapat
    printf("Trenin durumu dosyaya kaydedildi: %s\n", filename);
}


/*


void load_train_status_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");  // Dosyayı okuma modunda aç
       if (file == NULL) {
           printf("Dosya açılamadı: %s\n", filename);
           return;
       }

       // Dosyanın ilk karakterini kontrol et
       int c = fgetc(file);
       if (c == EOF) {  // Dosya boş ise EOF döner
           printf("Dosya boş: %s\n", filename);
           fclose(file);
           return;
       }

       // Dosya boş değilse baştan okumaya dön
       ungetc(c, file);  // İlk karakteri geri koy
       char line[256];   // Her satır için bir buffer
       while (fgets(line, sizeof(line), file)) {  // Satır satır oku
           printf("%s", line);  // Satırı ekrana yazdır
       }

       fclose(file);  // Dosyayı kapat
   
}



 ----------------------------------------------------------
 
 */
void load_train_status_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    // Listeleri sıfırlayalım
    reset_wagons();  // Vagon listesini sıfırlamak
    reset_materials();  // Materyal listesini sıfırlamak

    char line[100];
    int total_wagons;
    int which_wagon;
    int material_amount;
    float weight;
    char loaded_str[10];
    
    // İlk iki satırı oku ve toplam vagon sayısını al
    fgets(line, sizeof(line), file);  // "Train Status"
    fscanf(file, "Total Wagons: %d\n", &total_wagons);
    
    

    while (fgets(line, sizeof(line), file)) {
        // Eğer satır "Wagon ID: ..." formatındaysa yeni vagon oluştur burda dikkat etmek icab eder
        if (sscanf(line, "Wagon ID: %d, MaterialAmount: %d Current Weight: %2f  kg\n", &which_wagon,&material_amount,&weight) == 3) {
            // Yeni bir vagon oluştur
            Wagon* new_wagon = create_wagon(current_train);
            new_wagon->material_amount = material_amount;
            new_wagon->wagon_id = which_wagon;
            new_wagon->current_weight = weight;
            
            
        }
            
        // Eğer satır "Weight: ... Loaded: ..." formatındaysa materyal ekle basitçe yapıyoruz bunu
        else if (sscanf(line, " Weight: %f kg, Loaded: %9s Wagon ID: %d", &weight, loaded_str, &which_wagon) == 3) {
            MaterialType* new_material = create_one_material();
            new_material->weight = weight;
            new_material->loaded = (strcmp(loaded_str, "Yes") == 0) ? 1 : 0;
            new_material->which_wagon = which_wagon;
            
        
            
            if (material_head == NULL) {  //
                material_head = new_material;
                last_material_g = new_material;
               
            } else {
                last_material_g->next = new_material;
                new_material->prev = last_material_g;
                last_material_g = new_material;
               
            }
            
            
            
            // Materyali doğru vagona ekle
           
        }
        
        
        else {
            
            printf("   \n");
            
        }
       
    }
    
    
    
    // bu aşağıdakini şundan yazdım bütün listeyi güncelledik ya vagonların ilk materyalleri atanmadı burda atıyorum 
    
    Wagon* current_wagon = wagon_head;
    MaterialType* temp = material_head;

    while (current_wagon) {
        
        if(current_wagon->first_material ==NULL){
            while (temp) {
                if(temp->which_wagon==current_wagon->wagon_id){
                    current_wagon->first_material = temp;
                    temp = temp->next;
                    goto label;
                    }
                    
                temp = temp->next;
                
            }
        
            
        }
    label:
        current_wagon= current_wagon->next;
    }
   
    
    
    

    fclose(file);

    // Ekrana yazdırma
    Wagon* wagon = wagon_head;
    while (wagon) {
        printf("Wagon ID: %d, WagonMateryalMiktarı :%d   Current Weight: %.2f kg\n", wagon->wagon_id,wagon->material_amount, wagon->current_weight);
        MaterialType* material = wagon->first_material;
        while (material->which_wagon==wagon->wagon_id) {
            printf("  Material -> Weight: %.2f kg, Loaded: %s\n",
                   material->weight, material->loaded ? "Yes" : "No");
            material = material->next;
            if (material==NULL) {
                printf("liste bitti");
                break;
            }
        }
        wagon = wagon->next;
    }
}


void clear_file_content(const char *filename) {
    FILE *file = fopen(filename, "w"); // Dosyayı yazma modunda aç
    if (file == NULL) {
        perror("Dosya açılamadı");
        return;
    }
    fclose(file); // Dosyayı kapat
}

