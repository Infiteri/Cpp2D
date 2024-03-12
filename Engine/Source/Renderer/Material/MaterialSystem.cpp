#include "MaterialSystem.h"
#include "Resources/Loader/MaterialLoader.h"
#include "Core/Logger.h"
#include <unordered_map>

namespace Core
{
    struct
    {
        MaterialReference defaultMaterial;
        std::unordered_map<std::string, MaterialReference *> references;
    } state;

    void MaterialSystem::Init()
    {
        CE_DEFINE_LOG_CATEGORY("Material System", "CE_MAT_SYS");

        Material::Configuration defaultConfig;
        defaultConfig.Color.Set(255, 255, 255, 255);
        defaultConfig.Name = CE_DEFAULT_MATERIAL_NAME;

        state.defaultMaterial.material = new Material();
        state.defaultMaterial.material->Load(&defaultConfig);
        state.defaultMaterial.material->SetLoadMode(Material::Default);
        state.defaultMaterial.reference = 0;
    }

    void MaterialSystem::Shutdown()
    {
        for (auto it : state.references)
            delete it.second;

        state.references.clear();

        delete state.defaultMaterial.material;
    }

    Material *MaterialSystem::Get(const std::string &name)
    {
        if (!state.references[name])
            Load(name);

        state.references[name]->reference++;
        return state.references[name]->material;
    }

    void MaterialSystem::Load(const std::string &name)
    {
        if (state.references[name])
        {
            return;
        }

        auto cfg = MaterialLoader::GetFromFile(name);
        state.references[name] = new MaterialReference;
        state.references[name]->material = new Material();
        state.references[name]->material->Load(&cfg);
        if (cfg.FileName.empty())
            state.references[name]->material->SetLoadMode(Material::Config);
        else
            state.references[name]->material->SetLoadMode(Material::File);

        state.references[name]->reference++;
    }

    void MaterialSystem::Release(const std::string &name)
    {
        if (name == CE_DEFAULT_MATERIAL_NAME)
        {
            state.defaultMaterial.reference--;
            if (state.defaultMaterial.reference <= 0)
                delete state.defaultMaterial.material;
        }
        else
        {
            auto mat = state.references[name];
            if (!mat)
            {
                CE_LOG("CE_MAT_SYS", Warn, "Material %s non existent.", name.c_str());
                return;
            }

            mat->reference--;
            if (mat->reference <= 0)
            {
                CE_LOG("CE_MAT_SYS", Debug, "Clearing material: %s", name.c_str());
                delete mat->material;
                delete mat;
                state.references.erase(name);
            }
        }
    }

    Material *MaterialSystem::GetDefaultMaterial()
    {
        state.defaultMaterial.reference++;
        return state.defaultMaterial.material;
    }
}