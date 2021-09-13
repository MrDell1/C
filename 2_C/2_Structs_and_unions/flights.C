#include <stdio.h>
#include "flights.h"


int save_flights(const struct flight *flights, int size, const char *filename){
    if(flights == NULL || size <= 0 || filename == NULL){
        return 1;
    }
    FILE *file = fopen(filename, "wb");
    if(file == NULL){
        return 2;
    }
    fwrite(&size, sizeof(int), 1, file);
    for(int i = 0;i < size; i++){
        fwrite(flights, sizeof(struct flight), 1, file);
        flights++;
    }
    fclose(file);
    return 0;
}

int load_flights(struct flight *flights, int size, const char *filename){
    if(flights == NULL || size <= 0 || filename == NULL){
        return -1;
    }
    FILE *file = fopen(filename, "rb");
    if(file == NULL){
        return -2;
    }
    fseek(file, 0, SEEK_SET);
    int i, n = 0;
    if(fread(&n, sizeof(int), 1, file) != 1){
        fclose(file);
        return -3;
    }
    if(n <= 0){
        fclose(file);
        return -3;
    }
    if(n >= size) {
        for (i = 0; i < size; i++) {
            if (fread(flights, sizeof(struct flight), 1, file) != 1) {
                fclose(file);
                return -3;
            }
            flights++;
        }

    } else{
        for (i = 0; i < n; i++) {
            if (fread(flights, sizeof(struct flight), 1, file) != 1) {
                fclose(file);
                return -3;
            }
            flights++;
        }
    }
    if(i < 1){
        fclose(file);
        return -3;
    }

    fclose(file);
    return i;
}

int statistics_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type){
    if(flights == NULL || size <= 0 || f == NULL || (type != 0 && type != 1)){
        return -1;
    }

    int x = 0;
    int np = 0;
    double t = 0;
    for(int i = 0; i < size; i++){
        if(flights->type == type){
            np += flights->npassengers;
            t += flights->tonnages;
            x++;
        }
        flights++;
    }
    if(type == PASSENGER){
        f->npassengers = np;
    }
    else{
        f->tonnages = t;
    }
    f->flight_number = x;
    f->type = type;
    return x;
}

int best_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type){
    if(flights == NULL || size <= 0 || f == NULL || (type != 0 && type != 1)){
        return 1;
    }
    int max = 0, i;
    if(type == PASSENGER){
        for(i = 0; i < size; i++){
            if(flights->type == PASSENGER) {
                max = flights->npassengers;
                f->flight_number = flights->flight_number;
                f->type = flights->type;
                f->npassengers = flights->npassengers;
                break;
            }
            flights++;
        }
        for(int j = 0; j < size - i; j++){
            if(flights->type == PASSENGER){
                if(max <= flights->npassengers){
                    if(max == flights->npassengers) {
                        if (f->flight_number < flights->flight_number) {
                            max = flights->npassengers;
                            f->flight_number = flights->flight_number;
                            f->type = flights->type;
                            f->npassengers = flights->npassengers;
                        }
                    } else{
                        max = flights->npassengers;
                        f->flight_number = flights->flight_number;
                        f->type = flights->type;
                        f->npassengers = flights->npassengers;
                    }
                }
            }
            flights++;
        }
        if(max == 0){
            return 2;
        }

    }

    double max_d = 0;
    if(type == CARGO){
        for(i = 0; i < size; i++){
            if(flights->type == CARGO) {
                max_d = flights->tonnages;
                f->flight_number = flights->flight_number;
                f->type = flights->type;
                f->tonnages = flights->tonnages;
                break;
            }
            flights++;
        }
        for(int j = 0; j < size - i; j++){
            if(flights->type == CARGO){
                if(max_d <= flights->tonnages){
                    if(max_d == flights->tonnages) {
                        if (f->flight_number < flights->flight_number) {
                            max_d = flights->tonnages;
                            f->flight_number = flights->flight_number;
                            f->type = flights->type;
                            f->tonnages = flights->tonnages;
                        }
                    } else{
                        max_d = flights->tonnages;
                        f->flight_number = flights->flight_number;
                        f->type = flights->type;
                        f->tonnages = flights->tonnages;
                    }
                }
            }
            flights++;
        }
        if(max_d == 0){
            return 2;
        }

    }

    return 0;
}