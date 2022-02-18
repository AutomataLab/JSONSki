#ifndef PARALLEL_QUERY_H
#define PARALLEL_QUERY_H
#include <pthread.h>
#include <string>
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"
#include "task_queue.h"
#include "thread_metadata.h"
using namespace std;

#define SINGLE_THREAD_MAXRECORDS 200

typedef void (*query_callback)(BitmapIterator* iter, string& output, long& output_size);
void parallel_query(BitmapIterator* iter, query_callback qry, int num_recs, string* output, long& output_size, int thread_num);
#endif
