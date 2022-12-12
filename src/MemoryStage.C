#include <iostream>
#include <cstdint>
#include <stdio.h>
#include "Memory.h"
#include "ConditionCodes.h"
#include "Instructions.h"
#include "RegisterFile.h"
#include "PipeRegField.h"
#include "PipeReg.h"
#include "M.h"
#include "W.h"
#include "Stage.h"
#include "MemoryStage.h"
#include "Status.h"
#include "Debug.h"



bool MemoryStage::doClockLow(PipeReg ** pregs) {
    PipeReg * mreg = pregs[MREG];
    PipeReg * wreg = pregs[WREG];

    bool mem_error = false;

    uint64_t stat = mreg->get(M_STAT);
    uint64_t icode = mreg->get(M_ICODE);
    uint64_t cnd = mreg->get(M_CND);
    uint64_t vale = mreg->get(M_VALE);
    uint64_t vala = mreg->get(M_VALA);
    uint64_t dste = mreg->get(M_DSTE);
    uint64_t dstm = mreg->get(M_DSTM);
	

    uint64_t addr = Addr(icode, vale, vala);
    m_valM = 0;
    if(mem_read(icode)) {
	m_valM = mem->getLong(addr, mem_error);
    }

    if(mem_write(icode)) {
	mem->putLong(vala, addr, mem_error);
    }
 
    stat = getStat(stat, mem_error);	
    if(mem_error == true) {
	m_stat = SADR;
    }
    else {
	m_stat = stat;
    }	
    setWInput(wreg, stat, icode, vale, m_valM, dste, dstm);
    return false;
}

void MemoryStage::doClockHigh(PipeReg ** pregs) {
    PipeReg * wreg = pregs[WREG];
    wreg->normal();
}

uint64_t MemoryStage::Addr(uint64_t M_icode, uint64_t M_valE, uint64_t M_valA) {
    if (M_icode == IRMMOVQ || M_icode == IPUSHQ || M_icode == ICALL || M_icode == IMRMOVQ) {
   	return M_valE;
    }
    else if (M_icode == IPOPQ || M_icode == IRET) {
	return M_valA;
    }
    else {
   	return 0;
    }
}

bool MemoryStage::mem_read(uint64_t M_icode) {
    return (M_icode == IMRMOVQ || M_icode == IPOPQ || M_icode == IRET);
}

bool MemoryStage::mem_write(uint64_t M_icode) {
    return (M_icode == IRMMOVQ || M_icode == IPUSHQ || M_icode == ICALL);
}

uint64_t MemoryStage::getStat(uint64_t stat, bool mem_error) {
    if(mem_error)
    {
	return SADR;
    }
    return stat;
}

void MemoryStage::setWInput(PipeReg * wreg, uint64_t w_stat, uint64_t w_icode, uint64_t w_vale, uint64_t w_valm, uint64_t w_dste, uint64_t w_dstm) {
    wreg->set(W_STAT, w_stat);
    wreg->set(W_ICODE, w_icode);
    wreg->set(W_VALE, w_vale);
    wreg->set(W_VALM, w_valm);
    wreg->set(W_DSTE, w_dste);
    wreg->set(W_DSTM, w_dstm);
}


