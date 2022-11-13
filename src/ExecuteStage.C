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
#include "Stage.h"
#include "ExecuteStage.h"
#include "Status.h"
#include "Debug.h"

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
    uint64_t dste = ereg->get(E_DSTE);
    uint64_t dstm = ereg->get(E_DSTM);
    uint64_t srca  = ereg->get(E_SRCA);
    uint64_t srcb = ereg->get(E_SRCB);
    
    uint64_t cnd = 0;
    uint64_t vale = ereg->get(E_VALC);


    setMInput(mreg, stat, icode, cnd, vale, vala, dste, dstm); 
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

