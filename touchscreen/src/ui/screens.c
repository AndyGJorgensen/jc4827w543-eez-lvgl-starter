#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

static const char *screen_names[] = { "Main", "Settings", "WIFI", "Saved WiFi" };
static const char *object_names[] = { "main", "settings", "wifi", "saved_wi_fi", "obj0", "battery_bar", "battery_lbl", "obj1", "obj2", "sound_test_btn", "sd_status_val", "audio_status_val", "obj3", "wifi_net_lbl", "wifi_network_dd", "wifi_password", "wifi_scan_btn", "wifi_connect_btn", "wifi_disconnect_btn", "wifi_status_lbl", "wifi_status_val", "wifi_ssid_lbl", "wifi_ssid_val", "wifi_ip_lbl", "wifi_ip_val", "wifi_hostname_lbl", "wifi_hostname_val", "wifi_rssi_lbl", "wifi_rssi_val", "wifi_mac_lbl", "wifi_mac_val", "ota_lbl", "ota_switch", "ota_status_lbl", "ota_status_val", "wifi_saved_btn", "wifi_keyboard", "saved_title", "saved_wifi_1_val", "saved_connect_1", "saved_forget_1", "saved_wifi_2_val", "saved_connect_2", "saved_forget_2", "saved_wifi_3_val", "saved_connect_3", "saved_forget_3", "saved_status_lbl", "saved_status_val", "saved_back_btn" };

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_settings_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_settings_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 3, 0, e);
    }
}

static void event_handler_cb_settings_sound_test_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_play_test_sound(e);
    }
}

static void event_handler_cb_wifi_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 0, 0, e);
    }
}

static void event_handler_cb_wifi_wifi_password(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_keyboard_show(e);
    }
}

static void event_handler_cb_wifi_wifi_scan_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_scan(e);
    }
}

static void event_handler_cb_wifi_wifi_connect_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_connect(e);
    }
}

static void event_handler_cb_wifi_wifi_disconnect_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_disconnect(e);
    }
}

static void event_handler_cb_wifi_ota_switch(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target_obj(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 25, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_wifi_wifi_saved_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 28, 0, e);
    }
}

static void event_handler_cb_wifi_wifi_keyboard(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_READY) {
        e->user_data = (void *)0;
        action_wifi_keyboard_hide(e);
    }
    if (event == LV_EVENT_CANCEL) {
        e->user_data = (void *)0;
        action_wifi_keyboard_hide(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_connect_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_saved_connect(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_forget_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        action_wifi_saved_forget(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_connect_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)1;
        action_wifi_saved_connect(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_forget_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)1;
        action_wifi_saved_forget(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_connect_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)2;
        action_wifi_saved_connect(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_forget_3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)2;
        action_wifi_saved_forget(e);
    }
}

static void event_handler_cb_saved_wi_fi_saved_back_btn(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 19, 0, e);
    }
}

//
// Screens
//

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 272);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 380, 222);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Settings");
                }
            }
        }
        {
            // battery_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.battery_bar = obj;
            lv_obj_set_pos(obj, 400, 8);
            lv_obj_set_size(obj, 72, 16);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
        {
            // battery_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.battery_lbl = obj;
            lv_obj_set_pos(obj, 360, 28);
            lv_obj_set_size(obj, 112, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        int32_t new_val = evalIntegerProperty(flowState, 3, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.battery_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.battery_bar;
            lv_bar_set_value(objects.battery_bar, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.battery_lbl);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.battery_lbl;
            lv_label_set_text(objects.battery_lbl, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 272);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 380, 222);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj1, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Main\nMenu");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 281, 22);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_obj2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "WIFI");
                }
            }
        }
        {
            // sound_test_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.sound_test_btn = obj;
            lv_obj_set_pos(obj, 15, 100);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_settings_sound_test_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Test Sound");
                }
            }
        }
        {
            // sd_status_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sd_status_val = obj;
            lv_obj_set_pos(obj, 130, 106);
            lv_obj_set_size(obj, 340, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // audio_status_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.audio_status_val = obj;
            lv_obj_set_pos(obj, 130, 128);
            lv_obj_set_size(obj, 340, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.sd_status_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sd_status_val;
            lv_label_set_text(objects.sd_status_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 8, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.audio_status_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.audio_status_val;
            lv_label_set_text(objects.audio_status_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_wifi() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.wifi = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 272);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 380, 222);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_obj3, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Back");
                }
            }
        }
        {
            // wifi_net_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_net_lbl = obj;
            lv_obj_set_pos(obj, 8, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Network");
        }
        {
            // wifi_network_dd
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.wifi_network_dd = obj;
            lv_obj_set_pos(obj, 8, 28);
            lv_obj_set_size(obj, 228, 40);
            lv_dropdown_set_options(obj, "Press Scan");
            lv_dropdown_set_selected(obj, 0);
        }
        {
            // wifi_password
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.wifi_password = obj;
            lv_obj_set_pos(obj, 8, 76);
            lv_obj_set_size(obj, 228, 40);
            lv_textarea_set_max_length(obj, 64);
            lv_textarea_set_placeholder_text(obj, "Password");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, true);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_password, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ONE|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
        }
        {
            // wifi_scan_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.wifi_scan_btn = obj;
            lv_obj_set_pos(obj, 8, 124);
            lv_obj_set_size(obj, 108, 40);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_scan_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Scan");
                }
            }
        }
        {
            // wifi_connect_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.wifi_connect_btn = obj;
            lv_obj_set_pos(obj, 128, 124);
            lv_obj_set_size(obj, 108, 40);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_connect_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Connect");
                }
            }
        }
        {
            // wifi_disconnect_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.wifi_disconnect_btn = obj;
            lv_obj_set_pos(obj, 8, 172);
            lv_obj_set_size(obj, 108, 40);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_disconnect_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Disconnect");
                }
            }
        }
        {
            // wifi_status_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_status_lbl = obj;
            lv_obj_set_pos(obj, 250, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Status");
        }
        {
            // wifi_status_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_status_val = obj;
            lv_obj_set_pos(obj, 312, 8);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_ssid_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_ssid_lbl = obj;
            lv_obj_set_pos(obj, 250, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "SSID");
        }
        {
            // wifi_ssid_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_ssid_val = obj;
            lv_obj_set_pos(obj, 312, 32);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_ip_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_ip_lbl = obj;
            lv_obj_set_pos(obj, 250, 56);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "IP");
        }
        {
            // wifi_ip_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_ip_val = obj;
            lv_obj_set_pos(obj, 312, 56);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_hostname_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_hostname_lbl = obj;
            lv_obj_set_pos(obj, 250, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Host");
        }
        {
            // wifi_hostname_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_hostname_val = obj;
            lv_obj_set_pos(obj, 312, 80);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_rssi_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_rssi_lbl = obj;
            lv_obj_set_pos(obj, 250, 104);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Signal");
        }
        {
            // wifi_rssi_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_rssi_val = obj;
            lv_obj_set_pos(obj, 312, 104);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_mac_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_mac_lbl = obj;
            lv_obj_set_pos(obj, 250, 128);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "MAC");
        }
        {
            // wifi_mac_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_mac_val = obj;
            lv_obj_set_pos(obj, 312, 128);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // ota_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ota_lbl = obj;
            lv_obj_set_pos(obj, 128, 184);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "OTA");
        }
        {
            // ota_switch
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.ota_switch = obj;
            lv_obj_set_pos(obj, 180, 178);
            lv_obj_set_size(obj, 50, 28);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_ota_switch, LV_EVENT_ALL, flowState);
        }
        {
            // ota_status_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ota_status_lbl = obj;
            lv_obj_set_pos(obj, 250, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "OTA");
        }
        {
            // ota_status_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ota_status_val = obj;
            lv_obj_set_pos(obj, 312, 152);
            lv_obj_set_size(obj, 160, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // wifi_saved_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.wifi_saved_btn = obj;
            lv_obj_set_pos(obj, 250, 180);
            lv_obj_set_size(obj, 108, 40);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_saved_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Saved");
                }
            }
        }
        {
            // wifi_keyboard
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.wifi_keyboard = obj;
            lv_obj_set_pos(obj, 0, 120);
            lv_obj_set_size(obj, 480, 152);
            lv_obj_add_event_cb(obj, event_handler_cb_wifi_wifi_keyboard, LV_EVENT_ALL, flowState);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_width(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_width(obj, 480, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_min_height(obj, 152, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_max_height(obj, 152, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    lv_keyboard_set_textarea(objects.wifi_keyboard, objects.wifi_password);
    
    tick_screen_wifi();
}

void tick_screen_wifi() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 13, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_status_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_status_val;
            lv_label_set_text(objects.wifi_status_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 15, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_ssid_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_ssid_val;
            lv_label_set_text(objects.wifi_ssid_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_ip_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_ip_val;
            lv_label_set_text(objects.wifi_ip_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_hostname_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_hostname_val;
            lv_label_set_text(objects.wifi_hostname_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_rssi_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_rssi_val;
            lv_label_set_text(objects.wifi_rssi_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wifi_mac_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wifi_mac_val;
            lv_label_set_text(objects.wifi_mac_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.ota_switch, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.ota_switch;
            if (new_val) {
                lv_obj_add_state(objects.ota_switch, LV_STATE_CHECKED);
            } else {
                lv_obj_remove_state(objects.ota_switch, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 27, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.ota_status_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.ota_status_val;
            lv_label_set_text(objects.ota_status_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 30, 3, "Failed to evaluate Hidden flag");
        bool cur_val = lv_obj_has_flag(objects.wifi_keyboard, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.wifi_keyboard;
            if (new_val) {
                lv_obj_add_flag(objects.wifi_keyboard, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_remove_flag(objects.wifi_keyboard, LV_OBJ_FLAG_HIDDEN);
            }
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_saved_wi_fi() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.saved_wi_fi = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 272);
    {
        lv_obj_t *parent_obj = obj;
        {
            // saved_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_title = obj;
            lv_obj_set_pos(obj, 8, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Saved networks");
        }
        {
            // saved_wifi_1_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_wifi_1_val = obj;
            lv_obj_set_pos(obj, 8, 54);
            lv_obj_set_size(obj, 240, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // saved_connect_1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_connect_1 = obj;
            lv_obj_set_pos(obj, 260, 40);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_connect_1, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Connect");
                }
            }
        }
        {
            // saved_forget_1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_forget_1 = obj;
            lv_obj_set_pos(obj, 372, 40);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_forget_1, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Forget");
                }
            }
        }
        {
            // saved_wifi_2_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_wifi_2_val = obj;
            lv_obj_set_pos(obj, 8, 110);
            lv_obj_set_size(obj, 240, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // saved_connect_2
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_connect_2 = obj;
            lv_obj_set_pos(obj, 260, 96);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_connect_2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Connect");
                }
            }
        }
        {
            // saved_forget_2
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_forget_2 = obj;
            lv_obj_set_pos(obj, 372, 96);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_forget_2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Forget");
                }
            }
        }
        {
            // saved_wifi_3_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_wifi_3_val = obj;
            lv_obj_set_pos(obj, 8, 166);
            lv_obj_set_size(obj, 240, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // saved_connect_3
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_connect_3 = obj;
            lv_obj_set_pos(obj, 260, 152);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_connect_3, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Connect");
                }
            }
        }
        {
            // saved_forget_3
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_forget_3 = obj;
            lv_obj_set_pos(obj, 372, 152);
            lv_obj_set_size(obj, 100, 44);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_forget_3, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Forget");
                }
            }
        }
        {
            // saved_status_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_status_lbl = obj;
            lv_obj_set_pos(obj, 8, 236);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Status");
        }
        {
            // saved_status_val
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.saved_status_val = obj;
            lv_obj_set_pos(obj, 60, 236);
            lv_obj_set_size(obj, 300, 16);
            lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            lv_label_set_text(obj, "");
        }
        {
            // saved_back_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.saved_back_btn = obj;
            lv_obj_set_pos(obj, 380, 222);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_saved_wi_fi_saved_back_btn, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Back");
                }
            }
        }
    }
    
    tick_screen_saved_wi_fi();
}

void tick_screen_saved_wi_fi() {
    void *flowState = getFlowState(0, 3);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.saved_wifi_1_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.saved_wifi_1_val;
            lv_label_set_text(objects.saved_wifi_1_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.saved_wifi_2_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.saved_wifi_2_val;
            lv_label_set_text(objects.saved_wifi_2_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.saved_wifi_3_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.saved_wifi_3_val;
            lv_label_set_text(objects.saved_wifi_3_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.saved_status_val);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.saved_status_val;
            lv_label_set_text(objects.saved_status_val, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_settings,
    tick_screen_wifi,
    tick_screen_saved_wi_fi,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 4) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
//
//

void create_screens() {
    
    eez_flow_init_fonts(fonts, sizeof(fonts) / sizeof(ext_font_desc_t));

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    // Create screens
    create_screen_main();
    create_screen_settings();
    create_screen_wifi();
    create_screen_saved_wi_fi();
}