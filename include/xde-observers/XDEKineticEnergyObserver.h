#ifndef __XDE_KINETICENERGY_OBSERVER__H__
#define __XDE_KINETICENERGY_OBSERVER__H__

#include<Eigen/Core>
#include<Eigen/Lgsm>

#include <rtt/os/main.h>
#include <rtt/Logger.hpp>
#include <rtt/TaskContext.hpp>

#include <rtt/Property.hpp>
#include <rtt/Port.hpp>

#include <xdecore/gvm.h>
#include <xdecore/gvm/DynamicModel.h>


class XDEKineticEnergyObserver: public RTT::TaskContext{

	public:
		XDEKineticEnergyObserver(const std::string& name);
		~XDEKineticEnergyObserver();

		bool startHook();
		void stopHook();
		bool configureHook();
		void updateHook();
		
		void setDynModelPointerStr(const std::string& strPtr);
		
		double getObservation();

	private:
		RTT::InputPort< Eigen::VectorXd > in_q;
		RTT::InputPort< Eigen::VectorXd > in_qdot;
		RTT::InputPort< Eigen::Displacementd > in_d;
		RTT::InputPort< Eigen::Twistd > in_t;
		RTT::OutputPort< int > out_tick;

		Eigen::VectorXd q;
		Eigen::VectorXd qdot;
		Eigen::Displacementd d;
		Eigen::Twistd t;
		
		bool q_upToDate;
		bool qdot_upToDate;
		bool d_upToDate;
		bool t_upToDate;

		xde::gvm::extra::DynamicModel* dynModel;

		double score;
};

#include <rtt/Component.hpp>
ORO_CREATE_COMPONENT( XDEKineticEnergyObserver );

#endif


