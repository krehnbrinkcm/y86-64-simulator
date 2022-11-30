#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "E.h"
#include "M.h"
#include "W.h"
#include "Stage.h"
#include "ExecuteStage.h"
#include "Status.h"
#include "Debug.h"
#include "Tools.h"

bool ExecuteStage::doClockLow(PipeReg ** pregs) {
    PipeReg * ereg = pregs[EREG];
    PipeReg * mreg = pregs[MREG];
    bool mem_error = false;
    
    uint64_t stat = ereg->get(E_STAT);
    uint64_t icode = ereg->get(E_ICODE);
    uint64_t ifun = ereg->get(E_IFUN);
    uint64_t valc = ereg->get(E_VALC);
    uint64_t vala = ereg->get(E_VALA);
    uint64_t valb = ereg->get(E_VALB);
    uint64_t dstm = ereg->get(E_DSTM);
    uint64_t srca  = ereg->get(E_SRCA);
    uint64_t srcb = ereg->get(E_SRCB);
    
    e_valE = ALU(icode, ifun, vala, valb, valc);
    uint64_t A = getAluA(icode, vala, valc);
    uint64_t B = getAluB(icode,valb); 
    e_Cnd = cond(icode, ifun);//cc->getConditionCode(ifun, mem_error); 
    e_dstE =  getDstE(icode, e_Cnd, (ereg->get(E_DSTE)));

    setMInput(mreg, stat, icode, e_Cnd, e_valE, vala, e_dstE, dstm); 
    return false;
}

void ExecuteStage::doClockHigh(PipeReg ** pregs) {
    PipeReg * mreg = pregs[MREG];
    mreg->normal();
}

/*
 * do not know how to do this part 
void ExecuteStage::setEvalE(something in here)
*/

void ExecuteStage::setMInput(PipeReg * mreg, uint64_t m_stat, uint64_t m_icode, uint64_t m_cnd, uint64_t m_vale, uint64_t m_vala, uint64_t m_dste, uint64_t m_dstm)
{
    mreg->set(M_STAT, m_stat);
    mreg->set(M_ICODE, m_icode);
    mreg->set(M_CND, m_cnd);
    mreg->set(M_VALE, m_vale);
    mreg->set(M_VALA, m_vala);
    mreg->set(M_DSTE, m_dste);
    mreg->set(M_DSTM, m_dstm); 
}

uint64_t ExecuteStage::getAluA(uint64_t e_icode,uint64_t e_valA,uint64_t e_valC) {
	if (e_icode == IRRMOVQ || e_icode == IOPQ) {
		return e_valA;
	}
	else if (e_icode == IIRMOVQ || e_icode == IRMMOVQ || e_icode == IMRMOVQ) {
		return e_valC;
	}
	else if (e_icode == ICALL || e_icode == IPUSHQ) {
		return -8;
	}
	else if (e_icode == IRET || e_icode == IPOPQ) {
		return 8;
	}
	else
		return 0;	
}

uint64_t ExecuteStage::getAluB(uint64_t e_icode,uint64_t e_valB) {
        if (e_icode == IRMMOVQ || e_icode == IMRMOVQ || e_icode == IOPQ || e_icode == ICALL || e_icode == IPUSHQ || e_icode == IRET || e_icode == IPOPQ) {
                return e_valB;
        }
        else if (e_icode == IRRMOVQ || e_icode == IIRMOVQ) {
                return 0;
        }
        else
                return 0;
}

uint64_t ExecuteStage::getAluFun(uint64_t e_icode, uint64_t e_ifun) {
	if (e_icode == IOPQ) {
		return e_ifun;
	}
	else 
		return ADDQ;
}

bool ExecuteStage::set_cc(uint64_t e_icode) {
	if(e_icode == IOPQ)
	{
	    return true;
	}
	return false;
}

uint64_t ExecuteStage::getDstE(uint64_t e_icode, uint64_t e_cnd, uint64_t e_dste) {
	if (e_icode == IRRMOVQ && !(e_cnd)) {
		return RNONE;
	}
	else 
		return e_dste;
}

void ExecuteStage::CC(uint64_t e_icode, uint64_t num, uint64_t A, uint64_t B, uint64_t fun) {
	bool error = false;
	if (set_cc(e_icode)) {
	if (num == 0) {
		cc->setConditionCode(1,ZF,error);
	}
	else {
		 cc->setConditionCode(0,ZF,error);
	}
	if (Tools::sign(num) == 1) {
		 cc->setConditionCode(1,SF,error);
	}
	else {
		cc->setConditionCode(0,SF,error);
	}

	//implement overflow, implementation differs based on function, use tools class, no overflow for and/xor
	//
	
	if(fun == ADDQ) {
		if(Tools::addOverflow(A,B)) {
			cc->setConditionCode(1,OF,error);
		}
		else {
			cc->setConditionCode(0,OF,error);
		}
	}
	else if(fun == SUBQ) {
                if(Tools::subOverflow(A,B)) {
                        cc->setConditionCode(1,OF,error);
		}
                else {
                        cc->setConditionCode(0,OF,error);
		}
        }
	else {
		cc->setConditionCode(0,OF,error);
	}
	}
}

uint64_t ExecuteStage::cond(uint64_t e_icode, uint64_t e_ifun)
{
	bool error = false;
	cc->getInstance();
	bool zF = cc->getConditionCode(ZF, error);
	bool sF = cc->getConditionCode(SF,error);
	bool oF = cc->getConditionCode(OF, error);
	if(e_icode != IJXX && e_icode != ICMOVXX) {
		return 0;
	}
	else {
		if(e_ifun == UNCOND) {
			return 1;
		}
		else if(e_ifun == LESSEQ) {
			return ((sF ^ oF) | zF);
		} else if(e_ifun == LESS) {
			return (sF ^ oF);
		} else if(e_ifun == EQUAL) {
			return zF;
		} else if(e_ifun == NOTEQUAL) {
			return (!zF);
		} else if(e_ifun == GREATER) { 
			return (!(sF ^ oF) & !zF);
		} else if(e_ifun == GREATEREQ) {
			return (!(sF ^ oF));
		} else {
			return 0;
		}
	}
}

uint64_t ExecuteStage::ALU(uint64_t e_icode, uint64_t e_ifun, uint64_t e_valA, uint64_t e_valB, uint64_t e_valC) {
	uint64_t fun = getAluFun(e_icode, e_ifun);
	uint64_t A = getAluA(e_icode, e_valA, e_valC);
	uint64_t B = getAluB(e_icode,e_valB);
	if (fun == ADDQ) {
		uint64_t rtn = A + B;
		CC(e_icode, rtn, A, B, fun);
		return rtn;		
	}
	else if (fun == SUBQ) {
		uint64_t rtn = B - A;
		CC(e_icode, rtn, A, B, fun);
                return rtn;
	}
	else if (fun == XORQ) {
		uint64_t rtn = A ^ B;
		CC(e_icode, rtn, A, B, fun);
                return rtn;
	}
	else if (fun == ANDQ) {
		uint64_t rtn = A & B; 
		CC(e_icode, rtn, A, B, fun);
                return rtn;	
	}
	else 
		return 0;
}




