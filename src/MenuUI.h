#include "Drawable.h"
#include "Block.h"
#include "BlockOperations.h"
#include "Camera.h"
#include "Level.h"
#include "Array.h"

/**
 * Builds the block selection bar
 * 
 * @param rds A pointer to the rendering details
 * @param tds A pointer to the transformation details
 * @param drabs A pointer to the drawable details
 */
void BuildSelectMenu(RenderDetails* rds, TransformationDetails* tds, Drawables* drabs);

#pragma region Folding Sidebar

struct FoldingSidebar
    {
    unsigned int tid;   // the personal transform for this sidebar
    union {
        Array rids; // the render IDs of the menu items
        BLOCK block;
    };
    int folded; // has it been folded
    };
typedef struct FoldingSidebar FoldingSidebar;

// RIDICULOUSLY TEMPORARY
#define RenderContainer RenderDetails* rds, TransformationDetails* tds, Drawables* drabs

FoldingSidebar CreateFoldingSidebar(RenderContainer, int position, BLOCK icon);

void ToggleFoldingSidebar(RenderContainer, FoldingSidebar* fsb);

#pragma endregion

#pragma region Side Menu

struct SideFoldingMenu
    {
    unsigned int tid;   // the personal transform for this sidebar
    union {
        Array rids; // the render IDs of the menu items
    };
    int folded; // has it been folded
    };
typedef struct SideFoldingMenu SideFoldingMenu;

// RIDICULOUSLY TEMPORARY
#define RenderContainer RenderDetails* rds, TransformationDetails* tds, Drawables* drabs

CreateSideFoldingMenu(RenderContainer, vec2 position, FoldingSidebar* sidebars);

#pragma endregion
