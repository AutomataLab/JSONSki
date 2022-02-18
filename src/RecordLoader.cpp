#include <sys/time.h>
#include "RecordLoader.h"
using namespace std;

#define MAX_PAD 64

RecordLoader::RecordLoader(char* file_path){
    mFilePath = file_path;
}

char* RecordLoader::loadRecord() {
    char* file_name = mFilePath;
    unsigned long size;
    FILE* fp = fopen (file_name,"rb");
    if (fp == NULL) {
        return NULL;
    }
    fseek (fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    void* p;
    if (posix_memalign(&p, 64, (size + MAX_PAD)*sizeof(char)) != 0) {
        cout<<"Fail to allocate memory space for input record."<<endl;
    }
    char* record = (char*) p;
    size_t load_size = fread (record, 1, size, fp);
    if (load_size == 0) {
        cout<<"Fail to load the input record into memory"<<endl;
    }
    int remain = 64 - (size % 64);
    int counter = 0;
    // pad the input data where its size can be divided by 64 
    while (counter < remain)
    {
        record[size+counter] = 'd';
        counter++;
    }
    record[size+counter]='\0';
    fclose(fp);
    return record;
}

Records* RecordLoader::loadSingleRecord() {
    char* file_name = mFilePath;
    unsigned long size;
    FILE* fp = fopen (file_name,"rb");
    if (fp == NULL) {
        return NULL;
    }
    fseek (fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    void* p;
    if (posix_memalign(&p, 64, (size + MAX_PAD)*sizeof(char)) != 0) {
        cout<<"Fail to allocate memory space for input record."<<endl;
    }
    char* record = (char*) p;
    size_t load_size = fread (record, 1, size, fp);
    if (load_size == 0) {
        cout<<"Fail to load the input record into memory"<<endl;
    }
    int remain = 64 - (size % 64);
    int counter = 0;
    // pad the input data where its size can be divided by 64
    while (counter < remain)
    {
        record[size+counter] = 'd';
        counter++;
    }
    record[size+counter]='\0';
    fclose(fp);
    // only one single record
    Records* records = new Records();
    records->text = record;
    records->rec_start_pos = new long[1];
    records->rec_start_pos[0] = 0;
    records->rec_length = new long[1];
    records->rec_length[0] = strlen(record);
    records->num_records = 1;
    return records;
}

Records* RecordLoader::loadRecords() {
    char* file_name = mFilePath;
    FILE *fp = fopen(file_name, "r");
    Records* records = new Records();
    if (fp) {
        records->rec_start_pos = new long[MAX_NUM_RECORD];
        records->rec_length = new long[MAX_NUM_RECORD];
        records->num_records = 0;
        char line[MAX_RECORD_SIZE];
        string str;
        int start_pos = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (strlen(line) <= MIN_RECORD_SIZE) continue;
            int remain = 64 - strlen(line) % 64;
            int top = strlen(line);
            while (remain > 0) {
                line[top++] = 'd';
                --remain;
            }
            line[top] = '\0';
            if (strlen(line) > MIN_RECORD_SIZE) {
                // records are placed consecutively on a single line, which has better performance comparing with putting them into a string array
                str.append(line);
                records->rec_start_pos[records->num_records] = start_pos;
                records->rec_length[records->num_records++] = strlen(line);
                start_pos += strlen(line);
            }
        }
        void* p;
        if(posix_memalign(&p, 64, str.size()*sizeof(char)) != 0) {
            cout<<"Fail to allocate memory space for records from input file."<<endl;
        }
        records->text = (char*) p;
        strcpy(records->text, str.c_str());
        fclose(fp);
        return records;
    }
    cout<<"Fail open the file."<<endl;
    return NULL;
}
