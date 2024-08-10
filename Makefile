CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

todo_app: src/main.o
	$(CXX) $(CXXFLAGS) -o todo_app src/main.o

clean:
	rm -f src/*.o todo_app
