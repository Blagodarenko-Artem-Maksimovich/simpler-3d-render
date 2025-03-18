# OBJ to TGA Renderer (C++ Software Renderer) 

## Features    
### Core Rendering  
- Renders .obj models with triangles-only support (Quad faces may render incorrectly)  
- Supports diffuse, normal, and specular maps (TGA format, auto-loaded via naming convention)  
- Configurable camera, lighting, and rasterization settings via code constants  
- Rasterization algorithm: Barycentric (default) 
- Shading modes 
- Z-buffer visualization export
- Add custom models

### Shaders & Post-Processing  
- **Fog**: Depth-based atmospheric effect
- **Noise**: Film grain / static effect  
- **Negative**: Color inversion shader
- **Desaturate**: Grayscale conversion 
- **Blur**: Post-process Gaussian/Box blur
**You can combine shaders to get the desired effect**

[render without shaders](https://github.com/Blagodarenko-Artem-Maksimovich/simpler-3d-render/tree/main/Img/simple.png)

## Comand list
- 'resize int int' - change width and height of output tga image (current: 800 800);
- 'light float float float' - change light position (current: 1 1 1);
- 'camera float float float' - change camera position (current: 0 0 3);
- 'center float float float' - change lookat point position (current: 0 0 0);
- 'add_shader name1 name2 ...' - add shader 1.fog 2.noise 3.negative 4.desaturating 5.blur
- 'add_model filename.obj' - add another model to render with its position and specular coefficient (models to render: 0);
- 'render' - that's it, render

## Texture Requirements
Place textures in same directory as .obj file with naming:

- **Diffuse**: <modelname>_diffuse.tga
- **Normal map**: <modelname>_nm.tga
- **Specular**: <modelname>_spec.tga

Models without diffuse textures render in unlit mode

## Known Limitations
- Quad faces not supported - triangulate models first
- TGA-only texture format support
- Linesweep algorithm doesn't support Phong shading



