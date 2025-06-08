#ifndef DRAWABLE_DINO
#define DRAWABLE_DINO

#include <raylib-cpp.hpp>

class Asset {
  private:
  public:
    virtual ~Asset();
    virtual void draw(raylib::Vector2, int state) {};
    virtual float getWidth(int state) { return 0; };
    virtual float getHeight(int state) { return 0; };
};

Asset::~Asset() = default;

class Drawable {
  private:
    /* data */
  public:
    float rotation = 0;
    float scale = 1;
    raylib::Color color;
    raylib::Texture2D texture;
    raylib::Shader shader;

    Drawable(std::string texture_path, std::string shader_path);

    Drawable(const Drawable &) = delete;
    ~Drawable();

    Vector2 get_dimensions() {
        return raylib::Vector2(this->texture.GetSize());
    }

    void draw(Vector2 pos) {
        this->shader.BeginMode();

        this->texture.Draw(pos, this->rotation, this->scale, this->color);

        this->shader.EndMode();
    }
};

Drawable::Drawable(std::string texture_path, std::string shader_path)
    : shader("", shader_path) {
    this->texture.Load(texture_path);
    this->color = WHITE;
}

Drawable::~Drawable() {
    shader.Unload();
    texture.Unload();
}

#endif