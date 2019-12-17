/*
 * CarApplGameC2.h
 *
 *  Created on: 2019��7��11��
 *      Author: xiaow
 */

#ifndef SRC_VEINS_MODULES_EDGECOMPUTING_CarApplGameC2_H_
#define SRC_VEINS_MODULES_EDGECOMPUTING_CarApplGameC2_H_

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/edgecomputing/EdgeMessage/TaskRequest_m.h"
#include "veins/modules/edgecomputing/GameTheory/Player.h"

#include <map>

class CarApplGameC2 : public BaseWaveApplLayer {
    public:
        virtual void initialize(int stage);
//        virtual void initialize();
        ~CarApplGameC2();
        //virtual void finish();
        virtual void finish();


    protected:




        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
        virtual void handlePositionUpdate(cObject* obj);
        virtual void handleMessage(cMessage* msg);
        virtual void offLoad(TaskRequest* tsk);
        virtual void handleTaskAck(cMessage* msg);
        int connectRsuId=-1;


    protected:
        int TaskCount;
        cMessage* startTaskMsg;
        cMessage* stopTaskMsg;
        cMessage* checkCon;
        Player* dss;


        simtime_t lastDroveAt;
        bool sentMessage;
        int currentSubscribedServiceId;
        int taskmanagerin;
        int lastTaskSendId;
        int generateTasksCount{0};
        int receiveTasksCount{0};
        int offLoadTasksCount{0};
        bool issend;
        simtime_t applstart;
        simtime_t applend;
        simtime_t appldelay;
        simtime_t lastCheck;
        simtime_t pingInterval;
        simtime_t taskGeneInterval;


        simsignal_t applDelaysSignal;
        simsignal_t rsuDelaySignal;
        simsignal_t taskCompeleteRate;


        cOutVector delays;
        cOutVector rsuDelays;
        cOutVector utilities;

        cOutVector ByteLengths;
        cOutVector puis;
        cOutVector cc;


        std::map<int,simtime_t> applstarts;

        double rsudelay;
        double alaphaj;
        double betaj;
        double gamaj;
        double handleRate;
        double tem{66166};
        double geneRate;
        double tth;
        double learnningRate;

        int rsuID;


        double RiC=-1;
        double RiE=-1;



};



#endif /* SRC_VEINS_MODULES_EDGECOMPUTING_CarApplGameC2_H_ */
