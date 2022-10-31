//TODO add more #includes as you need them
#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "F.h"
#include "D.h"
#include "M.h"
#include "W.h"
#include "Stage.h"
#include "FetchStage.h"
#include "Status.h"
#include "Debug.h"

/*
 * doClockLow
 *
 * Performs the Fetch stage combinational logic that is performed when
 * the clock edge is low.
 *
 * @param: pregs - array of the pipeline register (F, D, E, M, W instances)
 */
bool FetchStage::doClockLow(PipeReg ** pregs)
{
   PipeReg * freg = pregs[FREG];  //pointer to object representing F pipeline register
   PipeReg * dreg = pregs[DREG];  //pointer to object representing D pipeline register
   bool mem_error = false;
   uint64_t icode = INOP, ifun = FNONE, rA = RNONE, rB = RNONE;
   uint64_t valC = 0, valP = 0, stat = 0, predPC = 0;
   bool needvalC = false;
   bool needregId = false;
  
   //TODO 
   //select PC value and read byte from memory
   //set icode and ifun using byte read from memory
   //uint64_t f_pc =  .... call your select pc function

   //status of this instruction is SAOK (this will change in a later lab)
   stat = SAOK;

   //TODO
   //In order to calculate the address of the next instruction,
   //you'll need to know whether this current instruction has an
   //immediate field and a register byte. (Look at the instruction encodings.)
   //needvalC =  .... call your need valC function
   //needregId = .... call your need regId function

   //TODO
   //determine the address of the next sequential function
   //valP = ..... call your PC increment function 

   //TODO
   //calculate the predicted PC value
   //predPC = .... call your function that predicts the next PC   

   //set the input for the PREDPC pipe register field in the F register
   freg->set(F_PREDPC, predPC);

   //set the inputs for the D register
   setDInput(dreg, stat, icode, ifun, rA, rB, valC, valP);
   return false;
}

/* doClockHigh
 *
 * applies the appropriate control signal to the F
 * and D register intances
 * 
 * @param: pregs - array of the pipeline register (F, D, E, M, W instances)
*/
void FetchStage::doClockHigh(PipeReg ** pregs)
{
   PipeReg * freg = pregs[FREG];  //pointer to 
   PipeReg * dreg = pregs[DREG];
   freg->normal();
   dreg->normal();
}

/* setDInput
 * provides the input to potentially be stored in the D register
 * during doClockHigh
 *
 * @param: dreg - pointer to the D register instance
 * @param: stat - value to be stored in the stat pipeline register within D
 * @param: icode - value to be stored in the icode pipeline register within D
 * @param: ifun - value to be stored in the ifun pipeline register within D
 * @param: rA - value to be stored in the rA pipeline register within D
 * @param: rB - value to be stored in the rB pipeline register within D
 * @param: valC - value to be stored in the valC pipeline register within D
 * @param: valP - value to be stored in the valP pipeline register within D
*/
void FetchStage::setDInput(PipeReg * dreg, uint64_t stat, uint64_t icode, 
                           uint64_t ifun, uint64_t rA, uint64_t rB,
                           uint64_t valC, uint64_t valP)
{
   dreg->set(D_STAT, stat);
   dreg->set(D_ICODE, icode);
   dreg->set(D_IFUN, ifun);
   dreg->set(D_RA, rA);
   dreg->set(D_RB, rB);
   dreg->set(D_VALC, valC);
   dreg->set(D_VALP, valP);
}

//TODO
//Write your selectPC, needRegIds, needValC, PC increment, and predictPC methods
//Remember to add declarations for these to FetchStage.h

// Here is the HCL describing the behavior for some of these methods. 
/*

//selectPC method: input is F, M, and W registers
word f_pc = [
    M_icode == IJXX && !M_Cnd : M_valA;
    W_icode == IRET : W_valM;
    1: F_predPC;
]

//needRegIds  method: input is f_icode
bool need_regids = f_icode in { IRRMOVQ, IOPQ, IPUSHQ, IPOPQ, IIRMOVQ, IRMMOVQ, IMRMOVQ };

//needValC method: input is f_icode
bool need_valC = f_icode in { IIRMOVQ, IRMMOVQ, IMRMOVQ, IJXX, ICALL };

//predictPC method: inputs are f_icode, f_valC, f_valP
word f_predPC = [
    f_icode in { IJXX, ICALL } : f_valC;
    1: f_valP;
];
*/

uint64_t FetchStage::selectPC(PipeReg * freg, PipeReg * mreg, PipeReg * wreg) {
	if (mreg->get(M_ICODE) == (IJXX && !(mreg->get(M_CND)))) {
		return (mreg->get(M_VALA));
	}
	else if (wreg->get(W_ICODE) == IRET) {
		return (wreg->get(W_VALM));
	}
	else {
		return (freg->get(F_PREDPC));
	}
}




     
