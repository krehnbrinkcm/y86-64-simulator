//TODO add more #includes as you need them
#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Tools.h"
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "F.h"
#include "E.h"
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
bool FetchStage::doClockLow(PipeReg ** pregs) {
   PipeReg * freg = pregs[FREG];  //pointer to object representing F pipeline register
   PipeReg * dreg = pregs[DREG];  //pointer to object representing D pipeline register
   PipeReg * mreg = pregs[MREG];
   PipeReg * wreg = pregs[WREG];
   PipeReg * ereg = pregs[EREG];
   bool mem_error = false;
   uint64_t icode = INOP, ifun = FNONE, rA = RNONE, rB = RNONE;
   uint64_t valC = 0, valP = 0, stat = 0, predPC = 0;
   bool needvalC = false;
   bool needregId = false;
  
   //TODO 
   //select PC value and read byte from memory
   //set icode and ifun using byte read from memory
   uint64_t f_pc = selectPC(freg, mreg, wreg);
   uint64_t byte = mem->getByte(f_pc, mem_error);
   icode = Tools::getBits(byte, 4, 7);
   ifun = Tools::getBits(byte, 0, 3); //getByte	
   //status of this instruction is SAOK (this will change in a later lab)
   stat = SAOK;

   //TODO
   //In order to calculate the address of the next instruction,
   //you'll need to know whether this current instruction has an
   //immediate field and a register byte. (Look at the instruction encodings.)
   needvalC = needValC(icode);
   needregId = needRegIds(icode);
     
   if(needregId) {
	getRegIds(mem->getByte((f_pc+1), mem_error), rA, rB);
   }     
   if(needvalC == true) {
       valC = buildValC(f_pc, icode);
   }
 
   //TODO
   //determine the address of the next sequential function
   valP = PCincrement(f_pc, needregId, needvalC);

   //TODO
   //calculate the predicted PC value
   predPC = predictPC(icode, valC, valP);

   icode = getIcode(icode, mem_error);
   ifun = getIfun(ifun, mem_error);
   stat = getStat(icode, mem_error);

   //set the input for the PREDPC pipe register field in the F register
   freg->set(F_PREDPC, predPC);

   calculateControlSignals(ereg);
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
void FetchStage::doClockHigh(PipeReg ** pregs) {
   PipeReg * freg = pregs[FREG];  //pointer to 
   PipeReg * dreg = pregs[DREG];

   if(F_stall != true) {
	freg->normal();	
   }
   
   if(D_stall != true) {
	dreg->normal();
   }
   if (D_bubble) {
	((D *)dreg)->bubble();
   }
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
                           uint64_t valC, uint64_t valP) {
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
w`ord f_pc = [
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
	if ((mreg->get(M_ICODE) == IJXX) && (!(mreg->get(M_CND)))) {
		return (mreg->get(M_VALA));
	}
	else if (wreg->get(W_ICODE) == IRET) {
		return (wreg->get(W_VALM));
	}
	else {
		return (freg->get(F_PREDPC));
	}
}

bool FetchStage::needRegIds(uint64_t f_icode) {
     if(f_icode == IRRMOVQ || f_icode == IOPQ || f_icode == IPUSHQ || f_icode == IPOPQ || f_icode == IIRMOVQ || f_icode == IRMMOVQ || f_icode == IMRMOVQ) {
	return true;
     }
     return false;
}

void FetchStage::getRegIds(uint64_t byte, uint64_t &rA, uint64_t &rB) {
    rA = Tools::getBits(byte, 4, 7);
    rB = Tools::getBits(byte, 0, 3);			
} 

bool FetchStage::needValC(uint64_t f_icode) {
    if(f_icode == IIRMOVQ || f_icode == IRMMOVQ || f_icode == IMRMOVQ || f_icode == IJXX || f_icode == ICALL) {
	return true;
    }
    return false;
}

uint64_t FetchStage::buildValC(int64_t f_pc, uint64_t icode) {
    uint8_t byte[LONGSIZE];
    bool error;
    f_pc++;
    if (needRegIds(icode)) {
        f_pc++;
    }
    for(int i = 0; i < 8; i++) {
        byte[i] = mem -> getByte(f_pc + i, error);
    }
    return Tools::buildLong(byte);
}

uint64_t FetchStage::predictPC(uint64_t f_icode, uint64_t f_valc, uint64_t f_valp) {
    if (f_icode == IJXX || f_icode == ICALL) {
	return f_valc;
    }
    return f_valp;
}

uint64_t FetchStage::PCincrement(uint64_t f_pc, bool needRegIds, bool needValC) {
    if (needValC) {
	f_pc += 8;
    } if (needRegIds) {
	f_pc += 1;
    } 
    f_pc += 1;
    return f_pc;	
}

bool FetchStage::instr_valid(uint64_t  f_icode) {
    if(f_icode == INOP || f_icode == IHALT || f_icode == IIRMOVQ || f_icode == IRRMOVQ || f_icode == IRMMOVQ
      || f_icode == IMRMOVQ  || f_icode == IOPQ  || f_icode == IJXX  || f_icode == ICALL
      || f_icode == IRET || f_icode == IPUSHQ || f_icode == IPOPQ) {
          return true; 
    }
    return false;
}

uint64_t FetchStage::getStat(uint64_t icode, bool mem_error) {
    if(mem_error) {
        return SADR;
    }
    bool ins = instr_valid(icode);
    if(!(ins)) {
        return SINS;
    }
    if(icode == IHALT) {
        return SHLT;
    }
    return SAOK;
}

uint64_t FetchStage::getIcode(uint64_t icode, bool mem_error) {
    if(mem_error) {
	return INOP;
    }
    return icode;
}

uint64_t FetchStage::getIfun(uint64_t ifun, bool mem_error) {
    if(mem_error) {
        return FNONE;
    }
    return ifun;
}

bool FetchStage::f_stall(PipeReg * ereg) {
    uint64_t e_icode = ereg->get(E_ICODE);
    uint64_t e_dstM = ereg->get(E_DSTM);
    if(e_icode == IMRMOVQ || e_icode == IPOPQ) {
	if(e_dstM == d_srcA || e_dstM == d_srcB) {
		return true;
	}
    }
    return false;
}

bool FetchStage::d_stall(PipeReg * ereg) {
    uint64_t e_icode = ereg->get(E_ICODE);   
    uint64_t e_dstM = ereg->get(E_DSTM);
    if(e_icode == IMRMOVQ || e_icode == IPOPQ) {
	if(e_dstM == d_srcA || e_dstM == d_srcB) {
        	return true;
	}
    }
    return false;
}

bool FetchStage::d_bubble(PipeReg * ereg) {
	uint64_t e_icode = ereg->get(E_ICODE);;
	return (e_icode == IJXX && !(e_Cnd));
}

void FetchStage::calculateControlSignals(PipeReg * ereg) {
	F_stall = f_stall(ereg);
	D_stall = d_stall(ereg);
	D_bubble = d_bubble(ereg);
}

