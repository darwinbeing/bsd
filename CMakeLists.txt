add_executable(pio_bsd)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(pio_bsd ${CMAKE_CURRENT_LIST_DIR}/bsd.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(pio_bsd PRIVATE bsd_read.c pio_bsd.c)

target_link_libraries(pio_bsd PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_bsd)

# add url via pico_set_program_url
example_auto_set_url(pio_bsd)

# Additionally generate python and hex pioasm outputs for inclusion in the RP2040 datasheet
add_custom_target(pio_bsd_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/bsd.py)
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/bsd.py
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/bsd.pio
        COMMAND pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/bsd.pio ${CMAKE_CURRENT_LIST_DIR}/generated/bsd.py
        VERBATIM)
add_dependencies(pio_bsd pio_bsd_datasheet)



pico_enable_stdio_usb(pio_bsd 1)
pico_enable_stdio_uart(pio_bsd 0)
pico_add_extra_outputs(pio_bsd)
