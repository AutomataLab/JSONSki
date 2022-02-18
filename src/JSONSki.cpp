#include "JSONSki.h"

string JSONSki::runQuery(Records* records, string query) {
    QueryAutomaton qa;
    // update query automaton based on the specific JSONPath query
    JSONPathParser::updateQueryAutomaton(query, qa);
    // run query automaton
    StreamProcessor processor(records->text, records->rec_length[0], qa);
    return processor.runQuery();
}
