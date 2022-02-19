#ifndef RECORDS_H
#define RECORDS_H

#include <stdlib.h>

#define MIN_RECORD_SIZE 5
#define MAX_RECORD_SIZE 1000000
#define MAX_NUM_RECORD 5000000

// information for line-delimited JSON stream with records
struct Records {
    char* text;
    long* rec_start_pos;
    long* rec_length;
    long num_records;
    Records() {
        text = NULL;
        rec_start_pos = (long*)malloc(MAX_NUM_RECORD * sizeof(long));
        rec_length = (long*)malloc(MAX_NUM_RECORD * sizeof(long));
        num_records = 0;
    }

    ~Records() {
        if (text) {
            free(text);
        }
        if (rec_start_pos) {
            free(rec_start_pos);
        }
        if (rec_length) {
            free(rec_length);
        }
    }
};
#endif
