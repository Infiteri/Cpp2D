
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

    static void SerializeMaterial(Material *material, YAML::Emitter &out)
    {
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
            CE_SERIALIZE_FIELD("TextureMin", (int)material->GetTexture()->GetConfig()->MinFilter);
            CE_SERIALIZE_FIELD("TextureMax", (int)material->GetTexture()->GetConfig()->MaxFilter);
            break;
        }
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
                auto geometry = mc->mesh->GetGeometry();
                out << YAML::Key << "MeshComponent " + std::to_string(index);
                out << YAML::BeginMap;

                SerializeMaterial(material, out);

                {
                    CE_SERIALIZE_FIELD("GeometryType", (int)geometry->GetType());

                    switch (geometry->GetType())
                    {
                    case Geometry::Square:
                        SquareGeometry *geo = geometry->As<SquareGeometry>();
                        CE_SERIALIZE_FIELD("Width", geo->Width);
                        CE_SERIALIZE_FIELD("Height", geo->Height);
                        break;
                    }
                }

                out << YAML::EndMap;
            }
        }

        {
            auto cameraComponent = a->GetComponents<CameraComponent>();
            CE_SERIALIZE_FIELD("CameraComponentCount", cameraComponent.size());
            int index = -1;
            for (auto cc : cameraComponent)
            {
                auto c = cc->camera;
                index++;
                out << YAML::Key << "CameraComponent " + std::to_string(index);
                out << YAML::BeginMap;
                CE_SERIALIZE_FIELD("Type", (int)c->GetType());
                CE_SERIALIZE_FIELD("OriginPoint", (int)c->GetOriginPoint());
                CE_SERIALIZE_FIELD("Zoom", (int)c->GetZoom());
                CE_SERIALIZE_FIELD("TransformType", (int)c->GetTransformationType());

                if (c->GetTransformationType() == Camera::TransformationType::Transform)
                {
                    CE_SERIALIZE_FIELD("Position", &c->GetTransform()->Position);
                    CE_SERIALIZE_FIELD("Rotation", &c->GetTransform()->Rotation);
                    CE_SERIALIZE_FIELD("Scale", &c->GetTransform()->Scale);
                }

                out << YAML::EndMap;
            }
        }

        {
            auto spriteComponent = a->GetComponents<SpriteComponent>();
            CE_SERIALIZE_FIELD("SpriteComponentCount", spriteComponent.size());
            int index = -1;
            for (auto sprite : spriteComponent)
            {
                index++;
                out << YAML::Key << "SpriteComponent " + std::to_string(index);
                out << YAML::BeginMap;
                SerializeMaterial(sprite->sprite->GetMaterial(), out);
                Vector2 s = sprite->sprite->GetSize();
                Vector2 l = sprite->sprite->GetFrameLayout();
                CE_SERIALIZE_FIELD("Sizes", &s);
                CE_SERIALIZE_FIELD("FrameLayout", &l);
                CE_SERIALIZE_FIELD("CurrentFrame", sprite->sprite->GetCurrentFrame());
                out << YAML::EndMap;
            }
        }

        {
            auto actorScriptComponent = a->GetComponents<ActorScriptComponent>();
            CE_SERIALIZE_FIELD("ActorScriptComponentCount", actorScriptComponent.size());
            int index = -1;
            for (auto sc : actorScriptComponent)
            {
                index++;
                out << YAML::Key << "ActorScriptComponent " + std::to_string(index);
                out << YAML::BeginMap;
                CE_SERIALIZE_FIELD("ClassName", sc->ClassName.c_str());
                out << YAML::EndMap;
            }
        }

        {
            auto physicsBodyComponent = a->GetComponents<PhysicsBodyComponent>();
            CE_SERIALIZE_FIELD("PhysicsBodyComponentCount", physicsBodyComponent.size());
            int index = -1;
            for (auto sc : physicsBodyComponent)
            {
                index++;
                out << YAML::Key << "PhysicsBodyComponent " + std::to_string(index);
                out << YAML::BeginMap;
                CE_SERIALIZE_FIELD("BodyType", (int)sc->BodyType);
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

                if (actor["Name"])
                    a->SetName(actor["Name"].as<std::string>());
                else
                    a->SetName("");

                if (actor["Transform"])
                {
                    YAMLToVector3(actor["Transform"]["Position"], &a->GetTransform()->Position);
                    YAMLToVector3(actor["Transform"]["Rotation"], &a->GetTransform()->Rotation);
                    YAMLToVector3(actor["Transform"]["Scale"], &a->GetTransform()->Scale);
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
                            config.TextureConfiguration.MinFilter = (Texture::TextureFilter)mc["TextureMin"].as<int>();
                            config.TextureConfiguration.MaxFilter = (Texture::TextureFilter)mc["TextureMax"].as<int>();

                            addedMc->mesh->SetMaterial(&config);

                            break;
                        }

                        Geometry::Type gType = (Geometry::Type)mc["GeometryType"].as<int>();
                        switch (gType)
                        {
                        case Geometry::Square:
                            addedMc->mesh->SetGeometry(new SquareGeometry(mc["Width"].as<float>(), mc["Height"].as<float>()));
                            break;

                        default:
                            addedMc->mesh->SetGeometry(new Geometry());
                            break;
                        }
                    }
                }

                for (int i = 0; i < actor["CameraComponentCount"].as<int>(); i++)
                {
                    auto addedMc = a->AddComponent<CameraComponent>();
                    auto mc = actor["CameraComponent " + std::to_string(i)];
                    if (mc)
                    {
                        auto c = addedMc->camera;
                        c->SetType((Camera::Type)mc["Type"].as<int>());
                        c->SetOriginPoint((Camera::OriginPoint)mc["OriginPoint"].as<int>());
                        c->SetZoom(mc["Zoom"].as<float>());
                        c->SetTransformationType((Camera::TransformationType)mc["TransformType"].as<int>());

                        if (c->GetTransformationType() == Camera::TransformationType::Transform)
                        {
                            YAMLToVector3(mc["Transform"]["Position"], &c->GetTransform()->Position);
                            YAMLToVector3(mc["Transform"]["Rotation"], &c->GetTransform()->Rotation);
                            YAMLToVector3(mc["Transform"]["Scale"], &c->GetTransform()->Scale);
                        }
                    }
                }

                for (int i = 0; i < actor["SpriteComponentCount"].as<int>(); i++)
                {
                    auto addedMc = a->AddComponent<SpriteComponent>();
                    auto mc = actor["SpriteComponent " + std::to_string(i)];
                    if (mc)
                    {
                        auto c = addedMc->sprite;
                        Material::LoadMode loadMode = (Material::LoadMode)mc["Load Mode"].as<int>();

                        switch (loadMode)
                        {
                        case Material::File:
                            addedMc->sprite->SetMaterial(mc["FileName"].as<std::string>());
                            break;

                        case Material::Config:
                            Material::Configuration config;
                            config.Name = mc["Name"].as<std::string>();
                            config.Color = {mc["Color"][0].as<float>(), mc["Color"][1].as<float>(), mc["Color"][2].as<float>(), mc["Color"][3].as<float>()};
                            config.TexturePath = mc["TextureName"].as<std::string>();
                            config.TextureConfiguration.MinFilter = (Texture::TextureFilter)mc["TextureMin"].as<int>();
                            config.TextureConfiguration.MaxFilter = (Texture::TextureFilter)mc["TextureMax"].as<int>();

                            addedMc->sprite->SetMaterial(&config);

                            break;
                        }

                        addedMc->sprite->SetSize({mc["Sizes"][0].as<float>(), mc["Sizes"][1].as<float>()});
                        addedMc->sprite->SetFrameLayout({mc["FrameLayout"][0].as<float>(), mc["FrameLayout"][1].as<float>()});
                        addedMc->sprite->SetCurrentFrame(mc["CurrentFrame"].as<float>());
                    }
                }

                for (int i = 0; i < actor["ActorScriptComponentCount"].as<int>(); i++)
                {
                    auto addedMc = a->AddComponent<ActorScriptComponent>();
                    auto mc = actor["ActorScriptComponent " + std::to_string(i)];
                    if (mc)
                    {
                        addedMc->ClassName = mc["ClassName"].as<std::string>();
                    }
                }

                for (int i = 0; i < actor["PhysicsBodyComponentCount"].as<int>(); i++)
                {
                    auto addedMc = a->AddComponent<PhysicsBodyComponent>();
                    auto mc = actor["PhysicsBodyComponent " + std::to_string(i)];
                    if (mc)
                    {
                        addedMc->BodyType = (PhysicsBody::BodyType)mc["BodyType"].as<int>();
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

                if (actor["UUID"])
                    a->SetUUID(actor["UUID"].as<CeU64>());
                else
                    a->SetUUID({});
            }
        }
    }
}