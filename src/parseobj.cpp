#include "../include/parseobj.hpp"

Mesh getMeshFromObj(const std::string& filename)
{
    std::ifstream file(filename);
    
    if(!file)
    {
        throw std::runtime_error("file " + filename + "not found.");
    }

    Mesh mesh;
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string prefix;

        iss >> prefix;

        if (prefix == "v")
        {
            float x, y, z;
            iss >> x >> y >> z;

            Vertex v {
                {x, y, z},
                {1.0f, 0.0f, 1.0f}
            };

            mesh.vertices.push_back(v);
        }
        if (prefix == "f")
        {
            std::string indices;

            for (int i = 0; i < 3; ++i)
            {
                iss >> indices;
                size_t pos = indices.find("/");
                uint32_t index = std::stoi(indices.substr(0, pos));

                mesh.indices.push_back(index - 1);
            }
        }
    }

    return mesh;
}
