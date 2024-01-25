
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>


#define MAX 3
void displayButtons() {
    printf("\nAvailable Moves:\n");
    printf("U: Rotate Up\n");
    printf("D: Rotate Down\n");
    printf("R: Rotate Right\n");
    printf("L: Rotate Left\n");
    printf("F: Rotate Front\n");
    printf("Q: Quit\n");
}
void rotateFaceClockwise(char face[MAX][MAX]) {
    char temp[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            temp[i][j] = face[MAX - 1 - j][i];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            face[i][j] = temp[i][j];
        }
    }
}

void rotateFaceCounterClockwise(char face[MAX][MAX]) {
    char temp[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            temp[i][j] = face[j][MAX - 1 - i];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            face[i][j] = temp[i][j];
        }
    }
}

void initializeFace(char face[MAX][MAX], char color) {
    // Fill the face with the specified color
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            face[i][j] = color;
        }
    }
}

void printCube(char cube[6][MAX][MAX]) {
    char colors[] = {'W', 'G', 'R', 'B', 'O', 'Y'};

    for (int face = 0; face < 6; face++) {
        printf("\nFace %c:\n", colors[face]);
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                printf("%c ", cube[face][i][j]);
            }
            printf("\n");
        }
    }
}

SDL_Window* createWindow(const char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(1);
    }
    return window;
}

// Function to create a new SDL renderer
SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        exit(1);
    }
    return renderer;
}

// Function to draw the Rubik's Cube on the given renderer
void drawCube(SDL_Renderer* renderer, char cube[6][MAX][MAX]) {
 // Draw each face of the cube with black borders
int blockSize = 50; // Adjust the size of each block
int borderSize = 2; // Adjust the size of the border

for (int face = 0; face < 6; face++) {
    int startX = (face % 3) * (blockSize * MAX + borderSize);
    int startY = (face / 3) * (blockSize * MAX + borderSize);

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            // Set color based on the cube face color
            switch (cube[face][i][j]) {
                case 'W':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
                    break;
                case 'G':
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
                    break;
                case 'R':
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
                    break;
                case 'B':
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
                    break;
                case 'O':
                    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
                    break;
                case 'Y':
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
                    break;
                default:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black (default)
                    break;
            }

            // Draw a filled rectangle for each block
            SDL_Rect blockRect = {startX + j * (blockSize + borderSize),
                                  startY + i * (blockSize + borderSize),
                                  blockSize, blockSize};
            SDL_RenderFillRect(renderer, &blockRect);

            // Draw a black border around each block
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect borderRect = {startX + j * (blockSize + borderSize),
                                   startY + i * (blockSize + borderSize),
                                   blockSize, blockSize};
            SDL_RenderDrawRect(renderer, &borderRect);
        }
    }
}


    // Present the renderer
    SDL_RenderPresent(renderer);

    // Small delay for visualization
    SDL_Delay(500);
}
void rotateCubeU(char cube[6][MAX][MAX], int clockwise) {
    // Rotate the entire cube's U face
    if (clockwise) {
        rotateFaceClockwise(cube[0]);
    } else {
        rotateFaceCounterClockwise(cube[0]);
    }

    // Adjust adjacent faces accordingly
    char temp[MAX];
    if (clockwise) {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[1][0][i];
            cube[1][0][i] = cube[4][0][i];
            cube[4][0][i] = cube[3][0][i];
            cube[3][0][i] = cube[2][0][i];
            cube[2][0][i] = temp[i];
        }
    } else {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[2][0][i];
            cube[2][0][i] = cube[3][0][i];
            cube[3][0][i] = cube[4][0][i];
            cube[4][0][i] = cube[1][0][i];
            cube[1][0][i] = temp[i];
        }
    }
}

void rotateCubeD(char cube[6][MAX][MAX], int clockwise) {
    // Rotate the entire cube's D face
    if (clockwise) {
        rotateFaceClockwise(cube[5]);
    } else {
        rotateFaceCounterClockwise(cube[5]);
    }

    // Adjust adjacent faces accordingly
    char temp[MAX];
    if (clockwise) {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[1][MAX - 1][i];
            cube[1][MAX - 1][i] = cube[2][MAX - 1][i];
            cube[2][MAX - 1][i] = cube[3][MAX - 1][i];
            cube[3][MAX - 1][i] = cube[4][MAX - 1][i];
            cube[4][MAX - 1][i] = temp[i];
        }
    } else {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[4][MAX - 1][i];
            cube[4][MAX - 1][i] = cube[3][MAX - 1][i];
            cube[3][MAX - 1][i] = cube[2][MAX - 1][i];
            cube[2][MAX - 1][i] = cube[1][MAX - 1][i];
            cube[1][MAX - 1][i] = temp[i];
        }
    }
}

void rotateCubeR(char cube[6][MAX][MAX], int clockwise) {
    // Rotate the entire cube's R face
    if (clockwise) {
        rotateFaceClockwise(cube[4]);
    } else {
        rotateFaceCounterClockwise(cube[4]);
    }

    // Adjust adjacent faces accordingly
    char temp[MAX];
    if (clockwise) {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[0][i][MAX - 1];
            cube[0][i][MAX - 1] = cube[2][MAX - 1 - i][MAX - 1];
            cube[2][MAX - 1 - i][MAX - 1] = cube[5][MAX - 1 - i][0];
            cube[5][MAX - 1 - i][0] = cube[3][i][MAX - 1];
            cube[3][i][MAX - 1] = temp[i];
        }
    } else {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[2][MAX - 1 - i][MAX - 1];
            cube[2][MAX - 1 - i][MAX - 1] = cube[0][i][MAX - 1];
            cube[0][i][MAX - 1] = cube[3][i][MAX - 1];
            cube[3][i][MAX - 1] = cube[5][MAX - 1 - i][0];
            cube[5][MAX - 1 - i][0] = temp[i];
        }
    }
}

void rotateCubeL(char cube[6][MAX][MAX], int clockwise) {
    // Rotate the entire cube's L face
    if (clockwise) {
        rotateFaceClockwise(cube[2]);
    } else {
        rotateFaceCounterClockwise(cube[2]);
    }

    // Adjust adjacent faces accordingly
    char temp[MAX];
    if (clockwise) {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[0][i][0];
            cube[0][i][0] = cube[3][i][0];
            cube[3][i][0] = cube[5][MAX - 1 - i][MAX - 1];
            cube[5][MAX - 1 - i][MAX - 1] = cube[4][MAX - 1 - i][0];
            cube[4][MAX - 1 - i][0] = temp[i];
        }
    } else {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[3][i][0];
            cube[3][i][0] = cube[0][i][0];
            cube[0][i][0] = cube[2][MAX - 1 - i][MAX - 1];
            cube[2][MAX - 1 - i][MAX - 1] = cube[4][MAX - 1 - i][0];
            cube[4][MAX - 1 - i][0] = temp[i];
        }
    }
}

void rotateCubeF(char cube[6][MAX][MAX], int clockwise) {
    // Rotate the entire cube's F face
    if (clockwise) {
        rotateFaceClockwise(cube[1]);
    } else {
        rotateFaceCounterClockwise(cube[1]);
    }

    // Adjust adjacent faces accordingly
    char temp[MAX];
    if (clockwise) {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[0][MAX - 1][i];
            cube[0][MAX - 1][i] = cube[4][i][MAX - 1];
            cube[4][i][MAX - 1] = cube[5][0][MAX - 1 - i];
            cube[5][0][MAX - 1 - i] = cube[2][MAX - 1 - i][0];
            cube[2][MAX - 1 - i][0] = temp[i];
        }
    } else {
        for (int i = 0; i < MAX; i++) {
            temp[i] = cube[2][MAX - 1 - i][0];
            cube[2][MAX - 1 - i][0] = cube[5][0][MAX - 1 - i];
            cube[5][0][MAX - 1 - i] = cube[4][i][MAX - 1];
            cube[4][i][MAX - 1] = cube[0][MAX - 1][i];
            cube[0][MAX - 1][i] = temp[i];
        }
    }
}

  /* int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Rubik's Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    char cube[6][MAX][MAX];

    // Initialize each face with the corresponding color
    for (int i = 0; i < 6; i++) {
        initializeFace(cube[i], "WGRBOY"[i]);
    }

    char move, prevMove = '\0';
    printf("Enter moves (U, D, R, L, F) or 'Q' to quit:\n");

    int consecutiveMoves = 0;  // Count consecutive moves of the same type
    int clockwise = 1;         // Flag to determine rotation direction (1 for clockwise, 0 for counter-clockwise)

    do {
        // Draw current state
        drawCube(renderer, cube);

        // Read user input
        printf("\nEnter move (U, D, R, L, F, Q): ");
        scanf(" %c", &move);

        // Check if the move is different from the previous move
        if (move != 'U' && move != 'D' && move != 'R' && move != 'L' && move != 'F') {
            consecutiveMoves = 0;
            continue;
        }
do {
    // Draw current state
    drawCube(renderer, cube);

    // Read user input
    printf("\nEnter move (U, D, R, L, F, Q): ");
    scanf(" %c", &move);

    // Check if the move is different from the previous move
    if (move != 'U' && move != 'D' && move != 'R' && move != 'L' && move != 'F') {
        consecutiveMoves = 0;
        continue;
    }

    // Check if the move is the same as the previous move
    if (move == prevMove) {
        consecutiveMoves++;
    } else {
        consecutiveMoves = 1;
        clockwise = 1; // Reset rotation direction to clockwise for a new move
    }

    // Update the cube based on the user's move
    switch (move) {
        case 'U':
            rotateCubeU(cube, clockwise);
            break;
        case 'D':
            rotateCubeD(cube, clockwise);
            break;
        case 'R':
            rotateCubeR(cube, clockwise);
            break;
        case 'L':
            rotateCubeL(cube, clockwise);
            break;
        case 'F':
            rotateCubeF(cube, clockwise);
            break;
    }

    // Update the rotation direction for the next move
    clockwise = !clockwise;

    // Store the current move as the previous move
    prevMove = move;

    // Display the cube state after each move
    printf("Cube after move %c:\n", move);
    printCube(cube);

} while (move != 'Q');

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
 }
    return 0;


}*/
int main(int argc, char* argv[]) {
    
// Initialize SDL
if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
}

// Create the initial window and renderer
SDL_Window* window = createWindow("Rubik's Cube", 600, 600);
SDL_Renderer* renderer = createRenderer(window);

char cube[6][MAX][MAX];

// Initialize each face with the corresponding color
for (int i = 0; i < 6; i++) {
    initializeFace(cube[i], "WGRBOY"[i]);
}

char move, prevMove = '\0';
printf("Enter moves (U, D, R, L, F) or 'Q' to quit:\n");

int consecutiveMoves = 0;  // Count consecutive moves of the same type
int clockwise = 1;         // Flag to determine rotation direction (1 for clockwise, 0 for counter-clockwise)

do {
    // Draw current state in the initial window
    drawCube(renderer, cube);

    // Display available moves as buttons
    displayButtons();

    // Read user input
    printf("\nEnter move (U, D, R, L, F, Q): ");
    scanf(" %c", &move);

    // Check if the move is different from the previous move
    if (move != 'U' && move != 'D' && move != 'R' && move != 'L' && move != 'F') {
        consecutiveMoves = 0;
        continue;
    }

    // Check if the move is the same as the previous move
    if (move == prevMove) {
        consecutiveMoves++;
    } else {
        consecutiveMoves = 1;
        clockwise = 1; // Reset rotation direction to clockwise for a new move
    }

    // Update the cube based on the user's move
    switch (move) {
        case 'U':
            rotateCubeU(cube, clockwise);
            break;
        case 'D':
            rotateCubeD(cube, clockwise);
            break;
        case 'R':
            rotateCubeR(cube, clockwise);
            break;
        case 'L':
            rotateCubeL(cube, clockwise);
            break;
        case 'F':
            rotateCubeF(cube, clockwise);
            break;
    }

    // Update the rotation direction for the next move
    clockwise = !clockwise;

    // Store the current move as the previous move
    prevMove = move;

    // Draw the updated state in a new window for each move
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = createWindow("Rubik's Cube", 600, 600);
    renderer = createRenderer(window);
    drawCube(renderer, cube);

} while (move != 'Q');

// Clean up resources
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();

return 0;
}