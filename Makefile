all:rbtree-tst

CFLAGS=-g -O0 -Wall
CXXFLAGS=-g -O0 -Wall

rbtree-tst:rbtree-tst.o linux_rbtree.o
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)


# rbtree-tst.o:rbtree-tst.cpp 

.PHONY:clean

clean:
	rm -rf *.o rbtree-tst
