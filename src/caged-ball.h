#include <raylib.h>
#include <raymath.h>

/*
0 - Draw Points
1 - Draw Lines

*/

typedef struct Cage {
    int mode;
    Vector3 origin;
    Vector3 velocity;
    Vector3 rotation;
    Vector3 dimensions;
    float rotationAngle;
    float scale;
    
};

int caged_ball();

