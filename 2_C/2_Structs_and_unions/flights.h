//
// Created by Marcin on 17.04.2021.
//

#ifndef DANTE_FLIGHTS_H
#define DANTE_FLIGHTS_H
enum flight_t {
    PASSENGER,
    CARGO
};

struct flight {
    int flight_number;
    enum flight_t type;
    union {
        unsigned short npassengers;
        double tonnages;
    };
};

int save_flights(const struct flight *flights, int size, const char *filename);

int load_flights(struct flight *flights, int size, const char *filename);

int statistics_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type);

int best_flight(const struct flight *flights, int size, struct flight *f, enum flight_t type);
#endif //DANTE_FLIGHTS_H