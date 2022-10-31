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
#include "Stage.h"
#include "DecodeStage.h"
#include "Status.h"
#include "Debug.h"



bool DecodeStage::doClockLow(PipeReg ** pregs) {
	PipeReg * dreg = pregs[DREG];
	PipeReg * ereg = pregs[EREG];

	bool mem_error = false;

	uint64_t stat = dreg->get(D_STAT);
	uint64_t icode = dreg->get(D_ICODE);
	uint64_t ifun = dreg->get(D_IFUN);
	uint64_t ra = dreg->get(D_RA);
	uint64_t rb = dreg->get(D_RB);
	uint64_t valc = dreg->get(D_VALC);
	uint64_t valp = dreg->get(D_VALP);

	uint64_t vala = 0;
	uint64_t valb = 0;
	uint64_t dste = RNONE;
	uint64_t dstm = RNONE;
	uint64_t srca = RNONE;
	uint64_t srcb = RNONE;

	setEInput(ereg, stat, icode, ifun, valc, vala, valb, dste, dstm, srca, srcb);	
	return false;
} 

void DecodeStage::doClockHigh(PipeReg ** pregs) {
	PipeReg * ereg = pregs[EREG];
	ereg->normal();
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

