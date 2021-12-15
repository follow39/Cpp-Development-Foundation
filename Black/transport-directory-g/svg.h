#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <memory>

namespace Svg {

    struct Point {
        double x = 0.0;
        double y = 0.0;
    };

    struct Rgb {
        Rgb() = default;

        Rgb(int new_red, int new_green, int new_blue, double new_alpha = 0.0)
                : red(new_red), green(new_green), blue(new_blue), alpha(new_alpha) {}

        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        double alpha = 0.0;
    };

    using Color = std::variant<std::monostate, std::string, Rgb>;
    static const Color NoneColor{};

    void RenderPoint(std::ostream &output, const Point &point);

    void RenderRgb(std::ostream &output, const Rgb &rgb);

    void RenderColor(std::ostream &output, std::monostate);

    void RenderColor(std::ostream &output, const std::string &color);

    void RenderColor(std::ostream &output, const Rgb &color);

    template<typename ParamType>
    void RenderParam(std::ostream &output, const std::string &paramName, const ParamType &paramValue);

    template<>
    void RenderParam(std::ostream &output, const std::string &paramName, const Color &paramValue);

    class Object {
    public:
        virtual void Render(std::ostream &output) const = 0;

        virtual ~Object() = default;
    };

    template<typename ObjectType>
    class SvgObject {
    public:
        SvgObject() = default;

        ObjectType &SetFillColor(const Color &new_fillColor) {
            fillColor = new_fillColor;
            return *obj();
        }

        ObjectType &SetStrokeColor(const Color &new_strokeColor) {
            strokeColor = new_strokeColor;
            return *obj();
        }

        ObjectType &SetStrokeWidth(double new_strokeWidth) {
            strokeWidth = new_strokeWidth;
            return *obj();
        }

        ObjectType &SetStrokeLineCap(const std::string &new_strokeLineCap) {
            strokeLineCap = new_strokeLineCap;
            return *obj();
        }

        ObjectType &SetStrokeLineJoin(const std::string &new_strokeLineJoin) {
            strokeLineJoin = new_strokeLineJoin;
            return *obj();
        }

        void RenderAttrs(std::ostream &output) const;

        virtual ~SvgObject() = default;

    private:
        ObjectType *obj() {
            return static_cast<ObjectType *>(this);
        }

        Color fillColor = NoneColor;
        Color strokeColor = NoneColor;
        double strokeWidth = 1.0;
        std::string strokeLineCap;
        std::string strokeLineJoin;
    };

    class Circle : public Object, public SvgObject<Circle> {
        friend class SvgObject;

    public:
        Circle &SetCenter(Point new_center) {
            center = new_center;
            return *this;
        }

        Circle &SetRadius(double new_radius) {
            radius = new_radius;
            return *this;
        }

        void Render(std::ostream &output) const override;

    private:
        Point center{0.0, 0.0};
        double radius = 1.0;
    };

    class Polyline : public Object, public SvgObject<Polyline> {
        friend class SvgObject;

    public:
        Polyline &AddPoint(Point new_point) {
            points.push_back(new_point);
            return *this;
        }

        void Render(std::ostream &output) const;

    private:
        std::vector<Point> points;
    };

    class Text : public Object, public SvgObject<Text> {
        friend class SvgObject;

    public:
        Text &SetPoint(Point new_point) {
            point = new_point;
            return *this;
        }

        Text &SetOffset(Point new_offset) {
            offset = new_offset;
            return *this;
        }

        Text &SetFontSize(uint32_t new_fontSize) {
            fontSize = new_fontSize;
            return *this;
        }

        Text &SetFontFamily(const std::string &new_fontFamily) {
            fontFamily = new_fontFamily;
            return *this;
        }

        Text &SetData(const std::string &new_text) {
            text = new_text;
            return *this;
        }

        void Render(std::ostream &output) const override;

    private:
        Point point{0.0, 0.0};
        Point offset{0.0, 0.0};
        uint32_t fontSize = 1;
        std::string fontFamily;
        std::string text;
    };


    class Document : public Object {
    public:
        template<class ObjectType>
        Document &Add(ObjectType &&svgObject) {
            objects.emplace_back(std::forward<ObjectType>(svgObject));
            return *this;
        }

        void Render(std::ostream &output) const;

    private:
        const std::string xmlVersion = R"(<?xml version="1.0" encoding="UTF-8" ?>)";
        const std::string svgBegin = R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)";
        const std::string svgEnd = R"(</svg>)";

        std::vector<std::variant<Circle, Polyline, Text>> objects;
    };

}
