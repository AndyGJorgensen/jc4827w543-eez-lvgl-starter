#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTINGS = 2,
    SCREEN_ID_WIFI = 3,
    SCREEN_ID_SAVED_WI_FI = 4,
    _SCREEN_ID_LAST = 4
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *settings;
    lv_obj_t *wifi;
    lv_obj_t *saved_wi_fi;
    lv_obj_t *obj0;
    lv_obj_t *battery_bar;
    lv_obj_t *battery_lbl;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *sound_test_btn;
    lv_obj_t *sd_status_val;
    lv_obj_t *audio_status_val;
    lv_obj_t *obj3;
    lv_obj_t *wifi_net_lbl;
    lv_obj_t *wifi_network_dd;
    lv_obj_t *wifi_password;
    lv_obj_t *wifi_scan_btn;
    lv_obj_t *wifi_connect_btn;
    lv_obj_t *wifi_disconnect_btn;
    lv_obj_t *wifi_status_lbl;
    lv_obj_t *wifi_status_val;
    lv_obj_t *wifi_ssid_lbl;
    lv_obj_t *wifi_ssid_val;
    lv_obj_t *wifi_ip_lbl;
    lv_obj_t *wifi_ip_val;
    lv_obj_t *wifi_hostname_lbl;
    lv_obj_t *wifi_hostname_val;
    lv_obj_t *wifi_rssi_lbl;
    lv_obj_t *wifi_rssi_val;
    lv_obj_t *wifi_mac_lbl;
    lv_obj_t *wifi_mac_val;
    lv_obj_t *ota_lbl;
    lv_obj_t *ota_switch;
    lv_obj_t *ota_status_lbl;
    lv_obj_t *ota_status_val;
    lv_obj_t *wifi_saved_btn;
    lv_obj_t *wifi_keyboard;
    lv_obj_t *saved_title;
    lv_obj_t *saved_wifi_1_val;
    lv_obj_t *saved_connect_1;
    lv_obj_t *saved_forget_1;
    lv_obj_t *saved_wifi_2_val;
    lv_obj_t *saved_connect_2;
    lv_obj_t *saved_forget_2;
    lv_obj_t *saved_wifi_3_val;
    lv_obj_t *saved_connect_3;
    lv_obj_t *saved_forget_3;
    lv_obj_t *saved_status_lbl;
    lv_obj_t *saved_status_val;
    lv_obj_t *saved_back_btn;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_settings();
void tick_screen_settings();

void create_screen_wifi();
void tick_screen_wifi();

void create_screen_saved_wi_fi();
void tick_screen_saved_wi_fi();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/