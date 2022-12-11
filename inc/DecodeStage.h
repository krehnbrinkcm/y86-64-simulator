class DecodeStage: public Stage
{

private:
      bool E_bubble;
      bool calculateControlSignals(uint64_t e_icode, uint64_t E_dstM);
      uint64_t getDsrcA(uint64_t d_icode, uint64_t d_rA);
      uint64_t getDsrcB(uint64_t d_icode, uint64_t d_rB);
      uint64_t getDstE(uint64_t d_icode, uint64_t d_rB);
      uint64_t getDstM(uint64_t d_icode, uint64_t d_rA);
      uint64_t getSelFwdA(PipeReg * mreg, PipeReg * wreg, PipeReg * dreg, uint64_t d_srcA, uint64_t d_valP, uint64_t icode);
      uint64_t getFwdB(PipeReg * mreg, PipeReg * wreg, uint64_t d_srcB);
      void setEInput(PipeReg * dreg, uint64_t e_stat, uint64_t e_icode, uint64_t e_ifun, uint64_t e_valc, uint64_t e_vala,
uint64_t e_valb, uint64_t e_dste, uint64_t e_dstm, uint64_t e_srca, uint64_t e_srcb);
public: 
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
}; 
