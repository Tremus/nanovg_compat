# nanovg_compat

Simple wrapper for [NanoVG](https://github.com/memononen/nanovg). Ready to include as a module for a CMake project. By default it uses the backends DirectX 11 on Windows and Metal on MacOS.

## Linking

CMake will build this as a static library you should link as `nanovg_compat`.

You will have to link additional libraries depending on your operating system.

-   Windows: `d3d11` & `dxguid`
-   MacOS: `-framework Metal`
