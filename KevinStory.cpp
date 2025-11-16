#include <GL/glut.h>
#include <string>
#include <cmath>
#include <cstring>

//will be reusing these
void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
}

void drawCircle(float cx, float cy, float r, int num_segments = 50) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

bool showBook = true;

// kevin story scenes
bool xmas_showBook = false;
bool xmas_showCouchScene = false;
bool xmas_showDialogue = false;
bool xmas_showToyScene = false;
bool xmas_showSellingScene = false;
bool xmas_showHomeCelebration = false;

// for walking animation
float xmas_peoplePosX = -1.3f;
bool xmas_peopleActive = true;

// kevin's new year globals
bool showTitle = false;
bool showThinking = false;
bool showNext = false;
bool showKitchenReturn = false;
bool showPlateScene = false;

// Animation state for kevin's new year 
bool animateBubble = true;
float bubblePhase = 0.0f;
float liftPhase = 0.0f;
float chandelierPhase = 0.0f;
float fireworksPhase = 0.0f;
float kevinX = -0.8f;
int movePhase = 0;

// Clock / fireworks for kevin's new year
bool clockAtMidnight = false;
bool fireworksActive = false;
float clockLeft = 0.0f, clockTop = 0.0f, clockRight = 0.0f, clockBottom = 0.0f;

// Kevin walking in globals kevin's new year
bool kevinWalking = false;
float kevinPosX = -1.2f;
float kevinPosY = -0.38f;
float kevinTargetX = 0.0f;
float kevinSpeed = 0.012f;

// Fridge footprint (for clicks)
float fridgeRX1 = 0.58f, fridgeRY1 = -0.95f, fridgeRX2 = 1.02f, fridgeRY2 = 0.75f;

// Kevin action state for Lance interactive sequence
enum KevinAction { K_IDLE = 0, K_WALK_TO_FRIDGE, K_PICK_DRINK, K_WALK_BACK, K_DRINKING };
KevinAction kevinAction = K_IDLE;
int pickTimer = 0;
int drinkTimer = 0;
bool kevinHasDrink = false;
bool initialWalkStarted = false;
bool initialWalkDone = false;

// view extents for kevin new year scenes
float viewLeft = -1.0f, viewRight = 1.0f, viewBottom = -1.0f, viewTop = 1.0f;

// Neighborhood state used in kevins new year
const int HOUSE_COUNT = 4;
float houseX[HOUSE_COUNT] = { -0.9f, -0.5f, -0.1f, 0.35f };
float houseY[HOUSE_COUNT] = { -0.6f, -0.6f, -0.6f, -0.6f };
float houseW[HOUSE_COUNT] = { 0.5f, 0.42f, 0.42f, 0.42f };
float houseH[HOUSE_COUNT] = { 0.6f, 0.56f, 0.56f, 0.56f };

bool friendActivated[HOUSE_COUNT] = { false, false, false, false };
bool friendWalkingArr[HOUSE_COUNT] = { false, false, false, false };
float friendPosX[HOUSE_COUNT] = { 0 }, friendPosY[HOUSE_COUNT] = { 0 };
float friendTargetX[HOUSE_COUNT] = { 0 }, friendTargetY[HOUSE_COUNT] = { 0 }, friendSpeedArr[HOUSE_COUNT] = { 0 };

float nextKevinX = 0.15f;
float nextKevinY = -0.75f;

// drawFunctions (ELEMENTS and SCENES) NOTE: we reused these
void xmas_drawBook();
void xmas_drawCouchScene();
void xmas_drawToyScene();
void xmas_drawSellingScene();
void xmas_drawHomeCelebration();
void xmas_drawTable(float x, float y);
void xmas_drawDad(float x, float y);
void xmas_drawMom(float x, float y);
void xmas_drawKevin(float x, float y);
void xmas_drawPerson1(float x, float y);
void xmas_drawPerson2(float x, float y);
void xmas_drawSofa(float centerX, float baseY);
void xmas_drawCarpet(float yBottom, float yTop);
void xmas_drawXmasTree(float x, float baseY);
void xmas_drawBed(float x, float y, float width, float height);
void xmas_drawGift(float x, float y);
void xmas_drawToys(float x, float y);
void xmas_drawWindow(float x, float y);
void xmas_updatePeople(int value);

// Kevin's new year(ELEMENTS and SCENES)
void drawTitleScene();
void drawThinkingScene();
void drawNextScene();
void drawReturnKitchenScene();
void drawPlateScene();
void updateAnimation(int value);
void drawKevin(float x, float y, float scale = 1.0f);
void drawDumbbellSmall(float x, float y, float s = 0.05f);
void drawMiniKevinLift(float cx, float cy, float scale, float t);
void drawThoughtBubble(float cx, float cy, float r);
void drawChandelier(float cx, float cy, float scale, float phase);
void drawPlateWithFood(float px, float py, float scale = 1.0f);
void drawRoastChicken(float x, float y, float s = 0.08f);
void drawCake(float x, float y, float s = 0.07f);
void drawGlass(float x, float y, float h = 0.08f);
void drawDiningTable(float centerX, float topY, float width = 1.6f, float depth = 0.28f);
void drawCabinetsAndFridge();
void drawDigit7(int d, float x, float y, float size, float thickness, const float color[3]);
void drawDigitalClock(float topLeftX, float topLeftY, float size);
void drawFirework(float cx, float cy, float baseR, float phase, const float color[3]);

// Unified callbacks
void display();
void reshape(int w, int h);
void mouseClick(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);


// draw table
void xmas_drawTable(float x, float y) {
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

void xmas_drawDad(float x, float y) {
    // Hair 
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

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

void xmas_drawMom(float x, float y) {
    // Hair hair with ponytail thingy
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

// drawKevin version for xmas
void xmas_drawKevin(float x, float y) {
    // Hair (short, male style)
    glColor3f(0.980f, 0.804f, 0.420f); // blonde
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

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
    //kevin's mouth
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();


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

void xmas_drawSofa(float centerX, float baseY) {
    glColor3f(0.631f, 0.380f, 0.227f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY);
    glVertex2f(centerX + 0.7f, baseY);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glEnd();
    // sides & top cushion
    glColor3f(0.439f, 0.255f, 0.141f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glVertex2f(centerX - 0.9f, baseY + 0.3f);
    glVertex2f(centerX - 0.9f, baseY + 0.0f);
    glVertex2f(centerX - 0.7f, baseY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.9f, baseY + 0.3f);
    glVertex2f(centerX + 0.9f, baseY + 0.0f);
    glVertex2f(centerX + 0.7f, baseY);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(centerX - 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.7f, baseY + 0.2f);
    glVertex2f(centerX + 0.7f, baseY + 0.4f);
    glVertex2f(centerX - 0.7f, baseY + 0.4f);
    glEnd();
}

void xmas_drawCarpet(float yBottom, float yTop) {
    glColor3f(129 / 255.0f, 150 / 255.0f, 199 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.01f, yBottom);
    glVertex2f(1.01f, yBottom);
    glVertex2f(1.01f, yTop);
    glVertex2f(-1.01f, yTop);
    glEnd();
    glColor3f(103 / 255.0f, 132 / 255.0f, 158 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yBottom + 0.01f);
    glVertex2f(1.0f, yTop - 0.01f);
    glVertex2f(-1.0f, yTop - 0.01f);
    glEnd();
}

void xmas_drawXmasTree(float x, float baseY) {
    glColor3f(0.439f, 0.255f, 0.141f);
    glBegin(GL_LINES);
    glVertex2f(x, baseY);
    glVertex2f(x, baseY - 0.05f);
    glEnd();
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

void xmas_drawBed(float x, float y, float width, float height) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2 + 0.02f, y - height / 2 + 0.02f);
    glVertex2f(x + width / 2 - 0.02f, y - height / 2 + 0.02f);
    glVertex2f(x + width / 2 - 0.02f, y + height / 2 - 0.1f);
    glVertex2f(x - width / 2 + 0.02f, y + height / 2 - 0.1f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 4, y + height / 4 - 0.05f);
    glVertex2f(x + width / 4, y + height / 4 - 0.05f);
    glVertex2f(x + width / 4, y + height / 2 - 0.02f);
    glVertex2f(x - width / 4, y + height / 2 - 0.02f);
    glEnd();
}

void xmas_drawGift(float x, float y) {
    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.2f, y - 0.1f);
    glVertex2f(x + 0.2f, y - 0.1f);
    glVertex2f(x + 0.2f, y + 0.2f);
    glVertex2f(x - 0.2f, y + 0.2f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x - 0.2f, y + 0.05f); glVertex2f(x + 0.2f, y + 0.05f);
    glVertex2f(x, y - 0.1f); glVertex2f(x, y + 0.2f);
    glEnd();
}

void xmas_drawToys(float x, float y) {
    // woody toy
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

    // buzz lightyear
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

    // rex toy
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

void xmas_drawWindow(float x, float y) {
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

void xmas_drawCouchScene() { // SCENE 1
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    // wall
    glColor3f(205 / 255.0f, 160 / 255.0f, 217 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, 1.0f); // bottom-left
    glVertex2f(5.0f, 1.0f);  // bottom-right
    glVertex2f(5.0f, 0.0f);   // top-right (y = 0)
    glVertex2f(-5.0f, 0.0f);  // top-left (y = 0)
    glEnd();

    // floor
    glColor3f(189 / 255.0f, 151 / 255.0f, 199 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, -1.0f);
    glVertex2f(5.0f, -1.0f);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(-5.0f, 0.0f);
    glEnd();

    xmas_drawWindow(-1.3f, 0.5f);
    xmas_drawGift(0.0f, 0.25f);
    xmas_drawXmasTree(1.4f, 0.05f);
    xmas_drawCarpet(-0.3f, -0.1f);
    xmas_drawSofa(0.0f, 0.0f);
    xmas_drawDad(-0.3f, 0.2f);
    xmas_drawMom(0.3f, 0.2f);
    xmas_drawKevin(0.4f, -0.4f);

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


    glColor3f(0.1f, 0.1f, 0.1f);
    if (!xmas_showDialogue) {
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

void xmas_drawToyScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    // wall
    glColor3f(217 / 255.0f, 200 / 255.0f, 128 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, 1.0f); glVertex2f(5.0f, 1.0f); glVertex2f(5.0f, 0.0f); glVertex2f(-5.0f, 0.0f);
    glEnd();

    glColor3f(173 / 255.0f, 159 / 255.0f, 99 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, -1.0f); glVertex2f(5.0f, -1.0f); glVertex2f(5.0f, 0.0f); glVertex2f(-5.0f, 0.0f);
    glEnd();

    xmas_drawWindow(-1.0f, 0.3f);
    xmas_drawToys(0.5f, 0.2f);
    xmas_drawTable(0.5f, 0.0f);
    xmas_drawBed(-1.0f, -0.5f, 0.6f, 0.9f);
    xmas_drawKevin(1.0f, -0.1f);

    glColor3f(0, 0, 0);
    drawText(-0.6f, 0.8f, "Kevin: I'm going to sell my toys to surprise them with a celebration!");

    glutSwapBuffers();
}

void xmas_drawSellingScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(151 / 255.0f, 240 / 255.0f, 232 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, 1.0f); glVertex2f(5.0f, 1.0f); glVertex2f(5.0f, 0.0f); glVertex2f(-5.0f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(186 / 255.0f, 155 / 255.0f, 130 / 255.0f);
    glVertex2f(-5.0f, -0.2f); glVertex2f(5.0f, -0.2f); glVertex2f(5.0f, 0.1f); glVertex2f(-5.0f, 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(103 / 255.0f, 181 / 255.0f, 111 / 255.0f);
    glVertex2f(-5.0f, -1.0f); glVertex2f(5.0f, -1.0f); glVertex2f(5.0f, -0.2f); glVertex2f(-5.0f, -0.2f);
    glEnd();

    // people walking
    if (xmas_peopleActive) {
        xmas_drawPerson1(xmas_peoplePosX, 0.2f);
        xmas_drawPerson2(xmas_peoplePosX + 0.5f, 0.2f);
    }

    xmas_drawKevin(0.5f, 0.0f);
    xmas_drawToys(0.0f, 0.2f);
    xmas_drawTable(0.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(-0.65f, -0.7f, "He goes on to sell, but people only passed by...");
    drawText(-0.65f, -0.9f, "In the end, nobody bought the toys. ");

    glutSwapBuffers();
}

void xmas_drawHomeCelebration() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(205 / 255.0f, 160 / 255.0f, 217 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, 1.0f); glVertex2f(5.0f, 1.0f); glVertex2f(5.0f, 0.0f); glVertex2f(-5.0f, 0.0f);
    glEnd();

    glColor3f(189 / 255.0f, 151 / 255.0f, 199 / 255.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-5.0f, -1.0f); glVertex2f(5.0f, -1.0f); glVertex2f(5.0f, 0.0f); glVertex2f(-5.0f, 0.0f);
    glEnd();

    xmas_drawXmasTree(1.4f, 0.05f);
    xmas_drawCarpet(-0.3f, -0.1f);
    xmas_drawSofa(0.0f, 0.0f);
    xmas_drawDad(-0.5f, 0.2f);
    xmas_drawMom(0.5f, 0.2f);

    drawText(-0.85f, 0.8f, "He goes home to see his parents actually surprised him with a gift and celebration");

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

    xmas_drawKevin(0.0f, -0.4f);
    xmas_drawGift(0.0f, 0.25f);

    glutSwapBuffers();
}

// ks person1 / person2
void xmas_drawPerson1(float x, float y) {
    // Hair 
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

    // mouth
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();


    //eyes
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

void xmas_drawPerson2(float x, float y) {
    // Hair (short, male style)
    glColor3f(0.1f, 0.1f, 0.1f); // black hair
    drawCircle(x, y + 0.28f, 0.13f);
    // Head
    glColor3f(1.0f, 0.8f, 0.6f); // skin
    drawCircle(x, y + 0.25f, 0.12f);

    // mouth
    glColor3f(0.8f, 0.0f, 0.0f); // red mouth
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f, y + 0.22f);
    glVertex2f(x, y + 0.20f);
    glVertex2f(x + 0.03f, y + 0.22f);
    glEnd();



    //eyes
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

// timer for people walking in Kevin's Christmas
void xmas_updatePeople(int value) {
    if (xmas_peopleActive) {
        xmas_peoplePosX += 0.005f;
        if (xmas_peoplePosX > 1.5f) xmas_peoplePosX = -1.3f;
        glutPostRedisplay();
        glutTimerFunc(30, xmas_updatePeople, 0);
    }
}

// rectangle
void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawKevin(float x, float y, float scale) {
    // hair
    glColor3f(0.98f, 0.80f, 0.42f);
    drawCircle(x, y + 0.28f * scale, 0.13f * scale);
    // head
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(x, y + 0.25f * scale, 0.12f * scale);
    // eyes
    float ex = 0.03f * scale, ey = 0.03f * scale;
    float er = 0.03f * scale, pr = 0.005f * scale;
    glColor3f(1, 1, 1); drawCircle(x - ex, y + 0.25f * scale + ey, er);
    glColor3f(0, 0, 0); drawCircle(x - ex, y + 0.25f * scale + ey, pr);
    glColor3f(1, 1, 1); drawCircle(x + ex, y + 0.25f * scale + ey, er);
    glColor3f(0, 0, 0); drawCircle(x + ex, y + 0.25f * scale + ey, pr);
    // mouth
    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 0.03f * scale, y + 0.22f * scale);
    glVertex2f(x, y + 0.20f * scale);
    glVertex2f(x + 0.03f * scale, y + 0.22f * scale);
    glEnd();
    // torso
    glColor3f(0.2f, 0.3f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.1f * scale, y);
    glVertex2f(x + 0.1f * scale, y);
    glVertex2f(x + 0.1f * scale, y + 0.2f * scale);
    glVertex2f(x - 0.1f * scale, y + 0.2f * scale);
    glEnd();
    // arms
    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON); glVertex2f(x - 0.12f * scale, y + 0.18f * scale); glVertex2f(x - 0.10f * scale, y + 0.18f * scale); glVertex2f(x - 0.10f * scale, y + 0.05f * scale); glVertex2f(x - 0.12f * scale, y + 0.05f * scale); glEnd();
    glBegin(GL_POLYGON); glVertex2f(x + 0.10f * scale, y + 0.18f * scale); glVertex2f(x + 0.12f * scale, y + 0.18f * scale); glVertex2f(x + 0.12f * scale, y + 0.05f * scale); glVertex2f(x + 0.10f * scale, y + 0.05f * scale); glEnd();
    // legs
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON); glVertex2f(x - 0.08f * scale, y - 0.1f * scale); glVertex2f(x - 0.02f * scale, y - 0.1f * scale); glVertex2f(x - 0.02f * scale, y); glVertex2f(x - 0.08f * scale, y); glEnd();
    glBegin(GL_POLYGON); glVertex2f(x + 0.02f * scale, y - 0.1f * scale); glVertex2f(x + 0.08f * scale, y - 0.1f * scale); glVertex2f(x + 0.08f * scale, y); glVertex2f(x + 0.02f * scale, y); glEnd();
}

void drawDumbbellSmall(float x, float y, float s) {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(x - s, y - 0.005f);
    glVertex2f(x + s, y - 0.005f);
    glVertex2f(x + s, y + 0.005f);
    glVertex2f(x - s, y + 0.005f);
    glEnd();
    glColor3f(0.15f, 0.15f, 0.15f);
    drawCircle(x - s - 0.02f, y, 0.02f);
    drawCircle(x + s + 0.02f, y, 0.02f);
}

void drawMiniKevinLift(float cx, float cy, float scale, float t) {
    float armLift = (sinf(t) + 1.0f) * 0.5f;
    float armOffset = armLift * 0.06f * scale;
    glColor3f(0.98f, 0.80f, 0.42f);
    drawCircle(cx, cy + 0.09f * scale, 0.045f * scale);
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle(cx, cy + 0.08f * scale, 0.04f * scale);
    glColor3f(1, 1, 1); drawCircle(cx - 0.01f * scale, cy + 0.085f * scale, 0.01f * scale);
    glColor3f(0, 0, 0); drawCircle(cx - 0.01f * scale, cy + 0.085f * scale, 0.004f * scale);
    glColor3f(1, 1, 1); drawCircle(cx + 0.01f * scale, cy + 0.085f * scale, 0.01f * scale);
    glColor3f(0, 0, 0); drawCircle(cx + 0.01f * scale, cy + 0.085f * scale, 0.004f * scale);

    glColor3f(0.2f, 0.3f, 0.8f);
    glBegin(GL_POLYGON); glVertex2f(cx - 0.03f * scale, cy - 0.01f * scale); glVertex2f(cx + 0.03f * scale, cy - 0.01f * scale); glVertex2f(cx + 0.03f * scale, cy + 0.05f * scale); glVertex2f(cx - 0.03f * scale, cy + 0.05f * scale); glEnd();

    glColor3f(1.0f, 0.8f, 0.6f);
    glBegin(GL_POLYGON); glVertex2f(cx - 0.035f * scale, cy + 0.035f * scale); glVertex2f(cx - 0.015f * scale, cy + 0.035f * scale); glVertex2f(cx - 0.015f * scale, cy + 0.035f * scale + armOffset); glVertex2f(cx - 0.035f * scale, cy + 0.035f * scale + armOffset); glEnd();
    glBegin(GL_POLYGON); glVertex2f(cx + 0.015f * scale, cy + 0.035f * scale); glVertex2f(cx + 0.035f * scale, cy + 0.035f * scale); glVertex2f(cx + 0.035f * scale, cy + 0.035f * scale + armOffset); glVertex2f(cx + 0.015f * scale, cy + 0.035f * scale + armOffset); glEnd();

    float dbY = cy + 0.035f * scale + armOffset + 0.01f * scale;
    drawDumbbellSmall(cx, dbY, 0.035f * scale);
}

// Thought bubble
void drawThoughtBubble(float cx, float cy, float r) {
    glColor3f(1, 1, 1);
    drawCircle(cx, cy, r, 48);
    drawCircle(cx - r * 0.6f, cy - r * 0.6f, r * 0.18f);
    drawCircle(cx - r * 0.85f, cy - r * 0.85f, r * 0.08f);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0;i < 48;i++) {
        float theta = 2.0f * 3.1415926f * float(i) / 48.0f;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

// chandelier (simplified)
void drawChandelier(float cx, float cy, float scale, float phase) {
    float angleDeg = sinf(phase) * 8.0f;
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(angleDeg, 0.0f, 0.0f, 1.0f);
    glColor3f(0.7f, 0.6f, 0.4f);
    glBegin(GL_LINES); glVertex2f(0.0f, 0.06f * scale); glVertex2f(0.0f, -0.02f * scale); glEnd();
    glColor3f(0.85f, 0.75f, 0.5f); drawCircle(0.0f, -0.04f * scale, 0.05f * scale, 24);
    int arms = 6;
    for (int i = 0;i < arms;i++) {
        float a = 2.0f * 3.1415926f * i / arms;
        float ax = cosf(a), ay = sinf(a);
        float len = 0.18f * scale;
        glColor3f(0.75f, 0.65f, 0.45f);
        glBegin(GL_LINES); glVertex2f(0.0f, -0.04f * scale); glVertex2f(ax * len, -0.04f * scale + ay * len); glEnd();
        float bx = ax * len; float by = -0.04f * scale + ay * len;
        glColor3f(1.0f, 0.95f, 0.6f); drawCircle(bx, by, 0.03f * scale, 16);
        glColor3f(1.0f, 0.9f, 0.5f); drawCircle(bx, by, 0.015f * scale, 12);
    }
    glPopMatrix();
}

// plate, roast, cake, glass, dining table
void drawPlateWithFood(float px, float py, float scale) {
    glColor3f(1, 1, 1); drawCircle(px, py, 0.09f * scale, 24);
    glColor3f(0.9f, 0.9f, 0.95f); drawCircle(px, py, 0.08f * scale, 24);
    glColor3f(0.9f, 0.5f, 0.2f); drawCircle(px - 0.01f * scale, py - 0.005f * scale, 0.05f * scale);
    glColor3f(0.8f, 0.3f, 0.1f); drawCircle(px + 0.03f * scale, py + 0.005f * scale, 0.03f * scale);
}
void drawRoastChicken(float x, float y, float s) { glColor3f(0.85f, 0.45f, 0.15f); drawCircle(x, y, s, 20); glColor3f(0.75f, 0.35f, 0.10f); drawCircle(x - 0.9f * s, y + 0.18f * s, s * 0.45f, 16); }
void drawCake(float x, float y, float s) { glColor3f(1.0f, 0.4f, 0.7f); drawCircle(x, y + 0.12f * s, s * 0.6f, 18); glColor3f(1, 0.8f, 0.2f); glBegin(GL_LINES); glVertex2f(x, y + s * 0.38f); glVertex2f(x, y + s * 0.58f); glEnd(); glColor3f(1, 0.6f, 0.1f); drawCircle(x, y + s * 0.6f, s * 0.05f, 8); }
void drawGlass(float x, float y, float h) { glColor3f(0.85f, 0.95f, 1.0f); glBegin(GL_POLYGON); glVertex2f(x - 0.02f, y - 0.02f); glVertex2f(x + 0.02f, y - 0.02f); glVertex2f(x + 0.03f, y + h - 0.02f); glVertex2f(x - 0.03f, y + h - 0.02f); glEnd(); glColor3f(0.2f, 0.6f, 1.0f); drawCircle(x, y + h - 0.02f, 0.015f); }

void drawDiningTable(float centerX, float topY, float width, float depth) {
    float dx = -0.5f;
    glColor3f(0.55f, 0.33f, 0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX + dx - width / 2.0f, topY);
    glVertex2f(centerX + dx + width / 2.0f, topY);
    glVertex2f(centerX + dx + width / 2.0f, topY - depth);
    glVertex2f(centerX + dx - width / 2.0f, topY - depth);
    glEnd();
    // legs
    float legW = 0.04f, legH = 0.15f;
    glColor3f(0.45f, 0.25f, 0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(centerX + dx - width / 2.0f + 0.06f, topY - depth);
    glVertex2f(centerX + dx - width / 2.0f + 0.06f + legW, topY - depth);
    glVertex2f(centerX + dx - width / 2.0f + 0.06f + legW, topY - depth - legH);
    glVertex2f(centerX + dx - width / 2.0f + 0.06f, topY - depth - legH);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(centerX + dx + width / 2.0f - 0.06f - legW, topY - depth);
    glVertex2f(centerX + dx + width / 2.0f - 0.06f, topY - depth);
    glVertex2f(centerX + dx + width / 2.0f - 0.06f, topY - depth - legH);
    glVertex2f(centerX + dx + width / 2.0f - 0.06f - legW, topY - depth - legH);
    glEnd();

    float start = centerX + dx - width / 2.0f + 0.15f;
    for (int i = 0;i < 5;i++) {
        if (i == 2) continue;
        float px = start + i * ((width - 0.3f) / 4.0f);
        float py = topY - depth * 0.4f;
        drawPlateWithFood(px, py, 1.0f);
        drawGlass(px + 0.12f, py - 0.02f, 0.08f);
    }
    drawRoastChicken(centerX + dx - 0.09f, topY - depth * 0.09f, 0.11f);
    drawCake(centerX + dx + 0.13f, topY - depth * 0.2f, 0.15f);
}

void drawCabinetsAndFridge() {
    float rx1 = fridgeRX1, ry1 = fridgeRY1, rx2 = fridgeRX2, ry2 = fridgeRY2;
    glColor3f(0.92f, 0.95f, 0.97f);
    drawRect(rx1, ry2, rx2, ry1);
    glColor3f(0.82f, 0.88f, 0.92f);
    drawRect(rx2 - 0.05f, ry2, rx2, ry1);
    glColor3f(0.5f, 0.55f, 0.6f);
    glBegin(GL_LINE_LOOP); glVertex2f(rx1, ry2); glVertex2f(rx2, ry2); glVertex2f(rx2, ry1); glVertex2f(rx1, ry1); glEnd();
    glColor3f(0.6f, 0.6f, 0.6f);
    drawRect(rx2 - 0.04f, ry2 - 0.10f, rx2 - 0.02f, ry2 - 0.02f);
    drawRect(rx2 - 0.04f, ry2 - 0.30f, rx2 - 0.02f, ry2 - 0.20f);
    glColor3f(0.72f, 0.74f, 0.77f); glBegin(GL_LINES); glVertex2f(rx1 + 0.02f, ry2 - 0.20f); glVertex2f(rx2 - 0.02f, ry2 - 0.20f); glEnd();
    glColor3f(0.2f, 0.18f, 0.16f); glBegin(GL_POLYGON); glVertex2f(rx1, ry1); glVertex2f(rx2, ry1); glVertex2f(rx2, ry1 - 0.02f); glVertex2f(rx1, ry1 - 0.02f); glEnd();

    float cabGap = 0.02f, cabWidth = 0.40f, cabHeight = 0.16f;
    float cabRight = rx1 - cabGap;
    float cabLeft = cabRight - cabWidth;
    float cabTop = ry2 - 0.04f;
    float cabBottom = cabTop - cabHeight;
    glColor3f(0.82f, 0.78f, 0.72f);
    int doors = 3;
    float doorW = (cabWidth - 0.04f) / doors;
    float doorH = cabHeight - 0.02f;
    for (int i = 0;i < doors;i++) {
        float cx = cabLeft + 0.02f + i * (doorW + 0.01f);
        float cyTop = cabTop;
        float cyBottom = cyTop - doorH;
        drawRect(cx, cyTop, cx + doorW, cyBottom);
        glColor3f(0.60f, 0.55f, 0.48f);
        glBegin(GL_LINE_LOOP); glVertex2f(cx, cyTop); glVertex2f(cx + doorW, cyTop); glVertex2f(cx + doorW, cyBottom); glVertex2f(cx, cyBottom); glEnd();
        float handleW = doorW * 0.22f;
        float handleH = doorH * 0.12f;
        float hx = cx + doorW - handleW - 0.04f;
        float hyTop = cyTop - doorH * 0.5f + handleH * 0.5f;
        glColor3f(0.58f, 0.58f, 0.6f); drawRect(hx, hyTop + handleH, hx + handleW, hyTop);
        glColor3f(0.82f, 0.78f, 0.72f);
    }
}

// 7-seg digit drawing (simplified)
void drawSegmentRect(float x, float y, float w, float h) {
    drawRect(x, y, x + w, y - h);
}
void drawDigit7(int d, float x, float y, float size, float thickness, const float color[3]) {
    bool map[10][7] = {
        {1,1,1,1,1,1,0},{0,1,1,0,0,0,0},{1,1,0,1,1,0,1},{1,1,1,1,0,0,1},
        {0,1,1,0,0,1,1},{1,0,1,1,0,1,1},{1,0,1,1,1,1,1},{1,1,1,0,0,0,0},
        {1,1,1,1,1,1,1},{1,1,1,1,0,1,1}
    };
    bool segs[7];
    for (int i = 0;i < 7;i++) segs[i] = map[d][i];
    glColor3f(color[0], color[1], color[2]);
    float segLen = size, segTh = thickness;
    if (segs[0]) drawSegmentRect(x + segTh, y, segLen, segTh);
    if (segs[1]) drawSegmentRect(x + segTh + segLen, y - segTh, segTh, segLen);
    if (segs[2]) drawSegmentRect(x + segTh + segLen, y - segTh - segLen - segTh, segTh, segLen);
    if (segs[3]) drawSegmentRect(x + segTh, y - 2 * (segTh + segLen), segLen, segTh);
    if (segs[4]) drawSegmentRect(x, y - segTh - segLen - segTh, segTh, segLen);
    if (segs[5]) drawSegmentRect(x, y - segTh, segTh, segLen);
    if (segs[6]) drawSegmentRect(x + segTh, y - segTh - segLen, segLen, segTh);
}

void drawColon(float x, float y, float size, const float color[3]) {
    glColor3f(color[0], color[1], color[2]);
    drawCircle(x, y - size * 0.7f, size * 0.08f, 12);
    drawCircle(x, y - size * 1.6f, size * 0.08f, 12);
}

void drawDigitalClock(float topLeftX, float topLeftY, float size) {
    float thickness = size * 0.22f;
    const float colorOn[3] = { 1.0f, 0.12f, 0.12f };
    float spacing = size * 0.18f;
    float segLen = size, segTh = thickness;
    float totalW = 4.0f * (segLen + segTh) + 4.0f * spacing + segTh;
    float rectLeft = topLeftX - segTh * 0.6f;
    float rectTop = topLeftY + segTh * 0.6f;
    float rectRight = topLeftX + totalW + segTh * 0.6f;
    float rectBottom = topLeftY - (2.0f * (segTh + segLen)) - segTh * 0.6f;
    clockLeft = rectLeft; clockTop = rectTop; clockRight = rectRight; clockBottom = rectBottom;
    glColor3f(0.03f, 0.03f, 0.03f);
    drawRect(rectLeft, rectTop, rectRight, rectBottom);
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_LINE_LOOP); glVertex2f(rectLeft, rectTop); glVertex2f(rectRight, rectTop); glVertex2f(rectRight, rectBottom); glVertex2f(rectLeft, rectBottom); glEnd();

    int d1, d2, d3, d4; const char* ampm = "PM";
    if (clockAtMidnight) { d1 = 1; d2 = 2; d3 = 0; d4 = 0; ampm = "AM"; }
    else { d1 = 1; d2 = 1; d3 = 5; d4 = 9; ampm = "PM"; }
    float x = topLeftX, y = topLeftY;
    drawDigit7(d1, x, y, size, thickness, colorOn);
    x += size + thickness + spacing;
    drawDigit7(d2, x, y, size, thickness, colorOn);
    x += size + thickness + spacing * 0.8f;
    drawColon(x + 0.02f, y - size * 0.2f, size, colorOn);
    x += spacing + thickness;
    drawDigit7(d3, x, y, size, thickness, colorOn);
    x += size + thickness + spacing;
    drawDigit7(d4, x, y, size, thickness, colorOn);
    glColor3f(1.0f, 0.9f, 0.6f);
    drawText(rectRight - 0.08f, topLeftY - size * 0.9f, ampm);
}

// small star & moon functions used by ln scenes
void drawStar(float x, float y, float s) {
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1.0f, 1.0f, 0.92f, 0.18f); drawCircle(x, y, s * 3.5f, 16);
    glColor4f(1.0f, 1.0f, 0.92f, 0.08f); drawCircle(x, y, s * 6.0f, 12);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(1.0f, 1.0f, 0.92f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    int spikes = 5;
    for (int i = 0;i <= spikes * 2;i++) {
        float a = i * 3.1415926f / spikes;
        float r = (i % 2 == 0) ? s : s * 0.4f;
        glVertex2f(x + cosf(a) * r, y + sinf(a) * r);
    }
    glEnd();
    glDisable(GL_BLEND);
}

void drawMoon(float x, float y, float r) {
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(0.98f, 0.97f, 0.88f, 0.24f); drawCircle(x, y, r * 1.8f, 32);
    glColor4f(0.98f, 0.97f, 0.88f, 0.12f); drawCircle(x, y, r * 1.25f, 24);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.98f, 0.97f, 0.88f); drawCircle(x, y, r, 32);
    glColor3f(0.05f, 0.08f, 0.20f); drawCircle(x + r * 0.35f, y + r * 0.12f, r * 0.78f, 32);
    glDisable(GL_BLEND);
}

// ln: Title scene
void drawTitleScene() {
    // Use ln projection (viewLeft/right)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    // background
    glColor3f(0.02f, 0.03f, 0.12f);
    glBegin(GL_POLYGON);
    glVertex2f(viewLeft, viewBottom);
    glVertex2f(viewRight, viewBottom);
    glVertex2f(viewRight, viewTop);
    glVertex2f(viewLeft, viewTop);
    glEnd();

    drawMoon(-0.7f, 0.75f, 0.08f);
    drawStar(-0.86f, 0.82f, 0.014f); drawStar(-0.78f, 0.76f, 0.010f);
    drawStar(-0.60f, 0.84f, 0.012f); drawStar(-0.45f, 0.78f, 0.009f);
    drawStar(-0.18f, 0.83f, 0.010f); drawStar(0.02f, 0.88f, 0.006f);
    drawStar(0.25f, 0.80f, 0.011f); drawStar(0.55f, 0.86f, 0.013f);

    // ground
    glColor3f(0.04f, 0.04f, 0.06f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, -0.25f); glVertex2f(viewLeft, -0.25f); glEnd();

    glColor3f(0.1f, 0.1f, 0.2f);
    float bx = 0.45f, by = 0.45f, br = 0.22f;
    drawThoughtBubble(bx, by, br);
    drawText(bx - 0.19f, by + 0.02f, "My new year's");
    drawText(bx - 0.18f, by - 0.06f, "resolution is...");
    drawKevin(0.0f, -0.2f, 0.9f);
    glColor3f(1, 1, 1);
    drawText(-0.5f, 0.4f, "Kevin's New Year");
    drawText(-0.5f, -0.4f, "Press ENTER to see Kevin's resolution...");
    glutSwapBuffers();
}

// new year thinking scene
void drawThinkingScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.98f, 0.95f, 0.92f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, viewTop); glVertex2f(viewLeft, viewTop); glEnd();

    // window
    glColor3f(0.05f, 0.08f, 0.20f);
    glBegin(GL_POLYGON); glVertex2f(-0.9f, 0.2f); glVertex2f(-0.4f, 0.2f); glVertex2f(-0.4f, 0.8f); glVertex2f(-0.9f, 0.8f); glEnd();
    drawStar(-0.86f, 0.75f, 0.012f); drawStar(-0.82f, 0.70f, 0.008f); drawStar(-0.78f, 0.78f, 0.009f);
    drawMoon(-0.54f, 0.74f, 0.06f);

    drawDigitalClock(viewLeft + 0.06f, viewTop - 0.06f, 0.06f);
    drawCabinetsAndFridge();

    glColor3f(0.05f, 0.05f, 0.12f);
    drawText(0.9f, 0.02f, "Click on fridge to");
    drawText(0.9f, -0.05f, "have a drink instead");

    glColor3f(0.88f, 0.82f, 0.75f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, -0.4f); glVertex2f(viewLeft, -0.4f); glEnd();

    drawChandelier(0.0f, 0.85f, 1.1f, chandelierPhase);
    float tableTopY = -0.05f;
    drawDiningTable(0.0f, tableTopY, 1.6f, 0.28f);

    // Kevin animated position
    drawKevin(kevinPosX, kevinPosY, 0.98f);

    if (kevinHasDrink || kevinAction == K_DRINKING) {
        float scale = 0.98f;
        float handX = kevinPosX + 0.12f * scale;
        float handY = kevinPosY + 0.24f * scale;
        float mouthX = kevinPosX + 0.0f * scale;
        float mouthY = kevinPosY + 0.20f * scale;
        float gx = handX, gy = handY;
        if (kevinAction == K_DRINKING) {
            float t = (float)drinkTimer / 60.0f;
            if (t > 1.0f) t = 1.0f;
            gx = handX + (mouthX - handX) * t;
            gy = handY + (mouthY - handY) * t;
            drawGlass(gx, gy, 0.045f * (1.0f - 0.15f * t));
        }
        else {
            drawGlass(gx, gy, 0.05f);
        }
    }

    if (initialWalkDone && kevinAction == K_IDLE) {
        float bob = sinf(bubblePhase) * 0.02f;
        float bubbleCx = 0.45f, bubbleCy = 0.45f + bob, bubbleR = 0.22f;
        drawThoughtBubble(bubbleCx, bubbleCy, bubbleR);
        drawMiniKevinLift(bubbleCx, bubbleCy - 0.03f, 0.9f, liftPhase);
        glColor3f(0, 0, 0);
        drawText(0.2f, 0.2f, "My resolution is to eat");
        drawText(0.4f, 0.1f, "healthy and be fit!");
        drawText(-1.0f, -0.7f, "December 31st: Kevin has come up with a resolution just before new year");
        drawText(-0.4f, -0.9f, "Press ENTER to continue...");
    }

    glutSwapBuffers();
}

// ln: Next scene (outside party invites / houses)
void drawNextScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);
    // background + stars (similar to previous)
    glColor3f(0.02f, 0.03f, 0.12f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, viewTop); glVertex2f(viewLeft, viewTop); glEnd();
    drawMoon(-0.7f, 0.75f, 0.08f);
    drawStar(-0.86f, 0.82f, 0.014f); drawStar(-0.78f, 0.76f, 0.010f);
    drawStar(-0.60f, 0.84f, 0.012f); drawStar(-0.45f, 0.78f, 0.009f);
    drawStar(-0.18f, 0.83f, 0.010f); drawStar(0.02f, 0.88f, 0.006f);
    drawStar(0.25f, 0.80f, 0.011f); drawStar(0.55f, 0.86f, 0.013f);

    // darker ground
    glColor3f(0.04f, 0.04f, 0.06f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, -0.75f); glVertex2f(viewLeft, -0.75f); glEnd();

    // houses and friends
    for (int i = 0;i < HOUSE_COUNT;i++) {
        float hx = houseX[i], hy = houseY[i], hw = houseW[i], hh = houseH[i];
        float r = 0.12f + 0.03f * (i % 5);
        float g = 0.10f + 0.025f * ((i + 2) % 5);
        float b = 0.14f + 0.035f * ((i + 4) % 5);
        glColor3f(r, g, b);
        drawRect(hx, hy, hx + hw, hy + hh);
        glColor3f(1.0f, 0.84f, 0.35f);
        drawRect(hx + hw * 0.12f, hy + hh * 0.6f, hx + hw * 0.25f, hy + hh * 0.45f);
        drawRect(hx + hw * 0.62f, hy + hh * 0.5f, hx + hw * 0.75f, hy + hh * 0.35f);
    }

    // friends drawn if activated
    for (int i = 0;i < HOUSE_COUNT;i++) {
        if (friendActivated[i] || friendWalkingArr[i]) {
            glColor3f(0.95f, 0.95f, 1.0f);
            // simplified friend draw: small Kevin-like figure
            float fx = friendPosX[i], fy = friendPosY[i];
            drawKevin(fx, fy, 1.0f);
        }
    }

    // Kevin at meeting point
    drawKevin(nextKevinX, nextKevinY, 0.95f);

    glColor3f(0.8f, 0.8f, 0.9f);
    drawText(-0.3f, 0.0f, "Click houses to invite friends to join the celebration");
    drawText(-1.0f, -0.9f, "Click clock on top left to celebrate the new year!                               Enter to continue...");

    glutSwapBuffers();
}

void drawReturnKitchenScene() {
    // background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.98f, 0.95f, 0.92f);
    drawRect(viewLeft, viewBottom, viewRight, viewTop);

    // window stars & moon
    glColor3f(0.05f, 0.08f, 0.20f); glBegin(GL_POLYGON);
    glVertex2f(-0.9f, 0.2f); glVertex2f(-0.4f, 0.2f); glVertex2f(-0.4f, 0.8f); glVertex2f(-0.9f, 0.8f);
    glEnd();
    drawStar(-0.86f, 0.75f, 0.012f); drawMoon(-0.54f, 0.74f, 0.06f);

    drawCabinetsAndFridge();
    glColor3f(0.88f, 0.82f, 0.75f); drawRect(viewLeft, viewBottom, viewRight, -0.4f);
    drawChandelier(0.0f, 0.85f, 1.1f, chandelierPhase);
    float tableTopY = -0.05f; drawDiningTable(0.0f, tableTopY, 1.6f, 0.28f);

    // anomation logic
    if (movePhase == 0) {
        if (kevinX < 0.0f) kevinX += 0.01f;
        else movePhase = 1;
    }
    if (movePhase == 2) {
        if (kevinX > -1.2f) kevinX -= 0.01f;
        else { showKitchenReturn = false; showPlateScene = true; }
    }
    drawKevin(kevinX, -0.38f, 1.0f);

    if (movePhase == 1) {
        float bx = 0.45f, by = 0.45f, br = 0.22f;
        drawThoughtBubble(bx, by, br);
        drawText(bx - 0.03f, by + 0.02f, "...");
        drawText(-0.7f, -0.9f, "Press ENTER to find out Kevin's choice...");
    }

    if (movePhase == 2) {
        float bx = 0.45f, by = 0.45f, br = 0.22f;
        drawThoughtBubble(bx, by, br);
        drawText(bx - 0.03f, by + 0.02f, "no!");
    }

    drawText(-0.9f, -0.7f, "January 1st: Kevin saw the delicious food and was tempted...");

    glutSwapBuffers();
}

void drawPlateScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.02f, 0.03f, 0.12f);
    drawRect(viewLeft, viewBottom, viewRight, viewTop);

    drawMoon(-0.7f, 0.75f, 0.08f);
    drawStar(-0.86f, 0.82f, 0.014f); drawStar(-0.78f, 0.76f, 0.010f);
    drawStar(-0.60f, 0.84f, 0.012f); drawStar(-0.45f, 0.78f, 0.009f);

    if (fireworksActive) {
        const float fwColors[4][3] = { {1.0f,0.4f,0.2f},{0.9f,0.9f,0.25f},{0.4f,0.9f,0.95f},{0.9f,0.5f,0.95f} };
        float fwX[5] = { -0.4f, -0.05f, 0.2f, 0.5f, 0.85f };
        float fwY[5] = { 0.6f, 0.78f, 0.75f, 0.7f, 0.72f };
        float fwR[5] = { 0.05f, 0.07f, 0.06f, 0.055f, 0.065f };
        for (int i = 0;i < 5;i++) drawFirework(fwX[i], fwY[i], fwR[i], fireworksPhase + i * 1.3f, fwColors[i % 4]);
    }

    // houses
    for (int i = 0;i < HOUSE_COUNT;i++) {
        float hx = houseX[i], hy = houseY[i], hw = houseW[i], hh = houseH[i];
        float r = 0.12f + 0.03f * (i % 5);
        float g = 0.10f + 0.025f * ((i + 2) % 5);
        float b = 0.14f + 0.035f * ((i + 4) % 5);
        glColor3f(r, g, b);
        drawRect(hx, hy, hx + hw, hy + hh);
        glColor3f(1.0f, 0.84f, 0.35f);
        drawRect(hx + hw * 0.12f, hy + hh * 0.6f, hx + hw * 0.25f, hy + hh * 0.45f);
        drawRect(hx + hw * 0.62f, hy + hh * 0.5f, hx + hw * 0.75f, hy + hh * 0.35f);
    }

    // ground
    glColor3f(0.04f, 0.04f, 0.06f);
    glBegin(GL_POLYGON); glVertex2f(viewLeft, viewBottom); glVertex2f(viewRight, viewBottom); glVertex2f(viewRight, -0.75f); glVertex2f(viewLeft, -0.75f); glEnd();

    // Kevin centered
    glColor3f(0.2f, 0.3f, 0.8f);
    drawCircle(0.0f, -0.6f, 0.15f, 30);
    drawKevin(0.0f, -0.7f, 1.0f);
    drawPlateWithFood(0.12f, -0.65f);

    float bx = 0.45f, by = -0.1f, br = 0.22f;
    drawThoughtBubble(bx, by, br);
    drawText(bx - 0.18f, by + 0.02f, "I'll do it");
    drawText(bx - 0.18f, by - 0.04f, "next year...");
    glColor3f(1, 1, 1);
    drawText(-0.2f, 0.0f, "Oh Kevin...");
    glutSwapBuffers();
}

void drawFirework(float cx, float cy, float baseR, float phase, const float color[3]) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(color[0], color[1], color[2], 0.12f); drawCircle(cx, cy, baseR * 2.4f, 24);
    glColor4f(color[0], color[1], color[2], 0.08f); drawCircle(cx, cy, baseR * 3.6f, 18);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float r = baseR * (0.6f + 0.8f * (0.5f + 0.5f * sinf(phase)));
    int spikes = 12;
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_LINES);
    for (int i = 0;i < spikes;i++) {
        float a = 2.0f * 3.1415926f * i / spikes;
        float ex = cosf(a) * r; float ey = sinf(a) * r;
        glVertex2f(cx, cy); glVertex2f(cx + ex, cy + ey);
    }
    glEnd();
    for (int i = 0;i < 8;i++) {
        float a = 2.0f * 3.1415926f * i / 8.0f + phase * 0.3f;
        float px = cx + cosf(a) * r * 1.15f;
        float py = cy + sinf(a) * r * 1.15f;
        glColor3f(fminf(1.0f, color[0] + 0.2f), fminf(1.0f, color[1] + 0.2f), fminf(1.0f, color[2] + 0.2f));
        drawCircle(px, py, baseR * 0.12f, 10);
    }
    glDisable(GL_BLEND);
}

// animation timer
void updateAnimation(int value) {
    // advance phases
    bubblePhase += 0.06f;
    liftPhase += 0.25f;
    chandelierPhase += 0.02f;
    fireworksPhase += 0.12f;

    // kevin walking logic for kevinWalking sequences
    if (kevinWalking) {
        float dx = kevinTargetX - kevinPosX;
        float step = kevinSpeed;
        if (fabsf(dx) <= step) {
            kevinPosX = kevinTargetX;
            kevinWalking = false;
            if (initialWalkStarted && !initialWalkDone && fabsf(kevinPosX - 0.0f) < 0.001f) {
                initialWalkDone = true;
                initialWalkStarted = false;
                animateBubble = true;
            }
        }
        else {
            kevinPosX += (dx > 0.0f ? step : -step);
        }
    }

    // advance friends walking
    for (int i = 0;i < HOUSE_COUNT;i++) {
        if (friendWalkingArr[i]) {
            float dx = friendTargetX[i] - friendPosX[i];
            float dy = friendTargetY[i] - friendPosY[i];
            float dist = sqrtf(dx * dx + dy * dy);
            float step = friendSpeedArr[i];
            if (dist <= step || dist == 0.0f) {
                friendPosX[i] = friendTargetX[i];
                friendPosY[i] = friendTargetY[i];
                friendWalkingArr[i] = false;
            }
            else {
                float nx = dx / dist;
                float ny = dy / dist;
                friendPosX[i] += nx * step;
                friendPosY[i] += ny * step;
            }
        }
    }

    // interactive Kevin action state machine
    if (kevinAction == K_WALK_TO_FRIDGE && !kevinWalking) {
        kevinAction = K_PICK_DRINK;
        pickTimer = 0;
    }
    else if (kevinAction == K_PICK_DRINK) {
        pickTimer++;
        if (pickTimer == 1) kevinHasDrink = true;
        if (pickTimer > 20) {
            kevinAction = K_WALK_BACK;
            kevinTargetX = 0.0f;
            kevinSpeed = fabs(kevinTargetX - kevinPosX) / 60.0f;
            kevinWalking = true;
        }
    }
    else if (kevinAction == K_WALK_BACK && !kevinWalking) {
        kevinAction = K_DRINKING;
        drinkTimer = 0;
    }
    else if (kevinAction == K_DRINKING) {
        drinkTimer++;
        if (drinkTimer > 80) {
            kevinAction = K_IDLE;
            kevinHasDrink = false;
        }
    }

    if (bubblePhase > 10000.0f) bubblePhase = 0.0f;
    if (liftPhase > 10000.0f) liftPhase = 0.0f;
    if (chandelierPhase > 10000.0f) chandelierPhase = 0.0f;
    if (fireworksPhase > 10000.0f) fireworksPhase = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateAnimation, 0);
}

// input handling 
void mouseClick(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    float nx = (float)x / (float)w; // 0..1 left->right
    float ny = 1.0f - (float)y / (float)h; // 0..1 bottom->top

    // Map mouse to book coordinates for the cover (book drawn in -1..1 coords)
    // Convert to ogl coords used by the ks scenes: oglX in [-1,1], oglY in [-1,1]
    float oglX = nx * 2.0f - 1.0f;
    float oglY = ny * 2.0f - 1.0f;

    if (showBook) {
        // left half of book page region corresponds approximately to x in [-0.6, 0.0] in kevinstory draw
        // We'll map relative to our -1..1 coords and approximate click region.
        if (oglX >= -0.6f && oglX <= 0.0f) {
            // Left page -> Kevin's Christmas
            showBook = false;
            xmas_showCouchScene = true;
            xmas_showBook = false;
            xmas_peopleActive = false; // will be enabled when selling scene starts
            xmas_peoplePosX = -1.3f;
            xmas_showDialogue = false;
            glutPostRedisplay();
            return;
        }
        // Right page -> Kevin's New Year
        if (oglX > 0.0f && oglX <= 0.6f) {
            showBook = false;
            // initialize lance flags / start at Title Scene
            showTitle = true;
            showThinking = false;
            showNext = false;
            showKitchenReturn = false;
            showPlateScene = false;
            initialWalkStarted = false;
            initialWalkDone = false;
            kevinPosX = viewLeft - 0.12f;
            // reset friends
            for (int i = 0;i < HOUSE_COUNT;i++) {
                friendActivated[i] = false;
                friendWalkingArr[i] = false;
                friendPosX[i] = 0; friendPosY[i] = 0;
                friendTargetX[i] = 0; friendTargetY[i] = 0; friendSpeedArr[i] = 0;
            }
            // start ln timer if needed
            glutTimerFunc(30, updateAnimation, 0);
            glutPostRedisplay();
            return;
        }
    }

    // If we're in Kevin's Christmas scenes, forward to its mouse handler behavior (only book click was needed originally).
    if (xmas_showCouchScene || xmas_showToyScene || xmas_showSellingScene || xmas_showHomeCelebration) {
        // ks code only had book click handler; no further mouse handling here - return
        return;
    }

    // Map clicks for Lance scenes using world coords mapping
    if (showThinking || showNext || showKitchenReturn || showPlateScene || showTitle) {
        // convert window coords to world coords for ln scenes
        float wx = viewLeft + nx * (viewRight - viewLeft);
        float wy = viewBottom + ny * (viewTop - viewBottom);

        // Check if click on clock region (toggle midnight)
        if (wx >= clockLeft && wx <= clockRight && wy <= clockTop && wy >= clockBottom) {
            clockAtMidnight = true;
            fireworksActive = true;
            fireworksPhase = 0.0f;
            glutTimerFunc(30, updateAnimation, 0);
            glutPostRedisplay();
            return;
        }

        // In showNext (outside neighborhood), clicking houses invites friends
        if (showNext) {
            for (int i = 0;i < HOUSE_COUNT;i++) {
                float hx = houseX[i], hy = houseY[i], hw = houseW[i], hh = houseH[i];
                if (wx >= hx && wx <= hx + hw && wy >= hy && wy <= hy + hh) {
                    if (!friendActivated[i] && !friendWalkingArr[i]) {
                        friendActivated[i] = true;
                        friendWalkingArr[i] = true;
                        // start at door center
                        float doorCenterX = hx + hw * 0.5f;
                        friendPosX[i] = doorCenterX;
                        friendPosY[i] = hy + 0.02f;
                        int slot = 0;
                        for (int j = 0;j < HOUSE_COUNT;j++) if (friendActivated[j] && j != i) ++slot;
                        float slotOffset = -0.33f + 0.22f * slot;
                        friendTargetX[i] = nextKevinX + slotOffset;
                        friendTargetY[i] = nextKevinY;
                        float dx = friendTargetX[i] - friendPosX[i];
                        float dy = friendTargetY[i] - friendPosY[i];
                        friendSpeedArr[i] = sqrtf(dx * dx + dy * dy) / 60.0f;
                    }
                    return;
                }
            }
        }

        // Fridge clicking when Kevin idle
        if (kevinWalking || kevinAction != K_IDLE) return;
        if (wx >= fridgeRX1 && wx <= fridgeRX2 && wy >= fridgeRY1 && wy <= fridgeRY2) {
            kevinAction = K_WALK_TO_FRIDGE;
            kevinTargetX = fridgeRX1 - 0.12f;
            kevinSpeed = fabs(kevinTargetX - kevinPosX) / 60.0f;
            kevinWalking = true;
            return;
        }
    }
}

void keyPressed(unsigned char key, int x, int y) {
    if (key == 13) { // ENTER
        // If book is shown, ignore (enter doesn't do anything)
        if (showBook) {
            // do nothing
        }
        else {
            // If in Kevin's Christmas flow
            if (xmas_showCouchScene) {
                if (!xmas_showDialogue) {
                    xmas_showDialogue = true;
                }
                else {
                    xmas_showCouchScene = false;
                    xmas_showToyScene = true;
                }
                glutPostRedisplay();
                return;
            }
            else if (xmas_showToyScene) {
                xmas_showToyScene = false;
                xmas_showSellingScene = true;
                xmas_peopleActive = true;
                xmas_peoplePosX = -1.3f;
                glutTimerFunc(30, xmas_updatePeople, 0);
                glutPostRedisplay();
                return;
            }
            else if (xmas_showSellingScene) {
                xmas_showSellingScene = false;
                xmas_showHomeCelebration = true;
                xmas_peopleActive = false;
                glutPostRedisplay();
                return;
            }
            else if (xmas_showHomeCelebration) {
                // End of Christmas story → return to book
                xmas_showHomeCelebration = false;
                showBook = true;
                glutPostRedisplay();
                return;
            }

            // Lance flow
            if (showTitle) {
                showTitle = false;
                showThinking = true;
                animateBubble = false;
                kevinPosX = viewLeft - 0.12f;
                kevinPosY = -0.38f;
                kevinTargetX = 0.0f;
                kevinSpeed = fabs(kevinTargetX - kevinPosX) / 90.0f;
                kevinWalking = true;
                initialWalkStarted = true;
                initialWalkDone = false;
                glutTimerFunc(30, updateAnimation, 0);
                return;
            }
            else if (showThinking) {
                showThinking = false;
                showNext = true;
                animateBubble = false;
                kevinWalking = false;
                return;
            }
            else if (showNext) {
                // pressing enter moves to kitchen return scene
                showNext = false;
                showKitchenReturn = true;
                movePhase = 0;
                kevinX = viewLeft - 0.8f;
                return;
            }
            else if (showKitchenReturn) {
                if (movePhase == 1) {
                    movePhase = 2;
                    return;
                }
            }
            else if (showPlateScene) {
                // in plate scene, Enter might reset to title or quit; do nothing for now
                showPlateScene = false;
                showBook = true;       // Return to book
                glutPostRedisplay();
                return;
            }
        }
    }

    glutPostRedisplay();
}

void display() {
    if (showBook) {
        // Draw book cover: left page and right page
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

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

        // Spine
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_LINES);
        glVertex2f(0.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();

        // Titles
        glColor3f(0.1f, 0.1f, 0.1f);
        drawText(-0.50f, 0.0f, "Kevin's Christmas");
        drawText(0.10f, 0.0f, "Kevin's New Year");

        glutSwapBuffers();
        return;
    }

    // If Kevin's Christmas is active
    if (xmas_showCouchScene) { xmas_drawCouchScene(); return; }
    if (xmas_showToyScene) { xmas_drawToyScene(); return; }
    if (xmas_showSellingScene) { xmas_drawSellingScene(); return; }
    if (xmas_showHomeCelebration) { xmas_drawHomeCelebration(); return; }

    // If LancenLEX/New Year is active
    if (showTitle) { drawTitleScene(); return; }
    if (showThinking) { drawThinkingScene(); return; }
    if (showNext) { drawNextScene(); return; }
    if (showKitchenReturn) { drawReturnKitchenScene(); return; }
    if (showPlateScene) { drawPlateScene(); return; }
}

// Reshape - for scaling and stuff
void reshape(int w, int h) {
    if (w <= 0) w = 1;
    if (h <= 0) h = 1;
    glViewport(0, 0, w, h);

    // For lance scenes we want aspect-aware orthographic extents:
    float aspect = (float)w / (float)h;
    viewTop = 1.0f; viewBottom = -1.0f;
    viewLeft = -aspect; viewRight = aspect;

    // Set a default projection; individual scenes will set their own as needed
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void initAll() {
    glClearColor(0.85f, 0.9f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(viewLeft, viewRight, viewBottom, viewTop, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Kevin Combined: Christmas & New Year");

    initAll();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyPressed);

    glutMainLoop();
    return 0;
}
