CC = g++ -g
SOURCES = main.cpp

raytracer: $(SOURCES)
	$(CC) -o raytracer $(SOURCES)

clean: rm *.o raytracer