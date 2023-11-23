all: test
test: 
	g++ -o test main.cpp 
install: 
	cp test ~/lab5/app
