#include <lighting/LightController.hpp>

/**
 * @brief Construct a new Point Light:: Point Light object
 * 
 */
PointLight::PointLight()
{
    LightController::GetInstance()->addPointLight(this);
}

/**
 * @brief Destroy the Point Light:: Point Light object
 * 
 */
PointLight::~PointLight()
{
    LightController::GetInstance()->removePointLight(this);
}