DIR = bin
EXEC = $(DIR)/jsonski
TARGET = $(EXEC)
all: $(TARGET)

CC = g++-7
CC_FLAGS = -O3 -std=c++11 -Ithird-party/include -mavx2 -mpclmul 
POST_FLAGS = -lpthread -mcmodel=medium -static-libstdc++

SOURCE = src/*.cpp demo/pison_test.cpp
$(EXEC): $(SOURCE)
	mkdir -p $(DIR)
	$(CC) $(CC_FLAGS) -o $(EXEC) $(SOURCE) $(POST_FLAGS)

clean:
	-$(RM) $(TARGET)
