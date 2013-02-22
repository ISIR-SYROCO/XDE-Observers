#include "xde-observers/XDEKineticEnergyObserver.h"
#include <rtt/FlowStatus.hpp>
#include <rtt/TaskContext.hpp>
#include<orocos/ocl/DeploymentComponent.hpp>


XDEKineticEnergyObserver::XDEKineticEnergyObserver(const std::string& name)
    : TaskContext(name)
    , score(0.0)
    , dynModel(0x0)
    , q_upToDate(false)
    , qdot_upToDate(false)
    , d_upToDate(false)
    , t_upToDate(false)
{
    this->addPort("q", in_q);
    this->addPort("qdot", in_qdot);
    this->addPort("d", in_d);
    this->addPort("t", in_t);
    this->addEventPort(in_q);
    this->addEventPort(in_qdot);
    this->addEventPort(in_d);
    this->addEventPort(in_t);
    this->addPort("tick", out_tick);

	this->addOperation("get_observation", &XDEKineticEnergyObserver::getObservation, this,  RTT::OwnThread);
	this->addOperation("setDynModel", &XDEKineticEnergyObserver::setDynModelPointerStr, this, RTT::OwnThread);
}

XDEKineticEnergyObserver::~XDEKineticEnergyObserver()
{
    //if (dynModel != NULL) delete dynModel;
}

double XDEKineticEnergyObserver::getObservation()
{
	return score;
}


void XDEKineticEnergyObserver::setDynModelPointerStr(const std::string& strPtr)
{
    long long dyn_ptr = atoll(strPtr.c_str());
    dynModel = reinterpret_cast<xde::gvm::extra::DynamicModel*>(dyn_ptr);
}


bool XDEKineticEnergyObserver::startHook(){
	score = 0.0;
    return true;
}

void XDEKineticEnergyObserver::stopHook(){
    
}

bool XDEKineticEnergyObserver::configureHook(){
    return true;
}

void XDEKineticEnergyObserver::updateHook(){
	RTT::FlowStatus flowStatus;

	if (!q_upToDate)
	{
		flowStatus = in_q.read(q);
    	if (flowStatus == RTT::NewData)
    	{
    		q_upToDate = true;
        	dynModel->setJointPositions(q);
    	}
    }
    
    if (!qdot_upToDate)
	{
		flowStatus = in_qdot.read(qdot);
    	if (flowStatus == RTT::NewData)
    	{
    		qdot_upToDate = true;
        	dynModel->setJointVelocities(qdot);
    	}
    }
    
    if (!d_upToDate)
	{
		flowStatus = in_d.read(d);
    	if (flowStatus == RTT::NewData)
    	{
    		d_upToDate = true;
        	dynModel->setFreeFlyerPosition(d);
    	}
    }
    
    if (!t_upToDate)
	{
		flowStatus = in_t.read(t);
    	if (flowStatus == RTT::NewData)
    	{
    		t_upToDate = true;
        	dynModel->setFreeFlyerVelocity(t);
    	}
    }


	if (q_upToDate && qdot_upToDate && d_upToDate && t_upToDate)
	{
		q_upToDate = qdot_upToDate = d_upToDate = t_upToDate = false;
		score -= dynModel->getJointVelocities().transpose() * dynModel->getInertiaMatrix() * dynModel->getJointVelocities();
        out_tick.write(0);
	}
}


