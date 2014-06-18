#pragma once
#ifdef __cplusplus
extern "C"{
#endif

enum {
  BARD,
  F_RGBA,
  F_RGB,
  S_32,
  S_24,
  R_PALETTE,
};

struct TowerImageRGBA{
    unsigned long w;
    unsigned long h;
    unsigned char *RGBA;
};

struct TowerImageRGBA *TowerImageLoadFile(const char *aName);

#ifdef __cplusplus
}
#endif