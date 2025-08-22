//=============================================================================
// _____     ___ ____  # insert another cool logo here
//  ____|   |    ____| # insert another cool logo here
// |     ___|   |____  # insert another cool logo here
// ---------------------------------------------------
//
// File:        filer.cpp
//
// Description: 
//
//=============================================================================

//========================================
// System Includes
//========================================

#include <exception>

//========================================
// PS2SDK Includes
//========================================

/* gsKit */
#include <gsKit.h>

/* gsToolkit */
#include <gsToolkit.h>

//========================================
// Project Includes
//========================================

/* sol */
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//========================================
// Definitions
//========================================

/* very ugly hack */
void* __dso_handle;

#define GS_BLACK GS_SETREG_RGBAQ(0x00, 0x00, 0x00, 0x80, 0x00)
#define GS_WHITE GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00)

#define GS_TEX_WHITE GS_SETREG_RGBAQ(0x80, 0x80, 0x80, 0x80, 0x00)

GSGLOBAL* gsGlobal = nullptr;
float globalZ = 0.0f;

namespace api {

void initialize() {
    gsGlobal = gsKit_init_global();

    gsGlobal->PrimAlpha = GS_BLEND_FRONT2BACK;
	gsGlobal->PSM = GS_PSM_CT16;
	gsGlobal->PSMZ = GS_PSMZ_16;
    
	gsKit_set_primalpha(gsGlobal, GS_SETREG_ALPHA(0, 1, 0, 1, 0), 0);
    
    dmaKit_init(D_CTRL_RELE_OFF,D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC, D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);

	gsKit_vram_clear(gsGlobal);
	gsKit_init_screen(gsGlobal);
	gsKit_mode_switch(gsGlobal, GS_ONESHOT);
}

void shutdown() {
    gsKit_deinit_global(gsGlobal);
    gsGlobal = nullptr;
}

void clear() {
    gsKit_clear(gsGlobal, GS_BLACK);
}

void sync() {
	gsKit_queue_exec(gsGlobal);
	gsKit_sync_flip(gsGlobal);
}

uint64_t color(int r, int g, int b, int a) {
    return GS_SETREG_RGBAQ(r, g, b, a >> 1, 0x00);
}

void setGlobalZ(float z) {
    globalZ = z;
}

float getGlobalZ() {
    return globalZ;
}

void drawPixel(float x, float y, uint64_t color, float z) {
    gsKit_prim_point(gsGlobal, x, y, z, color);
}

void drawLine(float x0, float y0, float x1, float y1, uint64_t c0, uint64_t c1, float z) {
    gsKit_prim_line_goraud(gsGlobal, x0, y0, x1, y1, z, c0, c1);
}

void drawRect(float x, float y, float width, float height, uint64_t color, float z) {
    gsKit_prim_line(gsGlobal, x, y, x + width, y, z, color);
    gsKit_prim_line(gsGlobal, x + width, y, x + width, y + height, z, color);
    gsKit_prim_line(gsGlobal, x + width, y + height, x, y + height, z, color);
    gsKit_prim_line(gsGlobal, x, y + height, x, y, z, color);
}

void fillRect(float x, float y, float width, float height, uint64_t color, float z) {
    gsKit_prim_quad(gsGlobal, x, y, x + width, y, x + width, y + height, x, y + height, z, color);
}

void drawQuad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, uint64_t c0, uint64_t c1, uint64_t c2, uint64_t c3, float z) {
    gsKit_prim_line_goraud(gsGlobal, x0, y0, x1, y1, z, c0, c1);
    gsKit_prim_line_goraud(gsGlobal, x1, y1, x2, y2, z, c1, c2);
    gsKit_prim_line_goraud(gsGlobal, x2, y2, x3, y3, z, c2, c3);
    gsKit_prim_line_goraud(gsGlobal, x3, y3, x0, y0, z, c3, c0);
}

void fillQuad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, uint64_t c0, uint64_t c1, uint64_t c2, uint64_t c3, float z) {
    gsKit_prim_quad_gouraud(gsGlobal, x0, y0, x1, y1, x2, y2, x3, y3, z, c0, c1, c2, c3);
}

void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint64_t c0, uint64_t c1, uint64_t c2, float z) {
    gsKit_prim_line_goraud(gsGlobal, x0, y0, x1, y1, z, c0, c1);
    gsKit_prim_line_goraud(gsGlobal, x1, y1, x2, y2, z, c1, c2);
    gsKit_prim_line_goraud(gsGlobal, x2, y2, x0, y0, z, c2, c0);
}

void fillTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint64_t c0, uint64_t c1, uint64_t c2, float z) {
    gsKit_prim_triangle_gouraud(gsGlobal, x0, y0, x1, y1, x2, y2, z, c0, c1, c2);
}

GSTEXTURE* loadImage(const std::string& path) {
    const char* ext = strrchr(path.c_str(), '.');
	if (!ext) throw std::runtime_error("invalid image path");

    GSTEXTURE* texture = new GSTEXTURE();
    texture->Delayed = 1;

	if (strcmp(ext, ".bmp") == 0) 
        gsKit_texture_bmp(gsGlobal, texture, const_cast<char*>(path.c_str()));
	else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0)
        gsKit_texture_jpeg(gsGlobal, texture, const_cast<char*>(path.c_str()));
	else if (strcmp(ext, ".png") == 0)
        gsKit_texture_png(gsGlobal, texture, const_cast<char*>(path.c_str()));
    else {
        delete texture;
        throw std::runtime_error("unsupported image format");
    }

	return texture;
}

void freeImage(GSTEXTURE* texture) {
    if (!texture) return;
    if(!texture->Delayed) throw std::runtime_error("cannot free non-delayed texture");
    gsKit_TexManager_free(gsGlobal, texture);
    free(texture->Mem);
	if(texture->Clut != NULL) free(texture->Clut);
    delete texture;
}

void drawImage(GSTEXTURE* texture, float x0, float y0, float u0, float v0, float x1, float y1, float u1, float v1, uint64_t color, float z) {
    if (!texture) throw std::runtime_error("invalid texture");
    if(texture->Delayed) gsKit_TexManager_bind(gsGlobal, texture);
    gsKit_prim_sprite_texture(gsGlobal, texture, x0, y0, u0, v0, x1, y1, u1, v1, z, color);
}

void drawAtlas(GSTEXTURE* texture, float x, float y, float width, float height, int columns, int rows, int index, uint64_t color, float z) {
    if (!texture) throw std::runtime_error("invalid texture");
    if(texture->Delayed) gsKit_TexManager_bind(gsGlobal, texture);

    float u0 = (index % columns) * (width / texture->Width);
    float v0 = (index / columns) * (height / texture->Height);
    float u1 = u0 + (width / texture->Width);
    float v1 = v0 + (height / texture->Height);

    gsKit_prim_sprite_texture(gsGlobal, texture, x, y, u0, v0, x + width, y + height, u1, v1, z, color);
}



} // namespace api

extern "C" __attribute__((visibility("default"))) int luaopen_luagraphics(lua_State* L) noexcept try {
    sol::state_view lua(L);

    auto table = lua.create_table();
    table["initialize"] = &api::initialize;
    table["shutdown"] = &api::shutdown;
    table["clear"] = &api::clear;
    table["sync"] = &api::sync;

    table["color"] = &api::color;

    table["setGlobalZ"] = &api::setGlobalZ;
    table["getGlobalZ"] = &api::getGlobalZ;

    table["drawPixel"] = [](float x, float y, uint64_t color) { api::drawPixel(x, y, color, globalZ); };
    table["drawPixelEx"] = &api::drawPixel;

    table["drawLine"] = [](float x0, float y0, float x1, float y1, uint64_t color) { api::drawLine(x0, y0, x1, y1, color, color, globalZ); };
    table["drawLineEx"] = &api::drawLine;

    table["drawRect"] = [](float x, float y, float width, float height, uint64_t color) { api::drawRect(x, y, width, height, color, globalZ); };
    table["drawRectEx"] = &api::drawRect;

    table["fillRect"] = [](float x, float y, float width, float height, uint64_t color) { api::fillRect(x, y, width, height, color, globalZ); };
    table["fillRectEx"] = &api::fillRect;

    table["drawQuad"] = &api::drawQuad;
    table["fillQuad"] = &api::fillQuad;
    table["drawTriangle"] = &api::drawTriangle;
    table["fillTriangle"] = &api::fillTriangle;

    table["loadImage"] = &api::loadImage;
    table["freeImage"] = &api::freeImage;
    table["drawImage"] = sol::overload(
        [](GSTEXTURE* texture, float x, float y) { api::drawImage(texture, x, y, 0.0f, 0.0f, x + texture->Width, y + texture->Height, texture->Width, texture->Height, GS_TEX_WHITE, globalZ); },
        [](GSTEXTURE* texture, float x, float y, float width, float height) { api::drawImage(texture, x, y, 0.0f, 0.0f, x + width, y + height, texture->Width, texture->Height, GS_TEX_WHITE, globalZ); }
    );
    table["drawImageColored"] = sol::overload(
        [](GSTEXTURE* texture, float x, float y, uint64_t color) { api::drawImage(texture, x, y, 0.0f, 0.0f, x + texture->Width, y + texture->Height, texture->Width, texture->Height, color, globalZ); },
        [](GSTEXTURE* texture, float x, float y, float width, float height, uint64_t color) { api::drawImage(texture, x, y, 0.0f, 0.0f, x + width, y + height, texture->Width, texture->Height, color, globalZ); }
    );
    table["drawImageEx"] = &api::drawImage;
    table["drawAtlas"] = [](GSTEXTURE* texture, float x, float y, float width, float height, int columns, int rows, int index) { api::drawAtlas(texture, x, y, width, height, columns, rows, index, GS_WHITE, globalZ); };
    table["drawAtlasEx"] = &api::drawAtlas;

    table.push();

    return 1;
} catch (std::exception& e) {
    return luaL_error(L, "%s", e.what());
}