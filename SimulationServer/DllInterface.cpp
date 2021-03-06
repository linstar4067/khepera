#include "DllInterface.h"
#include <ctime>

Simulation* createSimulation(char* fileName, bool readBinary)
{
    std::ifstream file(fileName);
    Simulation* simulation = new Simulation(file, readBinary);
    simulation->start();
    return simulation;
}

void removeSimulation(Simulation* simulation)
{
    delete simulation;
}

Simulation* cloneSimulation(Simulation* simulation)
{
    return new Simulation(*simulation);
}

void updateSimulation(Simulation* simulation, int steps)
{
    simulation->update((unsigned int)steps);
}

int getRobotCount(Simulation* simulation)
{
    return simulation->getIdsByShape(SimEnt::KHEPERA_ROBOT).size();
}

bool fillRobotsIdArray(Simulation* simulation, int* idArray, int arrLength)
{
    std::vector<int> robotIds = simulation->getIdsByShape(SimEnt::KHEPERA_ROBOT);
    for (int i = 0; i < arrLength; i++)
        idArray[i] = robotIds[i];
    return robotIds.size() <= (unsigned int)arrLength;
}

KheperaRobot* getRobot(Simulation* simulation, int robotId)
{
    SimEnt* entity = simulation->getEntity(robotId);
    if (entity != NULL && entity->getShapeID() == SimEnt::KHEPERA_ROBOT)
        return dynamic_cast<KheperaRobot*>(entity);
    else
        return NULL;
}

int getSensorCount(KheperaRobot* robot)
{
    return robot->getSensorCount();
}

float getSensorState(KheperaRobot* robot, int sensorNumber)
{
    float sensorState;
    return robot->getSensorState(sensorNumber, sensorState) ? sensorState : -1;
}

void setRobotSpeed(KheperaRobot* robot, double leftMotor, double rightMotor)
{
    robot->setLeftMotorSpeed(leftMotor);
    robot->setRightMotorSpeed(rightMotor);
}

int getXCoord(KheperaRobot* robot)
{
    return robot->getCenter().getX();
}

int getYCoord(KheperaRobot* robot)
{
    return robot->getCenter().getY();
}

void moveRandom(Simulation* simulation, KheperaRobot* robot)
{
    srand(time(NULL));
    int x = rand() % (simulation->getWorldWidth() - 1) + 1;
    int y = rand() % (simulation->getWorldHeight() - 1) + 1;
    robot->getCenter().setCoords(x, y);
    simulation->update();
}