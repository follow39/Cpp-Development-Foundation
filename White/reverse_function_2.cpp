#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;


//struct Image {
//    double quality;
//    double freshness;
//    double rating;
//};

//struct Params {
//    double a;
//    double b;
//    double c;
//};

class FunctionPart {
public:
    FunctionPart(char new_operatin, double new_value) {
        operation = new_operatin;
        value = new_value;
    }
    double Apply(double input_value) const {
        if(operation == '+')
        {
            return input_value + value;
        }
        else if(operation == '-')
        {
            return input_value - value;
        }
        else if(operation == '*')
        {
            return input_value * value;
        }
        else if(operation == '/')
        {
            return input_value / value;
        }
        return input_value;
    }
    void Invert()
    {
        if(operation == '+')
        {
            operation = '-';
        }
        else if(operation == '-')
        {
            operation = '+';
        }
        else if(operation == '*')
        {
            operation = '/';
        }
        else if(operation == '/')
        {
            operation = '*';
        }
    }

private:
    char operation;
    double value;
};

class Function {
public:
    void AddPart(char new_operation, double input_value) {
        parts.push_back({new_operation, input_value});
    }
    double Apply(double input_value) const {
        for(const auto& part : parts)
        {
            input_value = part.Apply(input_value);
        }
        return input_value;
    }
    void Invert() {
        for(auto& part : parts)
        {
            part.Invert();
        }
        reverse(begin(parts), end(parts));
    }
private:
    vector<FunctionPart> parts;

};

Function MakeWeightFunction(const Params& params,
                            const Image& image) {
    Function function;
    function.AddPart('*', params.a);
    function.AddPart('-', image.freshness * params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
    Function function = MakeWeightFunction(params, image);
    function.Invert();
    return function.Apply(weight);
}

//int main() {
//    Image image = {10, 2, 6};
//    Params params = {4, 2, 6};
//    cout << ComputeImageWeight(params, image) << endl;
//    cout << ComputeQualityByWeight(params, image, 52) << endl;
//    return 0;
//}



