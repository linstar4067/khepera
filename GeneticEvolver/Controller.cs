﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NNModule;

namespace GeneticEvolver
{
    class Controller : IComparable<Controller>
    {
        public static double MAX_ABS_SPEED = 5;

        public double Fitness { get; set; }
        public NeuralNetwork NeuralNetwork { get; set; }

        public Simulation Simulation;

        public Controller(NeuralNetwork network, Simulation simulation = null)
        {
            NeuralNetwork = network;
            if (simulation == null)
                Simulation = Simulation.CloneDefault();
            else
                Simulation = simulation.Clone();
        }

        public bool MoveRobot(/*Simulation Simulation*/)
        {
            NeuralNetwork.InLayer.SetInputs(Simulation.SensorStates);
            NeuralNetwork.Evaluate();
            List<double> motorSpeeds = NeuralNetwork.OutLayer.GetOutputs();
            if (motorSpeeds.Count != 2)
                return false;
            Simulation.SetRobotSpeed((motorSpeeds[0] - 0.5) * 2 * MAX_ABS_SPEED, 
                (motorSpeeds[1] - 0.5) * 2 * MAX_ABS_SPEED);
            return true;
        }

        public int CompareTo(Controller other)
        {
            return Fitness.CompareTo(other.Fitness);
        }

        public override string ToString()
        {
            return NeuralNetwork.ToString();
        }
    }
}
