MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
RGB_MATRIX_ENABLE = yes
CAPS_WORD_ENABLE = yes
DEBOUNCE_TYPE = sym_eager_pk

SRC += features/select_word.c

# Size optimisations
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESCAPE_ENABLE = no
MOUSEKEY_ENABLE = no
MAGIC_ENABLE = no
# Size optimisations END