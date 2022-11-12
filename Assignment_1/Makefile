CC = g++ -O2 -Wno-deprecated 

tag = -i

ifdef linux
tag = -n
endif

main: AvlTreeHelper.o AvlTree.o TreeNode.o main.o
	$(CC) -o main AvlTree.o TreeNode.o main.o -lfl

main.o: main.cc
	$(CC) -g -c main.cc

AvlTreeHelper.o: AvlTreeHelper.cc
	$(CC) -g -c AvlTreeHelper.cc

AvlTree.o: AvlTree.cc
	$(CC) -g -c AvlTree.cc

TreeNode.o: TreeNode.cc
	$(CC) -g -c TreeNode.cc

clean:
	rm -f *.o
	rm -f *.out