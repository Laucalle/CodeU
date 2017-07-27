GTEST_DIR = contrib/googletest/googletest
GTEST_SRCS = $(GTEST_DIR)/src/*.cc
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra --std=c++11

gtest-all.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) -I $(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

arrangement.o : arrangement.cpp arrangement.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c arrangement.cpp

arrangement_ut.o : arrangement_ut.cpp arrangement.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c arrangement_ut.cpp

parking_ui.o : parking_ui.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c parking_ui.cpp

unittest : arrangement.o arrangement_ut.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ -lpthread

clean :
	rm -rf *.o
	rm -rf *.a
