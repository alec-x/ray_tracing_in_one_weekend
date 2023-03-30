image_creator: main.cpp color.h vec3.h ray.h
	g++ -o image_creator main.cpp -Wall

clean: 
	rm ./image_creator