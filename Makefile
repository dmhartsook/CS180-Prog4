CC = g++ -g
SOURCES = main.cpp Vector.cpp Ray.cpp ImagePlane.cpp Sphere.cpp Object.cpp

raytracer: $(SOURCES)
	$(CC) -o raytracer $(SOURCES)

clean: rm *.o raytracer