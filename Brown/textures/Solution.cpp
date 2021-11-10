#include "Common.h"
#include "Textures.h"
#include <memory>

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`
class ShapeBasic : public IShape {
public:
    ShapeBasic() {
        pos = {0, 0};
        size = {0, 0};
    }

    void SetPosition(Point new_position) final {
        pos = new_position;
    }

    Point GetPosition() const final {
        return pos;
    }

    void SetSize(Size new_size) final {
        size = new_size;
    }

    Size GetSize() const final {
        return size;
    }

    void SetTexture(std::shared_ptr<ITexture> new_texture) final {
        texture = new_texture;
    }

    ITexture *GetTexture() const final {
        return texture.get();
    }

protected:
    Point pos;
    Size size;
    std::shared_ptr<ITexture> texture;
    ShapeType shapeType;
};

class Rectangle : public ShapeBasic {
public:
    Rectangle() : ShapeBasic() {
        shapeType = ShapeType::Rectangle;
    }

    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(*this);
    }

    void Draw(Image &image) const override {
        for (int i = pos.y; i < image.size() && i < pos.y + size.height; ++i) {
            for (int j = pos.x; j < image[i].size() && j < pos.x + size.width; ++j) {
                if (texture && i - pos.y < texture->GetSize().height &&
                    j - pos.x < texture->GetSize().width) {
                    image[i][j] = texture->GetImage()[i - pos.y][j - pos.x];
                } else {
                    image[i][j] = '.';
                }
            }
        }
    }
};

class Ellipse : public ShapeBasic {
public:
    Ellipse() : ShapeBasic() {
        shapeType = ShapeType::Ellipse;
    }

    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(*this);
    }

    void Draw(Image &image) const override {
        for (int i = pos.y; i < image.size() && i < pos.y + size.height; ++i) {
            for (int j = pos.x; j < image[i].size() && j < pos.x + size.width; ++j) {
                if (IsPointInEllipse({j - pos.x, i - pos.y}, size)) {
                    if (texture && i - pos.y < texture->GetSize().height &&
                        j - pos.x < texture->GetSize().width) {
                        image[i][j] = texture->GetImage()[i - pos.y][j - pos.x];
                    } else {
                        image[i][j] = '.';
                    }
                }
            }
        }
    }
};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type) {
        case ShapeType::Rectangle:
            return make_unique<Rectangle>();
        case ShapeType::Ellipse:
            return make_unique<Ellipse>();
    }
}