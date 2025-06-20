#pragma once

enum EVIEW_ID {
    NUM_RVM_VIEWS = 1,
    NUM_PLAYER_VIEWS = 3,
    NUM_RENDER_VIEWS = 21,
    NUM_EVIEWS = 22,
    EVIEW_LAST_ENVMAP = 21,
    EVIEW_FIRST_ENVMAP = 16,
    EVIEW_LAST_RVM = 3,
    EVIEW_FIRST_RVM = 3,
    EVIEW_LAST_PLAYER = 3,
    EVIEW_FIRST_PLAYER = 1,
    EVIEW_LAST_RENDER = 21,
    EVIEW_FIRST_RENDER = 1,
    EVIEW_LAST = 21,
    EVIEW_FIRST = 0,
    EVIEW_ENVMAP0D = 21,
    EVIEW_ENVMAP0U = 20,
    EVIEW_ENVMAP0L = 19,
    EVIEW_ENVMAP0B = 18,
    EVIEW_ENVMAP0R = 17,
    EVIEW_ENVMAP0F = 16,
    EVIEW_SHADOWMATTE = 15,
    EVIEW_SHADOWMAP2 = 14,
    EVIEW_SHADOWMAP1 = 13,
    EVIEW_HDR_SCENE = 12,
    EVIEW_QUADRANT_BOTTOM_RIGHT = 11,
    EVIEW_QUADRANT_BOTTOM_LEFT = 10,
    EVIEW_QUADRANT_TOP_RIGHT = 9,
    EVIEW_QUADRANT_TOP_LEFT = 8,
    EVIEW_PLAYER2_SPECULAR = 7,
    EVIEW_PLAYER1_SPECULAR = 6,
    EVIEW_PLAYER2_GLOW = 5,
    EVIEW_PLAYER1_GLOW = 4,
    EVIEW_PLAYER1_RVM = 3,
    EVIEW_PLAYER2 = 2,
    EVIEW_PLAYER1 = 1,
    EVIEW_FLAILER = 0,
    EVIEW_NONE = -1,
};

enum eVisibleState {
    EVISIBLESTATE_FULL = 2,
    EVISIBLESTATE_PARTIAL = 1,
    EVISIBLESTATE_NOT = 0,
};

enum TARGET_ID {
    NUM_RENDER_TARGETS = 17,
    LAST_RENDER_TARGET = 16,
    FIRST_RENDER_TARGET = 0,
    TOTAL_RENDER_TARGETS = 17,
    TARGET_ENVMAP0_FULL = 16,
    TARGET_ENVMAP0D = 15,
    TARGET_ENVMAP0U = 14,
    TARGET_ENVMAP0L = 13,
    TARGET_ENVMAP0B = 12,
    TARGET_ENVMAP0R = 11,
    TARGET_ENVMAP0F = 10,
    TARGET_QUADRANT_BOTTOM_RIGHT = 9,
    TARGET_QUADRANT_BOTTOM_LEFT = 8,
    TARGET_QUADRANT_TOP_RIGHT = 7,
    TARGET_QUADRANT_TOP_LEFT = 6,
    TARGET_PLAYER2_SPECULAR = 5,
    TARGET_PLAYER1_SPECULAR = 4,
    TARGET_PLAYER1_RVM = 3,
    TARGET_PLAYER2 = 2,
    TARGET_PLAYER1 = 1,
    TARGET_FLAYER = 0,
};

enum FILTER_ID {
    FILTER_TOTAL = 11,
    FILTER_PIXELATE = 10,
    FILTER_EFB_XFB_AA = 9,
    FILTER_CONTRAST_INTENSITY = 8,
    FILTER_GLOWBLOOM = 7,
    FILTER_MOTIONBLUR = 6,
    FILTER_REFLECTION = 5,
    FILTER_SPHERE_MAP = 4,
    FILTER_CUBE_FACES = 3,
    FILTER_EFB_XFB = 2,
    FILTER_DEFAULT = 1,
    FILTER_OFF = 0,
};
