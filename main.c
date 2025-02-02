
#include <stdio.h>
#include "train.h"
#include "vagon.h"
#include "material.h"
#include "utility.h"
#include "file_opr.h"
#include "string.h"
#include "stdlib.h"

void display_menu(void) {
    printf("\n*** Train Loading Management System ***\n");
    printf("1. Load train status from file\n");
    printf("2. Load material, starting from first suitable wagon from head of the Train\n");//
    printf("3. Load material to specific wagon\n");//
    printf("4. Unload material, starting from first suitable wagon from tail of the Train\n");
    printf("5. Unload material from specific wagon\n");
    printf("6. Display train status\n");
    printf("7. Display material status\n");
    printf("8. Empty train\n");
    printf("9. Save train status to file\n");//
    printf("10. Exit\n");
    printf("Select an option: ");
}

int main(void) {

    create_multiple_materials(20); createTrain();
    create_wagon(current_train);
   
   
    int choice;

    while (1) {
        display_menu();
           scanf("%d", &choice);
           fflush(stdin);
        switch (choice) {
            case 1:
                load_train_status_from_file("Train_Information.txt");
                break;
            case 2:
                add_materials_to_wagons();
                break;
            case 3:
                {
                    int istenen;
                    printf("lütfen vagon belirtiniz");
                    scanf("%d",&istenen);
                    add_material_to_specific_wagon(istenen);
                }
                break;
            case 4:
                     unload_last_material_from_last_wagon();
                break;
            case 5:
            {
                int istenen_;
                printf("lütfen vagon belirtiniz :");
                scanf("%d",&istenen_);
               unload_specific_wagon(istenen_);
            }
                break;
            case 6:
                display_train_status();
                break;
            case 7:
                display_material_status();
                break;
            case 8:
                empty_train();
                break;
            case 9:
                save_train_status_to_file("Train_Information.txt", current_train);
                break;
            case 10:
                printf("Exiting program.\n");

                           // Hafıza temizliği
                           free(current_train);
                           free(material_head);
                           free(wagon_head);
                           clear_file_content("Train_Information.txt");

                           return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;
   
   
    
}


