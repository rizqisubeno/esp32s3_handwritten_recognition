// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: handwritten_bismillah

#include "../ui.h"

void ui_TitleScreen_screen_init(void)
{
ui_TitleScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_TitleScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_TitleScreen, lv_color_hex(0x7DAEBB), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TitleScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PanelProfile = lv_obj_create(ui_TitleScreen);
lv_obj_set_width( ui_PanelProfile, 1);
lv_obj_set_height( ui_PanelProfile, 1);
lv_obj_set_align( ui_PanelProfile, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_PanelProfile, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_PanelProfile, 1000, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_PanelProfile, lv_color_hex(0x749BA9), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_PanelProfile, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_PanelProfile, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelProfile, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_PanelProfile, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_PanelProfile, 150, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_PanelProfile, 8, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_PanelProfile, 2, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_myNIM = lv_label_create(ui_PanelProfile);
lv_obj_set_width( ui_myNIM, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_myNIM, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_myNIM, 0 );
lv_obj_set_y( ui_myNIM, 30 );
lv_obj_set_align( ui_myNIM, LV_ALIGN_CENTER );
lv_label_set_text(ui_myNIM,"22 / 495313 / PTK / 14431");
lv_obj_set_style_text_color(ui_myNIM, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_myNIM, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_myNIM, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image2 = lv_img_create(ui_PanelProfile);
lv_img_set_src(ui_Image2, &ui_img_dteti_png);
lv_obj_set_width( ui_Image2, LV_SIZE_CONTENT);  /// 175
lv_obj_set_height( ui_Image2, LV_SIZE_CONTENT);   /// 84
lv_obj_set_x( ui_Image2, 0 );
lv_obj_set_y( ui_Image2, -55 );
lv_obj_set_align( ui_Image2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_myName = lv_label_create(ui_PanelProfile);
lv_obj_set_width( ui_myName, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_myName, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_myName, 0 );
lv_obj_set_y( ui_myName, -5 );
lv_obj_set_align( ui_myName, LV_ALIGN_CENTER );
lv_label_set_text(ui_myName,"Muhammad Rizqi Subeno");
lv_obj_set_style_text_color(ui_myName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_myName, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_myName, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PanelProj = lv_obj_create(ui_TitleScreen);
lv_obj_set_width( ui_PanelProj, 1);
lv_obj_set_height( ui_PanelProj, 1);
lv_obj_set_align( ui_PanelProj, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_PanelProj, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_PanelProj, 1000, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_PanelProj, lv_color_hex(0x31286A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_PanelProj, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_PanelProj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelProj, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_PanelProj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_PanelProj, 135, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_PanelProj, 8, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_PanelProj, 2, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_nameProj = lv_label_create(ui_PanelProj);
lv_obj_set_width( ui_nameProj, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_nameProj, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_nameProj, LV_ALIGN_CENTER );
lv_label_set_text(ui_nameProj,"Handwritten Digit Prediction\n\nUsing Tensorflow Lite Micro");
lv_obj_set_style_text_color(ui_nameProj, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_nameProj, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_align(ui_nameProj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);

}
