#include "JSONSki.h"

string JSONSki::runQuery(Record* record, string query) {
    QueryAutomaton qa;
    // update query automaton based on the specific JSONPath query
    JSONPathParser::updateQueryAutomaton(query, qa);
    // run query automaton
    StreamProcessor processor(record->text, record->rec_length, qa);
    return processor.runQuery();
}
