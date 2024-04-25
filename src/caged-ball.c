#include "caged-ball.h"



const int WIDTH = 640;
const int HEIGHT = 640;
const char* TITLE = "CagedBall";
const int FPS = 60;

Cage BuildCage(Vector3 origin, Vector3 dimensions, Color color, int mode){
    float xDim = fabsf(dimensions.x/2);
    float yDim = fabsf(dimensions.y/2);
    float zDim = fabsf(dimensions.z/2);

    Vector3 points[8] = {
        { xDim,  yDim,  zDim},
        {-xDim,  yDim,  zDim},
        {-xDim, -yDim,  zDim},
        { xDim, -yDim,  zDim},
        { xDim,  yDim, -zDim},
        {-xDim,  yDim, -zDim},
        {-xDim, -yDim, -zDim},
        { xDim, -yDim, -zDim}
    };

    Cage newCage;

    newCage.mode = mode;
    newCage.origin = origin;
    newCage.velocity = (Vector3){0.0f, 0.0f, 0.0f};
    newCage.rotation = (Vector3){0.0f, 0.0f, 0.0f};
    newCage.rotationAngle = 0.0f;
    newCage.scale = 1.0f;
    newCage.color = color;
    for (unsigned short i = 0; i < 8; i++){
        newCage.points[i] = points[i];
        Vector3 pos = points[i];
        printf("x: %.3f y: %.3f z: %.3f\n", pos.x, pos.y, pos.z);
    }

    return newCage;
}


void DrawCage(Cage* cage){
    switch (cage->mode)
    {
    case CUBE_POINTS:
        for (unsigned short i = 0; i < 8; i++){
            // Vector3 pos = Vector3Add(cage->origin, cage->points[i]);
            // printf("x: %.3f y: %.3f z: %.3f\n", pos.x, pos.y, pos.z);
            // DrawPoint3D(pos, cage->color);
            DrawPoint3D(cage->points[i], cage->color);
            // DrawCircle3D(pos, 0.05f, (Vector3){0.0f, 0.0f, 0.0f}, 0.0f, cage->color);
        }
        break;
    // case CUBE_LINES:
        // DrawLine3D()
    
    default:
        break;
    }
}

Camera DefaultCamera(int type, Vector3 sceneOrigin, Vector3 posRelToOrigin){
    Camera camera;
    camera.position = Vector3Add(sceneOrigin, posRelToOrigin);
    camera.target = sceneOrigin;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    switch (type) {
        case CAMERA_ORTHOGRAPHIC:
            camera.fovy = 10.0f;
            camera.projection = CAMERA_ORTHOGRAPHIC;
            break;
        case CAMERA_PERSPECTIVE: 
            camera.fovy = 45.0f;
            camera.projection = CAMERA_PERSPECTIVE;
            break;
        default:
            break;
    }
    return camera;
}

int caged_ball(){
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS); 

    Vector3 sceneOrigin = {0.0f, 0.0f, 0.0f};
    Vector3 cameraPos = {0.0f, 0.0f, -5.0f};
    Camera cam1 = DefaultCamera(CAMERA_ORTHOGRAPHIC, sceneOrigin, cameraPos);
    printf("x: %.3f y: %.3f z: %.3f\n", sceneOrigin.x, sceneOrigin.y, sceneOrigin.z);
    Camera cam2 = DefaultCamera(CAMERA_PERSPECTIVE, sceneOrigin, cameraPos);

    Cage cage = BuildCage(sceneOrigin, (Vector3){1.5f, 1.5f, 1.5f}, WHITE, CUBE_POINTS);
    Camera* activeCam = &cam1;
    int aCamIdx = 1;
    char aCamName[32];
    strcpy(aCamName, "ORTHOGRAPHIC");
    while(!WindowShouldClose()){
        if (IsKeyPressed(KEY_ONE)) {
            strcpy(aCamName, "ORTHOGRAPHIC");
            activeCam = &cam1;
        }
        if (IsKeyPressed(KEY_TWO)) {
            strcpy(aCamName, "PERSPECTIVE");
            activeCam = &cam2;
        }


        // Perform transforms on cage


        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(aCamName, 50, 50, 12, WHITE);
            BeginMode3D(*activeCam);
                DrawCage(&cage);
                // DrawCube(sceneOrigin, 1.0f, 1.0f, 1.0f, WHITE);
            EndMode3D();
        EndDrawing();
    }
        


    CloseWindow();
}