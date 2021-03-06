CC = g++ -g
SOURCES = main.cpp Vector.cpp Ray.cpp ImagePlane.cpp Sphere.cpp Object.cpp RGB.cpp Light.cpp InputFile.cpp Plane.cpp \
 Texture.cpp Ppm.cpp

raytracer: $(SOURCES)
	$(CC) -o raytracer $(SOURCES) -std=c++11

clean:
	rm -f *.o raytracer examples/*.ppm
