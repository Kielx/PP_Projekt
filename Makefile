SOURCES=$(wildcard ./src/*.cpp) #Określamy jako źródła wszystkie pliki z rozszerzeniem .cpp znajdujące się w bieżącym folderze (./) przy użyciu operatora wildcard (*)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))
#Zmienna OBJECTS otrzymuje zwróconą wartość z funkcji patsubst

main:	$(OBJECTS) # Reguła main otrzymuje zmienną OBJECTS
#Generuje plik wyjsciowy z polaczonych plikow .o przy użyciu nazwy aktualnego targetu ($@), dodaje rozszerzenie .out
	g++ $^ -o $@.out -g -Wall --std=c++17 -lstdc++fs

$(OBJECTS):	./%.o : ./%.cpp
#Generuje pliki obiektowe przy użyciu nazwy aktualnego targetu ($@)
	g++ -c $< -o $@ -g -Wall --std=c++17 -lstdc++fs

docs:
	doxygen

run:
	./main.out

clean:
#Usuwa wszystkie wygenerowane pliki zostawiając tylko pliki źródłowe
	rm -f ./src/*.o
	rm -f ./*.out
	rm -rf doc