#include <GL/glut.h>
#include <string>
#include <cmath>

//Screen states 
bool showBook = true;
bool showCouchScene = false;
bool showDialogue = false;
bool showToyScene = false;
bool showSellingScene = false;
bool showHomeCelebration = false;

//Toy data
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

void drawKevin(float x, float y) {

    // Hair (short, male style)
    glColor3f(0.980f, 0.804f, 0.420f); // blonde
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

// -------------------- REUSABLE ELEMENTS --------------------

// Draw sofa at a given position (x = center horizontal)
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

// Draw rectangular oblong carpet
void drawCarpet(float yBottom, float yTop) {
    glColor3f(0.141f, 0.651f, 0.643f); // outline
    glBegin(GL_POLYGON);
    glVertex2f(-1.01f, yBottom);
    glVertex2f(1.01f, yBottom);
    glVertex2f(1.01f, yTop);
    glVertex2f(-1.01f, yTop);
    glEnd();

    glColor3f(0.153f, 0.859f, 0.847f); // inner
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yTop - 0.01f);
    glVertex2f(-1.0f, yTop - 0.01f);
    glEnd();
}

// Draw a simple Christmas tree
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


// ---------------- COUCH SCENE ----------------
void drawCouchScene() {
    glClear(GL_COLOR_BUFFER_BIT);
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

    drawXmasTree(1.4f, 0.05f);
    drawCarpet(-0.3f, -0.1f);
    drawSofa(0.0f, 0.0f);
    drawDad(-0.5f, 0.2f);
    drawMom(0.5f, 0.2f);

    //emotion
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

    // Kevin WOW
    drawKevin(0.0f, -0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.0f);
    glVertex2f(0.0f, -0.02f);
    glVertex2f(0.2f, 0.0f);
    glEnd();


    // Text
    glColor3f(0.1f, 0.1f, 0.1f);
    drawText(-0.85f, 0.8f, "He goes home to see his parents actually surprised him with a gift and celebration");

    glutSwapBuffers();
}

// ---------------- MOUSE EVENTS ----------------
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
