#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include <list>

#include <lighting/Lighting.hpp>

class LightController
{
private:
    // Contains a list of point lights.
    std::list<PointLight *> point_lights;
    std::list<SpotLight *> spot_lights;

protected:
    // Used to enforce singleton pattern.
    static LightController *instance;
    LightController() {};

public:
    // Ensures no copying of object
    LightController(LightController &other) = delete;

    // Removes the ability to assign to this value.
    void operator=(const LightController &) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static LightController *GetInstance();

    void addPointLight(PointLight *point_light);
    void removePointLight(PointLight *point_light);

    void addSpotLight(SpotLight *spot_light);
    void removeSpotLight(SpotLight *spot_light);

    GLfloat *getLightPositions();
    GLfloat *getLightColors();
    GLfloat *getLightDirections();

    int getLightCount();

    int getPointLightCount() { return this->point_lights.size(); }
    int getSpotLightCount() { return this->spot_lights.size(); }
};

#endif