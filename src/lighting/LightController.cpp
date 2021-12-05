#include <lighting/LightController.hpp>

// * Define as a singleton * //

// Instance of the light controller.
LightController *LightController::instance = nullptr;

/**
 * @brief Gets the instance of the Light Controller
 * 
 * @return LightController* The Light Controller object.
 */
LightController *LightController::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new LightController();
    }
    return instance;
}

// * Define the important sections of the light controller * //

/**
 * @brief Adds the point light to the scene.
 * 
 * @param point_light The point light that has been created.
 */
void LightController::addPointLight(PointLight *point_light)
{
    this->point_lights.push_back(point_light);
}

/**
 * @brief Removes the point light from the scene.
 * 
 * @param point_light The point light that is getting removed.
 */
void LightController::removePointLight(PointLight *point_light)
{
    this->point_lights.remove(point_light);
}

/**
 * @brief Get the light positions for all of the lights being used.
 * 
 * @return GLfloat* A pointer to the position in memory storing the lighting
 * positions.
 */
GLfloat *LightController::getLightPositions()
{
    GLfloat *light_positions = (GLfloat *)calloc(3 * this->point_lights.size(), sizeof(GLfloat));
    int last_index = 0;

    // Adds every point light to the light positions array.
    for (PointLight *light : this->point_lights)
    {
        GLfloat *light_position = light->getPosition();
        for (int i = 0; i < 3; i++)
        {
            light_positions[last_index] = light_position[i];
            last_index++;
        }
        free(light_position);
    }

    return light_positions;
}

/**
 * @brief Gets a light color for all of the lights being used.
 * 
 * @return GLfloat* A pointer to the colors in memory storing the light
 */
GLfloat *LightController::getLightColors()
{
    GLfloat *light_colors = (GLfloat *)calloc(3 * this->point_lights.size(), sizeof(GLfloat));
    int last_index = 0;

    // Adds every point light to the light colors array.
    for (PointLight *light : this->point_lights)
    {
        GLfloat *light_color = light->getColor();
        for (int i = 0; i < 3; i++)
        {
            light_colors[last_index] = light_color[i];
            last_index++;
        }
        free(light_color);
    }

    return light_colors;
}

/**
 * @brief Gets the number of lights in the scene.
 * 
 * @return int the number of lights in the scene.
 */
int LightController::getLightCount()
{
    return this->point_lights.size();
}