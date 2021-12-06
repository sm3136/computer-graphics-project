#include <lighting/LightController.hpp>

/**
 * @brief Construct a new Spot Light:: Spot Light object
 * 
 */
SpotLight::SpotLight()
{
    LightController::GetInstance()->addSpotLight(this);
}

/**
 * @brief Destroy the Spot Light:: Spot Light object
 * 
 */
SpotLight::~SpotLight()
{
    LightController::GetInstance()->removeSpotLight(this);
}