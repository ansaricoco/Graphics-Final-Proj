#include <GL/glut.h>
#include <string>
#include <cmath>

// ------- SCREEN STATES -------
bool showBook = true;
bool showCouchScene = false;
bool showDialogue = false;
bool showToyScene = false;
bool showSellingScene = false;
bool showHomeCelebration = false;

// ------- TOY DATA -------
struct Toy {
    float x1, y1, x2, y2;
    bool selected;
};

Toy toys[4] = {
    {-0.7f, -0.2f, -0.4f, 0.1f, false},
    {-0.2f, -0.2f,  0.1f, 0.1f, false},
    { 0.3f, -0.2f,  0.6f, 0.1f, false},
    {-0.1f, -0.6f,  0.2f,-0.3f, false}
};

// ------- PEOPLE WALKING -------
float peoplePosX = -1.3f;
bool peopleActive = true;

// ---------------- TEXT RENDERING ----------------
void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
}

// ---------------- DRAW CIRCLE ----------------
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.f;
        glVertex2f(cx + std::cos(angle) * r, cy + std::sin(angle) * r);
    }
    glEnd();
}

// ---------------- BOOK SCENE ----------------
void drawBook() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Left page
    glColor3f(1.0f, 1.0f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, -1.0f);
    glVertex2f(-0.6f, 1.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, -1.0f);
    glEnd();

    // Right page
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.6f, 1.0f);
    glVertex2f(0.6f, -1.0f);
    glEnd();

    // Page division line
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();

    // Text
    glColor3f(0.1f, 0.1f, 0.1f);
    drawText(-0.50f, 0.0f, "Kevin's Christmas");
    drawText(0.10f, 0.0f, "Kevin's New Year");

    glutSwapBuffers();
}

void drawCircle2(float cx, float cy, float r) {
    int num_segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// ------------------------- DRAW DAD -------------------------
void drawDad(float x, float y) {

    // Hair (short, male style)
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle2(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle2(x, y + 0.25f, 0.12f);


    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle2(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle2(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
    // ----------------------------------------

    // Torso
    glColor3f(0.2f, 0.3f, 0.8f); // shirt
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.1f, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x - 0.1f, y + 0.2f);
    glEnd();

    // Left Arm
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.12f, y + 0.18f);
    glVertex2f(x - 0.1f, y + 0.18f);
    glVertex2f(x - 0.1f, y + 0.05f);
    glVertex2f(x - 0.12f, y + 0.05f);
    glEnd();

    // Right Arm
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.1f, y + 0.18f);
    glVertex2f(x + 0.12f, y + 0.18f);
    glVertex2f(x + 0.12f, y + 0.05f);
    glVertex2f(x + 0.1f, y + 0.05f);
    glEnd();

    // Legs
    glColor3f(0.1f, 0.1f, 0.1f); // pants
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.08f, y - 0.2f);
    glVertex2f(x - 0.02f, y - 0.2f);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x - 0.08f, y);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.02f, y - 0.2f);
    glVertex2f(x + 0.08f, y - 0.2f);
    glVertex2f(x + 0.08f, y);
    glVertex2f(x + 0.02f, y);
    glEnd();
}

// ------------------------- DRAW MOM -------------------------
void drawMom(float x, float y) {


    // Hair (long, female style)
    glColor3f(0.5f, 0.2f, 0.1f); // brown hair
    drawCircle2(x, y + 0.32f, 0.15f); // slightly bigger for long hair

    glBegin(GL_TRIANGLE_FAN); // hair sides
    glVertex2f(x, y + 0.25f);
    for (int i = 0; i <= 50; i++) {
        float theta = 3.1415926f * float(i) / 50.0f; // half circle down
        float x1 = 0.15f * cosf(theta);
        float y1 = 0.15f * sinf(theta);
        glVertex2f(x + x1, y + 0.25f + y1);
    }
    glEnd();
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle2(x, y + 0.25f, 0.12f);

    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle2(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle2(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
    // ----------------------------------------

    // Torso
    glColor3f(0.8f, 0.2f, 0.2f); // dress
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.1f, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x - 0.1f, y + 0.2f);
    glEnd();

    // Left Arm
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.12f, y + 0.18f);
    glVertex2f(x - 0.1f, y + 0.18f);
    glVertex2f(x - 0.1f, y + 0.05f);
    glVertex2f(x - 0.12f, y + 0.05f);
    glEnd();

    // Right Arm
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.1f, y + 0.18f);
    glVertex2f(x + 0.12f, y + 0.18f);
    glVertex2f(x + 0.12f, y + 0.05f);
    glVertex2f(x + 0.1f, y + 0.05f);
    glEnd();

    // Legs
    glColor3f(0.1f, 0.1f, 0.1f); // pants/shoes
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.08f, y - 0.2f);
    glVertex2f(x - 0.02f, y - 0.2f);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x - 0.08f, y);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.02f, y - 0.2f);
    glVertex2f(x + 0.08f, y - 0.2f);
    glVertex2f(x + 0.08f, y);
    glVertex2f(x + 0.02f, y);
    glEnd();
}


// ---------------- COUCH SCENE ----------------
void drawCouchScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    //COUCH MAIN CUSHION
    glColor3f(0.631f, 0.380f, 0.227f); //lighter brown
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, -0.2f);
    glVertex2f(0.7f, -0.2f);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(-0.7f, 0.2f);
    glEnd();
    //SIDE OF COUCH left
    glColor3f(0.439f, 0.255f, 0.141f); //darker brown
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.2f);
    glVertex2f(-0.9f, 0.3f);
    glVertex2f(-0.9f, 0.1f);
    glVertex2f(-0.9f, -0.2f);
    glVertex2f(-0.7f, -0.2f);
    glEnd();
    //side of couch right
    glColor3f(0.439f, 0.255f, 0.141f); //darker brown
    glBegin(GL_POLYGON);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.9f, 0.3f);
    glVertex2f(0.9f, 0.1f);
    glVertex2f(0.9f, -0.2f);
    glVertex2f(0.7f, -0.2f);
    glEnd();
    //top side of couch
    glColor3f(0.439f, 0.255f, 0.141f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, 0.2f);
    glVertex2f(0.7f, 0.2f);
    glVertex2f(0.7f, 0.4f);
    glVertex2f(-0.7f, 0.4f);
    glEnd();

    // parents
    drawDad(-0.3f, 0.2f); // left side
    drawMom(0.3f, 0.2f);  // right side
    //emotion mouth
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.29f, 0.41f);
    glVertex2f(-0.30f, 0.42f);
    glVertex2f(-0.31f, 0.41f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.29f, 0.41f);
    glVertex2f(0.30f, 0.42f);
    glVertex2f(0.31f, 0.41f);
    glEnd();



    // Text
    glColor3f(0.1f, 0.1f, 0.1f);
    if (!showDialogue)
        drawText(-0.45f, -0.6f, "Press ENTER to find out why they are sad...");
    else {
        drawText(-0.9f, -0.6f, "Parents: Kevin, we are short on money.");
        drawText(-0.9f, -0.7f, "We won't be able to celebrate Christmas. We're so sorry.");
        drawText(-0.4f, -0.9f, "Press ENTER to continue...");
    }

    glutSwapBuffers();
}

// ---------------- TOY SELECTION SCENE ----------------
void drawToyScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Floor
    glColor3f(0.8f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Kevin's hands
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(-0.3f, -0.9f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(-0.8f, -0.6f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.9f, -0.9f);
    glVertex2f(0.3f, -0.9f);
    glVertex2f(0.4f, -0.6f);
    glVertex2f(0.8f, -0.6f);
    glEnd();

    // Draw toys
    for (int i = 0; i < 4; i++) {
        if (toys[i].selected)
            glColor3f(0.1f, 0.8f, 0.2f);
        else
            glColor3f(0.2f, 0.3f, 0.9f);

        glBegin(GL_POLYGON);
        glVertex2f(toys[i].x1, toys[i].y1);
        glVertex2f(toys[i].x2, toys[i].y1);
        glVertex2f(toys[i].x2, toys[i].y2);
        glVertex2f(toys[i].x1, toys[i].y2);
        glEnd();
    }

    drawText(-0.6f, 0.8f, "Kevin: I'm going to sell my toys...");
    drawText(-0.7f, 0.7f, "Click on the toys to select them.");

    glutSwapBuffers();
}

// ---------------- DRAW PEOPLE ----------------
void drawPeople(float x) {
    glColor3f(0.0f, 0.0f, 0.0f);

    // Head
    drawCircle(x, 0.25f, 0.07f);

    // Body
    glBegin(GL_LINES);
    glVertex2f(x, 0.18f); glVertex2f(x, -0.1f);

    // Arms
    glVertex2f(x - 0.1f, 0.05f);
    glVertex2f(x + 0.1f, 0.05f);

    // Legs
    glVertex2f(x, -0.1f);
    glVertex2f(x - 0.08f, -0.35f);

    glVertex2f(x, -0.1f);
    glVertex2f(x + 0.08f, -0.35f);

    glEnd();
}

// ---------------- SELLING SCENE ----------------
void drawSellingScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Table
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -0.3f);
    glVertex2f(0.8f, -0.3f);
    glVertex2f(0.8f, -0.5f);
    glVertex2f(-0.8f, -0.5f);
    glEnd();

    // Kevin
    glColor3f(1.0f, 0.8f, 0.6f); drawCircle(0.0f, 0.3f, 0.15f); // head
    glColor3f(0.2f, 0.4f, 0.9f); // shirt
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(-0.2f, -0.2f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f); // legs
    glBegin(GL_LINES);
    glVertex2f(-0.1f, -0.2f); glVertex2f(-0.1f, -0.6f);
    glVertex2f(0.1f, -0.2f);  glVertex2f(0.1f, -0.6f);
    glEnd();

    // Sign
    drawText(-0.28f, 0.85f, "TOYS FOR SALE");

    // Selected toys on table
    for (int i = 0; i < 4; i++) {
        if (toys[i].selected) {
            glColor3f(0.2f, 0.3f, 0.9f);
            glBegin(GL_POLYGON);
            glVertex2f(toys[i].x1, -0.3f);
            glVertex2f(toys[i].x2, -0.3f);
            glVertex2f(toys[i].x2, -0.1f);
            glVertex2f(toys[i].x1, -0.1f);
            glEnd();
        }
    }

    // People walking past
    if (peopleActive) {
        drawPeople(peoplePosX);
        drawPeople(peoplePosX + 0.4f);
    }

    drawText(-0.65f, -0.9f, "He goes on to sell, but people only passed by...");

    glutSwapBuffers();
}

// ---------------- HOME CELEBRATION SCENE ----------------
void drawHomeCelebration() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Background
    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Parents standing (smiling)
    glColor3f(1.0f, 0.8f, 0.6f); // heads
    drawCircle(-0.5f, 0.3f, 0.12f);
    drawCircle(0.5f, 0.3f, 0.12f);

    // Parents bodies
    glColor3f(0.2f, 0.5f, 0.2f); // clothes
    glBegin(GL_POLYGON);
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.4f, -0.2f);
    glVertex2f(-0.6f, -0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.6f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glEnd();


    // Gift box on table
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // ribbon
    glBegin(GL_LINES);
    glVertex2f(-0.2f, 0.05f); glVertex2f(0.2f, 0.05f);
    glVertex2f(0.0f, -0.1f); glVertex2f(0.0f, 0.2f);
    glEnd();

    // Kevin
    glColor3f(1.0f, 0.8f, 0.6f); drawCircle(0.0f, -0.3f, 0.15f); // head
    glColor3f(0.2f, 0.4f, 0.9f); // shirt
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.4f);
    glVertex2f(0.2f, -0.4f);
    glVertex2f(0.2f, -0.7f);
    glVertex2f(-0.2f, -0.7f);
    glEnd();

    // Text
    glColor3f(0.1f, 0.1f, 0.1f);
    drawText(-0.85f, 0.8f, "He goes home to see his parents actually surprised him with a gift and celebration");

    glutSwapBuffers();
}

// ---------------- MOUSE EVENTS ----------------
void mouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    // Book click
    if (showBook) {
        float oglX = (float)x / 1000.0f * 2.0f - 1.0f;
        if (oglX >= -0.6f && oglX <= 0.0f) {
            showBook = false;
            showCouchScene = true;
        }
        glutPostRedisplay();
        return;
    }

    // Toy clicks
    if (showToyScene) {
        float oglX = (float)x / 1000.0f * 2.0f - 1.0f;
        float oglY = ((float)(1000 - y)) / 1000.0f * 2.0f - 1.0f;

        for (int i = 0; i < 4; i++) {
            if (oglX >= toys[i].x1 && oglX <= toys[i].x2 &&
                oglY >= toys[i].y2 && oglY <= toys[i].y1)
            {
                toys[i].selected = !toys[i].selected;
                glutPostRedisplay();
                return;
            }
        }
    }
}

// ---------------- PEOPLE TIMER ----------------
void updatePeople(int value) {
    if (peopleActive) {
        peoplePosX += 0.005f;
        if (peoplePosX > 1.5f) peoplePosX = -1.3f;
        glutPostRedisplay();
        glutTimerFunc(30, updatePeople, 0);
    }
}

// ---------------- KEYBOARD ----------------
void keyPressed(unsigned char key, int x, int y) {
    if (key == 13) {  // ENTER
        if (showCouchScene && !showDialogue) {
            showDialogue = true;
        }
        else if (showCouchScene && showDialogue) {
            showCouchScene = false;
            showDialogue = false;
            showToyScene = true;
        }
        else if (showToyScene) {
            showToyScene = false;
            showSellingScene = true;
            peopleActive = true;
            glutTimerFunc(30, updatePeople, 0);
        }
        else if (showSellingScene) {
            showSellingScene = false;
            showHomeCelebration = true;
            peopleActive = false;
        }
        glutPostRedisplay();
    }
}

// ---------------- DISPLAY ----------------
void display() {
    if (showBook)                 drawBook();
    else if (showCouchScene)      drawCouchScene();
    else if (showToyScene)        drawToyScene();
    else if (showSellingScene)    drawSellingScene();
    else if (showHomeCelebration) drawHomeCelebration();
}

// ---------------- INIT ----------------
void init() {
    glClearColor(0.85f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// ---------------- MAIN ----------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Kevin's Story");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
    return 0;
}
