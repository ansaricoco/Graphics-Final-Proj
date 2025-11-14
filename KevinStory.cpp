#include <GL/glut.h>
#include <string>
#include <cmath>

//states/scenes
bool showBook = true;
bool showCouchScene = false;
bool showDialogue = false;
bool showToyScene = false;
bool showSellingScene = false;
bool showHomeCelebration = false;

// walking animation
float peoplePosX = -1.3f;
bool peopleActive = true;

// drawtext function
void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
}

//drawCircle for heads
void drawCircle(float cx, float cy, float r) {
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

//to make scaling fix
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Always use square coordinates
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scale X to correct stretching
    float aspect = (float)w / (float)h;
    glScalef(1.0f / aspect, 1.0f, 1.0f);
}



// book scene
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

//ELEMENTS
void drawTable(float x, float y) {
    // Table top
    glColor3f(0.55f, 0.27f, 0.07f); // brown
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.3f, y);
    glVertex2f(x + 0.3f, y);
    glVertex2f(x + 0.3f, y + 0.05f);
    glVertex2f(x - 0.3f, y + 0.05f);
    glEnd();

    // Left leg
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.28f, y - 0.2f);
    glVertex2f(x - 0.23f, y - 0.2f);
    glVertex2f(x - 0.23f, y);
    glVertex2f(x - 0.28f, y);
    glEnd();

    // Right leg
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.23f, y - 0.2f);
    glVertex2f(x + 0.28f, y - 0.2f);
    glVertex2f(x + 0.28f, y);
    glVertex2f(x + 0.23f, y);
    glEnd();
}


// dad
void drawDad(float x, float y) {

    // Hair (short, male style)
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);


    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
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
//kevin
void drawKevin(float x, float y) {
    // Hair (short, male style)
    glColor3f(0.980f, 0.804f, 0.420f); // blonde
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
    // ----------------------------------------

    // ----------------- MOUTH -----------------
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();
    // -----------------------------------------

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
    glVertex2f(x - 0.08f, y - 0.1f);
    glVertex2f(x - 0.02f, y - 0.1f);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x - 0.08f, y);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(x + 0.02f, y - 0.1f);
    glVertex2f(x + 0.08f, y - 0.1f);
    glVertex2f(x + 0.08f, y);
    glVertex2f(x + 0.02f, y);
    glEnd();
}


// mom
void drawMom(float x, float y) {


    // Hair (long, female style)
    glColor3f(0.5f, 0.2f, 0.1f); // brown hair
    drawCircle(x, y + 0.32f, 0.15f); // slightly bigger for long hair

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
    drawCircle(x, y + 0.25f, 0.12f);

    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
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
//person 1
void drawPerson1(float x, float y) {

    // Hair (short, male style)
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

    // ----------------- MOUTH -----------------
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();
    // -----------------------------------------


    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
    // ----------------------------------------

    // Torso
    glColor3f(0.682f, 0.741f, 0.165f);//shirt yellow
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

//person 2
void drawPerson2(float x, float y) {

    // Hair (short, male style)
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

    // ----------------- MOUTH -----------------
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();
    // -----------------------------------------


    // ----------------- EYES -----------------
    float eyeOffsetX = 0.03f;  // horizontal distance from head center
    float eyeOffsetY = 0.03f;  // vertical offset from head center
    float eyeRadius = 0.03f;   // white eye radius
    float pupilRadius = 0.005f; // black pupil radius

    // Left eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Left pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);

    // Right eye (white)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, eyeRadius);
    // Right pupil
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + eyeOffsetX, y + 0.25f + eyeOffsetY, pupilRadius);
    // ----------------------------------------

    // Torso
    glColor3f(85 / 255.0f, 47 / 255.0f, 99 / 255.0f);
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


// sofa
void drawSofa(float centerX, float baseY) {
    // Main cushion
    glColor3f(0.631f, 0.380f, 0.227f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY);
    glVertex2f(centerX + 0.7f, baseY);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glEnd();

    // Side left
    glColor3f(0.439f, 0.255f, 0.141f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glVertex2f(centerX - 0.9f, baseY + 0.3f);
    glVertex2f(centerX - 0.9f, baseY + 0.0f);
    glVertex2f(centerX - 0.7f, baseY);
    glEnd();

    // Side right
    glBegin(GL_POLYGON);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.9f, baseY + 0.3f);
    glVertex2f(centerX + 0.9f, baseY + 0.0f);
    glVertex2f(centerX + 0.7f, baseY);
    glEnd();

    // Top cushion
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.7f, baseY + 0.4f);
    glVertex2f(centerX - 0.7f, baseY + 0.4f);
    glEnd();
}

// carpet
void drawCarpet(float yBottom, float yTop) {
    glColor3f(129 / 255.0f, 150 / 255.0f, 199 / 255.0f); // outline
    glBegin(GL_POLYGON);
    glVertex2f(-1.01f, yBottom);
    glVertex2f(1.01f, yBottom);
    glVertex2f(1.01f, yTop);
    glVertex2f(-1.01f, yTop);
    glEnd();

    glColor3f(103 / 255.0f, 132 / 255.0f, 158 / 255.0f); // inner
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yTop - 0.01f);
    glVertex2f(-1.0f, yTop - 0.01f);
    glEnd();
}

// xmas tree
void drawXmasTree(float x, float baseY) {
    // trunk
    glColor3f(0.439f, 0.255f, 0.141f);
    glBegin(GL_LINES);
    glVertex2f(x, baseY);
    glVertex2f(x, baseY - 0.05f);
    glEnd();

    // layers
    glColor3f(0.220f, 0.761f, 0.400f);
    float height = 0.2f;
    for (int i = 0; i < 3; i++) {
        glBegin(GL_POLYGON);
        glVertex2f(x - 0.2f, baseY + i * height);
        glVertex2f(x, baseY + height + i * height);
        glVertex2f(x + 0.2f, baseY + i * height);
        glEnd();
    }
}
//bed
void drawBed(float x, float y, float width, float height) {
    // Bed frame (outer rectangle)
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    // Mattress (inner rectangle)
    glColor3f(0.8f, 0.8f, 0.8f); // light grey
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2 + 0.02f, y - height / 2 + 0.02f);
    glVertex2f(x + width / 2 - 0.02f, y - height / 2 + 0.02f);
    glVertex2f(x + width / 2 - 0.02f, y + height / 2 - 0.1f);
    glVertex2f(x - width / 2 + 0.02f, y + height / 2 - 0.1f);
    glEnd();

    // Pillow
    glColor3f(1.0f, 1.0f, 1.0f); // white
    glBegin(GL_QUADS);
    glVertex2f(x - width / 4, y + height / 4 - 0.05f);
    glVertex2f(x + width / 4, y + height / 4 - 0.05f);
    glVertex2f(x + width / 4, y + height / 2 - 0.02f);
    glVertex2f(x - width / 4, y + height / 2 - 0.02f);
    glEnd();
}
//gift
void drawGift(float x, float y) {
    // Gift box
    glColor3f(0.9f, 0.2f, 0.2f); // red
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.2f, y - 0.1f);
    glVertex2f(x + 0.2f, y - 0.1f);
    glVertex2f(x + 0.2f, y + 0.2f);
    glVertex2f(x - 0.2f, y + 0.2f);
    glEnd();

    // Ribbon
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glBegin(GL_LINES);
    glVertex2f(x - 0.2f, y + 0.05f); glVertex2f(x + 0.2f, y + 0.05f); // horizontal
    glVertex2f(x, y - 0.1f); glVertex2f(x, y + 0.2f);                     // vertical
    glEnd();
}
//toys
void drawToys(float x, float y) {
    // ------- Woody (brown hat, yellow shirt, blue pants) -------
    float woodySize = 0.05f; // scale
    // Hat
    glColor3f(0.55f, 0.27f, 0.07f); // brown
    drawCircle(x - 0.1f, y + 0.05f, woodySize);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x - 0.1f, y, woodySize * 0.8f);
    // Body
    glColor3f(1.0f, 0.84f, 0.0f); // yellow shirt
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.12f, y - 0.05f);
    glVertex2f(x - 0.08f, y - 0.05f);
    glVertex2f(x - 0.08f, y - 0.15f);
    glVertex2f(x - 0.12f, y - 0.15f);
    glEnd();
    // Legs
    glColor3f(0.0f, 0.0f, 1.0f); // blue pants
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.12f, y - 0.15f);
    glVertex2f(x - 0.08f, y - 0.15f);
    glVertex2f(x - 0.08f, y - 0.2f);
    glVertex2f(x - 0.12f, y - 0.2f);
    glEnd();

    // ------- Buzz Lightyear (white suit with green & purple accents) -------
    float buzzSize = 0.05f;
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y, buzzSize);
    // Suit
    glColor3f(0.0f, 1.0f, 0.0f); // green
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.05f, y - 0.05f);
    glVertex2f(x + 0.05f, y - 0.05f);
    glVertex2f(x + 0.05f, y - 0.15f);
    glVertex2f(x - 0.05f, y - 0.15f);
    glEnd();
    // Chest / details
    glColor3f(0.5f, 0.0f, 0.5f); // purple accents
    drawCircle(x, y - 0.1f, buzzSize * 0.3f);

    // ------- Rex (green dinosaur) -------
    float rexSize = 0.05f;
    glColor3f(0.0f, 0.8f, 0.0f); // green
    drawCircle(x + 0.1f, y - 0.05f, rexSize); // head
    glBegin(GL_POLYGON); // body
    glVertex2f(x + 0.08f, y - 0.05f);
    glVertex2f(x + 0.12f, y - 0.05f);
    glVertex2f(x + 0.12f, y - 0.15f);
    glVertex2f(x + 0.08f, y - 0.15f);
    glEnd();
}
//window
void drawWindow(float x, float y) {
    float halfW = 0.2f; // half width
    float halfH = 0.2f; // half height

    // Draw 4 cyan
    glColor3f(0.0f, 1.0f, 1.0f); // cyan glass

    // Top-left pane
    glBegin(GL_POLYGON);
    glVertex2f(x - halfW, y);
    glVertex2f(x, y);
    glVertex2f(x, y + halfH);
    glVertex2f(x - halfW, y + halfH);
    glEnd();

    // Top-right pane
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + halfW, y);
    glVertex2f(x + halfW, y + halfH);
    glVertex2f(x, y + halfH);
    glEnd();

    // Bottom-left pane
    glBegin(GL_POLYGON);
    glVertex2f(x - halfW, y - halfH);
    glVertex2f(x, y - halfH);
    glVertex2f(x, y);
    glVertex2f(x - halfW, y);
    glEnd();

    // Bottom-right pane
    glBegin(GL_POLYGON);
    glVertex2f(x, y - halfH);
    glVertex2f(x + halfW, y - halfH);
    glVertex2f(x + halfW, y);
    glVertex2f(x, y);
    glEnd();

    // Draw black outlines
    glColor3f(0.0f, 0.0f, 0.0f);

    // Outer frame
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - halfW, y - halfH);
    glVertex2f(x + halfW, y - halfH);
    glVertex2f(x + halfW, y + halfH);
    glVertex2f(x - halfW, y + halfH);
    glEnd();

    // Vertical divider
    glBegin(GL_LINES);
    glVertex2f(x, y - halfH); glVertex2f(x, y + halfH);
    glEnd();

    // Horizontal divider
    glBegin(GL_LINES);
    glVertex2f(x - halfW, y); glVertex2f(x + halfW, y);
    glEnd();
}


// SCENE 1
void drawCouchScene() {

    glClear(GL_COLOR_BUFFER_BIT);
    //WALL
    glBegin(GL_POLYGON);
    glColor3f(205 / 255.0f, 160 / 255.0f, 217 / 255.0f);
    glVertex2f(-5.0f, 1.0f); // bottom-left
    glVertex2f(5.0f, 1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    //FLOOR
    glBegin(GL_POLYGON);
    glColor3f(189 / 255.0f, 151 / 255.0f, 199 / 255.0f);
    glVertex2f(-5.0f, -1.0f); // bottom-left
    glVertex2f(5.0f, -1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    drawWindow(-1.3f, 0.5f); // window on left
    drawGift(0.0f, 0.25f);
    drawXmasTree(1.4f, 0.05f);
    drawCarpet(-0.3f, -0.1f);
    drawSofa(0.0f, 0.0f);
    // parents
    drawDad(-0.3f, 0.2f); // left side
    drawMom(0.3f, 0.2f);  // right side
    drawKevin(0.4f, -0.4f);
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
    if (!showDialogue) {
        drawText(-0.8f, 0.8f, "On December 23rd afternoon, Kevin goes home to his parents looking sad.");
        drawText(-0.8f, 0.7f, "Kevin: Mom, Dad, what's the matter? It's almost christmas!");
        drawText(-0.45f, -0.6f, "Press ENTER to continue...");
    }
    else {
        drawText(-0.9f, -0.6f, "Parents: Kevin, we are short on money.");
        drawText(-0.9f, -0.7f, "We won't be able to celebrate Christmas. We're so sorry.");
        drawText(-0.4f, -0.9f, "Press ENTER to continue...");
    }

    glutSwapBuffers();
}

// SCENE 2
void drawToyScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    //WALL
    glBegin(GL_POLYGON);
    glColor3f(217 / 255.0f, 200 / 255.0f, 128 / 255.0f);
    glVertex2f(-5.0f, 1.0f); // bottom-left
    glVertex2f(5.0f, 1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();
    //FLOOR
    glBegin(GL_POLYGON);
    glColor3f(173 / 255.0f, 159 / 255.0f, 99 / 255.0f);
    glVertex2f(-5.0f, -1.0f); // bottom-left
    glVertex2f(5.0f, -1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    drawWindow(-1.0f, 0.3f); // window on left
    drawToys(0.5f, 0.2f);
    drawTable(0.5f, 0.0f);
    drawBed(-1.0f, -0.5f, 0.6f, 0.9f); // x, y, width, height
    drawKevin(1.0f, -0.1f);


    glColor3f(0.0f, 0.0f, 0.0f); // black text
    drawText(-0.6f, 0.8f, "Kevin: I'm going to sell my toys to surprise them with a celebration!");

    glutSwapBuffers();
}

// SCENE 3
void drawSellingScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    //WALL
    glBegin(GL_POLYGON);
    glColor3f(151 / 255.0f, 240 / 255.0f, 232 / 255.0f);
    glVertex2f(-5.0f, 1.0f); // bottom-left
    glVertex2f(5.0f, 1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    //walkway
    glBegin(GL_POLYGON);
    glColor3f(186 / 255.0f, 155 / 255.0f, 130 / 255.0f);
    glVertex2f(-5.0f, -0.2f); // bottom-left
    glVertex2f(5.0f, -0.2f);  // bottom-right
    glVertex2f(5.0f, 0.1f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.1f);  // top-left (y = 0)
    glEnd();
    //FLOOR
    glBegin(GL_POLYGON);
    glColor3f(103 / 255.0f, 181 / 255.0f, 111 / 255.0f);
    glVertex2f(-5.0f, -1.0f); // bottom-left
    glVertex2f(5.0f, -1.0f);  // bottom-right
    glVertex2f(5.0f, -0.2f);   // top-right (y = 0)
    glVertex2f(-5.0f, -0.2f);  // top-left (y = 0)
    glEnd();


    // People walking past
    if (peopleActive) {
        drawPerson1(peoplePosX, 0.2f);
        drawPerson2(peoplePosX + 0.5f, 0.2f);
    }

    //kevin
    drawKevin(0.5f, 0.0f);
    //table
    drawToys(0.0f, 0.2f);
    drawTable(0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    drawText(-0.65f, -0.7f, "He goes on to sell, but people only passed by...");
    drawText(-0.65f, -0.9f, "In the end, nobody bought the toys. ");

    glutSwapBuffers();
}

// SCENE 4
void drawHomeCelebration() {

    glClear(GL_COLOR_BUFFER_BIT);
    //WALL
    glBegin(GL_POLYGON);
    glColor3f(205 / 255.0f, 160 / 255.0f, 217 / 255.0f);
    glVertex2f(-5.0f, 1.0f); // bottom-left
    glVertex2f(5.0f, 1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    //FLOOR
    glBegin(GL_POLYGON);
    glColor3f(189 / 255.0f, 151 / 255.0f, 199 / 255.0f);
    glVertex2f(-5.0f, -1.0f); // bottom-left
    glVertex2f(5.0f, -1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    drawXmasTree(1.4f, 0.05f);
    drawCarpet(-0.3f, -0.1f);
    drawSofa(0.0f, 0.0f);
    drawDad(-0.5f, 0.2f);
    drawMom(0.5f, 0.2f);

    //emotion of parents
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.49f, 0.42f);
    glVertex2f(-0.50f, 0.41f);
    glVertex2f(-0.51f, 0.42f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.49f, 0.42f);
    glVertex2f(0.50f, 0.41f);
    glVertex2f(0.51f, 0.42f);
    glEnd();

    drawKevin(0.0f, -0.4f); //KEVIN
    drawGift(0.0f, 0.25f); //GIFT

    // Text
    glColor3f(0.1f, 0.1f, 0.1f);
    drawText(-0.85f, 0.8f, "He goes home to see his parents actually surprised him with a gift and celebration");

    glutSwapBuffers();
}

// MOUSE HANDLING for clicking on book
void mouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    // Get current window size
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    float aspect = (float)w / (float)h;

    // Convert mouse pixel to OpenGL coordinates (accounting for aspect)
    float oglX = ((float)x / w) * 2.0f - 1.0f;
    oglX /= aspect;  // <--- correct X for aspect ratio
    float oglY = ((float)(h - y) / h) * 2.0f - 1.0f;

    // Book click
    if (showBook) {
        if (oglX >= -0.6f && oglX <= 0.0f) {
            showBook = false;
            showCouchScene = true;
        }
        glutPostRedisplay();
        return;
    }

}


// timer for animation
void updatePeople(int value) {
    if (peopleActive) {
        peoplePosX += 0.005f;
        if (peoplePosX > 1.5f) peoplePosX = -1.3f;
        glutPostRedisplay();
        glutTimerFunc(30, updatePeople, 0);
    }
}

// keyboard handling enter stuff
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

// display scene compilation
void display() {
    if (showBook)                 drawBook();
    else if (showCouchScene)      drawCouchScene();
    else if (showToyScene)        drawToyScene();
    else if (showSellingScene)    drawSellingScene();
    else if (showHomeCelebration) drawHomeCelebration();
}

//init
void init() {
    glClearColor(0.85f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

//main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Kevin's Story");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyPressed);

    glutReshapeFunc(reshape);



    glutMainLoop();
    return 0;
}
