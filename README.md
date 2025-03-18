Rasterizator written on DirectXSimpleMath that draws object in .tga file.
(DirectXSimpleMath is such a pain tbh)

All you need to do is build the project and then you can either drag your object file to Rasterizator.exe or open terminal and write command "./Rasterizator.exe your_object.obj". The program will provide you with two files: rendered object and zbuffer, drawing depth.

Camera, light direction and etc is set in main.cpp as constants. Maybe I will change it later to be configured from terminal.
Rasterizator can work with normal, specular and diffuse maps, for that you need to have them in tga format with this naming: "your_object_nm.tga", "your_object_spec.tga", "your_object_diffuse.tga". You need to have them in the same directory as object.
Another thing to realize: rasterizator is working only with triangles so if your object has quad faces then the model will be rendered a little bit wrong. Maybe I will fix it later too, but that's unknown.

Also some operators and constructors are written in files that aren't in the solution (such as Simplemath.h and etc) I'll fix it too someday
