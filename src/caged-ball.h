#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <stdio.h>
/*
0 - Draw Points
1 - Draw Lines

*/

enum DrawMode {
    CUBE_LINES,
    CUBE_POINTS,

};

typedef struct Cage {
    int mode;
    Vector3 origin;
    Vector3 velocity;
    Vector3 rotation;
    Vector3 points[8];
    float rotationAngle;
    float scale;
    Color color;
} Cage;

int caged_ball();

Cage BuildCage(Vector3 origin, Vector3 dimensions, Color color, int mode);

Cage UpdateCage(Cage* cage);

void DrawCage(Cage* cage);

Camera DefaultCamera(int type, Vector3 sceneOrigin, Vector3 posRelToOrigin);