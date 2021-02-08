/*
Copyright 2020 Holten Campbell

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "meridian.h"

enum OPERATION_MODE {
    normal,
    layer1,
    layer2,
    korean,
    englishTransitionState,
    pushToTalk
};

enum OPERATION_MODE currentMode = normal;
enum OPERATION_MODE previousMode = normal;
int timer = 0;
int englishTransitionStateTimer = 0;
int pushToTalkIndex = 0;
int pushToTalkTimer = 0;

// Helper Function definitions
void rgbController(void);
void handleEnglishTransition(void);
void toggleLanguage(void);
void hardResetIndicators(void);
void handlePushToTalkLEDs(void);

//Initialize B12 for in-switch caps lock
void keyboard_pre_init_kb(void){
    // setPinOutput(B12);
    // keyboard_pre_init_user();
    rgblight_setrgb_at(0, 0, 0, 0);
    rgblight_setrgb_at(0, 0, 0, 1);
    rgblight_setrgb_at(0, 0, 0, 2);
}

//Initialize breathing mode and set purple as the start
__attribute__((weak))
void keyboard_pre_init_user(void) {
    rgblight_setrgb_at(0, 0, 0, 0);
    rgblight_setrgb_at(0, 0, 0, 1);
    rgblight_setrgb_at(0, 0, 0, 2);
}

void keyboard_post_init_kb(void) {
    rgblight_mode(3);
    rgblight_sethsv(175, 180, 255);
}

// Check rgb controller whenever a loop has been completed.
void housekeeping_task_kb(void) {
    rgbController();
}

// check if push to talk is pressed
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_F24) {
        if (record->event.pressed) {
            previousMode = currentMode;
            currentMode = pushToTalk;
        } else {
            currentMode = previousMode;
            pushToTalkIndex = 0;
            pushToTalkTimer = 0;
        }
    }
}

// Layer based colours
layer_state_t layer_state_set_kb(layer_state_t state) {
    if (get_highest_layer(state) == 1) {
        rgblight_mode(1);
        currentMode = layer1;
    } else if (get_highest_layer(state) == 2) {
        rgblight_mode(1);
        currentMode = layer2;
    } else {
        rgblight_reload_from_eeprom();
        rgblight_mode(3);
        currentMode = normal;
    }
    return state;
}

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 10: // Switch language
                toggleLanguage();
                return MACRO(D(RALT), D(UP), U(RALT), U(UP), END);
            case 20:
                hardResetIndicators();
        }
    }
    return MACRO_NONE;
};

// RGB controller
void rgbController() {
    if (currentMode == normal) { // Normal - Change hue constantly.
        if (timer > 5000) {
            rgblight_increase_hue();
            timer = 0;
        } else {
            timer++;
        }
    } else if (currentMode == korean) { // Shows korean flag colours.
        rgblight_setrgb_at(255, 26, 38, 0);
        rgblight_setrgb_at(0, 71, 255, 1);
        rgblight_setrgb_at(0, 0, 0, 2);
    }  else if (currentMode == englishTransitionState) { // English transition state that shows canada flag temporarily.
        handleEnglishTransition();
        rgblight_setrgb_at(255, 0, 0, 0);
        rgblight_setrgb_at(255, 255, 255, 1);
        rgblight_setrgb_at(255, 0, 0, 2);
    } else if (currentMode == pushToTalk) { // Blink LEDs while push to talk button is held.
        handlePushToTalkLEDs();
    } else { // Handle layers.
        if (currentMode == layer1) {
            rgblight_sethsv_noeeprom(130, 255, 255);
        } else if (currentMode == layer2) {
            rgblight_sethsv_noeeprom(212, 255, 255);
        }
    }
}

// Helper functions
void toggleLanguage() {
    if (currentMode == normal) {
        currentMode = korean;
        rgblight_mode(1);
    } else {
        currentMode = englishTransitionState;
        rgblight_mode(1);
    }
}

void handleEnglishTransition() {
    englishTransitionStateTimer++;
        if (englishTransitionStateTimer > 3000) {
            englishTransitionStateTimer = 0;
            rgblight_mode(3);
            currentMode = normal;
            return;
        }
}

void handlePushToTalkLEDs() {
    if (previousMode == korean) {
        // Seems to be a bug, cannot set first LED to 0 then set it again.
        if (pushToTalkIndex != 0) rgblight_setrgb_at(0, 0, 0, 0);
        rgblight_setrgb_at(0, 0, 0, 1);
        rgblight_setrgb_at(0, 0, 0, 2);
    }
    rgblight_setrgb_at(255, 255, 255, pushToTalkIndex);
    pushToTalkTimer++;
    if (pushToTalkTimer > 500) {
        pushToTalkTimer = 0;
        pushToTalkIndex = (pushToTalkIndex + 1) % 3;
    }
}

void hardResetIndicators() {
    currentMode = normal;
    rgblight_mode(3);
}
