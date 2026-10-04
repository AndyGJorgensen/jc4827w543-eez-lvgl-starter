/**
 * LVGL 9.x configuration for JC4827W543C (480x272, RGB565).
 * Anything not defined here takes the default from lv_conf_internal.h.
 */
#ifndef LV_CONF_H
#define LV_CONF_H

/* No #includes here: LVGL's assembly (.S) files also include this header */

/*====================
   COLOR SETTINGS
 *====================*/
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/
/* Use the C library malloc so large allocations can land in PSRAM */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_CLIB
#define LV_USE_STDLIB_STRING    LV_STDLIB_CLIB
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_CLIB

/*====================
   HAL SETTINGS
 *====================*/
#define LV_DEF_REFR_PERIOD  15      /*[ms]*/
#define LV_DPI_DEF          130

/*=======================
 * RENDERING
 *=======================*/
#define LV_USE_OS   LV_OS_NONE
#define LV_DRAW_BUF_ALIGN   4
#define LV_DRAW_SW_SUPPORT_RGB565   1
#define LV_USE_DRAW_SW_ASM          LV_DRAW_SW_ASM_NONE

/*=======================
 * LOGGING / ASSERTS
 *=======================*/
#define LV_USE_LOG 0
#define LV_USE_ASSERT_NULL          1
#define LV_USE_ASSERT_MALLOC        1

/*==================
 *   FONT USAGE
 *===================*/
/* Fonts referenced by the EEZ design (keep in sync with the project) */
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_48 1

#define LV_FONT_DEFAULT &lv_font_montserrat_14

/*==================
 * WIDGETS / THEMES
 *===================*/
/* All standard widgets are enabled by default in LVGL 9 */
#define LV_USE_THEME_DEFAULT 1
#define LV_THEME_DEFAULT_DARK 0

/*==================
 * DEMOS / EXAMPLES
 *===================*/
#define LV_BUILD_EXAMPLES 0
#define LV_USE_DEMO_WIDGETS 0

#endif /*LV_CONF_H*/
