CONSOLE_ENABLE = no

OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
LEADER_ENABLE = no        # Enable the Leader Key feature
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = no
UNICODE_ENABLE = no
WPM_ENABLE = no
VELOCIKEY_ENABLE = no
KEY_LOCK_ENABLE = yes

# Reduces firmware bloat due to changes in qmk toolchain.
# https://discord.com/channels/440868230475677696/473506116718952450/838845851962703893
GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no

LTO_ENABLE = yes

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
