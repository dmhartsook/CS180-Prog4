CC = g++ -g
SOURCES = main.cpp Vector.cpp Ray.cpp ImagePlane.cpp

raytracer: $(SOURCES)
	$(CC) -o raytracer $(SOURCES)

clean: rm *.o raytracer