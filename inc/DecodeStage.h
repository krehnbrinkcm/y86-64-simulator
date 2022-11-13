class DecodeStage: public Stage
{

private: 
      uint64_t getDsrcA(uint64_t d_icode, uint64_t d_rA);
      uint64_t getDsrcB(uint64_t d_icode, uint64_t d_rB);
      uint64_t getDstE(uint64_t d_icode, uint64_t d_rB);
      uint64_t getDstM(uint64_t d_icode, uint64_t d_rA);
      uint64_t getSelFwdA(uint64_t d_rvalA, uint64_t d_srcA);
      uint64_t getFwdB(uint64_t d_rvalB, uint64_t d_srcB);
      void setEInput(PipeReg * dreg, uint64_t e_stat, uint64_t e_icode, uint64_t e_ifun, uint64_t e_valc, uint64_t e_vala,
uint64_t e_valb, uint64_t e_dste, uint64_t e_dstm, uint64_t e_srca, uint64_t e_srcb);
public: 
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
}; 
