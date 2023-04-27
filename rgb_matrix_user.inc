// Declare custom effects using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(default_effect)
RGB_MATRIX_EFFECT(effect_lower)
RGB_MATRIX_EFFECT(effect_raise)
RGB_MATRIX_EFFECT(effect_adjust)
RGB_MATRIX_EFFECT(effect_game)
RGB_MATRIX_EFFECT(effect_qwerty)
RGB_MATRIX_EFFECT(effect_caps_word)

// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool default_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0, 0, 0);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_lower(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color(5, 100, 0, 0);
  rgb_matrix_set_color(32, 0, 0, 0);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_raise(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color(32, 100, 0, 0);
  rgb_matrix_set_color(5, 0, 0, 0);
  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_adjust(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color(32, 40, 0, 100);
  rgb_matrix_set_color(5, 40, 0, 100);

  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_game(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  rgb_matrix_set_color(16, 80, 15, 0);
  rgb_matrix_set_color(18, 80, 15, 0);
  rgb_matrix_set_color(19, 80, 15, 0);
  rgb_matrix_set_color(22, 80, 15, 0);

  rgb_matrix_set_color(32, 0, 0, 0);
  rgb_matrix_set_color(5, 0, 0, 0);

  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_qwerty(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < 6; i++) {
    rgb_matrix_set_color(i, 3, 0, 20);
  }
  for (uint8_t i = 27; i < 33; i++) {
    rgb_matrix_set_color(i, 3, 0, 20);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

static bool effect_caps_word(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0, 0, 0);
  } 
  rgb_matrix_set_color(0, 75, 40, 30);
  return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS7