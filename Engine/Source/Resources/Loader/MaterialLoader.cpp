#include "MaterialLoader.h"
#include "Core/Logger.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Core
{
    static YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->R << color->G << color->B << color->A << YAML::EndSeq;
        return out;
    }

    void MaterialLoader::ExposeToFile(const std::string &name, Material::Configuration *c)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Material";
        out << YAML::Value << name.c_str(); // TODO: Debatable. REVIEW-ME
        out << YAML::Key << "Name" << YAML::Value << c->Name.c_str();
        out << YAML::Key << "Color" << YAML::Value << &c->Color;
        out << YAML::Key << "TexturePath" << YAML::Value << c->TexturePath.c_str();
        out << YAML::Key << "TextureMin" << YAML::Value << (int)c->TextureConfiguration.MinFilter;
        out << YAML::Key << "TextureMax" << YAML::Value << (int)c->TextureConfiguration.MaxFilter;
        out << YAML::EndMap;

        std::ofstream fout(name);
        fout << out.c_str();
    }

    Material::Configuration MaterialLoader::GetFromFile(const std::string &filename)
    {
        Material::Configuration cfg;
        std::ifstream stream(filename);
        if (!stream.good())
        {
            CE_CORE_ERROR("MaterialLoader: Failed to load material file. %s", filename.c_str());
            return cfg;
        }

        std::stringstream strStream(filename);
        strStream << stream.rdbuf();
        YAML::Node node = YAML::Load(strStream.str());
        if (!node)
        {
            CE_CORE_ERROR("MaterialLoader: Unable to load nodes for file (Wrong format) '%s'", filename.c_str());
            return cfg;
        }

        cfg.FileName = filename;
        cfg.Name = node["Name"].as<std::string>();
        cfg.TexturePath = node["TexturePath"].as<std::string>();
        cfg.FileName = filename;

        if (node["TextureMin"])
        {
            cfg.TextureConfiguration.MinFilter = (Texture::TextureFilter)node["TextureMin"].as<int>();
        }

        if (node["TextureMax"])
        {
            cfg.TextureConfiguration.MaxFilter = (Texture::TextureFilter)node["TextureMax"].as<int>();
        }

        cfg.Color = {
            node["Color"][0].as<float>(),
            node["Color"][1].as<float>(),
            node["Color"][2].as<float>(),
            node["Color"][3].as<float>()};
        return cfg;
    }
}