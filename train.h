#ifndef TRAIN_H
#define TRAIN_H

// Wagon türüne ileri bildirim ekliyoruz
typedef struct Wagon Wagon;

typedef struct Train {
    Wagon* first_wagon;
    int wagon_count;
} Train;

Train* createTrain(void);

extern Train* current_train;

void display_train_status(void);
void empty_train(void);
#endif /* TRAIN_H */


