/*
 * CANClass.cpp
 *
 *  Created on: 2. nov. 2020
 *      Author: mohasa18
 */

#include <CANClass.hpp>
#include <iostream>
#include <string>
#include <sstream>


#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"
#include "stm32h7b3xxq.h"

#include "timer.hpp"

extern void Printf(const char *fmt, ...);


CANData::CANData(uint16_t ID,uint8_t msg_length, uint8_t* msg_data) {
  	this->ID = ID;
  	this->msg_length = msg_length;
  	this->next = NULL;
  	this->previous= NULL;
	for(int i = 0; i < msg_length; i++){
			msg[i] = msg_data[i];
	     }
}

void CAN::switch_decode(){

	CANData* temp = this->head;
	std::size_t i = 0;
	int j1 = 0;
	int j2 = 0;
	int j3 = 0;
	int j4 = 0;
	int j5 = 0;
	int j6 = 0;
	int j7 = 0;


	/* ID 0x102*/
	this->B_Pack_Voltage = 0;
	this->B_Pack_Current = 0;
	this->Neg_Termi_Temp = 0;
	/* ID 0x154*/
	this->rear_torque_Measured = 0;
	this->Pedal_position_A = 0;

	/*ID 0x232*/
	this->BMS_max_discharge = 0;
	this->BMS_max_charge = 0;

	/*ID 0x266*/
	this->Inverter12V = 0;
	this->Dissipation = 0; // kW
	this->mechPower = 0; // kW
	this->statorCurrent = 0; // A
	this->regenPowerMax = 0; //KW
	this->drivePowerMax = 0; //KW

	/*ID 0x382 kWh*/
	this->Nominal_full_pack = 0;
	this->nominalEnergyRemaining = 0;
	this->expectedEnergyRemaining = 0 ;
	this->idealEnergyRemaining = 0;
	this->energyToChargeComplete = 0;
	this->energyBuffer = 0;
	this->SOC = 0;
	this->usableFullPack = 0;
	this->usableRemaining = 0;

	/* ID 3D2 */
	this->kwhDischargeTotal = 0;
	this->kwhChargeTotal = 0;

	/*ID 0x562 */
	this->Battery_odometer = 0;

	   while(temp){

			switch(temp->ID){

				case CAN_ID_102:
				{


					this->B_Pack_Voltage += ((temp->msg[1] << 8) | temp->msg[0] ) * MyCANConstansts::Volt ;
					this->B_Pack_Current += ((((((temp->msg[3] & 0x7F) << 8) | (temp->msg[2] << 1) ))) ) * MyCANConstansts::Amp;
					this->Neg_Termi_Temp += ((( temp->msg[6] | ((temp->msg[7] & 0x07 ) << 8))) * 0.1); // - 10; ?
					this->remove(i);
					j1++;


					break;
				}
				case CAN_ID_154:
				{

				this->rear_torque_Measured += (((temp->msg[5]) | (((temp->msg[6] & 0x1F)<<8))) - (512 * (temp->msg[6] & 0x10))) * 0.25; // Convert from Nm to ftlb with see topp
				this->Pedal_position_A     += temp->msg[3] * 0.4;
				this->remove(i);
				j2++;


					break;
				}
				case CAN_ID_232:
				{


				this->BMS_max_discharge += (temp->msg[2] | (temp->msg[3] << 8)) / 100.0; // Kw
				this->BMS_max_charge    += (temp->msg[0] | (temp->msg[1] << 8)) / 100.0;
				this->remove(i);
				j3++;

					break;
				}
				case CAN_ID_266:
				{



				this->Inverter12V   += temp->msg[0]/10;
				this->Dissipation   += temp->msg[1] * 125 / 1000 - 0.5;
				this->mechPower     += ((temp->msg[2] | ((temp->msg[3] & 0x7)<<8)) - (512 * (temp->msg[3] & 0x4))) / 2;
				this->statorCurrent += temp->msg[4] | ((temp->msg[5] & 0x7)<<8);
				this->regenPowerMax += (temp->msg[7] * 4) - 200;
				this->drivePowerMax += (((temp->msg[6] & 0x3F) << 5) | ((temp->msg[5] & 0xF0) >> 3)) + 1;
				this->remove(i);
				j4++;


				break;
			}
			case CAN_ID_382:
			{

				this->Nominal_full_pack       += (temp->msg[0] | ((temp->msg[1] & 0x03) << 8)) * 0.1;
				this->nominalEnergyRemaining  += ((temp->msg[1] >> 2) | ((temp->msg[2] & 0x0F) * 64)) * 0.1;
				this->expectedEnergyRemaining += ((temp->msg[2] >> 4) | ((temp->msg[3] & 0x3F) * 16)) * 0.1;
				this->idealEnergyRemaining    += ((temp->msg[3] >> 6) | ((temp->msg[4] & 0xFF) * 4)) * 0.1;
				this->energyToChargeComplete  += (temp->msg[5] | ((temp->msg[6] & 0x03) << 8)) * 0.1;
				this->energyBuffer            += ((temp->msg[6] >> 2) | ((temp->msg[7] & 0x03) * 64)) * 0.1;
				this->SOC                     += (nominalEnergyRemaining - energyBuffer) / (Nominal_full_pack - energyBuffer) * 100.0;
				this->usableFullPack          += this->Nominal_full_pack - this->energyBuffer;
				this->usableRemaining         += this->nominalEnergyRemaining - this->energyBuffer;
				this->remove(i);
				j5++;


				break;
			}
			case CAN_ID_3D2:
			{

				this->kwhDischargeTotal += (temp->msg[0] | (temp->msg[1]<<8) | (temp->msg[2]<<16) | (temp->msg[3]<<24))/1000;
				this->kwhChargeTotal    += (temp->msg[0] |
						 (temp->msg[1] << 8) |
						 (temp->msg[2] << 16) |
						 (temp->msg[3] << 24)) / 1000.0;
				this->remove(i);
				j6++;



					break;
				}
				case CAN_ID_562:
				{

				this->Battery_odometer += ((temp->msg[0] | (temp->msg[1] << 8) | (temp->msg[2] << 16) | (temp->msg[3] << 24)) / 1000.0 )* MyCANConstansts::miles_to_km;
				this->remove(i);
				j7++;



					break;
				}
				default:
					break;

			}

		temp = temp->next;

	   }// end of while loop

		if(j1 != 0){
			this->B_Pack_Voltage /= j1;
			this->B_Pack_Current /= j1;
			this->Neg_Termi_Temp /= j1;
		}

		if(j2 != 0){
		this->rear_torque_Measured /= j2;
		this->Pedal_position_A     /= j2;
		}
		if(j3 != 0){
		this->BMS_max_discharge /= j3;
		this->BMS_max_charge    /= j3;
		}
		if(j4 != 0){
		this->Inverter12V	 /= j4;
		this->Dissipation 	 /= j4;
		this->mechPower 	 /= j4;
		this->statorCurrent  /= j4;
		this->regenPowerMax  /= j4;
		this->drivePowerMax  /= j4;
		}
		if(j5 != 0){
		this->Nominal_full_pack /= j5;
		this->nominalEnergyRemaining /= j5;
		this->expectedEnergyRemaining /= j5;
		this->idealEnergyRemaining /= j5;
		this->energyToChargeComplete /= j5;
		this->energyBuffer /= j5;
		this->SOC/= j5;
		this->usableFullPack /= j5;
		this->usableRemaining /= j5;
		}

		if(j6 != 0){
		this->kwhDischargeTotal /= j6;
		this->kwhChargeTotal    /= j6;
		}
		if(j7 != 0){
		this->Battery_odometer /= j7;
		}

}


CAN::CAN() {

	this->head = NULL;
	this->tail = NULL;
	this->list_size = 0;

	/* ID 0x102*/
	this->B_Pack_Voltage = 0;
	this->B_Pack_Current = 0;
	this->Neg_Termi_Temp = 0;
	/* ID 0x154*/
	this->rear_torque_Measured = 0;
	this->Pedal_position_A = 0;

	/*ID 0x232*/
	this->BMS_max_discharge = 0;
	this->BMS_max_charge = 0;

	/*ID 0x266*/
	this->Inverter12V = 0;
	this->Dissipation = 0; // kW
	this->mechPower = 0; // kW
	this->statorCurrent = 0; // A
	this->regenPowerMax = 0; //KW
	this->drivePowerMax = 0; //KW

	/*ID 0x382 kWh*/
	this->Nominal_full_pack = 0;
	this->nominalEnergyRemaining = 0;
	this->expectedEnergyRemaining = 0 ;
	this->idealEnergyRemaining = 0;
	this->energyToChargeComplete = 0;
	this->energyBuffer = 0;
	this->SOC = 0;
	this->usableFullPack = 0;
	this->usableRemaining = 0;

	/* ID 3D2 */
	this->kwhDischargeTotal = 0;
	this->kwhChargeTotal = 0;

	/*ID 0x562 */
	this->Battery_odometer = 0;
}


CAN::~CAN() {
  while (this->head) {
	  CANData* next = this->head->next;
	  delete this->head;
	  this->list_size = this->list_size - 1;
	  this->head = next;
  }
}




void CAN::printList() {

  CANData* temp = this->head;
  while(temp) {

	  temp = temp->next;
  }

}


void CAN::printOnce(std::size_t posi) {


}



std::size_t CAN::size() {

  std::size_t size = 0;
  CANData* temp = this->head;
  while (temp) {
	  size++;
	  temp = temp->next;
  }
  this->list_size = size;
  return this->list_size;
}


void CAN::push_back(CANData* new_node) {
  new_node->next = NULL;
  new_node->previous = NULL;

  if (this->head == NULL) {
	  this->head = new_node;
	  this->tail = this->head;
	  this->list_size = this->list_size + 1;
  } else {
	  this->tail->next = new_node;
	  new_node->previous = this->tail;
	  this->tail = new_node;
	  this->list_size = this->list_size + 1;
  }
}



void CAN::remove(std::size_t position) {

  if((position == ((this->list_size)-1)) && (this->tail == this->head) ){
	  CANData* temp = this->tail;

	  this->tail = NULL;
	  this->head = NULL;

	  this->list_size = this->list_size - 1;

	  delete  temp;

  }else if (position == 0){
	  CANData* temp = this->head;
	  head = temp->next;
	  this->list_size = this->list_size - 1;
	  delete  temp;
  }

}


CANData* CAN::get(std::size_t index) {
  if (index == 0) {
	  return this->head;
  } else if (index == this->list_size - 1) {
	  return this->tail;
  } else if (index < 0 || index >= this->list_size) {
	  return NULL;
  }
  if (index < this->list_size / 2) {
	  CANData* temp = this->head;
	  std::size_t i = 0;
	  while (temp) {
		  if (i == index) { return temp; }
		  i++;
		  temp = temp->next;
	  }
  } else {
	  CANData* temp = this->tail;
	  std::size_t i = this->list_size - 1;
	  while (temp) {
		  if (i == index) { return temp; }
		  i--;
		  temp = temp->previous;
	  }
  }
  return NULL;
}

