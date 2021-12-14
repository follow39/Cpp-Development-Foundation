#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <memory>

namespace Svg {

    struct Point;
    struct Rgb;
    struct Color;

    template<typename ObjectType>
    class SvgObject;

    class Circle;

    class Polyline;

    class Text;

    class Document;


    struct Point {
        double x = 0.0;
        double y = 0.0;

        Point() = default;

        Point(double new_x, double new_y) : x(new_x), y(new_y) {}

        [[nodiscard]] std::string ToString() const {
            std::string result;
            result += std::to_string(x) + "," +
                      std::to_string(y);
            return result;
        }
    };

    struct Rgb {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;

        Rgb() = default;

        explicit Rgb(uint8_t new_red, uint8_t new_green, uint8_t new_blue)
                : red(new_red), green(new_green), blue(new_blue) {}

        [[nodiscard]] std::string ToString() const {
            std::string result;
            result += "rgb(";
            result += std::to_string(red) + "," +
                      std::to_string(green) + "," +
                      std::to_string(blue);
            result += ")";
            return result;
        }
    };

    struct Color {
        std::variant<std::monostate, std::string, Rgb> color;

        Color() = default;

        Color(const std::string &new_color) {
            color = new_color;
        }

        Color(const char *new_color) {
            color = new_color;
        }

        Color(const Rgb &new_color) {
            color = new_color;
        }

        [[nodiscard]] std::string ToString() const {
            std::string result;
            if (std::holds_alternative<std::string>(color)) {
                result = std::get<std::string>(color);
            } else if (std::holds_alternative<Rgb>(color)) {
                result = std::get<Rgb>(color).ToString();
            } else {
                result = "none";
            }
            return result;
        }
    };

    Color NoneColor{};

    std::string PrintParam(const std::string &paramName, const std::string &paramValue) {
        return paramName + "=\"" + paramValue + "\" ";
    }

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

        [[nodiscard]] virtual std::string ToString() const {
            std::string result;
            result += PrintParam("fill", fillColor.ToString());
            result += PrintParam("stroke", strokeColor.ToString());
            result += PrintParam("stroke-width", std::to_string(strokeWidth));
            if (!strokeLineCap.empty()) {
                result += PrintParam("stroke-linecap", strokeLineCap);
            }
            if (!strokeLineJoin.empty()) {
                result += PrintParam("stroke-linejoin", strokeLineJoin);
            }
            return result;
        }

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

    class Circle : public SvgObject<Circle> {
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

        [[nodiscard]] std::string ToString() const override {
            std::string result;
            result += "<circle ";
            result += PrintParam("cx", std::to_string(center.x));
            result += PrintParam("cy", std::to_string(center.y));
            result += PrintParam("r", std::to_string(radius));
            result += SvgObject::ToString();
            result += "/>";
            return result;
        }

    private:
        Point center{0.0, 0.0};
        double radius = 1.0;
    };

    class Polyline : public SvgObject<Polyline> {
        friend class SvgObject;

    public:
        Polyline &AddPoint(Point new_point) {
            points.push_back(new_point);
            return *this;
        }

        [[nodiscard]] std::string ToString() const override {
            std::string result;
            result += "<polyline ";
            result += "points=\"";
            for (const auto &point: points) {
                result += point.ToString() + " ";
            }
            result += "\" ";
            result += SvgObject::ToString();
            result += "/>";
            return result;
        }

    private:
        std::vector<Point> points;
    };

    class Text : public SvgObject<Text> {
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

        [[nodiscard]] std::string ToString() const override {
            std::string result;
            result += "<text ";
            result += PrintParam("x", std::to_string(point.x));
            result += PrintParam("y", std::to_string(point.y));
            result += PrintParam("dx", std::to_string(offset.x));
            result += PrintParam("dy", std::to_string(offset.y));
            result += PrintParam("font-size", std::to_string(fontSize));
            if (!fontFamily.empty()) {
                result += PrintParam("font-family", fontFamily);
            }
            result += SvgObject::ToString();
            result += ">" + text;
            result += "</text>";
            return result;
        }

    private:
        Point point{0.0, 0.0};
        Point offset{0.0, 0.0};
        uint32_t fontSize = 1;
        std::string fontFamily;
        std::string text;
    };


    class Document {
    public:
        template<class ObjectType>
        Document &Add(ObjectType &&svgObject) {
            objects.emplace_back(std::forward<ObjectType>(svgObject));
            return *this;
        }

        Document &Render(std::ostream &os) {
            os << xmlVersion;
            os << svgBegin;
            for (const auto &object: objects) {
                os << std::visit([](const auto &obj) { return obj.ToString(); }, object);
            }
            os << svgEnd;
            return *this;
        }

    private:
        const std::string xmlVersion = R"(<?xml version="1.0" encoding="UTF-8" ?>)";
        const std::string svgBegin = R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)";
        const std::string svgEnd = R"(</svg>)";

        std::vector<std::variant<Circle, Polyline, Text>> objects;
    };

}
