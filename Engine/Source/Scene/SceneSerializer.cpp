
#include "SceneSerializer.h"
#include "Core/Logger.h"
#include "Math/Vectors.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

#define CE_SERIALIZE_FIELD(name, value) out << YAML::Key << name << YAML::Value << value

namespace Core
{
    YAML::Emitter &operator<<(YAML::Emitter &out, Vector2 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Vector3 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << v->z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Vector4 *v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v->x << v->y << v->z << v->w << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, Color *color)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << color->R << color->G << color->B << color->A << YAML::EndSeq;
        return out;
    }

    void YAMLToVector3(YAML::Node node, Vector3 *out)
    {
        if (node)
            out->Set(node[0].as<float>(), node[1].as<float>(), node[2].as<float>());
    }

    SceneSerializer::SceneSerializer(Scene *targetScene)
    {
        scene = targetScene;
    }

    SceneSerializer::~SceneSerializer()
    {
    }

    void SceneSerializer::Serialize(const std::string &filename)
    {
        if (filename.empty() || !scene)
            return;

        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene";
        out << YAML::Value << scene->GetName().c_str();

        out << YAML::Key << "Actors";
        out << YAML::Value << YAML::BeginSeq;

        //
        for (Actor *a : scene->GetActors())
            SerializeActor(a, out);

        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(filename);
        fout << out.c_str();
    }

    void SceneSerializer::SerializeActor(Actor *a, YAML::Emitter &out)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Actor";
        out << YAML::Value << "Filed";

        CE_SERIALIZE_FIELD("UUID", a->GetUUID()->Get());

        out << YAML::Key << "Name";
        out << YAML::Value << a->GetName().c_str();

        out << YAML::Key << "ParentUUID";

        if (a->GetParent() != nullptr)
            out << YAML::Value << a->GetParent()->GetUUID()->Get();
        else
            out << YAML::Value << 0;

        out << YAML::Key << "Transform";
        out << YAML::Value << YAML::BeginMap;
        CE_SERIALIZE_FIELD("Position", &a->GetTransform()->Position);
        CE_SERIALIZE_FIELD("Rotation", &a->GetTransform()->Rotation);
        CE_SERIALIZE_FIELD("Scale", &a->GetTransform()->Scale);
        out << YAML::Value << YAML::EndMap;

        {
            auto meshComponent = a->GetComponents<MeshComponent>();
            CE_SERIALIZE_FIELD("MeshComponentCount", meshComponent.size());
            int index = -1;
            for (auto mc : meshComponent)
            {
                index++;
                auto material = mc->mesh->GetMaterial();
                out << YAML::Key << "MeshComponent " + std::to_string(index);
                out << YAML::BeginMap;

                CE_SERIALIZE_FIELD("Load Mode", material->GetLoadMode());

                switch (material->GetLoadMode())
                {
                case Material::File:
                    CE_SERIALIZE_FIELD("FileName", material->GetFileName().c_str());
                    break;

                case Material::Config:
                    CE_SERIALIZE_FIELD("Name", material->GetName().c_str());
                    CE_SERIALIZE_FIELD("Color", material->GetColor());
                    CE_SERIALIZE_FIELD("TextureName", material->GetTexture()->GetImagePath().c_str());
                    break;
                }

                out << YAML::EndMap;
            }
        }

        out << YAML::EndMap;

        for (auto c : a->GetChildren())
            SerializeActor(c, out);
    }

    void SceneSerializer::Deserialize(const std::string &filename)
    {
        if (filename.empty() || !scene)
            return;

        std::ifstream stream(filename);
        std::stringstream strStream(filename);

        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());

        if (!data["Scene"])
            return;

        std::string sceneName = data["Scene"].as<std::string>();
        scene->SetName(sceneName);

        auto actors = data["Actors"];
        if (actors)
        {
            for (auto actor : actors)
            {
                Actor *a = new Actor();
                if (actor["UUID"])
                    a->SetUUID(actor["UUID"].as<CeU64>());
                else
                    a->SetUUID({});

                if (actor["Name"])
                    a->SetName(actor["Name"].as<std::string>());
                else
                    a->SetName("");

                if (actor["Transform"])
                {
                    YAMLToVector3(actor["Transform"]["Position"], &a->GetTransform()->Position);
                }

                for (int i = 0; i < actor["MeshComponentCount"].as<int>(); i++)
                {
                    auto addedMc = a->AddComponent<MeshComponent>();
                    auto mc = actor["MeshComponent " + std::to_string(i)];
                    if (mc)
                    {
                        Material::LoadMode loadMode = (Material::LoadMode)mc["Load Mode"].as<int>();

                        switch (loadMode)
                        {
                        case Material::File:
                            addedMc->SetMaterial(mc["FileName"].as<std::string>());
                            break;

                        case Material::Config:
                            Material::Configuration config;
                            config.Name = mc["Name"].as<std::string>();
                            config.Color = {mc["Color"][0].as<float>(), mc["Color"][1].as<float>(), mc["Color"][2].as<float>(), mc["Color"][3].as<float>()};
                            config.TexturePath = mc["TextureName"].as<std::string>();

                            addedMc->mesh->SetMaterial(&config);

                            break;
                        }
                    }
                }

                if (actor["ParentUUID"].as<CeU64>() == 0)
                    scene->AddActor(a);
                else
                {
                    auto thing = scene->FindActorByUUIDInHierarchy(
                        actor["ParentUUID"].as<CeU64>());
                    thing->AddChild(a);
                }
            }
        }
    }
}