#pragma once
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int COLS = WINDOW_WIDTH / CELL_SIZE;
const int ROWS = WINDOW_HEIGHT / CELL_SIZE;

// Button positions
const int BUTTON_Y_START = 600;
const int BUTTON_Y_END = 650;
const int BUTTON_HEIGHT = 50;

// Button X positions
const int BTN_BACK_X1 = 0;
const int BTN_BACK_X2 = 70;
const int BTN_START_X1 = 70;
const int BTN_START_X2 = 140;
const int BTN_RESET_X1 = 140;
const int BTN_RESET_X2 = 210;
const int BTN_RANDOM_X1 = 210;
const int BTN_RANDOM_X2 = 280;
const int BTN_STEP_X1 = 280;
const int BTN_STEP_X2 = 350;
const int BTN_GEN_X1 = 350;
const int BTN_GEN_X2 = 420;

// Frame rates
const int FPS_LOW = 6;
const int FPS_HIGH = 60;

// Generation limit
const int MAX_GENERATION = 999;

extern int Theme; // 0为默认，1为电棍， 2为钻头
extern int FPS; // 0为6帧， 1为无限制

