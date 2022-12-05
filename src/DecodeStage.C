#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "D.h"
#include "E.h"
#include "M.h"
#include "W.h"
#include "Stage.h"
#include "DecodeStage.h"
#include "Status.h"
#include "Debug.h"



bool DecodeStage::doClockLow(PipeReg ** pregs) {
	PipeReg * dreg = pregs[DREG];
	PipeReg * ereg = pregs[EREG];
	PipeReg * wreg = pregs[WREG];
	PipeReg * mreg = pregs[MREG];


	bool mem_error = false;

	uint64_t stat = dreg->get(D_STAT);
	uint64_t icode = dreg->get(D_ICODE);
	uint64_t ifun = dreg->get(D_IFUN);
	uint64_t ra = dreg->get(D_RA);
	uint64_t rb = dreg->get(D_RB);
	uint64_t valc = dreg->get(D_VALC);
	uint64_t valp = dreg->get(D_VALP);

	uint64_t dste = getDstE(icode, rb);
	uint64_t dstm = getDstM(icode, ra);
	d_srcA = getDsrcA(icode, ra);
	d_srcB = getDsrcB(icode, rb);
	uint64_t vala = getSelFwdA(mreg, wreg, dreg, d_srcA, valp, icode);
    uint64_t valb = getFwdB(mreg, wreg, d_srcB);

        
	setEInput(ereg, stat, icode, ifun, valc, vala, valb, dste, dstm, d_srcA, d_srcB);	
	return false;
} 

void DecodeStage::doClockHigh(PipeReg ** pregs) {
	PipeReg * ereg = pregs[EREG];
	ereg->normal();
}

uint64_t DecodeStage::getDsrcA(uint64_t d_icode, uint64_t d_rA)
{
    if(d_icode == IRRMOVQ || d_icode == IRMMOVQ || d_icode == IOPQ || d_icode == IPUSHQ) {
	return d_rA;
    } else if (d_icode == IPOPQ || d_icode == IRET) {
	return RSP;
    } else {
	return RNONE;
    }
}

uint64_t DecodeStage::getDsrcB(uint64_t d_icode, uint64_t d_rB)
{
    if (d_icode == IOPQ || d_icode == IRMMOVQ || d_icode == IMRMOVQ) {
	return d_rB;
    } else if (d_icode == IPUSHQ || d_icode == IPOPQ || d_icode == ICALL || d_icode == IRET) {
	return RSP;
    } else {
	return RNONE;
    }
}

uint64_t DecodeStage::getDstE(uint64_t d_icode, uint64_t d_rB) 
{
    if (d_icode == IRRMOVQ || d_icode == IIRMOVQ || d_icode == IOPQ) {
	return d_rB;
    } else if (d_icode == IPUSHQ || d_icode == IPOPQ || d_icode == ICALL || d_icode == IRET){
	return RSP;
    } else {
	return RNONE;
    }
}

uint64_t DecodeStage::getDstM(uint64_t d_icode, uint64_t d_rA)
{
    if (d_icode == IMRMOVQ || d_icode == IPOPQ) {
	return d_rA;
    }
    return RNONE;
}


uint64_t DecodeStage::getSelFwdA(PipeReg * mreg, PipeReg * wreg, PipeReg * dreg, uint64_t d_srca, uint64_t d_valP, uint64_t icode)
{
    if((icode == ICALL) || (icode == IJXX)) {
        return d_valP;//dreg -> get(D_VALP);
    }
    if (d_srca == RNONE) return 0;
    bool error;
    uint64_t d_rvalA = 0;    
    if(d_srcA == e_dstE) {
	return e_valE;
    } else if (d_srca == (mreg -> get(M_DSTM))) {
	return m_valM;
    } else if (d_srca == (mreg -> get(M_DSTE))) {
	return mreg -> get(M_VALE);
    } else if (d_srca == (wreg -> get(W_DSTM))) { 
	return wreg -> get(W_VALM);
    } else if (d_srca == (wreg -> get(W_DSTE))) { 
	return wreg -> get(W_VALE);
    } else {
		d_rvalA = rf->readRegister(d_srca, error);
    	return d_rvalA; 
    }
}

uint64_t DecodeStage::getFwdB(PipeReg * mreg, PipeReg * wreg, uint64_t d_srcb)
{
    if (d_srcb == RNONE) return 0;
    bool error;
    uint64_t d_rvalB = 0;
    if(d_srcb == e_dstE) {
        return e_valE;
    } else if (d_srcb == (mreg -> get(M_DSTM))) {
	return m_valM;
    } else if (d_srcb == (mreg -> get(M_DSTE))) {
	return mreg -> get(M_VALE);
    } else if (d_srcb == (wreg -> get(W_DSTM))) { 
	return wreg -> get(W_VALM);
    } else if (d_srcb == (wreg -> get(W_DSTE))) { 
        return wreg -> get(W_VALE);
    } else {
        d_rvalB = rf->readRegister(d_srcb, error);
        return d_rvalB;
    }
}

void DecodeStage::setEInput(PipeReg * ereg, uint64_t e_stat, uint64_t e_icode, uint64_t e_ifun, uint64_t e_valc, uint64_t e_vala, uint64_t e_valb, uint64_t e_dste, uint64_t e_dstm, uint64_t e_srca, uint64_t e_srcb) {
	ereg->set(E_STAT, e_stat);
	ereg->set(E_ICODE, e_icode);
	ereg->set(E_IFUN, e_ifun);
	ereg->set(E_VALC, e_valc);
	ereg->set(E_VALA, e_vala);
	ereg->set(E_VALB, e_valb);
	ereg->set(E_DSTE, e_dste);
	ereg->set(E_DSTM, e_dstm);
	ereg->set(E_SRCA, e_srca);
	ereg->set(E_SRCB, e_srcb);
}

