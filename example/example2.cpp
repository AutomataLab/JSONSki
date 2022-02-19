#include "../src/RecordLoader.h"
#include "../src/StreamProcessor.h"

int main() {
    char* file_path = "../dataset/bestbuy_sample_large_record.json";
    cout<<"start loading the single large record from "<<file_path<<endl;
    Record* rec = RecordLoader::loadSingleRecord(file_path);
    if (rec == NULL) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    cout<<"finish loading the single large record"<<endl;

    string query = "$.products[*].categoryPath[1:3].name";
    cout<<"\nstart executing query "<<query<<endl;
    StreamProcessor processor(query);
    string output = processor.runQuery(rec);
    cout<<"finish query execution"<<endl;
    cout<<"matches are: "<<output<<endl;
    return 0;
}
