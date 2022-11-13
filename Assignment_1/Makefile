CC = g++ -O2 -Wno-deprecated 

tag = -i

ifdef linux
tag = -n
endif

avltree: Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o avltree.o
	$(CC) -o avltree Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o avltree.o -lfl

avltree.o: avltree.cc
	$(CC) -g -c avltree.cc

Utils.o: Utils.cc
	$(CC) -g -c Utils.cc

AvlTreeHelper.o: AvlTreeHelper.cc
	$(CC) -g -c AvlTreeHelper.cc

AvlTreeImpl.o: AvlTreeImpl.cc
	$(CC) -g -c AvlTreeImpl.cc

TreeNode.o: TreeNode.cc
	$(CC) -g -c TreeNode.cc

clean:
	rm -f *.o
	rm -f *.out