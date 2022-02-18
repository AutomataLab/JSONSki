#include "../src/RecordLoader.h"
#include "../src/BitmapIterator.h"
#include "../src/BitmapConstructor.h"
#include "parallel_query.h"
#include <sys/time.h>
#include <sys/file.h>
#include <unordered_set>
using namespace std;

// $.id
void query_tt0_small(BitmapIterator* iter, string& output, long& output_size);

// $.root[*].id
void query_tt0_large(BitmapIterator* iter, string& output, long& output_size);

// $.root[*].id
void query_tt0_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// $.user.id
void query_tt1_small(BitmapIterator* iter, string& output, long& output_size);

// $.root[*].user.id
void query_tt1_large(BitmapIterator* iter, string& output, long& output_size);

// $.root[*].user.id
void query_tt1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.user.id, $.retweet_count}
void query_tt2_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.id, $.root[*].retweet_count}
void query_tt2_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.id, $.root[*].retweet_count}
void query_tt2_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.user.id, $.user.lang}
void query_tt3_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.id, $.root[*].user.lang}
void query_tt3_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.id, $.root[*].user.lang}
void query_tt3_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.user.name, $.retweet_count}
void query_tt4_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.name, $.root[*].retweet_count}
void query_tt4_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.name, $.root[*].retweet_count}
void query_tt4_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.user.lang, $.lang}
void query_tt5_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.lang, $.root[*].lang}
void query_tt5_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].user.lang, $.root[*].lang}
void query_tt5_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.id, $.retweeted_status.id}
void query_tt6_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].retweeted_status.id}
void query_tt6_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].retweeted_status.id}
void query_tt6_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.id, $.entities.urls[*].url}
void query_tt7_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].url}
void query_tt7_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].url}
void query_tt7_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.id, $.entities.urls[*].indices[*]}
void query_tt8_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].indices[*]}
void query_tt8_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].indices[*]}
void query_tt8_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.id, $.entities.urls[*].url, $.entities.urls[*].expanded_url, $.entities.urls[*].display_url}
void query_tt9_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].url, $.root[*].entities.urls[*].expanded_url, $.root[*].entities.urls[*].display_url}
void query_tt9_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].id, $.root[*].entities.urls[*].url, $.root[*].entities.urls[*].expanded_url, $.root[*].entities.urls[*].display_url}
void query_tt9_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.categoryPath[1:3].id, $.categoryPath[1:3].name}
void query_bb1_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root.products[*].categoryPath[1:3].id, $.root.products[*].categoryPath[1:3].name}
void query_bb1_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root.products[*].categoryPath[1:3].id, $.root.products[*].categoryPath[1:3].name}
void query_bb1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.routes[*].legs[*].steps[*].distance.text}
void query_gmd1_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].routes[*].legs[*].steps[*].distance.text}
void query_gmd1_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root[*].routes[*].legs[*].steps[*].distance.text}
void query_gmd1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.view.columns[*].name}
void query_nspl1_small(BitmapIterator* iter, string& output, long& output_size);

// {$.root.meta.view.columns[*].name}
void query_nspl1_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root.meta.view.columns[*].name}
void query_nspl1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

// {$.bestMarketplacePrice.price, $.name}
void query_wm1_small(BitmapIterator* iter, string& output, long& output_size) ;

// {$.root.items[*].bestMarketplacePrice.price, $.root.items[*].name}
void query_wm1_large(BitmapIterator* iter, string& output, long& output_size);

// {$.root.items[*].bestMarketplacePrice.price, $.root.items[*].name}
void query_wm1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

//{$.claims.P150[*].mainsnak.property}
void query_wp1_small(BitmapIterator* iter, string& output, long& output_size);

//{$.root[*].claims.P150[*].mainsnak.property}
void query_wp1_large(BitmapIterator* iter, string& output, long& output_size);

//{$.root[*].claims.P150[*].mainsnak.property}
void query_wp1_large_parallel(BitmapIterator* iter, string* output, long& output_size, int thread_num);

typedef void (*parallel_query_callback)(BitmapIterator* iter, string* output, long& output_size, int thread_num);
