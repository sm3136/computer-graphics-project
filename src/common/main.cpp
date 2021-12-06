#include <iostream>
#include <string>
#include <math.h>

#include <GL/glew.h> // Core OpenGL
#include <GL/glut.h> // Display Window

// * #define configs here! *//
// #include <common/config.hpp>

// Other Imports
#include <classes/Matrix.hpp>
#include <classes/Vector.hpp>

#include <shapes/ShapeGenerator.hpp>
#include <shapes/Shape.hpp>

// * Method Declarations * //
Cube *c1;
Octahedron *o1;
Sphere *s1;
Cylinder *cy1;

/**
 * @brief Converts degrees to radians since math.h apparently
 * does not have that.
 * 
 * @param degrees the number of degrees.
 * @return float the number of degrees but in radians.
 */
float rad(float degrees)
{
    return 2 * 3.1415926 * degrees / 180.0;
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

    WorldLight *worldLight = WorldLight::GetInstance();
    worldLight->setColor(new Vector3(128, 128, 128));
    worldLight->setIntensity(1.1);

    PointLight *p1 = new PointLight();
    p1->setColor(new Vector3(255, 0, 0));
    p1->setPosition(new Vector3(-5, 0, 5));
    p1->setIntensity(5);

    PointLight *p2 = new PointLight();
    p2->setColor(new Vector3(0, 0, 255));
    p2->setPosition(new Vector3(5, 0, 5));
    p2->setIntensity(5);

    SpotLight *sp1 = new SpotLight();
    sp1->setColor(new Vector3(225, 225, 0));
    sp1->setPosition(new Vector3(0, 2, 5));
    sp1->setDirection(new Vector3(0, -1, 0));
    sp1->setIntensity(10);

    // SpotLight *sp2 = new SpotLight();
    // sp2->setColor(new Vector3(255, 0, 0));
    // sp2->setPosition(new Vector3(0, 0, 0));
    // sp2->setDirection(new Vector3(0, 0, 1));
    // sp2->setIntensity(10);

    // When initializing the shape generator it automatically initializes
    // OpenGL
    ShapeGenerator *jenny = ShapeGenerator::GetInstance();

    // Making of a Cube
    c1 = new Cube();
    c1->setScale(new Vector3(1, 1, 1));
    c1->setPosition(new Vector3(-1.5, 3, 5));
    c1->setOrientation(Matrix::rotationXZ(-15));
    c1->setColor(new Vector3(255, 0, 0));

    // Making of another Cube
    Cube *c2 = new Cube();
    c2->setScale(new Vector3(.5, .5, .5));
    c2->setPosition(new Vector3(0, -2, 4));
    c2->setOrientation(Matrix::rotationYZ(75));
    c2->setColor(new Vector3(146, 19, 209));
    // c2->visible = false;

    // Making of a Octahedron
    o1 = new Octahedron();
    o1->setScale(new Vector3(.5,1,.5));
    o1->setPosition(new Vector3(-1.5, -2.5, 5));
    o1->setColor(new Vector3(23, 36, 227));
    o1->setOrientation(Matrix::rotationXZ(15));

    // Making of a Octahedron
    Octahedron *o2 = new Octahedron();
    o2->setScale(new Vector3(.5,1,.5));
    o2->setPosition(new Vector3(3, 0, 5));
    o2->setColor(new Vector3(48, 190, 230));
    o2->setOrientation(Matrix::rotationXZ(15));

    // Making of a Sphere
    s1 = new Sphere();
    s1->setScale(new Vector3(1.5, 2.25, 1.5));
    s1->setPosition(new Vector3(0, 0, 6));
    s1->setColor(new Vector3(180, 180, 225));

    // Making of a Sphere
    Sphere *s2 = new Sphere();
    s2->setScale(new Vector3(1, 1, 1));
    s2->setPosition(new Vector3(1.5, 3, 5));
    s2->setColor(new Vector3(238, 255, 3));

    // Making the Cylinder
    cy1 = new Cylinder();
    cy1->setScale(new Vector3(0.5, 0.5, 0.5));
    cy1->setPosition(new Vector3(1.5, -2.5, 5));
    cy1->setOrientation(Matrix::rotationYZ(-15));
    cy1->setColor(new Vector3(247, 245, 247));

    // Making the Cylinder
    Cylinder *cy2 = new Cylinder();
    cy2->setScale(new Vector3(0.5, 0.5, 0.5));
    cy2->setPosition(new Vector3(0, 2.5, 4.5));
    cy2->setOrientation(Matrix::rotationXY(-15));
    cy2->setColor(new Vector3(255, 162, 3));
}

float tick = 0;

/**
 * Flushes the verticies to the gpu. This allows the gpu to render 
 * out the image that we are passing it.
 */
void display(void)
{
    // Animates the cube in the center
    c1->setOrientation(*(c1->getOrientation()) * *new Matrix(Matrix::rotationXY(0.5)));
    
    // Animates the octahedron
    o1->setOrientation(*(o1->getOrientation()) * *new Matrix(Matrix::rotationXZ(0.5)));

    tick += 0.25;

    // Animates the sphere
    s1->setOrientation(
        *new Matrix(Matrix::rotationXZ(tick)) *
        *new Matrix(Matrix::rotationYZ(tick))
    );

    s1->setPosition(new Vector3(sin(rad(tick)), 0, cos(rad(tick)) + 5));
    
    // Animates the cylinder
    cy1->setOrientation(
        *(cy1->getOrientation()) * 
        *new Matrix(Matrix::rotationXZ(0.5)) * 
        *new Matrix(Matrix::rotationYZ(0.5))
    );

    // Writes out to the display and then posts a redisplay.
    ShapeGenerator::GetInstance()->display();
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