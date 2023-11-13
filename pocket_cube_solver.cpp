#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
enum {
    RED = 0,
    BLUE = 1,
    WHITE = 2,
    YELLOW = 3,
    GREEN = 4,
    ORANGE = 5
  
};

char color(int cc){
    switch (cc)
    {
    case RED:
        return 'R';
        break;
    case BLUE:
        return 'B';
        break;
    case ORANGE:
        return 'O';
        break;
    case GREEN:
        return 'G';
        break;
    case WHITE:
        return 'W';
        break;
    
    default:
        return 'Y';
        break;
    }
}


typedef char face[2][2];
typedef struct {
    face f0;
    face f1;
    face f2;
    face f3;
    face f4;
    face f5;
} cube_t;


// void init_cube(cube_t* cube) {
//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 2; j++) {
//             cube->f0[i][j] = color(RED);
//             cube->f1[i][j] = color(BLUE);
//             cube->f2[i][j] = color(WHITE);
//             cube->f3[i][j] = color(YELLOW);
//             cube->f4[i][j] = color(GREEN);
//             cube->f5[i][j] = color(ORANGE);
//         }
//     }
// }

void init_cube(cube_t* cube) {
    // Initialize the cube with default colors
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cube->f0[i][j] = color(RED);
            cube->f1[i][j] = color(BLUE);
            cube->f2[i][j] = color(WHITE);
            cube->f3[i][j] = color(YELLOW);
            cube->f4[i][j] = color(GREEN);
            cube->f5[i][j] = color(ORANGE);
        }
    }
}
void clockwise(face of,face cf){

    for (int i = 0; i < 2; i++)

    {
        for (int j = 0; j < 2; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[1][0];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[0][0];
                break;
                }
                else{
                    of[i][j] = cf[1][1];
                    break;
                }
                
            case 2:
                
                of[i][j]= cf[0][1];
                break;
            
            }
        }
        
    }
    
}
void anticlockwise(face of,face cf){

    for (int i = 0; i < 2; i++)

    {
        for (int j = 0; j < 2; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[0][1];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[1][1];
                break;
                }
                else{
                    of[i][j] = cf[0][0];
                    break;
                }
                
            case 2:
                
                of[i][j]= cf[1][0];
                break;
            
            }
        }
        
    }
    
}

void printcube(cube_t* cube) {
    printf("Face 0 Front face: %c %c\n", cube->f0[0][0], cube->f0[0][1]);
    printf("                   %c %c\n", cube->f0[1][0], cube->f0[1][1]);
    printf("Face 1 Top face:   %c %c\n", cube->f1[0][0], cube->f1[0][1]);
    printf("                   %c %c\n", cube->f1[1][0], cube->f1[1][1]);
    printf("Face 2 Left face:  %c %c\n", cube->f2[0][0], cube->f2[0][1]);
    printf("                   %c %c\n", cube->f2[1][0], cube->f2[1][1]);
    printf("Face 3 Right face: %c %c\n", cube->f3[0][0], cube->f3[0][1]);
    printf("                   %c %c\n", cube->f3[1][0], cube->f3[1][1]);
    printf("Face 4 Bottom face:%c %c\n", cube->f4[0][0], cube->f4[0][1]);
    printf("                   %c %c\n", cube->f4[1][0], cube->f4[1][1]);
    printf("Face 5 Back Face:  %c %c\n", cube->f5[0][0], cube->f5[0][1]);
    printf("                   %c %c\n", cube->f5[1][0], cube->f5[1][1]);
}

void move_R(cube_t* cube) {
    // Save a temporary copy of the affected faces
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    // Copy the current state of the faces
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    // Perform the R move (right face clockwise)
    for (int i = 0; i < 2; i++) {
        cube->f0[i][1] = temp_f4[i][1];
        cube->f1[i][1] = temp_f0[i][1];
        cube->f4[i][1] = temp_f5[i][0];
        cube->f5[i][0] = temp_f1[1-i][1];
    }
    clockwise(cube->f3,temp_f3);
}

void move_Ri(cube_t* cube) {
    // Save a temporary copy of the affected faces
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    // Copy the current state of the faces
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    for (int i = 0; i < 2; i++) {
        cube->f0[i][1] = temp_f1[i][1];
        cube->f1[i][1] = temp_f5[1-i][0];
        cube->f4[i][1] = temp_f0[i][1];
        cube->f5[i][0] = temp_f4[1-i][1];
    }
    anticlockwise(cube->f3,temp_f3);
}


void move_U(cube_t* cube) {
    
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    
    for (int i = 0; i < 2; i++) {
        cube->f0[0][i] = temp_f3[0][i];
        cube->f2[0][i] = temp_f0[0][i];
        cube->f3[0][i] = temp_f5[0][i];
        cube->f5[0][i] = temp_f2[0][i];
    }
    clockwise(cube->f1,temp_f1);
}

void move_Ui(cube_t* cube) {
    
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    anticlockwise(cube->f1,temp_f1);
    for (int i = 0; i < 2; i++) {
        cube->f0[0][i] = temp_f2[0][i];
        cube->f2[0][i] = temp_f5[0][i];
        cube->f3[0][i] = temp_f0[0][i];
        cube->f5[0][i] = temp_f3[0][i];
    }
    
}
void move_F(cube_t* cube) {
    
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    clockwise(cube->f0,temp_f0);
    for (int i = 0; i < 2; i++) {
        cube->f1[1][i] = temp_f2[1-i][1];
        cube->f2[i][1] = temp_f4[0][i];
        cube->f3[i][0] = temp_f1[1][i];
        cube->f4[0][i] = temp_f3[1-i][0];
    }
    
}
void move_Fi(cube_t* cube) {
    
    face temp_f0, temp_f1, temp_f2, temp_f3, temp_f4, temp_f5;

    
    memcpy(temp_f0, cube->f0, sizeof(face));
    memcpy(temp_f1, cube->f1, sizeof(face));
    memcpy(temp_f2, cube->f2, sizeof(face));
    memcpy(temp_f3, cube->f3, sizeof(face));
    memcpy(temp_f4, cube->f4, sizeof(face));
    memcpy(temp_f5, cube->f5, sizeof(face));

    anticlockwise(cube->f0,temp_f0);
    for (int i = 0; i < 2; i++) {
        cube->f1[1][i] = temp_f3[i][0];
        cube->f2[i][1] = temp_f1[1][1-i];
        cube->f3[i][0] = temp_f4[0][1-i];
        cube->f4[0][i] = temp_f2[i][1];
    }
    
}

void move_R2(cube_t* cube){
    move_R(cube);
    move_R(cube);
}
void move_U2(cube_t* cube){
    move_U(cube);
    move_U(cube);
}
void move_F2(cube_t* cube){
    move_F(cube);
    move_F(cube);
}

int complete(cube_t* cube){
    char x= cube->f0[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f0[i][j] != x){
                return 0;
            }
        }
        
    }
    char y= cube->f1[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f1[i][j] != y){
                return 0;
            }
        }
        
    }
    char z= cube->f2[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f2[i][j] != z){
                return 0;
            }
        }
        
    }
    char a= cube->f3[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f3[i][j] != a){
                return 0;
            }
        }
        
    }
    char b= cube->f4[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f4[i][j] != b){
                return 0;
            }
        }
        
    }
    char c= cube->f5[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f5[i][j] != c){
                return 0;
            }
        }
        
    }

    return 1;
     
}

typedef struct CubeState {
    cube_t cube;
    char moves[50]; // To store the sequence of moves to reach this state
} CubeState;

typedef struct QueueNode {
    CubeState state;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueue(Queue* queue, CubeState state) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->state = state;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

CubeState dequeue(Queue* queue) {
    if (queue->front == NULL) {
        CubeState emptyState;
        return emptyState;
    }
    CubeState state = queue->front->state;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return state;
}

bool isSolved(cube_t* cube) {
    // Check if all faces are solved (all the same color)
    return complete(cube);
}

void solvePocketCube(cube_t* initialCube, int * count) {
    Queue queue;
    initQueue(&queue);
    int a =1;
    CubeState initialState;
    initialState.cube = *initialCube;
    memset(initialState.moves, 0, sizeof(initialState.moves));

    enqueue(&queue, initialState);
    
    while (queue.front) {
        CubeState curr_state = dequeue(&queue);
        
        if (isSolved(&curr_state.cube)) {
            
            printf("Solved! Sequence of moves: %s\n", curr_state.moves);
            return;
        }
        CubeState next_state = curr_state;
        
        strcat(next_state.moves, "R ");
        move_R(&next_state.cube);
        enqueue(&queue, next_state);
        
        
        CubeState next_state1 = curr_state;
        strcat(next_state1.moves, "U ");
        move_U(&next_state1.cube);
        enqueue(&queue, next_state1);
        

        CubeState next_state3 = curr_state;
        strcat(next_state3.moves, "F ");
        move_F(&next_state3.cube);
        enqueue(&queue, next_state3);

        CubeState next_state4 = curr_state;
        strcat(next_state4.moves, "Ri ");
        move_Ri(&next_state4.cube);
        enqueue(&queue, next_state4);

        CubeState next_state5 = curr_state;
        strcat(next_state5.moves, "Ui ");
        move_Ui(&next_state5.cube);
        enqueue(&queue, next_state5);

        CubeState next_state6 = curr_state;
        strcat(next_state6.moves, "Fi ");
        move_Fi(&next_state6.cube);
        enqueue(&queue, next_state6);

        CubeState next_state7 = curr_state;
        strcat(next_state7.moves, "R2 ");
        move_R2(&next_state7.cube);
        enqueue(&queue, next_state7);

        CubeState next_state8 = curr_state;
        strcat(next_state8.moves, "U2 ");
        move_U2(&next_state8.cube);
        enqueue(&queue, next_state8);

        CubeState next_state2 = curr_state;
        strcat(next_state2.moves, "F2 ");
        move_F2(&next_state2.cube);
        enqueue(&queue, next_state2);
        
        a+=9;

       
    }

    printf("Unable to solve the Pocket Cube.\n");
}

int main(int argc, char const *argv[]) {
    cube_t cube;
    int count= 0;
    init_cube(&cube);
    // move_R2(&cube);
    // move_Fi(&cube);
    // move_Ui(&cube);
    // move_Fi(&cube);
    // move_F(&cube);
    // move_Ui(&cube);
    // move_R(&cube);    
    // move_Ri(&cube);    
    // move_U2(&cube);
    // move_F(&cube);
    // move_R2(&cube);
    // printcube(&cube);

    // // Solve the Pocket Cube
    printf("Calculating moves....");
    solvePocketCube(&cube,&count);
    
    return 0;
}
