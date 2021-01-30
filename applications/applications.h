#pragma once

#include <stddef.h>
//#include <furi.h>
//#include <assets_icons.h>

typedef void (*FlipperApplication)(void*);

typedef struct {
    const FlipperApplication app;
    const char* name;
    //const IconName icon;
} FuriApplication;

 
 
 