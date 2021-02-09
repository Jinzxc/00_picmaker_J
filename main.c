#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#define B_SIZE 100
#define WIDTH 500
#define HEIGHT 500

int function(int x) 
{
    return abs((int)(255 * sin(2 * sin(2 * sin(2 * sin(x))))));
}

int main() 
{
    int fd;
    char buffer[B_SIZE];
    int x, y;
	
    fd = open ("graph.ppm", O_CREAT | O_WRONLY, 0644);
    snprintf(buffer, B_SIZE - 1, "P3 %d %d 255\n", WIDTH, HEIGHT);
    write(fd, buffer, strlen(buffer));

    for(int x = 0; x < WIDTH + 1; x++) {
        for(int y = 0; y < HEIGHT + 1; y++) {
            if(abs(x - y) < 150) {
                snprintf(buffer, B_SIZE - 1, "%d %d %d ", function(x), function(y), 255);
            } else if (abs(x - y) > 350){
                snprintf(buffer, B_SIZE - 1, "%d %d %d ", 255, function(x), function(y));
            } else {
                snprintf(buffer, B_SIZE - 1, "%d %d %d ", function(x), 255, function(y));
            }
            write(fd, buffer, strlen(buffer));
        }
    }
    
    close (fd);
    return 0;
}