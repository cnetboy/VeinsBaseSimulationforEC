/*
 * CarApplGameC2.cc
 *
 *  Created on: 2019��7��11��
 *      Author: xiaow
 */

#include "veins/modules/edgecomputing/CarApplGameC2.h"
#include "veins/modules/edgecomputing/EdgeMessage/TaskRequest_m.h"
#include <random>

Define_Module(CarApplGameC2);

CarApplGameC2::~CarApplGameC2() {
    cancelAndDelete(startTaskMsg);
    cancelAndDelete(stopTaskMsg);
    cancelAndDelete(checkCon);
    delete dss;

}



void CarApplGameC2::handleSelfMsg(cMessage* msg) {
    if (msg == startTaskMsg) {
       // simtime_t TaskDuration = par("TaskDuration");
        scheduleAt(simTime() +  exponential(taskGeneInterval), stopTaskMsg);

        TaskRequest * tsk = new TaskRequest("taskRequest");
        generateTasksCount++;

        tsk->setTaskownerid(getId());
        tsk->setTasksendid(lastTaskSendId++);
        tsk->setMi(100.0+normal(0.0, 10.0));
        tsk->setStme(1.0+normal(0.0, 1.0));
        tsk->setDyme(1.0+normal(0.0, 1.0));
        tsk->setDeadline(0.1);
        tsk->setGeneRate(10);
        tsk->setTTh(0.1);
        tsk->setAlapha(0.1);
        tsk->setBeta(1);
        tsk->setGama(0.001);


//        dss->setWeight(alaphaj,betaj,gamaj);
//        ����Ԥ��ѡ������ִ�з�ʽ
        if(RiE!=-1){
            tsk->setQjE(dss->iterQ());
            tsk->setRiE(RiE);
        }
        if(RiC!=-1){
            tsk->setQjC(dss->iterQ());
            tsk->setRiC(RiC);
        }
        tsk->setPurchexe(1);
        dss->addPreDecision(tsk->getQjE(),dss->getUtilityPre(tsk->getQjE(),5000/1024.0, 27/8.0,RiE,0.02));

//        double i=dss->getUtility(tsk->getGeneRate(), 1000/tsk->getMi(),RiE,0.002,500,50);
//        double j=dss->getUtility(tsk->getGeneRate(), 1000/tsk->getMi(),RiC,0.1,500,45);
//        double k=dss->getsUtility(tsk->getGeneRate(), 1000/tsk->getMi(),0,0,0,45);

//        if(i>j&&i>k)
//            tsk->setPurchexe(1);
//        else if(j>i&&j>i){
//            tsk->setPurchexe(2);
//        }else{
//            tsk->setPurchexe(0);
//        }
        //tsk->setByteLength(1e2);

        applstart = getSimulation()->getSimTime();
        applstarts.insert(
                std::pair<int, simtime_t>(tsk->getTasksendid(), applstart));

        TaskCount--;
        //issend = true;
        if (rsudelay > 0.5||tsk->getPurchexe()==0) {
            //send(tsk, "taskManager$o");//����������ŵ�����ִ��
            cancelAndDelete(tsk);
        } else {
            offLoad(tsk);
//            send(tsk, "taskManager$o");
        }


    } else if (msg == stopTaskMsg) {
        if (TaskCount > 0) {
            //simtime_t TaskInterval = par("TaskInterval");
            scheduleAt(simTime(), startTaskMsg);
        }
    } else if (msg == checkCon) {
        if (getSimulation()->getSimTime().dbl() - lastCheck.dbl() >= 1) {
            rsudelay = 100;
            connectRsuId = -1;
        }
        scheduleAt(simTime() + pingInterval, checkCon);

    }

}

void CarApplGameC2::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
        TaskCount = par("TaskCount");
        alaphaj=par("alaphaj");
        betaj=par("betaj");
        gamaj=par("gamaj");
        geneRate=par("geneRate");
        taskGeneInterval=par("TaskGeneInterval");
        handleRate=par("handleRate");
        tth=par("tTh");
        learnningRate=par("learnningRate");

        taskmanagerin = findGate("taskManager$i");
        //issend = true;

        if (TaskCount > 0) {
            startTaskMsg = new cMessage("start");
            stopTaskMsg = new cMessage("stop");

            simtime_t TaskStart = par("TaskStart");
            scheduleAt(simTime() + TaskStart, startTaskMsg);
            TaskCount--;
        }


        findHost()->getDisplayString().updateWith("r=0");

        delays.setName("Appl Layer Delays");
        rsuDelays.setName("RSU Delays");
        utilities.setName("Utility Values");
        puis.setName("puis");
        ByteLengths.setName("sent packet sizes");


        cc.setName("test");
        cc.record(14);

        lastTaskSendId = 0;

        applDelaysSignal = registerSignal("applDelays");
        rsuDelaySignal = registerSignal("rsuDelay");
        taskCompeleteRate=registerSignal("applCompeleteRate");

        rsudelay = 100;
        WATCH(rsudelay);
        WATCH(connectRsuId);
        checkCon = new cMessage("check ping");
        pingInterval = par("pingInterval");
        scheduleAt(simTime(), checkCon);
        lastCheck = getSimulation()->getSimTime();

        dss=new Player(alaphaj,betaj,gamaj,geneRate,handleRate,tth,learnningRate);
        WATCH(RiE);
        WATCH(RiC);
        WATCH(tem);

    }

}

void CarApplGameC2::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage()) {
        handleSelfMsg(msg);
    } else if (msg->getArrivalGateId() == upperLayerIn) {
        recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_DATA, msg);
        handleUpperMsg(msg);
    } else if (msg->getArrivalGateId() == upperControlIn) {
        recordPacket(PassedMessage::INCOMING, PassedMessage::UPPER_CONTROL,
                msg);
        handleUpperControl(msg);
    } else if (msg->getArrivalGateId() == lowerControlIn) {
        recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_CONTROL,
                msg);
        handleLowerControl(msg);
    } else if (msg->getArrivalGateId() == lowerLayerIn) {
        recordPacket(PassedMessage::INCOMING, PassedMessage::LOWER_DATA, msg);
        handleLowerMsg(msg);
        //delete msg;
    } else if (msg->getArrivalGateId() == taskmanagerin) {
        handleTaskAck(msg);
    } else if (msg->getArrivalGateId() == -1) {
        throw cRuntimeError(
                "No self message and no gateID?? Check configuration.");
    } else {
        throw cRuntimeError(
                "Unknown gateID?? Check configuration or override handleMessage().");
    }
}

void CarApplGameC2::onWSA(WaveServiceAdvertisment* wsa) {

}

void CarApplGameC2::finish() {


    recordScalar("TaskCompeleteRate", (receiveTasksCount*1.0/generateTasksCount*1.0)*100.0);
    emit(taskCompeleteRate, (receiveTasksCount*1.0/generateTasksCount*1.0)*100.0);

}


void CarApplGameC2::onWSM(WaveShortMessage* wsm) {

    if (wsm->getPsid() == 10) {
        TaskRequest *tsk = dynamic_cast<TaskRequest*>(wsm->getObject(
                "taskRequest"));
        ASSERT(tsk);
        if (tsk->getTaskownerid() == getId()) {
            //issend = true;
            applend = getSimulation()->getSimTime();
            appldelay = applend - applstarts[tsk->getTasksendid()];
            applstarts.erase(tsk->getTasksendid());
            delays.record(appldelay.dbl());
            emit(applDelaysSignal, appldelay.dbl());
            //dss->addPreDecision(tsk->getQjE(),dss->getUtilityPost(tsk->getQjE(),tsk->getRiE(),appldelay.dbl()));
            utilities.record(dss->getUtilityPost(tsk->getQjE(),tsk->getRiE(),appldelay.dbl()));
//            if(tsk->getPurchexe()==1)
//            utilities.record(dss->getPostUtility(10,tsk->getMi()/1000,tsk->getRiE(),appldelay.dbl(),tsk->getQjE()));
//            else
//                utilities.record(dss->getPostUtility(10,tsk->getMi()/1000,tsk->getRiC(),appldelay.dbl(),tsk->getQjC()));




            receiveTasksCount++;
            offLoadTasksCount++;

//            if(tsk->getExe()==1){
//                   RiE=tsk->getRiE();
//               }else if(tsk->getExe()==2){
//                   RiC=tsk->getRiC();
//                   RiE=tsk->getRiE();
//               }
        }

    } else if (wsm->getPsid() == 11) {
        rsudelay = getSimulation()->getSimTime().dbl()
                - wsm->getCreationTime().dbl();
        //bubble("!!!!!!");

        rsuDelays.record(rsudelay);
        connectRsuId = wsm->getSenderAddress();
        emit(rsuDelaySignal, rsudelay);
        rsuID=wsm->getSenderModuleId();
        this->RiC=wsm->getRiC();
        this->RiE=wsm->getRiE();
    }

}

void CarApplGameC2::offLoad(TaskRequest* tsk) {

    WaveShortMessage* wsm = new WaveShortMessage();
    puis.record(tsk->getQjE());
    populateWSM(wsm,-1, 0);
    wsm->setWsmData(mobility->getRoadId().c_str());
    wsm->addObject(tsk);
    wsm->setPsid(10);
    wsm->setBitLength(5000 + normal(0.0, 100.0));
    ByteLengths.record(wsm->getByteLength());
    sendDown(wsm);
}

void CarApplGameC2::handleTaskAck(cMessage* msg) {
    TaskRequest* tsk = dynamic_cast<TaskRequest*>(msg);
//    RiC=tsk->getRiC();
//    RiE=tsk->getRiE();
    applend = getSimulation()->getSimTime();
    appldelay = applend - applstarts[tsk->getTasksendid()];
    applstarts.erase(tsk->getTasksendid());
    delays.record(appldelay.dbl());
    emit(applDelaysSignal, appldelay.dbl());
    receiveTasksCount++;
    delete tsk;
}

void CarApplGameC2::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    lastDroveAt = simTime();

}
