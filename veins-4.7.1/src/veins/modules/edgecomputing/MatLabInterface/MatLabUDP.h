/*
 * MatLabUDP.h
 *
 *  Created on: 2020��4��11��
 *      Author: cojims
 */

#ifndef SRC_VEINS_MODULES_EDGECOMPUTING_MatLabUDP_H_
#define SRC_VEINS_MODULES_EDGECOMPUTING_MatLabUDP_H_

#include <omnetpp.h>
using namespace omnetpp;
#include "veins/modules/messages/WaveShortMessage_m.h"
#include "veins/modules/edgecomputing/MAOCO/WSMwithSignal_m.h"
#include "veins/modules/edgecomputing/MatLabInterface/UDPData_m.h"

class MatLabUDP : public cSimpleModule
{
  private:

    int datain;
    int resultout;
    SOCKET sockclient;
    struct sockaddr_in addr;



  public:


  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish();




};



#endif /* SRC_VEINS_MODULES_EDGECOMPUTING_MatLabUDP_H_ */
