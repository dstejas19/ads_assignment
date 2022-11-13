CC = g++ -O2 -Wno-deprecated 

tag = -i

ifdef linux
tag = -n
endif

main: AvlTreeHelper.o AvlTreeImpl.o TreeNode.o main.o
	$(CC) -o main AvlTreeHelper.o AvlTreeImpl.o TreeNode.o main.o -lfl

main.o: main.cc
	$(CC) -g -c main.cc

AvlTreeHelper.o: AvlTreeHelper.cc
	$(CC) -g -c AvlTreeHelper.cc

AvlTreeImpl.o: AvlTreeImpl.cc
	$(CC) -g -c AvlTreeImpl.cc

TreeNode.o: TreeNode.cc
	$(CC) -g -c TreeNode.cc

clean:
	rm -f *.o
	rm -f *.out