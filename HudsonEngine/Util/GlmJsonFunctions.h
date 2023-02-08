#pragma once
#include <glm/common.hpp>
#include <json.hpp>

// see https://github.com/nlohmann/json#how-do-i-convert-third-party-types
namespace nlohmann
{
    template <glm::length_t L, typename T>
    struct adl_serializer<glm::vec<L, T>>
    {
        static void to_json(json& j, const glm::vec<L, T>& vector) {
            j["size"] = L;
            j["values"] = nlohmann::json::array();
            for (int i = 0; i < L; ++i)
            {
                j["values"].push_back(vector[i]);
            }
        }

        static void from_json(const json& j, glm::vec<L, T>& vector) {
            if (j.is_null())
            {
                vector = glm::vec<L, T>(0);
            }
            else
            {
                for (int i = 0; i < L; ++i)
                {
                    vector[i] = j["values"][i];
                }
            }
        }
    };

    template <glm::length_t C, glm::length_t R, typename T>
    struct adl_serializer<glm::mat<C, R, T>>
    {
        static void to_json(json& j, const glm::mat<C, R, T>& matrix) {
            j["rows"] = R;
            j["cols"] = C;
            j["values"] = nlohmann::json::array();
            for (int c = 0; c < C; ++c)
            {
                for (int r = 0; r < R; ++r)
                {
                    j["values"].push_back(matrix[c][r]);
                }
            }
        }

        static void from_json(const json& j, glm::mat<C, R, T>& matrix) {
            if (j.is_null())
            {
                matrix = glm::mat<C, R, T>(0);
            }
            else
            {
                if (j["rows"] != R || j["cols"] != C)
                {
                    // TODO: log
                }
                for (int c = 0; c < C; ++c)
                {
                    for (int r = 0; r < R; ++r)
                    {
                        matrix[c][r] = j["values"][c][r];                        
                    }
                }
            }
        }
    };
}
