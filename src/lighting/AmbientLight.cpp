#include <lighting/Lighting.hpp>

/**
 * @brief The only instance of the ambient light. There
 * should only be one Ambient light instance therefore it has
 * been made as a singleton.
 * 
 */
AmbientLight *AmbientLight::instance = nullptr;

/**
 * @brief Gets the instance of the ambient light.
 *
 * @return AmbientLight* The ambient light object.
 */
AmbientLight *AmbientLight::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new AmbientLight();
    }

    return instance;
}