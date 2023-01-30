//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v1.2 - Style data exported as a values array            //
//                                                                              //
// USAGE: On init call: GuiLoadStyleDark();                             //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui                        //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2023 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define DARK_STYLE_PROPS_COUNT  22

// Custom style name: dark
static const GuiStyleProp darkStyleProps[DARK_STYLE_PROPS_COUNT] = {
    { 0, 0, 0x878787ff },    // DEFAULT_BORDER_COLOR_NORMAL 
    { 0, 1, 0x2c2c2cff },    // DEFAULT_BASE_COLOR_NORMAL 
    { 0, 2, 0xc3c3c3ff },    // DEFAULT_TEXT_COLOR_NORMAL 
    { 0, 3, 0xe1e1e1ff },    // DEFAULT_BORDER_COLOR_FOCUSED 
    { 0, 4, 0x848484ff },    // DEFAULT_BASE_COLOR_FOCUSED 
    { 0, 5, 0x181818ff },    // DEFAULT_TEXT_COLOR_FOCUSED 
    { 0, 6, 0x000000ff },    // DEFAULT_BORDER_COLOR_PRESSED 
    { 0, 7, 0xefefefff },    // DEFAULT_BASE_COLOR_PRESSED 
    { 0, 8, 0x202020ff },    // DEFAULT_TEXT_COLOR_PRESSED 
    { 0, 9, 0x6a6a6aff },    // DEFAULT_BORDER_COLOR_DISABLED 
    { 0, 10, 0x818181ff },    // DEFAULT_BASE_COLOR_DISABLED 
    { 0, 11, 0x606060ff },    // DEFAULT_TEXT_COLOR_DISABLED 
    { 0, 16, 0x00000010 },    // DEFAULT_TEXT_SIZE 
    { 0, 17, 0x00000000 },    // DEFAULT_TEXT_SPACING 
    { 0, 18, 0x9d9d9dff },    // DEFAULT_LINE_COLOR 
    { 0, 19, 0x3c3c3cff },    // DEFAULT_BACKGROUND_COLOR 
    { 1, 5, 0xf7f7f7ff },    // LABEL_TEXT_COLOR_FOCUSED 
    { 1, 8, 0x898989ff },    // LABEL_TEXT_COLOR_PRESSED 
    { 4, 5, 0xb0b0b0ff },    // SLIDER_TEXT_COLOR_FOCUSED 
    { 5, 5, 0x848484ff },    // PROGRESSBAR_TEXT_COLOR_FOCUSED 
    { 9, 5, 0xf5f5f5ff },    // TEXTBOX_TEXT_COLOR_FOCUSED 
    { 10, 5, 0xf6f6f6ff },    // VALUEBOX_TEXT_COLOR_FOCUSED 
};

// WARNING: This style uses a custom font: PixelOperator.ttf (size: 16, spacing: 0)

#define DARK_COMPRESSED_DATA_SIZE 1031

// Font image pixels data compressed (DEFLATE)
// NOTE: Original pixel data simplified to GRAYSCALE
static unsigned char darkFontData[DARK_COMPRESSED_DATA_SIZE] = { 0xed,
    0xdd, 0xd1, 0x76, 0x9b, 0x30, 0x0c, 0x00, 0x50, 0xff, 0xff, 0x4f, 0x6b, 0x4f, 0x3b, 0xeb, 0xb6, 0x16, 0x90, 0x90, 0x8d,
    0x93, 0xdc, 0xdd, 0x97, 0x9d, 0x36, 0x25, 0xc4, 0xc2, 0xc6, 0x04, 0xc9, 0xc4, 0x00, 0x00, 0xf8, 0x47, 0x7c, 0xfb, 0x93,
    0xf8, 0xf1, 0x95, 0x71, 0x79, 0x3b, 0xc7, 0x3f, 0xff, 0xfd, 0xdb, 0x38, 0x78, 0xaf, 0x6b, 0xfb, 0x9a, 0x7d, 0xdf, 0x48,
    0xb4, 0xc4, 0xf7, 0xfb, 0x17, 0x97, 0xb7, 0xfb, 0xd3, 0xe7, 0xcb, 0xbf, 0xfe, 0x68, 0x4b, 0xe7, 0xed, 0xfc, 0x54, 0xfc,
    0xe3, 0x52, 0x24, 0xe2, 0x62, 0xdb, 0x5c, 0x6f, 0xc5, 0xa3, 0x77, 0x8e, 0xe6, 0x16, 0x3c, 0x3f, 0x3a, 0x7f, 0x8a, 0x74,
    0xbe, 0x3d, 0xe2, 0xa0, 0x1f, 0xcd, 0x8d, 0xff, 0xd7, 0x7f, 0xb9, 0x7e, 0x1c, 0xc9, 0x88, 0x76, 0xf4, 0xf4, 0xe3, 0xfd,
    0x8c, 0xd4, 0xf6, 0x67, 0xc4, 0x3f, 0x5a, 0xc7, 0xae, 0x68, 0xed, 0xff, 0xc7, 0xaf, 0xcc, 0xf6, 0xb7, 0x48, 0xf6, 0xdd,
    0x8e, 0x36, 0xa9, 0xf5, 0xff, 0xee, 0xe8, 0xff, 0xf9, 0xec, 0x7d, 0xe3, 0x50, 0x7e, 0x5c, 0x5e, 0x19, 0xff, 0x4a, 0xec,
    0xae, 0x8e, 0x5c, 0x95, 0x3e, 0x31, 0x36, 0x88, 0x7f, 0xf6, 0x38, 0x3c, 0x6e, 0xab, 0x91, 0x3e, 0x33, 0x3c, 0x1f, 0xff,
    0xf3, 0xf1, 0x3f, 0x26, 0xc4, 0xff, 0xf9, 0x79, 0xf4, 0x9f, 0x88, 0x45, 0xb2, 0x2f, 0xe7, 0xce, 0x31, 0x91, 0xe8, 0x45,
    0xf5, 0xd6, 0xab, 0x9d, 0xff, 0xbf, 0x46, 0x3f, 0xde, 0x38, 0xfe, 0x91, 0x9c, 0xdf, 0x66, 0xe7, 0x38, 0x3b, 0xb4, 0xc2,
    0xf9, 0xfc, 0xff, 0x78, 0xef, 0xe2, 0xe6, 0xd8, 0x15, 0x2f, 0xd6, 0xfb, 0x3b, 0xe3, 0x1f, 0xd3, 0xe2, 0x1f, 0x4b, 0xe2,
    0x3f, 0x0e, 0xaf, 0x6a, 0xe3, 0xf6, 0x0c, 0x7b, 0xcf, 0xf8, 0x67, 0xaf, 0xff, 0x6b, 0x23, 0xec, 0xf3, 0x2d, 0x11, 0x37,
    0xaf, 0x41, 0x78, 0xfd, 0x6f, 0x11, 0x43, 0xf4, 0x7d, 0x8f, 0x8c, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8b, 0xef,
    0xd0, 0x45, 0x53, 0xb6, 0x6c, 0x25, 0x53, 0xfd, 0x5e, 0x9e, 0x7f, 0x2e, 0x6b, 0xf7, 0x6c, 0xef, 0xf2, 0xfb, 0xde, 0xf9,
    0x37, 0x47, 0x59, 0xc8, 0xb5, 0x1c, 0xeb, 0x2b, 0x95, 0x16, 0x9d, 0xb9, 0x25, 0xf5, 0x4c, 0xf5, 0xee, 0x3b, 0x49, 0x51,
    0xae, 0x2b, 0xe8, 0xf9, 0x54, 0x77, 0x7e, 0xd3, 0x13, 0xa5, 0xae, 0xf8, 0x8f, 0x2d, 0xe2, 0x9f, 0xcf, 0x13, 0xca, 0x1f,
    0xb7, 0x91, 0xce, 0x47, 0x8b, 0xd6, 0x9c, 0xad, 0x68, 0x8d, 0x52, 0x24, 0x2a, 0xad, 0x7a, 0x72, 0x4e, 0x77, 0xef, 0xff,
    0xd7, 0x32, 0xb2, 0x3f, 0x2b, 0xfe, 0xf9, 0x73, 0xeb, 0xdd, 0x33, 0xec, 0x8a, 0x5c, 0x82, 0x6a, 0xa5, 0x4c, 0x3e, 0xfe,
    0xf9, 0xde, 0x73, 0xb6, 0xb5, 0x51, 0xca, 0xa3, 0xbe, 0x9b, 0x01, 0x9e, 0xad, 0x52, 0x5b, 0x9d, 0x8f, 0x3a, 0x3f, 0x23,
    0x37, 0x2e, 0xd4, 0xb8, 0xed, 0xdb, 0xff, 0x63, 0x42, 0xff, 0x5f, 0x93, 0x8f, 0x1c, 0x4b, 0x8f, 0x92, 0xb3, 0x5e, 0xd4,
    0x75, 0x56, 0x7b, 0x95, 0xf8, 0xaf, 0xfe, 0x6c, 0xb1, 0x65, 0xd6, 0xd8, 0xbc, 0x36, 0xda, 0x7d, 0xfe, 0xdf, 0x75, 0xc5,
    0x7e, 0xbf, 0x52, 0x7d, 0x4d, 0xf4, 0xa3, 0xf4, 0x3d, 0x48, 0x65, 0x8e, 0xd4, 0x7b, 0xfd, 0x9f, 0x9f, 0xc1, 0x87, 0x0c,
    0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x8f, 0xca, 0xff, 0x5f, 0x93, 0x11, 0x34, 0x4a, 0x2b, 0xa1, 0xcf, 0xcf,
    0xb9, 0xbf, 0xb3, 0x26, 0x78, 0x3c, 0x9c, 0x61, 0x7e, 0x5c, 0x2d, 0xf0, 0xda, 0xf1, 0x7f, 0xfe, 0x37, 0xa3, 0xb0, 0x7e,
    0xe7, 0xca, 0xf8, 0x8f, 0x42, 0x34, 0x7a, 0xb2, 0xe4, 0x73, 0x5b, 0x89, 0xff, 0xfe, 0xb7, 0x63, 0xfc, 0xc7, 0x92, 0xf8,
    0xc7, 0xcb, 0xc7, 0xbf, 0x52, 0x6b, 0x71, 0x9c, 0x59, 0x2b, 0xfe, 0xe7, 0x6d, 0x1b, 0xa5, 0x2a, 0x8c, 0xfe, 0xf8, 0x47,
    0x71, 0x2b, 0x71, 0x72, 0x44, 0xf5, 0xe6, 0xdc, 0xf7, 0xe4, 0xe9, 0xad, 0x8d, 0x7f, 0xf7, 0x73, 0x3f, 0x76, 0xea, 0xff,
    0xd7, 0xea, 0xae, 0x66, 0x67, 0x1f, 0xdf, 0xe9, 0xe9, 0x4f, 0xf6, 0xff, 0xee, 0x67, 0x6b, 0xad, 0x3e, 0xff, 0xcf, 0x9a,
    0xff, 0x8d, 0xf4, 0x68, 0x12, 0xdb, 0xc6, 0xff, 0xce, 0x2c, 0xb4, 0x3b, 0xfe, 0xf1, 0x22, 0xf3, 0xff, 0x51, 0x38, 0x3e,
    0x67, 0xcf, 0xff, 0xaf, 0x3d, 0xef, 0x68, 0xef, 0xf8, 0x8f, 0x1b, 0xe7, 0xd7, 0x58, 0x72, 0xfd, 0x3f, 0x4e, 0xae, 0x36,
    0x7a, 0xde, 0x67, 0xb4, 0xad, 0xdf, 0xff, 0xf7, 0xbe, 0xe5, 0x6b, 0xf5, 0xb3, 0x2b, 0x16, 0x58, 0x75, 0x1d, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x40, 0xfe, 0xff, 0xd9, 0x1d, 0xe4, 0xfc, 0xbd, 0xe8, 0xd1, 0x78, 0x6f, 0x3f, 0x9a, 0x32, 0x19,
    0xc6, 0xc1, 0x9d, 0xf8, 0xec, 0x0a, 0x7c, 0x3d, 0x99, 0xb9, 0x47, 0x7b, 0xdf, 0x57, 0xd3, 0x30, 0x6e, 0xef, 0x51, 0x7e,
    0x3d, 0xc1, 0xe7, 0x57, 0x96, 0x8d, 0xc6, 0xcc, 0xae, 0x75, 0xd5, 0x36, 0x33, 0x73, 0xc6, 0xbb, 0xeb, 0x3f, 0xba, 0x5a,
    0x23, 0x6e, 0x8c, 0x0c, 0xb3, 0xe3, 0x5f, 0x5f, 0xe9, 0xbb, 0x7a, 0x7c, 0xad, 0x88, 0x7f, 0x4f, 0x16, 0x69, 0x3e, 0xf2,
    0x6b, 0xd6, 0xd3, 0x3e, 0x7b, 0x9e, 0xca, 0xba, 0xdc, 0xc7, 0x4a, 0x06, 0xed, 0xbb, 0xc6, 0xff, 0xf9, 0xf5, 0xb4, 0x67,
    0x55, 0x76, 0xf5, 0x66, 0xd0, 0x8b, 0xff, 0xbc, 0xda, 0xbe, 0x58, 0x38, 0x32, 0x55, 0x2b, 0x68, 0xe6, 0xd5, 0x0c, 0x76,
    0x57, 0x91, 0xcc, 0x1f, 0xff, 0x6b, 0xcf, 0xb9, 0xaa, 0x3c, 0x1d, 0x68, 0xb7, 0xfe, 0xdf, 0x99, 0x3b, 0xbd, 0x4b, 0xfc,
    0xeb, 0xb3, 0xfc, 0xd1, 0x34, 0x2b, 0x7d, 0x6e, 0xfc, 0x5f, 0xfd, 0xc4, 0x8b, 0xfa, 0x3c, 0xfc, 0x89, 0x3d, 0xa9, 0xbc,
    0x73, 0xe5, 0xaf, 0xb2, 0x99, 0xfd, 0x9d, 0xf1, 0xdf, 0xef, 0x08, 0xe0, 0xe9, 0x51, 0x8c, 0xf7, 0x3a, 0x02, 0x54, 0xe0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x36, 0xbb, 0xe3, 0x7e, 0x9c, 0xa5, 0x13, 0x2d, 0x19, 0x37, 0xbb, 0xaf, 0xa5,
    0x3f, 0x4e, 0xd6, 0xa7, 0xbd, 0x96, 0xdb, 0x15, 0xdb, 0xde, 0x0f, 0xae, 0xb6, 0x7f, 0x57, 0xfe, 0xf4, 0xee, 0x6b, 0xe9,
    0xdf, 0x5f, 0x93, 0x33, 0x4e, 0x8e, 0x8e, 0x57, 0x8c, 0x7f, 0x25, 0x67, 0xf4, 0xf9, 0xb5, 0x94, 0xa3, 0x94, 0xf1, 0x1a,
    0x9b, 0xe7, 0xcc, 0xed, 0x94, 0x8b, 0xbd, 0x72, 0xfc, 0x8f, 0x72, 0x74, 0xa2, 0x21, 0x0f, 0x5a, 0xfc, 0x47, 0xba, 0x16,
    0x6f, 0xe7, 0xfe, 0xff, 0xc4, 0xda, 0xeb, 0xef, 0x17, 0xff, 0xce, 0x8a, 0xab, 0x19, 0x6b, 0x69, 0xe7, 0xab, 0x3b, 0xdf,
    0xbf, 0xff, 0x57, 0xe7, 0xff, 0x3d, 0xe3, 0xff, 0xea, 0xb5, 0xb4, 0xf3, 0xf3, 0xff, 0xcf, 0x18, 0xff, 0xef, 0xbc, 0x22,
    0x73, 0xac, 0xbd, 0x5e, 0x5e, 0xae, 0xf8, 0x7f, 0x7a, 0x5e, 0xee, 0xdd, 0xeb, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x46, 0xbf, 0x00 };

// Font characters rectangles data
static const Rectangle darkFontRecs[95] = {
    { 4, 4, 4 , 16 },
    { 16, 4, 1 , 9 },
    { 25, 4, 3 , 3 },
    { 36, 4, 6 , 9 },
    { 50, 4, 5 , 13 },
    { 63, 4, 7 , 9 },
    { 78, 4, 5 , 9 },
    { 91, 4, 1 , 3 },
    { 100, 4, 3 , 9 },
    { 111, 4, 3 , 9 },
    { 122, 4, 5 , 5 },
    { 135, 4, 5 , 5 },
    { 148, 4, 2 , 3 },
    { 158, 4, 4 , 1 },
    { 170, 4, 1 , 1 },
    { 179, 4, 3 , 9 },
    { 190, 4, 5 , 9 },
    { 203, 4, 3 , 9 },
    { 214, 4, 5 , 9 },
    { 227, 4, 5 , 9 },
    { 240, 4, 5 , 9 },
    { 4, 28, 5 , 9 },
    { 17, 28, 5 , 9 },
    { 30, 28, 5 , 9 },
    { 43, 28, 5 , 9 },
    { 56, 28, 5 , 9 },
    { 69, 28, 1 , 7 },
    { 78, 28, 2 , 9 },
    { 88, 28, 3 , 5 },
    { 99, 28, 4 , 3 },
    { 111, 28, 3 , 5 },
    { 122, 28, 5 , 9 },
    { 135, 28, 7 , 9 },
    { 150, 28, 5 , 9 },
    { 163, 28, 5 , 9 },
    { 176, 28, 5 , 9 },
    { 189, 28, 5 , 9 },
    { 202, 28, 5 , 9 },
    { 215, 28, 5 , 9 },
    { 228, 28, 5 , 9 },
    { 241, 28, 5 , 9 },
    { 4, 52, 1 , 9 },
    { 13, 52, 5 , 9 },
    { 26, 52, 5 , 9 },
    { 39, 52, 5 , 9 },
    { 52, 52, 7 , 9 },
    { 67, 52, 5 , 9 },
    { 80, 52, 5 , 9 },
    { 93, 52, 5 , 9 },
    { 106, 52, 5 , 9 },
    { 119, 52, 5 , 9 },
    { 132, 52, 5 , 9 },
    { 145, 52, 5 , 9 },
    { 158, 52, 5 , 9 },
    { 171, 52, 5 , 9 },
    { 184, 52, 7 , 9 },
    { 199, 52, 5 , 9 },
    { 212, 52, 5 , 9 },
    { 225, 52, 5 , 9 },
    { 238, 52, 3 , 9 },
    { 4, 76, 3 , 9 },
    { 15, 76, 3 , 9 },
    { 26, 76, 5 , 3 },
    { 39, 76, 5 , 1 },
    { 52, 76, 2 , 2 },
    { 62, 76, 5 , 7 },
    { 75, 76, 5 , 9 },
    { 88, 76, 5 , 7 },
    { 101, 76, 5 , 9 },
    { 114, 76, 5 , 7 },
    { 127, 76, 4 , 9 },
    { 139, 76, 5 , 9 },
    { 152, 76, 5 , 9 },
    { 165, 76, 1 , 9 },
    { 174, 76, 5 , 11 },
    { 187, 76, 5 , 9 },
    { 200, 76, 2 , 9 },
    { 210, 76, 7 , 7 },
    { 225, 76, 5 , 7 },
    { 238, 76, 5 , 7 },
    { 4, 100, 5 , 9 },
    { 17, 100, 5 , 9 },
    { 30, 100, 5 , 7 },
    { 43, 100, 5 , 7 },
    { 56, 100, 4 , 8 },
    { 68, 100, 5 , 7 },
    { 81, 100, 5 , 7 },
    { 94, 100, 7 , 7 },
    { 109, 100, 5 , 7 },
    { 122, 100, 5 , 9 },
    { 135, 100, 5 , 7 },
    { 148, 100, 4 , 9 },
    { 160, 100, 1 , 9 },
    { 169, 100, 4 , 9 },
    { 181, 100, 6 , 2 },
};

// Font glyphs info data
// NOTE: No glyphs.image data provided
static const GlyphInfo darkFontChars[95] = {
    { 32, 0, 13, 4, { 0 }},
    { 33, 2, 4, 5, { 0 }},
    { 34, 2, 4, 7, { 0 }},
    { 35, 1, 4, 8, { 0 }},
    { 36, 1, 2, 7, { 0 }},
    { 37, 1, 4, 9, { 0 }},
    { 38, 1, 4, 7, { 0 }},
    { 39, 2, 4, 5, { 0 }},
    { 40, 3, 4, 7, { 0 }},
    { 41, 1, 4, 7, { 0 }},
    { 42, 1, 4, 7, { 0 }},
    { 43, 1, 6, 7, { 0 }},
    { 44, 1, 12, 5, { 0 }},
    { 45, 1, 8, 6, { 0 }},
    { 46, 2, 12, 5, { 0 }},
    { 47, 1, 4, 5, { 0 }},
    { 48, 1, 4, 7, { 0 }},
    { 49, 2, 4, 7, { 0 }},
    { 50, 1, 4, 7, { 0 }},
    { 51, 1, 4, 7, { 0 }},
    { 52, 1, 4, 7, { 0 }},
    { 53, 1, 4, 7, { 0 }},
    { 54, 1, 4, 7, { 0 }},
    { 55, 1, 4, 7, { 0 }},
    { 56, 1, 4, 7, { 0 }},
    { 57, 1, 4, 7, { 0 }},
    { 58, 2, 6, 5, { 0 }},
    { 59, 1, 6, 5, { 0 }},
    { 60, 1, 6, 5, { 0 }},
    { 61, 1, 7, 6, { 0 }},
    { 62, 1, 6, 5, { 0 }},
    { 63, 1, 4, 7, { 0 }},
    { 64, 1, 4, 9, { 0 }},
    { 65, 1, 4, 7, { 0 }},
    { 66, 1, 4, 7, { 0 }},
    { 67, 1, 4, 7, { 0 }},
    { 68, 1, 4, 7, { 0 }},
    { 69, 1, 4, 7, { 0 }},
    { 70, 1, 4, 7, { 0 }},
    { 71, 1, 4, 7, { 0 }},
    { 72, 1, 4, 7, { 0 }},
    { 73, 2, 4, 5, { 0 }},
    { 74, 1, 4, 7, { 0 }},
    { 75, 1, 4, 7, { 0 }},
    { 76, 1, 4, 7, { 0 }},
    { 77, 1, 4, 9, { 0 }},
    { 78, 1, 4, 7, { 0 }},
    { 79, 1, 4, 7, { 0 }},
    { 80, 1, 4, 7, { 0 }},
    { 81, 1, 4, 7, { 0 }},
    { 82, 1, 4, 7, { 0 }},
    { 83, 1, 4, 7, { 0 }},
    { 84, 1, 4, 7, { 0 }},
    { 85, 1, 4, 7, { 0 }},
    { 86, 1, 4, 7, { 0 }},
    { 87, 1, 4, 9, { 0 }},
    { 88, 1, 4, 7, { 0 }},
    { 89, 1, 4, 7, { 0 }},
    { 90, 1, 4, 7, { 0 }},
    { 91, 3, 4, 7, { 0 }},
    { 92, 1, 4, 5, { 0 }},
    { 93, 1, 4, 7, { 0 }},
    { 94, 1, 4, 7, { 0 }},
    { 95, 0, 14, 5, { 0 }},
    { 96, 1, 4, 5, { 0 }},
    { 97, 1, 6, 7, { 0 }},
    { 98, 1, 4, 7, { 0 }},
    { 99, 1, 6, 7, { 0 }},
    { 100, 1, 4, 7, { 0 }},
    { 101, 1, 6, 7, { 0 }},
    { 102, 1, 4, 6, { 0 }},
    { 103, 1, 6, 7, { 0 }},
    { 104, 1, 4, 7, { 0 }},
    { 105, 2, 4, 5, { 0 }},
    { 106, 1, 4, 7, { 0 }},
    { 107, 1, 4, 7, { 0 }},
    { 108, 2, 4, 5, { 0 }},
    { 109, 1, 6, 9, { 0 }},
    { 110, 1, 6, 7, { 0 }},
    { 111, 1, 6, 7, { 0 }},
    { 112, 1, 6, 7, { 0 }},
    { 113, 1, 6, 7, { 0 }},
    { 114, 1, 6, 7, { 0 }},
    { 115, 1, 6, 7, { 0 }},
    { 116, 1, 5, 6, { 0 }},
    { 117, 1, 6, 7, { 0 }},
    { 118, 1, 6, 7, { 0 }},
    { 119, 1, 6, 9, { 0 }},
    { 120, 1, 6, 7, { 0 }},
    { 121, 1, 6, 7, { 0 }},
    { 122, 1, 6, 7, { 0 }},
    { 123, 2, 4, 7, { 0 }},
    { 124, 2, 4, 5, { 0 }},
    { 125, 1, 4, 7, { 0 }},
    { 126, 1, 4, 8, { 0 }},
};

// Style loading function: dark
static void GuiLoadStyleDark(void)
{
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < DARK_STYLE_PROPS_COUNT; i++)
    {
        GuiSetStyle(darkStyleProps[i].controlId, darkStyleProps[i].propertyId, darkStyleProps[i].propertyValue);
    }

    // Custom font loading
    // NOTE: Compressed font image data (DEFLATE), it requires DecompressData() function
    int darkFontDataSize = 0;
    unsigned char *data = DecompressData(darkFontData, DARK_COMPRESSED_DATA_SIZE, &darkFontDataSize);
    Image imFont = { data, 256, 256, 1, 2 };

    Font font = { 0 };
    font.baseSize = 16;
    font.glyphCount = 95;

    // Load texture from image
    font.texture = LoadTextureFromImage(imFont);
    UnloadImage(imFont);  // Uncompressed data can be unloaded from memory

    // Copy char recs data from global fontRecs
    // NOTE: Required to avoid issues if trying to free font
    font.recs = (Rectangle *)malloc(font.glyphCount*sizeof(Rectangle));
    memcpy(font.recs, darkFontRecs, font.glyphCount*sizeof(Rectangle));

    // Copy font char info data from global fontChars
    // NOTE: Required to avoid issues if trying to free font
    font.glyphs = (GlyphInfo *)malloc(font.glyphCount*sizeof(GlyphInfo));
    memcpy(font.glyphs, darkFontChars, font.glyphCount*sizeof(GlyphInfo));

    GuiSetFont(font);

    // TODO: Setup a white rectangle on the font to be used on shapes drawing,
    // this way we make sure all gui can be drawn on a single pass because no texture change is required
    // NOTE: Setting up this rectangle is a manual process (for the moment)
    Rectangle whiteChar = { 124, 6, 1, 1 };
    SetShapesTexture(font.texture, whiteChar);

    //-----------------------------------------------------------------

    // TODO: Custom user style setup: Set specific properties here (if required)
    // i.e. Controls specific BORDER_WIDTH, TEXT_PADDING, TEXT_ALIGNMENT
}
