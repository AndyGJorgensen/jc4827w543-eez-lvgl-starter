#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_wifi_scan(lv_event_t * e);
extern void action_wifi_connect(lv_event_t * e);
extern void action_wifi_disconnect(lv_event_t * e);
extern void action_wifi_keyboard_show(lv_event_t * e);
extern void action_wifi_keyboard_hide(lv_event_t * e);
extern void action_wifi_saved_connect(lv_event_t * e);
extern void action_wifi_saved_forget(lv_event_t * e);
extern void action_play_test_sound(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/