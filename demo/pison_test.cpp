#include "../src/RecordLoader.h"
#include "../src/JSONPathParser.h"
#include "../src/StreamProcessor.h"
#include "../src/JSONSki.h"
#include <sys/time.h>
#include <sys/file.h>
using namespace std;

void generateAutomatonForSingleRecord(QueryAutomaton& qa, string query_id) {
    string path = "";
    if (query_id == "TT1") {
        path = "$[*].entities.urls[*].url";
    } else if (query_id == "TT2") {
        path = "$[*].text";
    } else if (query_id == "BB1") {
        path = "$.products[*].categoryPath[0:1].id"; 
    } else if (query_id == "BB2") {
        path =  "$.products[*].videoChapters[*].chapter"; 
    } else if (query_id == "GMD1") {
        path = "$[*].routes[*].legs[*].steps[*].distance.text";
    } else if (query_id == "GMD2") {
        path = "$[*].available_travel_modes";
    } else if (query_id == "NSPL1") {
        path = "$.meta.view.columns[*].name";  
    } else if (query_id == "NSPL2") {
        path = "$.data[*][*][2]"; 
    } else if (query_id == "WM1") {
        path = "$.items[*].bestMarketplacePrice.price"; 
    } else if (query_id == "WM2") {
        path = "$.items[*].name"; 
    } else if (query_id == "WP1") {
        path = "$[*].claims.P150[*].mainsnak.property"; 
    } else if (query_id == "WP2") {
        path = "$[10:21].claims.P150[*].mainsnak.property";
    }
    JSONPathParser::updateQueryAutomaton(path, qa); 
}

void generateAutomatonForSmallRecords(QueryAutomaton& qa, string query_id) {
    string path = "";
    if (query_id == "TT1") {
        path = "$.entities.urls[*].url";
    } else if (query_id == "TT2") {
        path = "$.text";
    } else if (query_id == "BB1") {
        path = "$.categoryPath[0].id";
    } else if (query_id == "BB2") {
        path =  "$.videoChapters[*].chapter";
    } else if (query_id == "GMD1") {
        path = "$.routes[*].legs[*].steps[*].distance.text";
    } else if (query_id == "GMD2") {
        path = "$.available_travel_modes";
    } else if (query_id == "NSPL2") {
        path = "$[*][2:3]";
    } else if (query_id == "WM1") {
        path = "$.bestMarketplacePrice.price";
    } else if (query_id == "WM2") {
        path = "$.name";
    } else if (query_id == "WP1") {
        path = "$.claims.P150[*].mainsnak.property";
    }
    JSONPathParser::updateQueryAutomaton(path, qa);
}

void testSmallRecords(char* file_path, string query_id) {
    struct timeval begin,end;
    double duration;
    RecordLoader loader(file_path);
    Records* recs = loader.loadRecords();;
    if (recs == NULL) {
        cout<<"record loading fails."<<endl;
        return;
    }
    QueryAutomaton qa;
    generateAutomatonForSmallRecords(qa, query_id);
    int num_iterations = 20;
    vector<double> exe_time;
    long output_size = 0;
    string output;
    for (int i = 1; i <= num_iterations; ++i) {
        gettimeofday(&begin,NULL);
        string output;
        output_size = 0;
        // visit each record sequentially
        long start_idx = 0;
        long end_idx = recs->num_records;
        StreamProcessor* processor = new StreamProcessor(qa);
        gettimeofday(&begin,NULL);
        while (start_idx < end_idx) {
            char* record = recs->text + recs->rec_start_pos[start_idx];
            long length = recs->rec_length[start_idx];
            processor->setRecord(record, length);
            processor->init();
            processor->runQuery();
            ++start_idx;
        }
        // cout<<"output "<<output<<endl;
        gettimeofday(&end,NULL);
        duration=1000000*(end.tv_sec-begin.tv_sec)+end.tv_usec-begin.tv_usec;
        double time = duration / (double) 1000000;
        exe_time.push_back(time);
        cout<<"Query execution time is "<<time<<endl;
        cout<<"output size is "<<processor->getNumOfOutputs()<<endl;
        output_size = processor->getNumOfOutputs(); 
        delete processor;
    }
    double sum_exe_time = 0.0;
    for (int i = 0; i < num_iterations; ++i) {
        sum_exe_time += exe_time[i];
    }
    double avg_exe_time = sum_exe_time / (double)num_iterations;
    cout<<"[Performance Result]: total execution time is "<<avg_exe_time<<" seconds (avg. of 20 runs)"<<endl;
    delete recs;
}

void testLargeRecord(char* file_path, string query_id) {
    struct timeval begin,end;
    double duration;
    RecordLoader loader(file_path);
    Records* records = loader.loadSingleRecord();
    if (records == NULL) {
        cout<<"record loading fails."<<endl;
        return;
    }
    QueryAutomaton qa;
    generateAutomatonForSingleRecord(qa, query_id);
    int num_iterations = 20;
    vector<double> exe_time;
    long output_size = 0;
    for (int i = 0; i < num_iterations; ++i) {
        StreamProcessor* processor = new StreamProcessor(records->text, records->rec_length[0], qa);
        gettimeofday(&begin,NULL);
        processor->runQuery();
        gettimeofday(&end,NULL);
        duration=1000000*(end.tv_sec-begin.tv_sec)+end.tv_usec-begin.tv_usec;
        double time = duration / (double) 1000000;
        cout<<"Query execution time is "<<time<<endl;
        cout<<"output size is "<<processor->getNumOfOutputs()<<endl;
        output_size = processor->getNumOfOutputs();
        exe_time.push_back(time); 
        delete processor;
    }
    double sum_exe_time = 0.0;
    for (int i = 0; i < num_iterations; ++i) {
        sum_exe_time += exe_time[i];
    }
    double avg_exe_time = sum_exe_time / (double)(num_iterations);
    cout<<"[Performance Result]: total execution time is "<<avg_exe_time<<" seconds (avg. of 20 runs)"<<endl;
    delete records;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("the number of input arguments should be at least three: file_path, input_type(small (for small records), large (for large record)), query_id used in Pison paper\n");
        return -1;
    }
    char* file_path = argv[1];
    char* input_type = argv[2];
    string query_id(argv[3]);
    cout<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    cout<<"[Start Evaluation]: "<<query_id<<" on file "<<file_path<<endl;
    if (strcmp(input_type, "small") == 0) {
        testSmallRecords(file_path, query_id);
    } else if (strcmp(input_type, "large") == 0) {
        testLargeRecord(file_path, query_id);
    }
    cout<<"[End Evaluation]: "<<query_id<<" on file "<<file_path<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    return 0;
}
