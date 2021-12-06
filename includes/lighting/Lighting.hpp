#ifndef LIGHTING_H
#define LIGHTING_H

#include <classes/Matrix.hpp>
#include <classes/Vector.hpp>

// * Lighting * //

/**
 * @brief A basic lighting class which is used in definition
 * of all light sources. It helps me keep track of commonalities
 * between different forms of light and modify the basic way that
 * light works in the scene.
 */
class Lighting
{
protected:
    Vector3 *color;
    float intensity = 1;

public:
    Lighting() { this->setColor(new Vector3(0, 0, 0)); }

    GLfloat *getColor();
    Vector3 *getColorVector();

    void setColor(Vector3 *new_color);

    float getIntensity();
    void setIntensity(float intensity);
};

// * Directional Lighting * //

/**
 * @brief Holds data about a directional light
 *
 */
class DirectionalLight
{
protected:
    Vector3 *direction;

public:
    DirectionalLight() { this->setDirection(new Vector3(-1, 1, -1)); };

    GLfloat *getDirection();
    Vector3 *getDirectionVector();

    void setDirection(Vector3 *new_direction);
};

// * Positional Light * //

/**
 * @brief A general class for light that is positional
 * in nature. This allows for easy creation of new positional
 * light sources.
 */
class PositionalLight
{
protected:
    Vector3 *position;

public:
    PositionalLight() { this->position = new Vector3(0, 0, 0); }

    GLfloat *getPosition();
    Vector3 *getPositionVector();

    void setPosition(Vector3 *new_position);
};

// * Ambient Light * //

/**
 * @brief Holds data about the ambient light in the sceen.
 * The important part about this is that it is a singleton.
 * There should only ever be one form of ambient light in the
 * scene. Therefore, altering this will alter that ambient light.
 */
class AmbientLight : public Lighting
{
protected:
    static AmbientLight *instance;
    AmbientLight() {}

public:
    // Ensures no copying of object
    AmbientLight(AmbientLight &other) = delete;
    // Removes assigning to this value.
    void operator=(const AmbientLight &) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static AmbientLight *GetInstance();
};

// * World Light * //

/**
 * @brief Holds data about the ambient light in the sceen.
 * The important part about this is that it is a singleton.
 * There should only ever be one form of ambient light in the
 * scene. Therefore, altering this will alter that ambient light.
 */
class WorldLight : public DirectionalLight, public Lighting
{
protected:
    static WorldLight *instance;
    WorldLight() {}

public:
    // Ensures no copying of object
    WorldLight(WorldLight &other) = delete;
    // Removes assigning to this value.
    void operator=(const WorldLight &) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static WorldLight *GetInstance();
};

// * Point Light * //

/**
 * @brief The point light object, this is used to create a point light in
 * the world.
 * 
 */
class PointLight : public PositionalLight, public Lighting
{
public:
    PointLight();
    ~PointLight();
};

/**
 * @brief The spot light object, this is used to create a spot light in 
 * the world.
 * 
 */
class SpotLight : public PositionalLight, public DirectionalLight, public Lighting
{
public:
    SpotLight();
    ~SpotLight();
};

#endif