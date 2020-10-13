#include <boost/mpi.hpp>
#include "repast_hpc/RepastProcess.h"

#include "Model.h"
#include "Location.h"
#include "Household.h"
#include <iomanip>


int main(int argc, char** argv){


	std::string configFile = argv[1]; // The name of the configuration file
	std::string propsFile  = argv[2]; // The name of the properties file
	boost::mpi::environment env(argc, argv);
	boost::mpi::communicator* world;

	repast::RepastProcess::init(configFile);
	world = new boost::mpi::communicator;
	AnasaziModel* model = new AnasaziModel(propsFile, argc, argv, world);
	repast::ScheduleRunner& runner = repast::RepastProcess::instance()->getScheduleRunner();

	model->initAgents();
	model->initSchedule(runner);

	runner.run();
	delete model;
	repast::RepastProcess::instance()->done();
}
