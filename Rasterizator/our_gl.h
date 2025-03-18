#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

extern mat4 View;
extern mat4 Viewport;
extern mat4 Projection;

void viewport(int x, int y, int w, int h);
void projection(float coeff = 0.f); // coeff = -1/c
void lookat(Vec3f eye, Vec3f center, Vec3f up);

struct IShader {
    virtual ~IShader();
    virtual Vec4f vertex(int iface, int vertex, Model* model) = 0;
    virtual bool fragment(Vec3f bar, TGAColor& color, Model* model, bool id[5]) = 0;
};

void triangle(Vec4f screen_coords[3], IShader& shader, TGAImage& image, TGAImage& zbuffer, Model* model, bool id[5]);

void triangle(Vec2i screen_coords[3], IShader& shader, TGAImage& image, TGAImage& zbuffer, TGAImage& output, bool id[5]);

struct CombShader : public IShader 
{
    TGAImage* image;
    TGAImage* zbuffer;
    Vec4f vertex(int iface, int vertex, Model* model) override
    {
        return Vec4f{ 0., 0., 0., 0. };
    };
    bool fragment(Vec3f bar, TGAColor& color, Model* model = nullptr, bool id [5] = {0}) override;
};