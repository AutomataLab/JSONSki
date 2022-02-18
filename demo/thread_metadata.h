#ifndef THREAD_METADATA_H
#define THREAD_METADATA_H

// #include "../src/BitmapConstructor.h"
#include "../src/StreamProcessor.h"

struct ThreadMetaData {
    // current thread id for parsing and querying
    int thread_id;
    QueryAutomaton qa;
    string* output;
    long output_size;
    StreamProcessor* bitmap;
    int start_idx;
    int end_idx;
};
#endif
