CC = g++ -g
SOURCES = main.cpp Vector.cpp Ray.cpp ImagePlane.cpp Sphere.cpp Object.cpp RGB.cpp Light.cpp InputFile.cpp Plane.cpp

raytracer: $(SOURCES)
	$(CC) -o raytracer $(SOURCES)

clean:
	rm -f *.o raytracer examples/*.ppm
