#ifndef _RECORDLOADER_H
#define _RECORDLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <malloc.h>
#include <sys/time.h>
#include <sys/file.h>
#include <unistd.h>
#include <sched.h>
#include <iostream>
#include <string>
#include "Records.h"
using namespace std;

class RecordLoader{
  private:
    char* mFilePath;
      
  public:
    RecordLoader(char* file_path);
    char* loadRecord();
    Records* loadSingleRecord();
    Records* loadRecords();
};
#endif
