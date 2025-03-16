#pragma once

#include <optional>
#include <iostream>
#include <type_traits>

#include <nlohmann/json.hpp>

// functions are defined here due to "inclusion compilation model" (recommended in the lectures)

/**
 * @brief Automize reading from json using nholman/json
*/
template <typename T, typename = void>
struct has_from_json : std::false_type
{};

template <typename T>
struct has_from_json<T, std::void_t<decltype(from_json(std::declval<const nlohmann::json&>(), std::declval<T&>()))>> : std::true_type
{};

template <typename T>
concept JsonDeserializable = has_from_json<T>::value;

template <typename T, typename = void>
struct has_to_json : std::false_type
{};

template <typename T>
struct has_to_json<T, std::void_t<decltype(to_json(std::declval<nlohmann::json&>(), std::declval<const T&>()))>> : std::true_type
{};

template <typename T>
concept JsonSerializable = has_to_json<T>::value;

template <typename T>
concept JsonConvertibleType = JsonSerializable<T> && JsonDeserializable<T>;

static constexpr int JSON_INDENT = 4;

template <JsonDeserializable T>
std::optional<T> jsonToObject(const nlohmann::json& j) 
{
    try 
    {
        return j.get<T>();
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "JSON conversion error: " << e.what() << std::endl;

        return std::nullopt;
    }
}

template <JsonDeserializable T>
std::optional<T> jsonToObject(const std::string& filepath)
{
    std::ifstream inputFile(filepath);

    if (!inputFile)
    {
        inputFile.close();

        std::cerr << "JSON problem file cannot be opened" << std::endl;

        return std::nullopt;
    }

    nlohmann::json jsonData;

    inputFile >> jsonData;

    return jsonToObject<T>(jsonData);
}

template <JsonSerializable T>
std::optional<std::string> objectToJson(const T& obj)
{
    try 
    {
        auto jsonObject{ nlohmann::json(obj) };

        return jsonObject.dump(JSON_INDENT);
    }
    catch (const nlohmann::json::exception& e)
    {
        std::cerr << "JSON serialization error: " << e.what() << std::endl;

        return std::nullopt;
    }
}