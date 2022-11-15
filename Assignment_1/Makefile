CC = g++ -O2 -Wno-deprecated 

tag = -i

ifdef linux
tag = -n
endif

avltree: Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o avltree.o
	$(CC) -o avltree Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o avltree.o -lfl

avltree.o: avltree.cc
	$(CC) -g -c avltree.cc

main: Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o main.o
	$(CC) -o main Utils.o AvlTreeHelper.o AvlTreeImpl.o TreeNode.o main.o -lfl

main.o: main.cc
	$(CC) -g -c main.cc

Utils.o: Utils/Utils.cc
	$(CC) -g -c Utils/Utils.cc

AvlTreeHelper.o: Tree/AvlTreeHelper.cc
	$(CC) -g -c Tree/AvlTreeHelper.cc

AvlTreeImpl.o: Tree/AvlTreeImpl.cc
	$(CC) -g -c Tree/AvlTreeImpl.cc

TreeNode.o: Node/TreeNode.cc
	$(CC) -g -c Node/TreeNode.cc

clean:
	rm -f *.o
	rm -f *.out