// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: handwritten_bismillah

#include "../ui.h"

void ui_ScreenMain_screen_init(void)
{
ui_ScreenMain = lv_obj_create(NULL);
lv_obj_clear_flag( ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ScreenMain, lv_color_hex(0x36286A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ScreenMain, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Title = lv_label_create(ui_ScreenMain);
lv_obj_set_width( ui_Title, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Title, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Title, 0 );
lv_obj_set_y( ui_Title, -105 );
lv_obj_set_align( ui_Title, LV_ALIGN_CENTER );
lv_label_set_text(ui_Title,"Handwritten Digit Prediction");
lv_obj_set_style_text_color(ui_Title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Title, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Title, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_MainPanel = lv_obj_create(ui_ScreenMain);
lv_obj_set_width( ui_MainPanel, 315);
lv_obj_set_height( ui_MainPanel, 200);
lv_obj_set_x( ui_MainPanel, 0 );
lv_obj_set_y( ui_MainPanel, 15 );
lv_obj_set_align( ui_MainPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_MainPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_MainPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_MainPanel, lv_color_hex(0x43347F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_MainPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_MainPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_MainPanel, 50, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_predictButton = lv_btn_create(ui_MainPanel);
lv_obj_set_width( ui_predictButton, 100);
lv_obj_set_height( ui_predictButton, 20);
lv_obj_set_x( ui_predictButton, 6 );
lv_obj_set_y( ui_predictButton, 5 );
lv_obj_set_align( ui_predictButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_predictButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_predictButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_predictButton, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_predictButton, lv_color_hex(0x7E48FE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_predictButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label3 = lv_label_create(ui_predictButton);
lv_obj_set_width( ui_Label3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label3, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label3, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label3,"Predict");
lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_delButton = lv_btn_create(ui_MainPanel);
lv_obj_set_width( ui_delButton, 100);
lv_obj_set_height( ui_delButton, 20);
lv_obj_set_x( ui_delButton, 6 );
lv_obj_set_y( ui_delButton, -25 );
lv_obj_set_align( ui_delButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_delButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_delButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_delButton, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_delButton, lv_color_hex(0xE53935), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_delButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label2 = lv_label_create(ui_delButton);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label2,"Delete");
lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_settingsButton = lv_btn_create(ui_MainPanel);
lv_obj_set_width( ui_settingsButton, 100);
lv_obj_set_height( ui_settingsButton, 20);
lv_obj_set_x( ui_settingsButton, 6 );
lv_obj_set_y( ui_settingsButton, -55 );
lv_obj_set_align( ui_settingsButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_settingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_settingsButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_settingsButton, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_settingsButton, lv_color_hex(0x27C35D), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_settingsButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label4 = lv_label_create(ui_settingsButton);
lv_obj_set_width( ui_Label4, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label4, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label4, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label4,"Settings");
lv_obj_set_style_text_font(ui_Label4, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_setting = lv_obj_create(ui_ScreenMain);
lv_obj_set_width( ui_setting, 226);
lv_obj_set_height( ui_setting, 163);
lv_obj_set_x( ui_setting, -300 );
lv_obj_set_y( ui_setting, 16 );
lv_obj_set_align( ui_setting, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_setting, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_setting, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_setting, lv_color_hex(0x8471CF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_setting, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_setting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_setting, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Arc1 = lv_arc_create(ui_setting);
lv_obj_set_width( ui_Arc1, 100);
lv_obj_set_height( ui_Arc1, 100);
lv_obj_set_x( ui_Arc1, 0 );
lv_obj_set_y( ui_Arc1, -10 );
lv_obj_set_align( ui_Arc1, LV_ALIGN_CENTER );
lv_arc_set_range(ui_Arc1, 8,18);
lv_arc_set_value(ui_Arc1, 14);
lv_arc_set_bg_angles(ui_Arc1,150,30);
lv_obj_set_style_radius(ui_Arc1, 350, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Arc1, lv_color_hex(0x1E232D), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Arc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Arc1, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Arc1, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Arc1, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Arc1, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_color(ui_Arc1, lv_color_hex(0x36286A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_Arc1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_Arc1, 7, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_width(ui_Arc1, 7, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_img_src( ui_Arc1, &ui_img_path1_png, LV_PART_INDICATOR | LV_STATE_DEFAULT );

lv_obj_set_style_bg_color(ui_Arc1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Arc1, 255, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_Label1 = lv_label_create(ui_setting);
lv_obj_set_width( ui_Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label1, 0 );
lv_obj_set_y( ui_Label1, -70 );
lv_obj_set_align( ui_Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label1,"Line Size");
lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_applyButton = lv_btn_create(ui_setting);
lv_obj_set_width( ui_applyButton, 63);
lv_obj_set_height( ui_applyButton, 20);
lv_obj_set_x( ui_applyButton, 75 );
lv_obj_set_y( ui_applyButton, 65 );
lv_obj_set_align( ui_applyButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_applyButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_applyButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_applyButton, lv_color_hex(0x5427C1), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_applyButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label7 = lv_label_create(ui_applyButton);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label7, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label7,"Apply");
lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lineLabel = lv_label_create(ui_setting);
lv_obj_set_width( ui_lineLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lineLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_lineLabel, 0 );
lv_obj_set_y( ui_lineLabel, -15 );
lv_obj_set_align( ui_lineLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_lineLabel,"14");
lv_obj_set_style_text_color(ui_lineLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_lineLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_lineLabel, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label6 = lv_label_create(ui_setting);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label6, 0 );
lv_obj_set_y( ui_Label6, 47 );
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"Invert Written Color");
lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_colorSw = lv_switch_create(ui_setting);
lv_obj_set_width( ui_colorSw, 40);
lv_obj_set_height( ui_colorSw, 20);
lv_obj_set_x( ui_colorSw, -90 );
lv_obj_set_y( ui_colorSw, 47 );
lv_obj_set_align( ui_colorSw, LV_ALIGN_CENTER );
lv_obj_set_style_bg_color(ui_colorSw, lv_color_hex(0x857BC6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_colorSw, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(ui_colorSw, lv_color_hex(0x36286A), LV_PART_INDICATOR | LV_STATE_CHECKED );
lv_obj_set_style_bg_opa(ui_colorSw, 255, LV_PART_INDICATOR| LV_STATE_CHECKED);

lv_obj_set_style_bg_color(ui_colorSw, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_colorSw, 255, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_predictPanel = lv_obj_create(ui_ScreenMain);
lv_obj_set_width( ui_predictPanel, 315);
lv_obj_set_height( ui_predictPanel, 200);
lv_obj_set_x( ui_predictPanel, -350 );
lv_obj_set_y( ui_predictPanel, 15 );
lv_obj_set_align( ui_predictPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_predictPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_predictPanel, lv_color_hex(0x43347F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_predictPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_predictPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_predictPanel, 50, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image1 = lv_img_create(ui_predictPanel);
lv_img_set_src(ui_Image1, &ui_img_roller_bg_png);
lv_obj_set_width( ui_Image1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Image1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Image1, -95 );
lv_obj_set_y( ui_Image1, -17 );
lv_obj_set_align( ui_Image1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_namePredict = lv_label_create(ui_predictPanel);
lv_obj_set_width( ui_namePredict, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_namePredict, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_namePredict, -95 );
lv_obj_set_y( ui_namePredict, -83 );
lv_obj_set_align( ui_namePredict, LV_ALIGN_CENTER );
lv_label_set_text(ui_namePredict,"Predict Output :");
lv_obj_set_style_text_color(ui_namePredict, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_namePredict, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_namePredict, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Roller2 = lv_roller_create(ui_predictPanel);
lv_roller_set_options( ui_Roller2, "Class 0\nClass 1\nClass 2\nClass 3\nClass 4\nClass 5\nClass 6\nClass 7\nClass 8\nClass 9", LV_ROLLER_MODE_INFINITE );
lv_obj_set_width( ui_Roller2, 86);
lv_obj_set_height( ui_Roller2, 83);
lv_obj_set_x( ui_Roller2, -95 );
lv_obj_set_y( ui_Roller2, -19 );
lv_obj_set_align( ui_Roller2, LV_ALIGN_CENTER );
lv_obj_set_style_text_color(ui_Roller2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Roller2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Roller2, &lv_font_montserrat_10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Roller2, 11, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Roller2, lv_color_hex(0x31286A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Roller2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Roller2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Roller2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_text_font(ui_Roller2, &lv_font_montserrat_14, LV_PART_SELECTED| LV_STATE_DEFAULT);

ui_Arc2 = lv_arc_create(ui_predictPanel);
lv_obj_set_width( ui_Arc2, 100);
lv_obj_set_height( ui_Arc2, 100);
lv_obj_set_x( ui_Arc2, 51 );
lv_obj_set_y( ui_Arc2, -12 );
lv_obj_set_align( ui_Arc2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Arc2, LV_OBJ_FLAG_CLICKABLE );    /// Flags
lv_arc_set_value(ui_Arc2, 50);
lv_arc_set_bg_angles(ui_Arc2,140,40);
lv_obj_set_style_radius(ui_Arc2, 350, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Arc2, lv_color_hex(0x1E232D), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Arc2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_Arc2, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Arc2, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Arc2, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Arc2, 4, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_color(ui_Arc2, lv_color_hex(0x36286A), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_Arc2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_Arc2, 7, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_width(ui_Arc2, 7, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_img_src( ui_Arc2, &ui_img_path1_png, LV_PART_INDICATOR | LV_STATE_DEFAULT );

lv_obj_set_style_bg_color(ui_Arc2, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Arc2, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_nameProb = lv_label_create(ui_predictPanel);
lv_obj_set_width( ui_nameProb, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_nameProb, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_nameProb, 51 );
lv_obj_set_y( ui_nameProb, -83 );
lv_obj_set_align( ui_nameProb, LV_ALIGN_CENTER );
lv_label_set_text(ui_nameProb,"Probability :");
lv_obj_set_style_text_color(ui_nameProb, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_nameProb, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_nameProb, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_label1 = lv_label_create(ui_predictPanel);
lv_obj_set_width( ui_label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_label1, -75 );
lv_obj_set_y( ui_label1, 50 );
lv_obj_set_align( ui_label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_label1,"Time NN Calculation : ");
lv_obj_set_style_text_color(ui_label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_label1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_label1, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_timeNN = lv_label_create(ui_predictPanel);
lv_obj_set_width( ui_timeNN, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_timeNN, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_timeNN, 25 );
lv_obj_set_y( ui_timeNN, 50 );
lv_obj_set_align( ui_timeNN, LV_ALIGN_CENTER );
lv_label_set_text(ui_timeNN,"0.000 ms");
lv_obj_set_style_text_color(ui_timeNN, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_timeNN, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_timeNN, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_backButton = lv_btn_create(ui_predictPanel);
lv_obj_set_width( ui_backButton, 100);
lv_obj_set_height( ui_backButton, 20);
lv_obj_set_x( ui_backButton, 6 );
lv_obj_set_y( ui_backButton, 5 );
lv_obj_set_align( ui_backButton, LV_ALIGN_BOTTOM_RIGHT );
lv_obj_add_flag( ui_backButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_backButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_backButton, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_backButton, lv_color_hex(0x7E48FE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_backButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label5 = lv_label_create(ui_backButton);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"Back");
lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_percentPredict = lv_label_create(ui_predictPanel);
lv_obj_set_width( ui_percentPredict, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_percentPredict, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_percentPredict, 52 );
lv_obj_set_y( ui_percentPredict, -15 );
lv_obj_set_align( ui_percentPredict, LV_ALIGN_CENTER );
lv_label_set_text(ui_percentPredict,"50%");
lv_obj_set_style_text_color(ui_percentPredict, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_percentPredict, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_percentPredict, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);

// lv_obj_add_event_cb(ui_predictButton, ui_event_predictButton, LV_EVENT_ALL, NULL);
// lv_obj_add_event_cb(ui_settingsButton, ui_event_settingsButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Arc1, ui_event_Arc1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_applyButton, ui_event_applyButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_backButton, ui_event_backButton, LV_EVENT_ALL, NULL);

}
