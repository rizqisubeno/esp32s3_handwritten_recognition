include(${CMAKE_CURRENT_SOURCE_DIR}/../main/squareline_ui/CMakeLists.txt)

idf_component_register(SRCS "NeuralNetwork.cpp" "main.cpp" "lvgl_component_init.c" "lcd_touch_init.c" ${SOURCES}
                    INCLUDE_DIRS "." "./squareline_ui"
                    )

target_compile_options(${COMPONENT_LIB} PUBLIC -std=gnu++23)
# set_source_files_properties("main.cpp" "NeuralNetwork.cpp"
#                             PROPERTIES COMPILE_FLAGS 
#                             "-std=gnu++23 -Wall -Wno-unused-variable")                      