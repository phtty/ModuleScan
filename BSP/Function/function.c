#include "function.h"
#include "display.h"
#include "pic.h"

void display_fill(uint8_t color)
{
    memset(pixel_map, color, DISRAM_SIZE);

    convert_pixelmap();
}

void display_stop_flag(void)
{
    for (uint8_t i = 0; i < SCREEN_PIXEL_COL; i++) {
        for (uint8_t j = 0; j < SCREEN_PIXEL_ROW; j++) {
            if (stop_flag_bk[i * SCREEN_PIXEL_ROW / 8 + j / 8] & (uint8_t)(0x80 >> (j % 8))) {
                pixel_map[i * SCREEN_PIXEL_ROW + j] = red;
            } else {
                pixel_map[i * SCREEN_PIXEL_ROW + j] = black;
            }
        }
    }
    for (uint8_t i = 0; i < SCREEN_PIXEL_COL; i++) {
        for (uint8_t j = 0; j < SCREEN_PIXEL_ROW; j++) {
            if (stop_flag[i * SCREEN_PIXEL_ROW / 8 + j / 8] & (uint8_t)(0x80 >> (j % 8))) {
                pixel_map[i * SCREEN_PIXEL_ROW + j] = white;
            }
        }
    }
    convert_pixelmap();
}

void display_high_limit(void)
{
    for (uint8_t i = 0; i < SCREEN_PIXEL_COL; i++) {
        for (uint8_t j = 0; j < SCREEN_PIXEL_ROW; j++) {
            if (high_limit[i * SCREEN_PIXEL_ROW / 8 + j / 8] & (uint8_t)(0x80 >> (j % 8))) {
                pixel_map[i * SCREEN_PIXEL_ROW + j] = white;
            } else {
                pixel_map[i * SCREEN_PIXEL_ROW + j] = black;
            }
        }
    }
    convert_pixelmap();
}
