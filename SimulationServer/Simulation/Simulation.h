#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include <iostream>

#include "Entities/SimEnt.h"
#include "Sensors/Sensor.h"
#include "Buffer.h"
#include "Constants.h"
#include "Math/MathLib.h"

class Simulation
{
	public:
        Simulation(unsigned int worldWidth, unsigned int worldHeight, bool addBounds,
                double simulationStep = DEFAULT_SIMULATION_STEP, int simulationDelay = DEFAULT_SIMULATION_DELAY);
        Simulation(std::ifstream& file, bool readBinary, double simulationStep = DEFAULT_SIMULATION_STEP,
			int simulationDelay = DEFAULT_SIMULATION_DELAY);
        Simulation(const Simulation& simulation);
        ~Simulation();

		void addEntity(SimEnt* newEntity);
        bool addSensor(Sensor* sensor, uint16_t id);
		void start();
        void update(unsigned int steps = 1);
		SimEnt* getEntity(uint16_t id);
        std::vector<int> getIdsByShape(uint8_t shapeId);
        int getWorldWidth() { return _worldWidth; }
        int getWorldHeight() { return _worldHeight; }

		void serialize(Buffer& buffer) const;
		void serialize(std::ofstream& file) const;

	protected:
        void update(double deltaTime); // deltaTime in [ s ]
        void checkCollisions();
        void removeCollision(SimEnt& fst, SimEnt& snd, double collisionLen, Point& proj);
        void updateSensorsState();

        DistanceMap                   _distances;
		SimEntMap                     _entities;
		uint32_t                      _worldWidth;
		uint32_t                      _worldHeight;
		double                        _time;
		double                        _simulationStep; // in [ s ]
		uint16_t                      _simulationDelay; // in [ ms ]
        bool                          _hasBounds;

		bool                          _isRunning;

    private:
        void addBounds();
        void addEntityInternal(SimEnt* newEntity);
        SimEnt* readEntity(std::ifstream& file, bool readBinary);
        Sensor* readSensor(std::ifstream& file, bool readBinary);
};


#endif
