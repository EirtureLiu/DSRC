all: example1 example2

INC_PATH = ../../include/dsrc
LIB_PATH = ../../lib/
LIB_JNI_PATH = /System/Library/Frameworks/JavaVM.framework/Headers
DSRC_LIB = -ldsrc

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INC_PATH) -I$(LIB_JNI_PATH)

example1: example1.o
	$(CXX) $(CXXFLAGS) -o $@ $? -L$(LIB_PATH) $(DSRC_LIB) $(DEP_LIBS)
	strip $@

example2: example2.o
	$(CXX) $(CXXFLAGS) -o $@ $? -L$(LIB_PATH) $(DSRC_LIB) $(DEP_LIBS)
	strip $@

dsrcimpl: dsrcimpl.o
	c++ -dynamiclib -o libdsrcjava.jnilib  dsrcimpl.o -L../../lib/ -ldsrc

clean:
	-rm *.o
	-rm example1
	-rm example2
