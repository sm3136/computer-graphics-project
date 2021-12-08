#include <iostream>
#include <string>
#include <math.h>
#include <random>

#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window

// * #define configs here! *//
// #include <common/config.hpp>

// Other Imports
#include <classes/Matrix.hpp>
#include <classes/Vector.hpp>

#include <shapes/ShapeGenerator.hpp>
#include <shapes/BasePart.hpp>

const float PI = 3.1415926;

// * Local veriables * //
int old_time = 0;

Cylinder *center_pole;
std::list<Sphere *> horses;
std::list<PointLight *>lights;


// * Method Declarations * //
/**
 * @brief Converts degrees to radians since math.h apparently
 * does not have that.
 * 
 * @param degrees the number of degrees.
 * @return float the number of degrees but in radians.
 */
float rad(float degrees)
{
    return 2 * PI * degrees / 180.0;
}

float randomColor()
{
    return (rand() / (float) RAND_MAX) * 255.0;
}

void addHorse(Cylinder *parent, double angle)
{
    Cylinder *pole = new Cylinder();
    pole->setPosition(new Vector3(cos(angle * 2 * PI) * 2, 0, sin(angle * 2 * PI) * 2));
    pole->setScale(new Vector3(0.1, 1, 0.1));
    pole->setOrientation(*new Matrix(Matrix::rotationXZ(angle * 360.0)));
    pole->setColor(new Vector3(148, 148, 148));
    pole->parent = parent;

    Sphere *horse = new Sphere();
    horse->parent = pole;
    horse->setScale(new Vector3(0.5, 0.5, 0.5));
    horse->setColor(new Vector3(randomColor(), randomColor(), randomColor()));

    horses.push_back(horse);
}

void addLight(Cylinder *parent, double angle)
{
    PointLight *light = new PointLight();
    light->setPosition(new Vector3(cos(angle * 2 * PI), 0, sin(angle * 2 * PI) + 5 ));
    light->setColor(new Vector3(randomColor(), randomColor(), randomColor()));
    light->setIntensity(0.5);
    lights.push_back(light);
}


/**
 * @brief Creates all of my shapes the first initial time.
 * 
 */
void init(void)
{
    // Initialize lighting
    AmbientLight *ambient = AmbientLight::GetInstance();
    ambient->setColor(new Vector3(15, 15, 15));

    // WorldLight *worldLight = WorldLight::GetInstance();
    // worldLight->setColor(new Vector3(128, 128, 128));
    // worldLight->setIntensity(1.1);

    SpotLight *sp1 = new SpotLight();
    sp1->setColor(new Vector3(255, 0, 0));
    sp1->setPosition(new Vector3(0, 0, 0));
    sp1->setDirection(new Vector3(0, 0, 1));
    sp1->setIntensity(5);

    // When initializing the shape generator it automatically initializes
    // OpenGL
    ShapeGenerator *jenny = ShapeGenerator::GetInstance();

    // * TESTING HIERARCHICAL MODELING * //
    center_pole = new Cylinder();
    center_pole->setPosition(new Vector3(0, 0, 5));
    center_pole->setOrientation(*new Matrix(Matrix::rotationYZ(-2.5)) * *new Matrix(Matrix::rotationXY(-2.5)));
    center_pole->setScale(new Vector3(1,1,1));
    center_pole->visible = false;

    Cylinder *base = new Cylinder();
    base->setPosition(new Vector3(0, -0.5, 0));
    base->setScale(new Vector3(5, 0.1, 5));
    base->setColor(new Vector3(145, 145, 145));
    base->parent = center_pole;

    Cylinder *top = new Cylinder();
    top->setPosition(new Vector3(0, 0.5, 0));
    top->setScale(new Vector3(5, 0.1, 5));
    top->setColor(new Vector3(145, 145, 145));
    top->parent = center_pole;

    float num_horses = 16;
    for (int i = 0; i < num_horses; i++)
    {
        addHorse(center_pole, i / num_horses);
    }

    float num_lights = 4;
    for (int i = 0; i < num_lights; i++)
    {
        addLight(center_pole, i / num_lights);
    }


    // Used in delta time, we need to know the first frame time.
    old_time = glutGet(GLUT_ELAPSED_TIME);
}

/**
 * Flushes the verticies to the gpu. This allows the gpu to render 
 * out the image that we are passing it.
 */
void display(void)
{
    // Handles deltaTime
    int time = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (time - old_time) / 1000.0;

    // Animation
    center_pole->setOrientation(
        *(center_pole->getOrientation()) *
        *new Matrix(Matrix::rotationXZ(deltaTime * 50 * 0.5))
    );

    float i = 0;
    for (Sphere *horse : horses)
    {
        float velocity = glutGet(GLUT_ELAPSED_TIME) / 24.0;
        float phase_angle = i / horses.size() * 360.0;

        if ((int)i % 2 == 0)
        {
            horse->setPosition(new Vector3(0, 0.20 * cos(rad(velocity + phase_angle)) - 0.1, 0));
        } else 
        {
            horse->setPosition(new Vector3(0, 0.20 * sin(rad(velocity + phase_angle)) - 0.1, 0));
        }

        i += 1;
    }

    // Writes out to the display.
    ShapeGenerator::GetInstance()->display();

    // Sets old time and redisplays
    old_time = time;
    glutPostRedisplay();
}

/**
 * The bread and butter of the program. This initializes almost everything
 * inside of the program in order to make everything run smoothly. 
 */
int main(int argc, char **argv)
{
    // Initialize Glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow(argv[0]);

    // Initialize Glew
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    // initializes our stuff
    glEnable(GL_DEPTH_TEST);
    init();

    // Sets the display function
    glutDisplayFunc(display);

    // Starts up the main loop
    glutMainLoop();
}