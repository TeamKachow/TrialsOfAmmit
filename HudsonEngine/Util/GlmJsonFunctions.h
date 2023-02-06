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
            j = vector;
        }

        static void from_json(const json& j, glm::vec<L, T>& vector) {
            if (j.is_null())
            {
                vector = glm::vec<L, T>(0);
            }
            else
            {
                vector = j;
            }
        }
    };

    template <glm::length_t C, glm::length_t R, typename T>
    struct adl_serializer<glm::mat<C, R, T>>
    {
        static void to_json(json& j, const glm::mat<C, R, T>& matrix) {
            j = matrix;
        }

        static void from_json(const json& j, glm::mat<C, R, T>& matrix) {
            if (j.is_null())
            {
                matrix = glm::mat<C, R, T>(0);
            }
            else
            {
                matrix = j;
            }
        }
    };
}
