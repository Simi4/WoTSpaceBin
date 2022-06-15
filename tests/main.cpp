#include <filesystem>
#include <iostream>

#include "spacebin.h"

int main()
{
    namespace fs = std::filesystem;

    auto spacebin_path = fs::path("../tests/space.bin");
    if (!fs::exists(spacebin_path))
    {
        std::cerr << spacebin_path << " doesn't exist!" << std::endl;
        return 1;
    }

    auto stream = std::ifstream(spacebin_path, std::ifstream::binary | std::ifstream::in);
    if (!stream)
    {
        std::cerr << spacebin_path << " couldn't open!" << std::endl;
        return 1;
    }

    SpaceBin s(stream);
    auto bwst = s.GetBWST();
    auto bsma = s.GetBSMA();
    auto bsmo = s.GetBSMO();
    auto bsmi = s.GetBSMI();
    auto bwt2 = s.GetBWT2();
    stream.close();

    auto models_loddings = bsmo.GetModelsLoddings();
    auto lod_renders = bsmo.GetLodRenders();
    auto renders = bsmo.GetRenders();

    std::cout << "lod_level : verts_name" << std::endl;
    for (const auto &model_lod : models_loddings)
    {
        auto lod_count = model_lod.lod_end - model_lod.lod_begin + 1;
        for (auto lod_level = 0; lod_level < lod_count; ++lod_level)
        {
            auto lod_render = lod_renders[model_lod.lod_begin + lod_level];
            auto render_set_count = lod_render.render_set_end - lod_render.render_set_begin + 1;
            for (auto i = 0; i < render_set_count; ++i)
            {
                auto render = renders[lod_render.render_set_begin + i];
                auto verts_name = bwst.GetString(render.verts_name);
                auto prims_name = bwst.GetString(render.prims_name);
                std::cout << lod_level << " " << verts_name << std::endl;
            }
        }
    }

    return 0;
}
