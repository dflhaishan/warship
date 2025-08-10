#include "lv_port.h"
#include "lvgl.h"
#include "hal.h"
#include "bsp_tft_lcd.h"

#define CONFIG_SCREEN_HOR_RES    480
#define CONFIG_SCREEN_VER_RES    800
#define CONFIG_SCREEN_BUFFER_SIZE   (CONFIG_SCREEN_HOR_RES * CONFIG_SCREEN_VER_RES)


static lv_disp_drv_t* disp_drv_p;

static void disp_flush_cb(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    disp_drv_p = disp;

    lv_coord_t x;
    lv_coord_t y;
    uint16_t *color_pp = (uint16_t *)color_p;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
            /*Put a pixel to the display. For example:*/
            /*put_px(x, y, *px_map)*/
            LCD_PutPixel(x, y, *color_pp);
            color_pp++;
        }
    }

    lv_disp_flush_ready(disp);
}

static void disp_send_finish_callback()
{
    lv_disp_flush_ready(disp_drv_p);
}

static void disp_wait_cb(lv_disp_drv_t* disp_drv)
{
    __asm volatile("wfi");
}

void lv_port_disp_init()
{
    HAL::Display_SetSendFinishCallback(disp_send_finish_callback);

#if 0
    static lv_color_t lv_disp_buf[CONFIG_SCREEN_BUFFER_SIZE];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf, NULL, CONFIG_SCREEN_BUFFER_SIZE);
#else
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf_1[CONFIG_SCREEN_HOR_RES * 10];                          /*A buffer for 10 rows*/
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, CONFIG_SCREEN_HOR_RES * 10);   /*Initialize the display buffer*/
#endif

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = CONFIG_SCREEN_HOR_RES;
    disp_drv.ver_res = CONFIG_SCREEN_VER_RES;
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.wait_cb = disp_wait_cb;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);
}
void lv_user_gui_init(void)
{
#if 1
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 200, 400);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, NULL, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
#endif
}
