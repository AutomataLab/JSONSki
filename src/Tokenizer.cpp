#include "Tokenizer.h"
#include <iostream>
using namespace std;

int Tokenizer::getStringToken(int& pos) {
    while (pos < 64) {
        int escape_cnt = 0;
        while (pos < 64 &&mChunk[pos] == '\\') {
            ++escape_cnt;
            ++pos;
        }
        if (mChunk[pos] == '"') {
            ++pos;
            if (escape_cnt % 2 == 0) {
                mCurTknType = STRING;
                mNextTknPos = pos;
                return TRUE;
            }
        } else {
            ++pos;
        }
    }
    return END;
}

int Tokenizer::getStringToken1(int& pos) {
    while (pos < mLength) {
        int escape_cnt = 0;
        while (pos < mLength &&mChunk[pos] == '\\') {
            ++escape_cnt;
            ++pos;
        }
        if (mChunk[pos] == '"') {
            ++pos;
            if (escape_cnt % 2 == 0) {
                mCurTknType = STRING;
                mNextTknPos = pos;
                return TRUE;
            }
        } else {
            ++pos;
        }
    }
    return END;
}

int Tokenizer::hasNextToken() {
    if (mCurPos >= 64) return END;
    // current chunk starts inside string
    if (mCurPos == 0 && mStartState == IN) {
        int pos = mCurPos;
        return getStringToken(pos);
    }
    int pos = mCurPos;
    /*for (int i = 0; i < 64; ++i)
       cout<<mChunk[i];
    cout<<endl;
    cout<<"current pos "<<mCurPos<<" "<<mNextTknPos<<" "<<mChunk[pos]<<endl;
    */while (pos < 64) {
        switch(mChunk[pos]) {
            case '\t':
            case '\n':
                ++pos;
                break;
            case '{':
                ++pos;
                mCurTknType = LCB;
                mNextTknPos = pos;
                return TRUE;
            case '}':
                ++pos;
                mCurTknType = RCB;
                mNextTknPos = pos;
                return TRUE;
            case '[':
                ++pos;
                mCurTknType = LB;
                mNextTknPos = pos;
                return TRUE;
            case ']':
                ++pos;
                mCurTknType = RB;
                mNextTknPos = pos;
                return TRUE;
            case ',':
                ++pos;
                mCurTknType = COM;
                mNextTknPos = pos;
                return TRUE;
            case ':':
                ++pos;
                mCurTknType = COLON;
                mNextTknPos = pos;
                return TRUE;
            case '"':
                ++pos;
                return getStringToken(pos);
            case 't':
            {
                if (mChunk[pos + 1] == 'r' && mChunk[pos + 2] == 'u' && mChunk[pos + 3] == 'e') {
                    pos += 4;
                    mCurTknType = PRI;
                    mNextTknPos = pos; 
                    return TRUE;
                } else {
                    return ERROR;
                }
            }
            case 'r':
            {
                if (mChunk[pos + 2] == 'u' && mChunk[pos + 3] == 'e') {
                    pos += 3;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return TRUE;
                } else {
                    return ERROR;
                }
            }
            case 'e':
            {
               if (mChunk[pos + 1] == ',' || mChunk[pos + 1] == ']' || mChunk[pos + 1] == '}') {
                   ++pos;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else {
                   return ERROR;
               }
            } 
            case 'f':
            {
                if (mChunk[pos + 1] == 'a' && mChunk[pos + 2] == 'l' && mChunk[pos + 3] == 's' && mChunk[pos + 4] == 'e') {
                    pos += 5;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return TRUE;
                } else {
                    return ERROR;
                }
            }
            case 'a':
            {
                if (mChunk[pos + 1] == 'l' && mChunk[pos + 2] == 's' && mChunk[pos + 3] == 'e') {
                    pos += 4;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return TRUE;
                } else {
                    return ERROR;
                }
            }
            case 's':
            {
                if (mChunk[pos + 1] == 'e') {
                    pos += 2;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return TRUE;
                } else {
                    return ERROR;
                }
            } 
            case 'n':
            {
               if (mChunk[pos + 1] == 'u' && mChunk[pos + 2] == 'l' && mChunk[pos + 3] == 'l') {
                   pos += 4;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else {
                   return ERROR;
               }
            }
            case 'u':
            {
               if (mChunk[pos + 1] == 'l' && mChunk[pos + 2] == 'l') {
                   pos += 3;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else if (mChunk[pos + 1] == 'e') {
                   pos += 2;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else {
                   return ERROR;
               }
            }
            case 'l':
            {
               if (mChunk[pos + 1] == 'l' || mChunk[pos + 1] == ',' || mChunk[pos + 1] == ']' || mChunk[pos + 1] == '}') {
                   ++pos;
                   if (mChunk[pos] == 'l') ++pos;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else if (mChunk[pos + 1] == 's' && mChunk[pos + 2] == 'e') {
                   pos += 3;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return TRUE;
               } else {
                   return ERROR;
               }
            }
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
            {
                ++pos;
                char ch = mChunk[pos];
                if (ch == '}' || ch == ']' || ch == ' ' || ch == '\t' || ch == ',') {
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return TRUE;
                }
                if (ch == '"') {
                    return ERROR;
                }
                //cout<<"break "<<ch<<endl;
                break;
            }
            case ' ':
                ++pos;
                break;
            default:
                return ERROR;
        } 
    }
    //cout<<"END "<<endl;
    return END;
}

int Tokenizer::nextToken2() {
    mCurPos = mNextTknPos;
    return mCurTknType;
}

int Tokenizer::nextToken1() {
    // if (mCurPos >= 64) return END;
    // current chunk starts inside string
    /*if (mCurPos == 0 && mStartState == IN) {
        int pos = mCurPos;
        return getStringToken(pos);
    }*/
    // assume current cbunk starts outside string
    int pos = mCurPos;
    cout<<"pos "<<pos<<" "<<mLength<<" "<<mChunk[pos]<<endl;
    while (pos < mLength) {
        switch(mChunk[pos]) {
            case '\t':
            case '\n':
                ++pos;
                break;
            case '{':
                ++pos;
                mCurTknType = LCB;
                mCurPos = pos;
                return LCB;
            case '}':
                ++pos;
                mCurTknType = RCB;
                mCurPos = pos;
                return RCB;
            case '[':
                ++pos;
                mCurTknType = LB;
                mCurPos = pos;
                return LB;
            case ']':
                ++pos;
                mCurTknType = RB;
                mCurPos = pos;
                return RB;
            case ',':
                ++pos;
                mCurTknType = COM;
                mCurPos = pos;
                return COM;
            /*case ':':
                ++pos;
                mCurTknType = COLON;
                mNextTknPos = pos;
                return TRUE;*/
            case '"':
            {
                ++pos;
                int type = getStringToken1(pos);
                if (type != END) {
                    while (mChunk[pos] != ' ') {
                        ++pos;
                    }
                    if (pos < mLength) {
                        if (mChunk[pos] == ':') {
                            mCurTknType = KY;
                            ++pos;
                            mCurPos = pos;
                            return KY;
                        } else {
                            mCurTknType = PRI;
                            mCurPos = pos;
                            return PRI;
                        }
                    }
                    return PRI;
                }
                return END;
            }
            case 't':
            {
                if (mChunk[pos + 1] == 'r' && mChunk[pos + 2] == 'u' && mChunk[pos + 3] == 'e') {
                    pos += 4;
                    mCurTknType = PRI;
                    mCurPos = pos; 
                    return PRI;
                } else {
                    return ERROR;
                }
            }
            case 'r':
            {
                if (mChunk[pos + 2] == 'u' && mChunk[pos + 3] == 'e') {
                    pos += 3;
                    mCurTknType = PRI;
                    mCurPos = pos;
                    return PRI;
                } else {
                    return ERROR;
                }
            }
            case 'e':
            {
               if (mChunk[pos + 1] == ',' || mChunk[pos + 1] == ']' || mChunk[pos + 1] == '}') {
                   ++pos;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else {
                   return ERROR;
               }
            } 
            case 'f':
            {
                if (mChunk[pos + 1] == 'a' && mChunk[pos + 2] == 'l' && mChunk[pos + 3] == 's' && mChunk[pos + 4] == 'e') {
                    pos += 5;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return PRI;
                } else {
                    return ERROR;
                }
            }
            case 'a':
            {
                if (mChunk[pos + 1] == 'l' && mChunk[pos + 2] == 's' && mChunk[pos + 3] == 'e') {
                    pos += 4;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return PRI;
                } else {
                    return ERROR;
                }
            }
            case 's':
            {
                if (mChunk[pos + 1] == 'e') {
                    pos += 2;
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return PRI;
                } else {
                    return ERROR;
                }
            } 
            case 'n':
            {
               if (mChunk[pos + 1] == 'u' && mChunk[pos + 2] == 'l' && mChunk[pos + 3] == 'l') {
                   pos += 4;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else {
                   return ERROR;
               }
            }
            case 'u':
            {
               if (mChunk[pos + 1] == 'l' && mChunk[pos + 2] == 'l') {
                   pos += 3;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else if (mChunk[pos + 1] == 'e') {
                   pos += 2;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else {
                   return ERROR;
               }
            }
            case 'l':
            {
               if (mChunk[pos + 1] == 'l' || mChunk[pos + 1] == ',' || mChunk[pos + 1] == ']' || mChunk[pos + 1] == '}') {
                   ++pos;
                   if (mChunk[pos] == 'l') ++pos;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else if (mChunk[pos + 1] == 's' && mChunk[pos + 2] == 'e') {
                   pos += 3;
                   mCurTknType = PRI;
                   mNextTknPos = pos;
                   return PRI;
               } else {
                   return ERROR;
               }
            }
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
            {
                ++pos;
                char ch = mChunk[pos];
                if (ch == '}' || ch == ']' || ch == ' ' || ch == '\t' || ch == ',') {
                    mCurTknType = PRI;
                    mNextTknPos = pos;
                    return PRI;
                }
                if (ch == '"') {
                    return ERROR;
                }
                break;
            }
            case ' ':
                ++pos;
                break;
            default:
                return ERROR;
        } 
    }
    mCurPos = mNextTknPos;
    return END;    
}
