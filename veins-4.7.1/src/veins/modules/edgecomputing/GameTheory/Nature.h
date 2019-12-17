/*
 * Nature.h
 *
 *  Created on: 2019��11��26��
 *      Author: cojims
 */

#ifndef SRC_VEINS_MODULES_EDGECOMPUTING_GAMETHEORY_NATURE_H_
#define SRC_VEINS_MODULES_EDGECOMPUTING_GAMETHEORY_NATURE_H_

class Nature{
private:
    double x,y,tau;

public:
    Nature(double x,double y,double tau);
    double getPrice(double Q);

};




#endif /* SRC_VEINS_MODULES_EDGECOMPUTING_GAMETHEORY_NATURE_H_ */
