/*
 * CANClass.hpp
 *
 *  Created on: 9. nov. 2020
 *      Author: mohasa18
 */

#ifndef CANCLASS_HPP_
#define CANCLASS_HPP_



#include <iostream>
#include <string>
#include <sstream>
#include <list>

#include "main.h"
using namespace std;

namespace MyCANConstansts{

const double miles_to_km = 1.609344;
const double Volt = 0.01;
const double Amp = 0.05;
}
class CANData{
public:

  uint16_t ID;
  uint8_t msg_length;
  uint8_t msg[8];

  CANData* next;
  CANData* previous;

  uint16_t getID(){
	  return this->ID;
  }

  CANData(uint16_t ID,uint8_t msg_length, uint8_t* msg_data);
  ~CANData(){}

};


/* Linked List: */


class CAN {
public:
	CANData* head;
	CANData* tail;
	std::size_t list_size;

	/* ID 0x102*/
	uint32_t B_Pack_Voltage; // Byte 1&0 : Low byte in byte 0, high byte in byte 1, Unit: 0.01V

	int32_t B_Pack_Current; /*Byte 3&2: Low byte in byte 2, high byte in byte 3
								high bit (bit 7) of byte 3 is unknown
								bit 6 of byte 3 is the sign bit
								Unit: 0.1A */
	uint32_t Neg_Termi_Temp; /*Byte 6 (8­byte frame only)
							Negative terminal temperature degrees C
							temp_C = ((byte6 + (byte7 & 0x07)<<8)) * 0.1
							 */

	/* ID 0x154*/
	uint32_t rear_torque_Measured; // Nm
	uint32_t Pedal_position_A;  //%

	/*ID 0x232*/
	uint32_t BMS_max_discharge;
	uint32_t BMS_max_charge;

	/*ID 0x266*/
	uint32_t Inverter12V;
	uint32_t Dissipation; // kW
	int32_t mechPower; // kW
	uint32_t statorCurrent; // A
	uint32_t regenPowerMax; //KW
	uint32_t drivePowerMax; //KW

	/*ID 0x382 kWh*/
	uint32_t Nominal_full_pack;
	uint32_t nominalEnergyRemaining;
	uint32_t expectedEnergyRemaining ;
	uint32_t idealEnergyRemaining ;
	uint32_t energyToChargeComplete;
	uint32_t energyBuffer;
	uint32_t SOC;
	uint32_t usableFullPack;
	uint32_t usableRemaining;

	/* ID 3D2 */
	uint32_t kwhDischargeTotal;
	uint32_t kwhChargeTotal;

	/*ID 0x562 */
	uint32_t Battery_odometer;

	CAN();
	~CAN();


	std::size_t size();
	void push_back(CANData* new_node);
	void remove(std::size_t position);
	CANData* get(std::size_t index);
	void switch_decode();
	void printList();
	void printOnce(std::size_t posi);
};


#endif /* CANCLASS_HPP_ */
