#include "display.h"
#include "hub75.h"

/**
 * @brief P15的扫描
 * 
 */
void convert_pixelmap(void)
{
    uint16_t ModuelGroup = 0;
    uint8_t  row_cnt = 0, col_cnt = 0;

    for (uint16_t map_cnt = 0; map_cnt < DISRAM_SIZE; map_cnt++) {
        row_cnt     = map_cnt / SCREEN_PIXEL_ROW; // 屏幕的行标
        col_cnt     = map_cnt % SCREEN_PIXEL_ROW;
        ModuelGroup = col_cnt / 4 + (row_cnt / 4 * (MODULE_PER_ROW * 4)); // 组标

        switch (row_cnt % 4) {
            case 0:
                hub75_buff[2 * (3 - col_cnt % 4) + ModuelGroup * GROUP_SIZE] = pixel_map[map_cnt];
                break;

            case 1:
                hub75_buff[2 * (3 - col_cnt % 4) + 1 + ModuelGroup * GROUP_SIZE] = pixel_map[map_cnt];
                break;

            case 2:
                hub75_buff[2 * (col_cnt % 4) + 9 + ModuelGroup * GROUP_SIZE] = pixel_map[map_cnt];
                break;

            case 3:
                hub75_buff[2 * (col_cnt % 4) + 8 + ModuelGroup * GROUP_SIZE] = pixel_map[map_cnt];
                break;

            default:
                break;
        }
    }
}

/**
 * @brief P6模组的扫描
 * 
 */
void convert_pixelmap_p6(void)
{
    uint16_t ModuelGroup = 0;
    uint8_t  row_cnt = 0, col_cnt = 0;

    for (uint16_t map_cnt = 0; map_cnt < DISRAM_SIZE; map_cnt++) {
        row_cnt     = map_cnt / SCREEN_PIXEL_ROW; // 屏幕的行标
        col_cnt     = map_cnt % SCREEN_PIXEL_ROW;
        ModuelGroup = row_cnt / 16 * 8 + row_cnt % 8; // 组标

        // 在单行扫描内判断是上半行还是下半行
        if ((row_cnt % 16) >= 8) // 上半行
            hub75_buff[col_cnt + (col_cnt / MODULE_PIXEL_ROW * MODULE_PIXEL_ROW) + (ModuelGroup * GROUP_SIZE)] =
                pixel_map[map_cnt];
        else // 下半行
            hub75_buff[col_cnt + ((col_cnt / MODULE_PIXEL_ROW + 1) * MODULE_PIXEL_ROW) + ModuelGroup * GROUP_SIZE] =
                pixel_map[map_cnt];
    }
}
