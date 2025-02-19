#pragma once
#include "nlohmann/json.hpp"

#define TO_JSON(temp, type, ...) \
temp void to_json(nlohmann::json &j, const type &v) __VA_ARGS__ \
temp void to_json(nlohmann::ordered_json &j, const type &v) __VA_ARGS__

#define FROM_JSON(temp, type, ...) \
temp void from_json(const nlohmann::json &j, type &v) __VA_ARGS__ \
temp void from_json(const nlohmann::ordered_json &j, type &v) __VA_ARGS__
