#include "model.h"

//TODO: CREATE MODELVIEW

Model::Model(std::string filename, Vec3f modelCenter, float specCoeff)
    : _defaultSpec{specCoeff}
{
	std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!";
        return;
    }

    std::string line;

    while (!file.eof())
    {
        std::getline(file, line);
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            if (word == "v")
            {
                Vec3f vertix;
                ss >> vertix.x >> vertix.y >> vertix.z;
                _vertices.push_back(vertix);

                if (std::abs(vertix.x) > _scale)
                {
                    _scale = vertix.x;
                }
                if (std::abs(vertix.y) > _scale)
                {
                    _scale = vertix.y;
                }
                if (std::abs(vertix.z) > _scale)
                {
                    _scale = vertix.z;
                }
            }
            else if (word == "f")
            {
                std::vector<std::vector<int>> face{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
                for (int i = 0; i < 3; i++)
                {
                    ss >> word;
                    std::stringstream iss(word);
                    std::string vertix;
                    for (int j = 0; j < 3; j++)
                    {
                        std::getline(iss, vertix, '/');
                        try
                        {
                            face[i][j] = std::stoi(vertix);
                        }
                        catch (...)
                        {
                            face[i][j] = 0;
                        }
                    }
                }
                _faces.push_back(face);
                
            }
            else if (word == "vt")
            {
                Vec2f texVertix;
                ss >> texVertix.x >> texVertix.y;
                _texVertices.push_back(texVertix);
            }
            else if (word == "vn")
            {
                Vec3f normal;
                ss >> normal.x >> normal.y >> normal.z;
                _norms.push_back(normal);
            }
            else
            {
                break;
            }
        }
    }

    std::cout << "file has been read: " << _vertices.size() << " vertices, " << _faces.size() << " faces." << std::endl;
    load_texture(filename, "_diffuse.tga", _diffMap);
    load_texture(filename, "_nm.tga", _normalMap);
    load_texture(filename, "_spec.tga", _specularMap);


    
    _ModelView(0, 3) = -modelCenter.x;
    _ModelView(1, 3) = -modelCenter.y;
    _ModelView(2, 3) = -modelCenter.z;

    file.close();
}

int Model::nfaces()
{
    return (int)_faces.size();
}

std::vector<std::vector<int>> Model::face(int i)
{
    return _faces[i];
}

Vec3f Model::vert(int i)
{
    return _vertices[i]/_scale;
}

Vec2i Model::uv(int i)
{
    Vec2f vertix = _texVertices[i];
    return { int(vertix.x*_diffMap.get_width() + .5), int(vertix.y * _diffMap.get_height() + .5)};
}

TGAColor Model::diffuse(Vec2f uv)
{
    if (_diffMap.get_bytespp())
    {
        return _diffMap.get(int(uv.x + .5), int(uv.y + .5));
    }
    else
    {
        return TGAColor(255, 255, 255, 255);
    }
}

Vec3f Model::normal(int i)
{
    return _norms[i];
}

Vec3f Model::normal(Vec2f uv)
{
    TGAColor normal = _normalMap.get(int(uv.x + .5), int(uv.y + .5));
    Vec3f normalVec = Vec3f( (float)normal.r, (float)normal.g, (float)normal.b);
    normalVec = (normalVec * 2. / 255.) - Vec3f(1., 1., 1.);
    return normalVec;
}

bool Model::hasNormalMap()
{
    return _normalMap.get_bytespp();
}

float Model::spec(Vec2f uv)
{
    if (_specularMap.get_bytespp())
    {
        return _specularMap.get(uv.x, uv.y).b;
    }
    else return _defaultSpec;
}

mat4 Model::ModelView()
{
    return _ModelView;
}

void Model::load_texture(std::string filename, const char* suffix, TGAImage& img)
{
    std::string texfile(filename);
    size_t dot = texfile.find_last_of(".");
    if (dot != std::string::npos) {
        texfile = texfile.substr(0, dot) + std::string(suffix);
        std::cerr << "texture file " << texfile << " loading " << (img.read_tga_file(texfile.c_str()) ? "ok" : "failed") << std::endl;
        img.flip_vertically();
    }
}