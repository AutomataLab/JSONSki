#include "../src/lib/RecordLoader.h"
#include "../src/lib/QueryProcessor.h"

int main() {
    char* file_path = "../dataset/twitter_sample_large_record.json";
    Record* rec = RecordLoader::loadSingleRecord(file_path);
    if (rec == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }

    QueryProcessor processor("$[*].entities.urls[*].url");
    string output = processor.runQuery(rec);
    cout<<"matches are: "<<output<<endl;
    return 0;
}
