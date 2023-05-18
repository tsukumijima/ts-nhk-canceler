CXX=g++
CXXFLAGS=-std=c++17 -O2

TARGET=ts-nhk-canceler
SRCS=ts-nhk-canceler.cpp

OBJS=$(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
