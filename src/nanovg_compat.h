#ifndef NANOVG_COMPAT_H
#define NANOVG_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <nanovg.h>

#define NVG_ALIGN_TL (NVG_ALIGN_TOP | NVG_ALIGN_LEFT)
#define NVG_ALIGN_TC (NVG_ALIGN_TOP | NVG_ALIGN_CENTER)
#define NVG_ALIGN_TR (NVG_ALIGN_TOP | NVG_ALIGN_RIGHT)

#define NVG_ALIGN_CL (NVG_ALIGN_MIDDLE | NVG_ALIGN_LEFT)
#define NVG_ALIGN_CC (NVG_ALIGN_MIDDLE | NVG_ALIGN_CENTER)
#define NVG_ALIGN_CR (NVG_ALIGN_MIDDLE | NVG_ALIGN_RIGHT)

#define NVG_ALIGN_BL (NVG_ALIGN_BOTTOM | NVG_ALIGN_LEFT)
#define NVG_ALIGN_BC (NVG_ALIGN_BOTTOM | NVG_ALIGN_CENTER)
#define NVG_ALIGN_BR (NVG_ALIGN_BOTTOM | NVG_ALIGN_RIGHT)

#ifdef _WIN32
#define D3D11_NO_HELPERS
#define NOMINMAX
#include <nanovg_d3d11.h>

struct D3DNVGframebuffer
{
    int image; // nvg image id
    struct ID3D11RenderTargetView* pRenderTargetView;
    float width;
    float height;
};
typedef struct D3DNVGframebuffer D3DNVGframebuffer;

NVGcontext* d3dnvgCreateContext(void* hwnd, int flags, unsigned int width,
                                unsigned int height);
long d3dnvgSetViewBounds(void* hwnd, unsigned int width, unsigned int height);
void d3dnvgDeleteContext(NVGcontext* ctx);
void d3dnvgClearWithColor(NVGcontext* ctx, NVGcolor color);

// Binds the output-merger render target
void d3dnvgBindFramebuffer(D3DNVGframebuffer* fb);
// Creates a 2D texture to use as a render target
D3DNVGframebuffer* d3dnvgCreateFramebuffer(NVGcontext* ctx, int w, int h,
                                           int flags);
// Deletes the frame buffer
void d3dnvgDeleteFramebuffer(NVGcontext* ctx, D3DNVGframebuffer* fb);

void d3dPresent(void);

#define nvgCreateContext(layer, flags, w, h)                                   \
    d3dnvgCreateContext(layer,                                                 \
                        flags | NVG_ANTIALIAS | NVG_STENCIL_STROKES,           \
                        (unsigned)w, (unsigned)h)
#define nvgDeleteContext(context) d3dnvgDeleteContext(context)
#define nvgBindFramebuffer(fb) d3dnvgBindFramebuffer(fb)
#define nvgCreateFramebuffer(ctx, w, h, flags)                                 \
    d3dnvgCreateFramebuffer(ctx, w, h, flags)
#define nvgDeleteFramebuffer(ctx, fb) d3dnvgDeleteFramebuffer(ctx, fb)
#define nvgClearWithColor(ctx, color) d3dnvgClearWithColor(ctx, color)
#define nvgSetViewBounds(layer, w, h)                                          \
    d3dnvgSetViewBounds(layer, (unsigned)w, (unsigned)h)
typedef D3DNVGframebuffer NVGframebuffer;

#elif defined __APPLE__
#include <nanovg_mtl.h>

NVGcontext* mnvgCreateContext(void* view, int flags, int width, int height);
void mnvgSetViewBounds(void* view, int width, int height);

#define nvgCreateContext(layer, flags, w, h)                                   \
    mnvgCreateContext(layer, flags | NVG_ANTIALIAS | NVG_TRIPLE_BUFFER, w, h)
#define nvgDeleteContext(context) nvgDeleteMTL(context)
#define nvgBindFramebuffer(fb) mnvgBindFramebuffer(fb)
#define nvgCreateFramebuffer(ctx, w, h, flags)                                 \
    mnvgCreateFramebuffer(ctx, w, h, flags)
#define nvgDeleteFramebuffer(ctx, fb) mnvgDeleteFramebuffer(fb)
#define nvgClearWithColor(ctx, color) mnvgClearWithColor(ctx, color)
#define nvgSetViewBounds(nsview, w, h) mnvgSetViewBounds(nsview, w, h)
typedef MNVGframebuffer NVGframebuffer;

#elif defined __linux__
#include <nanovg_gl.h>
#include <nanovg_gl_utils.h>

#define nvgCreateContext(flags) nvgCreateGLES2(flags)
#define nvgDeleteContext(context) nvgDeleteGLES2(context)
#define nvgBindFramebuffer(fb) nvgluBindFramebuffer(fb)
#define nvgCreateFramebuffer(ctx, w, h, flags)                                 \
    nvgluCreateFramebuffer(ctx, w, h, flags)
#define nvgDeleteFramebuffer(ctx, fb) nvgluDeleteFramebuffer(fb)
typedef NVGLUframebuffer NVGframebuffer;

#endif

struct NanoVGDrawCallCount
{
    int draws;
    int fill;
    int stroke;
    int text;
    int total;
};
typedef struct NanoVGDrawCallCount NanoVGDrawCallCount;

NanoVGDrawCallCount nvgGetDrawCallCount(NVGcontext* ctx);

NVGcolor nvgGetFillColor(NVGcontext* ctx);

void nvgCurrentScissor(NVGcontext* ctx, float* x, float* y, float* w, float* h);

// Fills the current path with current stroke style.
// Set fringeWidth to value > 1 to control blur amount.
// https://github.com/memononen/nanovg/issues/460
void nvgStrokeBlur(NVGcontext* ctx, float fringeWidth);

#ifdef __cplusplus
}
#endif

#endif // NANOVG_COMPAT_H
