CROSS_COMPILE=

CC=$(CROSS_COMPILE)g++
# CFLAGS=-c -g -rdynamic -funwind-tables -Wall -I./
CFLAGS=-c -std=c++11 -g -rdynamic -funwind-tables -I./
LDFLAGS=   -lpthread -lrt

STRIP=$(CROSS_COMPILE)strip

# SOURCES= 04_casting.cpp

OBJECTS=$(SRC:.cpp=.o)

TARGET=exe_app

all: $(SRC) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 
# 	$(STRIP) $(TARGET)
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o $(TARGET)
