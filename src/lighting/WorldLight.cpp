#include <lighting/Lighting.hpp>

/**
 * @brief The instance of the world light. We 
 * can only have one world light so it is set up as
 * a singleton.
 * 
 */
WorldLight *WorldLight::instance = nullptr;

/**
 * @brief Gets the instance of the world light
 *
 * @return WorldLight* The world light instance.
 */
WorldLight *WorldLight::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new WorldLight();
    }

    return instance;
}