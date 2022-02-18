#ifndef JSONSKI_H
#define JSONSKI_H

#include "JSONPathParser.h"
#include "StreamProcessor.h"
#include "../src/RecordLoader.h"
#include <string>
using namespace std;
// #include "SerialBitmap.h"
// #include "QueryAutomaton.h"

class JSONSki {
  public:
    static string runQuery(Records* rec, string query);
};
#endif
