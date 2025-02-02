#include "material.h"
#include "stdlib.h"
#include "utility.h"
#include "vagon.h"

MaterialType* material_head = NULL;
MaterialType* last_material_g = NULL;

// Tek bir materyal oluşturma fonksiyonu
MaterialType* create_one_material(void) {
    MaterialType* material = (MaterialType*)malloc(sizeof(MaterialType));
    if (!material) {
        printf("Memory allocation failed for material.\n");
        return NULL;
    }

    material->weight = get_random_value(); // Rastgele 100, 150 veya 200 kg arasında bir ağırlık alır
    material->loaded = 0;
    material->next = NULL;
    material->prev = NULL;
    return material;
}

// Birden fazla materyal oluşturma fonksiyonu
MaterialType* create_multiple_materials(int count) {
    MaterialType* current = NULL;

    for (int i = 0; i < count; i++) {
        MaterialType* new_material = create_one_material();
        if (!new_material) {
            printf("Failed to create material.\n");
            return NULL; // Bellek tahsisi başarısızsa işlemi durdur
        }

        // Listeye ekle
        if (material_head == NULL) {
            material_head = new_material;  // Eğer liste boşsa, yeni materyal ilk eleman olur
            current = material_head;      // İlk elemanı current olarak ayarla
        } else {
            current->next = new_material;  // Yeni materyali mevcut son elemana ekle
            new_material->prev = current;  // Yeni materyalin önceki elemanını güncelle
            current = new_material;        // Mevcut son elemanı yeni materyale güncelle
        }
    }

    return material_head;  // Liste başını döndür
}

void display_material_status(void) {
    MaterialType* current_material = material_head;

    int total_materials = 0;
    int total_steel = 0, total_aluminum = 0, total_wood = 0;
    int loaded_materials = 0;
    int materials_in_warehouse = 0;

    printf("Materyal Durumu:\n");

    // Materyalleri gezme
    while (current_material) {
        total_materials++;
        
        // Materyalin türünü belirleme
        if (current_material->weight == 200) {
            total_steel++;
        } else if (current_material->weight == 150) {
            total_aluminum++;
        } else if (current_material->weight == 100) {
            total_wood++;
        }

        // Yüklü materyalleri kontrol et
        if (current_material->loaded) {
            printf("Yüklü Materyal: %.2f kg, Vagon: %d\n", current_material->weight, current_material->which_wagon);
            loaded_materials++;
        } else {
            printf("Material Yüklü değil : %.2f kg, -----Depoda \n", current_material->weight);
            materials_in_warehouse++;
        }

        current_material = current_material->next; // Bir sonraki materyale geç
    }

    // Sonuçları yazdırma
    printf("\nToplam Materyal Sayısı: %d\n", total_materials);
    printf("Steel: %d adet (200 kg)\n", total_steel);
    printf("Aluminum: %d adet (150 kg)\n", total_aluminum);
    printf("Wood: %d adet (100 kg)\n", total_wood);

    printf("\nYüklü Materyaller: %d\n", loaded_materials);
    printf("Depoda Bekleyen Materyaller: %d\n", materials_in_warehouse);
}
