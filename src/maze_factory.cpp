#include <napi.h>
#include <vector>
#include <string>
#include <sstream>

class Cell {
public:
    int x, y;
    std::string type;

    Cell(int x, int y, const std::string& type) : x(x), y(y), type(type) {}

    std::string toJson() const {
        std::ostringstream oss;
        oss << "{ \"x\": " << x << ", \"y\": " << y << ", \"type\": \"" << type << "\" }";
        return oss.str();
    }
};

std::string generateMazeJson(int width, int height, const std::string& algorithm) {
    std::vector<Cell> objects;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            objects.emplace_back(i, j, "cell");
        }
    }

    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < objects.size(); ++i) {
        oss << objects[i].toJson();
        if (i < objects.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

Napi::String GenerateMazeWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    int width = info[0].As<Napi::Number>().Int32Value();
    int height = info[1].As<Napi::Number>().Int32Value();
    std::string algorithm = info[2].As<Napi::String>();

    std::string result = generateMazeJson(width, height, algorithm);
    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "generateMaze"), Napi::Function::New(env, GenerateMazeWrapped));
    return exports;
}

NODE_API_MODULE(addon, Init)
